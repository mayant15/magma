#!/usr/bin/env python3
"""Write PoC inputs for the file-format OpenSSL harnesses into argv[1].

harness_0 (X.509):  ssl003 ssl009 ssl012 ssl013 ssl014 ssl017
harness_1 (crypto): ssl001 ssl006 ssl010 ssl011 ssl015 ssl016 ssl007_reach
harness_2 (server): ssl002 ssl005 ssl018 ssl020
harness_3 (client): ssl008_dhe ssl008_ecdhe

SSL019 needs a completed handshake; its transcript comes from gen_tls.c.
DER is assembled by hand so the script has no dependencies.
"""
import base64
import os
import re
import struct
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
out = sys.argv[1]


def w(name, data):
    with open(os.path.join(out, name), "wb") as f:
        f.write(data)


# ---- DER ---------------------------------------------------------------------

def tlv(tag, body):
    n = len(body)
    if n < 0x80:
        ln = bytes([n])
    else:
        b = n.to_bytes((n.bit_length() + 7) // 8, "big")
        ln = bytes([0x80 | len(b)]) + b
    return bytes([tag]) + ln + body


def seq(*xs): return tlv(0x30, b"".join(xs))
def set_(*xs): return tlv(0x31, b"".join(xs))
def integer(v): return tlv(0x02, v.to_bytes(max(1, (v.bit_length() + 8) // 8), "big"))
def octets(b): return tlv(0x04, b)
def bits(b): return tlv(0x03, b"\0" + b)
def null(): return b"\x05\x00"
def boolean(v): return tlv(0x01, b"\xff" if v else b"\0")
def utc(s): return tlv(0x17, s.encode())
def explicit(n, x): return tlv(0xa0 | n, x)


def oid(dotted):
    p = [int(x) for x in dotted.split(".")]
    body = bytes([40 * p[0] + p[1]])
    for v in p[2:]:
        enc = [v & 0x7f]
        v >>= 7
        while v:
            enc.append(0x80 | (v & 0x7f))
            v >>= 7
        body += bytes(reversed(enc))
    return tlv(0x06, body)


def der_children(b):
    """Split the contents of a constructed DER value into child TLVs."""
    tag, i = b[0], 1
    n = b[i]; i += 1
    if n & 0x80:
        k = n & 0x7f
        n = int.from_bytes(b[i:i + k], "big"); i += k
    body, kids, j = b[i:i + n], [], 0
    while j < len(body):
        m = body[j + 1]; h = 2
        if m & 0x80:
            k = m & 0x7f
            m = int.from_bytes(body[j + 2:j + 2 + k], "big"); h += k
        kids.append(body[j:j + h + m]); j += h + m
    return kids


def name(cn): return seq(set_(seq(oid("2.5.4.3"), tlv(0x0c, cn.encode()))))


RSA_ENC = "1.2.840.113549.1.1.1"
SHA256_RSA = "1.2.840.113549.1.1.11"
RSA_PSS = "1.2.840.113549.1.1.10"

# The harness' RSA public key (SubjectPublicKeyInfo) from support/keys.h.
keys_h = open(os.path.join(HERE, "..", "support", "keys.h")).read()
cert_b64 = re.search(r"BEGIN CERTIFICATE-----\\n\"\n(.*?)\s*\"-----END",
                     keys_h, re.S).group(1)
cert_der = base64.b64decode("".join(re.findall(r'"([A-Za-z0-9+/=]+)\\n"', cert_b64)))
RSA_SPKI = der_children(der_children(cert_der)[0])[6]
KEY_SERIAL = 1
KEY_NAME = der_children(der_children(cert_der)[0])[3]


def cert(sigalg, spki=RSA_SPKI, exts=(), subject="poc", issuer="poc", serial=2):
    tbs = [explicit(0, integer(2)), integer(serial), sigalg, name(issuer),
           seq(utc("200101000000Z"), utc("491231235959Z")), name(subject), spki]
    if exts:
        tbs.append(explicit(3, seq(*exts)))
    return seq(seq(*tbs), sigalg, bits(b"\x00" * 256))


def ext(o, value, critical=False):
    return seq(oid(o), *( [boolean(True)] if critical else [] ), octets(value))


SHA256_ALG = seq(oid(SHA256_RSA), null())

# ---- harness_0: X.509 --------------------------------------------------------

# SSL003: header promises 64 KiB, stream ends after a few bytes.
w("ssl003.der", b"\x30\x83\x01\x00\x00" + b"\x30\x00" * 4)

# SSL009: sbgp-ipAddrBlock with a 1-byte addressFamily, choice "inherit".
w("ssl009.der", cert(SHA256_ALG, exts=[
    ext("1.3.6.1.5.5.7.1.7", seq(seq(octets(b"\x01"), null())), critical=True)]))

# SSL012: public key algorithm nobody implements.
w("ssl012.der", cert(SHA256_ALG, spki=seq(seq(oid("1.2.3.4.5")), bits(b"\x01\x02"))))

# SSL013: RSASSA-PSS with a hash algorithm OpenSSL does not know.
pss_bad = seq(oid(RSA_PSS), seq(explicit(0, seq(oid("1.2.3.4.5.6")))))
w("ssl013.der", cert(pss_bad))

# SSL014: AlgorithmIdentifier parameters are a BOOLEAN (inner == outer).
w("ssl014.der", cert(seq(oid(SHA256_RSA), boolean(True))))

# SSL017: certificate followed by a CRL from an unrelated issuer (score 0).
crl = seq(seq(integer(1), SHA256_ALG, name("someone-else"), utc("200101000000Z"),
              utc("491231235959Z")), SHA256_ALG, bits(b"\x00" * 256))
w("ssl017.der", cert(SHA256_ALG) + crl)

# ---- harness_1: crypto -------------------------------------------------------
# First byte selects the mode (see harness_1.c).

# SSL001: ANY with universal tag 258 (V_ASN1_NEG_INTEGER), content 0x00 ->
# decoded as a "negative" zero and crashes on re-encoding.
w("ssl001.bin", b"\x00" + seq(b"\x1f\x82\x02\x01\x00"))

PKCS7_SIGNED = "1.2.840.113549.1.7.2"
PKCS7_DATA = "1.2.840.113549.1.7.1"
SHA256 = "2.16.840.1.101.3.4.2.1"

# SSL011: signedData with detached content (no eContent).
signed = seq(oid(PKCS7_SIGNED), explicit(0, seq(
    integer(1), set_(seq(oid(SHA256), null())), seq(oid(PKCS7_DATA)), set_())))
w("ssl011.bin", b"\x01" + signed)

# SSL015: ContentInfo with no [0] content at all. (pkcs7-data: an absent
# signedData already crashes inside d2i_PKCS7, which is not a magma bug.)
w("ssl015.bin", b"\x01" + seq(oid(PKCS7_DATA)))

# SSL016: GF(2^m) inverse modulo the reducible x^64 + 1 (low word becomes 0).
def bn(v):
    b = v.to_bytes(max(1, (v.bit_length() + 7) // 8), "big")
    return struct.pack(">H", len(b)) + b
w("ssl016.bin", b"\x02" + bn((1 << 64) + 1) + bn(0x3))

# SSL010: BN_hex2bn on INT_MAX/4 digits; mode 3 expands a repeat count.
w("ssl010.bin", b"\x03" + b"\x00" + struct.pack(">I", 0x1fffffff) + b"f")

# SSL006: one EVP_EncodeUpdate of (INT_MAX - 10) bytes after a 20-byte one.
w("ssl006.bin", b"\x04" + b"\x00" + struct.pack(">I", 20) + b"A" * 20 +
  b"\x80" + struct.pack(">I", 0x7ffffff5))

# SSL007 (reach only): MDC2 streaming update after a partial block.
w("ssl007_reach.bin", b"\x04" + b"\x01" + struct.pack(">I", 3) + b"abc" +
  b"\x01" + struct.pack(">I", 20) + b"B" * 20)

# ---- TLS records -------------------------------------------------------------

def u8(v): return struct.pack(">B", v)
def u16(v): return struct.pack(">H", v)
def u24(v): return struct.pack(">I", v)[1:]
def vec8(b): return u8(len(b)) + b
def vec16(b): return u16(len(b)) + b
def tls_ext(t, body): return u16(t) + vec16(body)


def records(ctype, payload, version=0x0301, max_frag=16384):
    outb = b""
    for i in range(0, len(payload), max_frag):
        frag = payload[i:i + max_frag]
        outb += u8(ctype) + u16(version) + vec16(frag)
    return outb


def handshake(htype, body): return u8(htype) + u24(len(body)) + body


def client_hello(suites, exts, version=0x0303, random=b"\x42" * 32, sid=b""):
    body = (u16(version) + random + vec8(sid) +
            vec16(b"".join(u16(c) for c in suites)) + vec8(b"\x00") +
            vec16(b"".join(exts)))
    return handshake(1, body)


SIGALGS = tls_ext(0x000d, vec16(u16(0x0804) + u16(0x0401) + u16(0x0201)))
GROUPS = tls_ext(0x000a, vec16(u16(0x001d) + u16(0x0017)))
POINTS = tls_ext(0x000b, vec8(b"\x00"))
TLS = b"\x00"   # harness_2 byte 0: TLS
DTLS = b"\x01"  # harness_2 byte 0: DTLS

# SSL002: ~40 KiB ClientHello (padding extension) over three records; the
# initial init_buf holds 4/3 * 16 KiB.
ch = client_hello([0x002f, 0xc02f], [SIGALGS, GROUPS, POINTS,
                                     tls_ext(0x0015, b"\x00" * 40000)])
w("ssl002.tls", TLS + records(22, ch))

# SSL005: TLS 1.3 ClientHello without a key share -> HelloRetryRequest ->
# second ClientHello; both carry status_request with one byKey responder id.
respid = b"\xa2\x16\x04\x14" + b"\x11" * 20
status = tls_ext(0x0005, u8(1) + vec16(vec16(respid)) + vec16(b""))
v13 = tls_ext(0x002b, vec8(u16(0x0304)))
g13 = tls_ext(0x000a, vec16(u16(0x001d)))
ch1 = client_hello([0x1301], [v13, g13, SIGALGS, status,
                              tls_ext(0x0033, vec16(b""))], sid=b"\x07" * 32)
ks = tls_ext(0x0033, vec16(u16(0x001d) + vec16(b"\x09" * 32)))
ch2 = client_hello([0x1301], [v13, g13, SIGALGS, status, ks], sid=b"\x07" * 32)
w("ssl005.tls", TLS + records(22, ch1) + records(22, ch2, version=0x0303))

# SSL020: TLS 1.2 SessionTicket, 50 bytes, starting with the server's ticket
# key name (01 02 .. 10 under the harness' deterministic RNG).
ticket = bytes(range(1, 17)) + b"\x00" * 34
ch = client_hello([0x002f, 0xc02f], [SIGALGS, GROUPS, POINTS,
                                     tls_ext(0x0023, ticket)], sid=b"\x05" * 32)
w("ssl020.tls", TLS + records(22, ch))

# SSL018: DTLS ClientHello fragment announcing a 1 MiB message. Zero-length
# fragment: partial ones go to dtls1_reassemble_fragment instead.
hs = u8(1) + u24(0x100000) + u16(0) + u24(0) + u24(0)
w("ssl018.tls", DTLS + u8(22) + u16(0xfeff) + u16(0) + b"\x00" * 6 + vec16(hs))

# ---- harness_3: client -------------------------------------------------------
# SSL008: TLS 1.2 anonymous (EC)DHE server flight; byte 0 = (N << 1) | TLS
# makes the client's N-th RNG request (its ephemeral key generation) fail.

def server_hello(suite, version=0x0303):
    reneg = tls_ext(0xff01, vec8(b""))  # secure renegotiation, initial
    body = (u16(version) + b"\x24" * 32 + vec8(b"") + u16(suite) + b"\x00" +
            vec16(reneg))
    return handshake(2, body)


def bn16(v): return vec16(v.to_bytes((v.bit_length() + 7) // 8, "big"))


SHD = handshake(14, b"")
dh_p = (1 << 1024) - 1  # odd, 1024 bits: passes the quick parameter check
ske_dhe = handshake(12, bn16(dh_p) + bn16(2) + bn16(3))
ske_ecdhe = handshake(12, u8(3) + u16(0x001d) + vec8(b"\x09" * 32))
SSL008_RAND_FAIL = 4  # first N that fails the keygen (scan N in 1..8)
w("ssl008_dhe.tls", u8(SSL008_RAND_FAIL << 1) +
  records(22, server_hello(0x0034) + ske_dhe + SHD, version=0x0303))
w("ssl008_ecdhe.tls", u8(SSL008_RAND_FAIL << 1) +
  records(22, server_hello(0xc018) + ske_ecdhe + SHD, version=0x0303))
