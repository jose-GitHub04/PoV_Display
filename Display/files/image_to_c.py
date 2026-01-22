#!/usr/bin/env python3
"""
Convert an image to a C header with RGB data arranged as [cols][rows][3].

Usage:
  python files/image_to_c.py --input files/imagem.png --out include/image_matrix.h --cols 48 --rows 24

Requires: Pillow
  pip install pillow
"""
import sys
from PIL import Image
import argparse

def main():
    p = argparse.ArgumentParser()
    p.add_argument('--input', required=True)
    p.add_argument('--out', required=True)
    p.add_argument('--cols', type=int, required=True)
    p.add_argument('--rows', type=int, required=True)
    args = p.parse_args()

    # Load as RGBA so we can composite transparent pixels over a background
    img = Image.open(args.input).convert('RGBA')
    img = img.resize((args.cols, args.rows), Image.LANCZOS)

    # parse background color
    bg_r, bg_g, bg_b = 0, 0, 0
    if hasattr(args, 'bg') and args.bg:
        parts = args.bg.split(',')
        if len(parts) == 3:
            bg_r, bg_g, bg_b = [int(p) for p in parts]

    # composite alpha onto background and collect RGB tuples
    pixels = []
    for px in list(img.getdata()):
        r, g, b, a = px
        if a == 255:
            pixels.append((r, g, b))
        elif a == 0:
            pixels.append((bg_r, bg_g, bg_b))
        else:
            # alpha composite: out = src*a + bg*(1-a)
            oa = a / 255.0
            nr = int(r * oa + bg_r * (1 - oa))
            ng = int(g * oa + bg_g * (1 - oa))
            nb = int(b * oa + bg_b * (1 - oa))
            pixels.append((nr, ng, nb))

    # column-major layout: [col][row]
    header_lines = []
    header_lines.append('#ifndef IMAGE_MATRIX_H')
    header_lines.append('#define IMAGE_MATRIX_H')
    header_lines.append('#define IMAGE_MATRIX_DEFINED 1')
    header_lines.append(f'static const uint8_t image_data[{args.cols}][{args.rows}][3] = {{')

    for x in range(args.cols):
        header_lines.append('  {')
        for y in range(args.rows):
            r,g,b = pixels[y * args.cols + x]
            header_lines.append(f'    {{{r},{g},{b}}},')
        header_lines.append('  },')
    header_lines.append('};')
    header_lines.append('#endif // IMAGE_MATRIX_H')

    with open(args.out, 'w') as f:
        f.write('\n'.join(header_lines))

    print('Wrote', args.out)

if __name__ == '__main__':
    main()
