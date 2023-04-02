/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */

#pragma bank=2

#include "bar_fight_map.h"
#include "bar_fight_tiles.h"
#include "bar_fight_palette.h"
#include "game_constants.h"
#include "bar_fight.h"
#include "main.h"

#define BAR_FIGHT_TILE_SCRATCH 69U
#define BAR_FIGHT_NUMERIC_TILE_START 63U

UINT8 add_number(UINT8 tile_x, UINT8 tile_y, UINT16 number)
{
    UINT8 digit_count;
    UINT16 overflow;
    UINT8 remainder;
    UINT16 multiple;
    BOOLEAN has_run;
    UINT8 current_map_index;
    unsigned char tile_to_insert[0xFU];
    UINT8 source_tile_offset;
    UINT8 source_tile_data_offset;
    UINT8 destination_tile_offset;
    UINT8 byte_itx;

    digit_count = 0;
    current_map_index = BAR_FIGHT_TILE_SCRATCH;
    overflow = number;
    has_run = 0U;
    destination_tile_offset = 0U;
 
   // Iterate over number to display, until number is reduced to single digit
   // Use has_run to handle showing 0
    while (overflow > 0 || has_run == 0U) {
        digit_count ++;
        remainder = overflow % 10U;
        overflow = overflow / 10U;

        // Each source tile contains 2 numbers,
        // so source tile is tile main offset with an offset of number to use / 2
        source_tile_offset = remainder / 2U;
        // Each line in tile is made of 2 chars, meaing each line of a number is 1 byte.
        // Offset for first number (0, 2, etc.) is 0 (start of tile) and odd numbers are on the right
        // hand side, so each line offset is 1
        source_tile_data_offset = (remainder % 2U);

        // Flip the destination file offset on each number
        if (destination_tile_offset == 0U) {
            destination_tile_offset = 1U;
        } else {
            destination_tile_offset = 0U;
        }

        // Iterate through each line, copying the byte to the tile data to insert.
        for (byte_itx = 0; byte_itx <= 8U; byte_itx ++) {
            tile_to_insert[destination_tile_offset + byte_itx] = barfighttiles[BAR_FIGHT_NUMERIC_TILE_START + source_tile_offset + source_tile_data_offset];
        }

        set_bkg_data(current_map_index, 1U, &(tile_to_insert[0U]));
        has_run = 1U;
    }

    return current_map_index;
}

void enter_bar_fight()
{

    DISPLAY_OFF;

    // Hide sprites
    HIDE_SPRITES;

    // Hide Window
    HIDE_WIN;

    screen_state.background_color_palette = bar_fight_palette;
    screen_state.background_tile_map = barfightmap;
    screen_state.background_tiles = barfighttiles;
    screen_state.background_width = barfightmapWidth;

    screen_state.draw_offset_x = 0U;
    screen_state.draw_offset_y = 0U;
    screen_state.draw_max_x = SCREEN_WIDTH_TILES;
    screen_state.draw_max_y = SCREEN_HEIGHT_TILES;

    set_background_tiles(
        ROM_BANK_BAR_FIGHT,  // Load tiles from this ROM bank
        ROM_BANK_BAR_FIGHT  // Return to the ROM bank for this function
    );

    // Move background to top left
    move_bkg(0, 0);

    // Load additional tiles required
    set_bkg_data(8U, 60U, &(barfighttiles[8U << 4]));

    DISPLAY_ON;

    // Wait for user to press A or START
    add_number(2U, 12U, 8U);
    joypad_state.a_pressed = 0U;
    joypad_state.start_pressed = 0U;
    while (joypad_state.a_pressed == 0U && joypad_state.start_pressed == 0U)
    {
        wait_vbl_done();

        main_check_joy(ROM_BANK_BAR_FIGHT);
    }
}
