/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */

#pragma bank=5

#include <gb/gb.h>

const UBYTE MAIN_MAP_BOUNDARIES[] = {
    // Each row  of map is 8.75 bytes. Each row in this array ends with any leading tiles form next map row.
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xE0, 0xFF, 0x07, 0x00, 0x00, 0x00,
    // ^ end of 4th row (0-3)
    
    // Rows 4-7
    0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x00, 0x00,

    // Rows 8-11
    0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x07, 0x00, 0x20, 0x00, 0x04, 0x00, 0x00, 0x00,
    0xF8, 0xFD, 0xFF, 0x3F, 0x00, 0x04, 0x00, 0x00, 0x00,

    // Rows 12-15
    0x08, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x08, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x08, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x08, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
    
    // Rows 16-19
    0x08, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x08, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x08, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x08, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
    
    // Rows 20-23
    0x08, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x08, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x08, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x0F, 0x00,
    0x08, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xFF, 0xF9, 0x1F,
    
    // Rows 24-27
    0xF8, 0xFF, 0xFF, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x10,
    0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x10,
    0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x10,
    0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x10,

    // Rows 28-31
    0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x10,
    0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x10,
    0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x10,
    0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x10,
    
    // Rows 32-35
    0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x10,
    0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x10,
    0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x10,
    0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x10,
    
    // Rows 36-39
    0x00, 0x00, 0x00, 0x20, 0x00, 0xFC, 0xFF, 0xFF, 0x1F,
    0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x00, 0x00,
    
    // Rows 40-43
    0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x00, 0x00,
    
    // Rows 44-47
    0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x00, 0x00,
    
    // Rows 48-51
    0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x00, 0x00,

    // Rows 52-55
    0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xE0, 0xFF, 0x07, 0x00, 0x00, 0x00,
    
    // Row 56
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

};
