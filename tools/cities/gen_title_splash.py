#!/usr/bin/env python3
"""Generate the Cities of Emerald title-splash assets from source.gif.

The splash is a tile-delta video: VRAM holds one fixed 8bpp tile slot per
screen position (30x20 = 600), the tilemap never changes after init, and
each 80ms tick copies the changed positions' new tile pixels from a ROM
atlas into their slots.

Outputs (into graphics/cities_title/):
  palette.bin   u16[32]  BGR555, first N entries used
  frame0map.bin u16[600] atlas tile id per position for the first frame
  atlas.bin     u8[ntiles*64]  8bpp tile pixels (palette indices)
  stream.bin    per tick: u16 count, then count * (u16 pos, u16 tileId);
                tick f encodes the changes from frame (f-1) mod NFRAMES to
                frame f, so tick 0 is the loop's wrap delta.

Run from the repo root:  python3 tools/cities/gen_title_splash.py
"""
import struct
from pathlib import Path

import numpy as np
from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
OUT = ROOT / "graphics" / "cities_title"


def load_frames(path):
    im = Image.open(path)
    frames = []
    i = 0
    while True:
        frames.append(np.array(im.convert("RGB")))
        i += 1
        try:
            im.seek(i)
        except EOFError:
            break
    return np.stack(frames)


def main():
    F = load_frames(OUT / "source.gif")
    nframes, h, w, _ = F.shape
    assert (w, h) == (240, 160), f"expected 240x160, got {w}x{h}"

    enc = (F[..., 0].astype(np.int32) << 16) | (F[..., 1].astype(np.int32) << 8) | F[..., 2].astype(np.int32)
    palette = sorted(np.unique(enc).tolist())
    assert len(palette) <= 32, f"{len(palette)} colors won't fit the reserved palette"
    lut = {c: i for i, c in enumerate(palette)}
    idx = np.vectorize(lut.get)(enc).astype(np.uint8)

    # (frame, ty, tx, py, px)
    tiles = idx.reshape(nframes, 20, 8, 30, 8).transpose(0, 1, 3, 2, 4)

    atlas = {}
    tilemap = np.zeros((nframes, 600), dtype=np.uint16)
    for f in range(nframes):
        flat = tiles[f].reshape(600, 64)
        for pos in range(600):
            key = flat[pos].tobytes()
            if key not in atlas:
                atlas[key] = len(atlas)
            tilemap[f, pos] = atlas[key]

    pal = bytearray()
    for c in palette:
        r, g, b = c >> 16, (c >> 8) & 0xFF, c & 0xFF
        pal += struct.pack("<H", ((b >> 3) << 10) | ((g >> 3) << 5) | (r >> 3))
    pal += b"\x00\x00" * (32 - len(palette))

    stream = bytearray()
    for f in range(nframes):
        prev = tilemap[(f - 1) % nframes]
        cur = tilemap[f]
        changed = np.where(prev != cur)[0]
        stream += struct.pack("<H", len(changed))
        for pos in changed:
            stream += struct.pack("<HH", pos, cur[pos])

    (OUT / "palette.bin").write_bytes(bytes(pal))
    (OUT / "frame0map.bin").write_bytes(tilemap[0].tobytes())
    (OUT / "atlas.bin").write_bytes(b"".join(atlas.keys()))
    (OUT / "stream.bin").write_bytes(bytes(stream))
    print(f"frames={nframes} colors={len(palette)} tiles={len(atlas)} "
          f"atlas={len(atlas)*64}B stream={len(stream)}B")


if __name__ == "__main__":
    main()
