/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */

#pragma bank=5
/*

 MAIN_MAP_TILESET.C

 Tile Source File.

 Info:
  Form                 : All tiles as one unit.
  Format               : Gameboy 4 color.
  Compression          : None.
  Counter              : None.
  Tile size            : 8 x 8
  Tiles                : 0 to 26

  Palette colors       : None.
  SGB Palette          : None.
  CGB Palette          : 1 Byte per entry.

  Convert to metatiles : No.

 This file was generated by GBTD v2.2

*/

/* CGBpalette entries. */
const unsigned char mainmaptilesCGB[] =
{
  0x01,0x01,0x01,0x00,0x01,0x00,0x01,0x01,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,
  0x07,0x07,0x00,0x06,0x06,0x06,0x06,0x03,
  0x00,0x05,0x05
};
/* Start of tile array. */
const unsigned char mainmaptiles[] =
{
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,
  0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,
  0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
  0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,
  0xFF,0x00,0xFF,0x00,0xFF,0x00,0xE0,0x00,
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
  0x0D,0x03,0x0D,0x03,0xFD,0x03,0xFD,0x03,
  0x0D,0xF3,0x0D,0xF3,0xFD,0xF3,0xFD,0xF3,
  0xFD,0x03,0xFD,0x03,0xFD,0x03,0xFD,0x03,
  0xFD,0x03,0xFD,0x03,0x01,0xFF,0xFF,0xFF,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,
  0x80,0xFF,0xC0,0xFF,0xE0,0xFF,0xF0,0xFF,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0xFF,0xF8,0xFC,0xF0,0xF8,0xE0,0xF0,0xE0,
  0xE0,0xC0,0xE0,0xC0,0xE0,0xC0,0xFF,0xC0,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0xF1,0xF1,0xE4,0xE0,0xCE,0xC0,0xDE,0xC0,
  0x9A,0x80,0xBB,0x80,0x31,0x00,0x75,0x04,
  0x64,0x04,0x6F,0x0F,0x6F,0x0F,0x00,0x0F,
  0x80,0xFF,0x80,0xFF,0xCF,0xFF,0xCF,0xFF,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0xFF,0x00,0xFF,0x00,0x01,0x00,0x01,0x00,
  0x01,0x00,0x01,0x00,0x01,0x00,0xFF,0x00,
  0xFF,0x00,0x81,0x7C,0x81,0x54,0x81,0x00,
  0x81,0x78,0x81,0x08,0x81,0x78,0x81,0x04,
  0x81,0x7C,0x81,0x04,0x81,0x7C,0x81,0x54,
  0x81,0x00,0x81,0x7C,0x81,0x04,0xFF,0x00,
  0xF3,0xFF,0x80,0xFF,0xA4,0xDB,0x81,0xFE,
  0xD5,0xAA,0x95,0xEA,0xA4,0xDB,0x8D,0xFF,
  0x9F,0xEF,0x0F,0xF7,0x0F,0xF0,0x1D,0xE2,
  0x8B,0x77,0xC3,0x3D,0xC7,0xB9,0xDF,0xEF,
  0xFF,0x00,0x80,0x03,0x81,0x02,0x81,0x02,
  0x81,0x02,0x81,0x02,0x80,0x03,0xFF,0x00,
  0xFF,0x00,0x83,0x00,0x83,0x00,0xFF,0x00,
  0x83,0x00,0x83,0x00,0xFF,0x00,0x83,0x00,
  0x18,0x00,0x7F,0x42,0x7F,0x5A,0x7F,0x12,
  0xFF,0x04,0xFF,0x4D,0xFF,0x61,0x0C,0x00,
  0x00,0x00,0xFF,0x3F,0xFF,0x09,0xFF,0x6A,
  0xBF,0x28,0xBF,0x03,0xDF,0x41,0x12,0x00
};

/* End of MAIN_MAP_TILESET.C */
