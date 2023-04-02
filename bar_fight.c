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

#define BAR_FIGHT_TILE_SCRATCH 68U
#define BAR_FIGHT_NUMERIC_TILE_START 63U

UINT8 add_number(UINT8 tile_x, UINT8 tile_y, UINT16 number)
{
    UINT8 digit_count;
    UINT16 overflow;
    UINT16 source_tile_index;
    UINT8 remainder;
    BOOLEAN has_run;
    UINT8 current_map_index;
    unsigned char tile_to_insert[16U];
    UINT8 source_tile_offset;
    UINT8 source_data_mask;
    UINT8 destination_data_mask;
    unsigned char map_reference_data;
    UINT8 byte_itx;
    UINT8 number_data;
    
    for (byte_itx = 0; byte_itx < 16U; byte_itx ++)
    {
      tile_to_insert[byte_itx] = 0U;
    }
    destination_data_mask = 0x0FU;

    digit_count = 0;
    current_map_index = BAR_FIGHT_TILE_SCRATCH;
    overflow = number;
 
   // Iterate over number to display, until number is reduced to single digit
   // Use has_run to handle showing 0
    while (1) {
        digit_count ++;
        remainder = (overflow & 0xFFU) % 10U;
        overflow = overflow / 10U;

        // Each source tile contains 2 numbers,
        // so source tile is tile main offset with an offset of number to use / 2
        source_tile_offset = remainder / 2U;
        // Each line in tile is made of 2 chars, meaing each line of a number is 1 byte.
        // Offset for first number (0, 2, etc.) is 0 (start of tile) and odd numbers are on the right
        // hand side, so each line offset is 1
        if (remainder % 2U == 0U) {
            source_data_mask = 0xF0U;
        } else {
            source_data_mask = 0x0FU;
        }

        // Iterate through each line, copying the byte to the tile data to insert.
        for (byte_itx = 0; byte_itx < 16U; byte_itx ++) {
            source_tile_index = BAR_FIGHT_NUMERIC_TILE_START + source_tile_offset;
            source_tile_index = source_tile_index << 4;
            source_tile_index += byte_itx;
            // Remove the currently character side of destination data
            number_data = barfighttiles[source_tile_index] & source_data_mask;

            // Bit shift part of source tile data to match mask of destination tile number position,
            // pushing number to the right or left to match the destination location
            if (source_data_mask != destination_data_mask)
            {
                if (source_data_mask == 0xF0U)
                {
                    number_data = number_data >> 4;
                }
                else
                {
                    number_data = number_data << 4;
                }
            }
            // Combine previous tile data with new tile data
            tile_to_insert[byte_itx] = tile_to_insert[byte_itx] | number_data;
        }

        set_bkg_data(current_map_index, 1U, tile_to_insert);
        
        // Create map data for tile
        map_reference_data = current_map_index;

        set_bkg_tiles(tile_x, tile_y, 1, 1, &map_reference_data);
        VBK_REG = 1;
        // Bank 0, not flipped and no priority flag
        map_reference_data = 0U;
        set_bkg_tiles(tile_x, tile_y, 1, 1, &map_reference_data);
        VBK_REG = 0;

        if (overflow == 0U) {
            break;
        }
        
        // Flip the destination file offset on each number
        if (destination_data_mask == 0x0FU) {
            destination_data_mask = 0xF0U;
        } else {
            // If going abck to first digit, blank the tile data
            destination_data_mask = 0x0FU;
            // Reset file data
            for (byte_itx = 0; byte_itx < 16U; byte_itx ++)
            {
              tile_to_insert[byte_itx] = 0U;
            }
        }
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
    add_number(2U, 12U, 87U);
    joypad_state.a_pressed = 0U;
    joypad_state.start_pressed = 0U;
    while (joypad_state.a_pressed == 0U && joypad_state.start_pressed == 0U)
    {
        wait_vbl_done();

        main_check_joy(ROM_BANK_BAR_FIGHT);
    }
}
