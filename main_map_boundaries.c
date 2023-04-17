/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */

#pragma bank=7

#include <gb/gb.h>
#include "main.h"
#include "game_constants.h"
#include "main_map.h"

const UBYTE MAIN_MAP_BOUNDARIES[] = {
    // Each row  of map is 8.75 bytes. Each row in this array ends with any leading tiles form next map row.
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xE0, 0xFF, 0x07, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x00, 0x00,
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
    0xFC, 0xFD, 0xFF, 0x3F, 0x00, 0x04, 0x00, 0x00, 0x00,

    // Rows 12-15
    0x04, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,

    // Rows 16-19
    0x04, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,

    // Rows 20-23
    0x04, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x0F, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xFF, 0xF9, 0x3F,

    // Rows 24-27
    0xFC, 0x9F, 0xFF, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x20,
    0x00, 0xF0, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x20,
    0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x20,
    0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x20,

    // Rows 28-31
    0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x20,
    0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x20,
    0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x20,
    0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x20,

    // Rows 32-35
    0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x20,
    0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x20,
    0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x20,
    0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x20,

    // Rows 36-39
    0x00, 0x00, 0x00, 0x20, 0x00, 0xFC, 0xFF, 0x9F, 0xFF,
    0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0xF0, 0x00,
    0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x00, 0x00,

    // Rows 40-43
    0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x00, 0x00,

    // Rows 44-47
    0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x30, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x10, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x10, 0x00, 0x04, 0x00, 0x00, 0x00,

    // Rows 48-51
    0x00, 0x00, 0x00, 0x30, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x00, 0x00,

    // Rows 52-55
    0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x20, 0xFF, 0x04, 0x00, 0x00, 0x00,

    // Row 56
    0x00, 0x00, 0x00, 0xE0, 0xFF, 0x07, 0x00, 0x00, 0x00,

};

// Check if next position will hit a boundary
void check_boundary_hit()
{
    unsigned int new_x;
    unsigned int new_y;
    unsigned int new_tile_itx;

#if IN_TESTING && DEBUG_IGNORE_BOUNDARIES
    return;
#endif

    new_x = game_state.user_pos_x + (signed int)joypad_state.travel_x;
    new_y = game_state.user_pos_y + (signed int)joypad_state.travel_y;

    // Check if traveling to new tile
    if ((joypad_state.travel_x == 1 && (new_x & 0x07U) == 0x00U) ||
        (joypad_state.travel_x == -1 && (new_x & 0x07U) == 0x07U) ||
        (joypad_state.travel_y == 1 && (new_y & 0x07U) == 0x00U) ||
        (joypad_state.travel_y == -1 && (new_y & 0x07U) == 0x07U))
    {
            new_tile_itx = X_Y_TO_TILE_INDEX(
                PIXEL_LOCATION_TO_TILE_COUNT(new_x),
                PIXEL_LOCATION_TO_TILE_COUNT(new_y)
            );

            // Check if new tile is a boundary
            if (TILE_INDEX_BIT_MAP_VALUE(MAIN_MAP_BOUNDARIES, new_tile_itx))
            {
                // Reset travel directions, acting as if user is not moving.
                joypad_state.travel_x = 0;
                joypad_state.travel_y = 0;
            }
    }
}
