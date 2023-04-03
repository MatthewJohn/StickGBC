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


/*
 *  bar_fight_write_digit_to_screen
 * 
 */
void bf_wrt_dgt_to_scr(UINT8 tile_x, UINT8 tile_y, UINT8 source_tile_offset, UINT8 source_data_mask, UINT8 destination_data_mask, unsigned char* tile_to_insert, UINT8 add_underscore, UINT16 current_map_index)
{
    UINT8 byte_itx2;
    UINT16 source_tile_index;
    unsigned char map_reference_data;
    UINT8 number_data;

    // Iterate through each line, copying the byte to the tile data to insert.
    for (byte_itx2 = 0; byte_itx2 < 16U; byte_itx2 ++)
    {
        source_tile_index = BAR_FIGHT_NUMERIC_TILE_START + source_tile_offset;
        source_tile_index = source_tile_index << 4;
        source_tile_index += byte_itx2;
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
        if (byte_itx2 == 14U && add_underscore == 1U)
        {
            // Set entire row to black if underscoring and on final line
            tile_to_insert[byte_itx2] = 0xFFU;
        }
        else
        {
            // Combine previous tile data with new tile data
            tile_to_insert[byte_itx2] = tile_to_insert[byte_itx2] | number_data;
        }
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
}

/*
 * add_number
 *
 * Draw a number to the screen, combining number tiles to provide 2 numbers per tile
 * Add optional underscoring for placement of numbers in action box
 *
 * @param tile_x rightmost X coordinate for tile placement on map. Numbers are drawn to the left
 * @param tile_y Y coordinate for tile placement on map
 * @param number Number to br drawn to screen
 * @param add_underscore Whether to add bottom line to fill in action box
 */
UINT8 add_number(UINT8 current_map_index, UINT8 tile_x, UINT8 tile_y, UINT16 number, UINT16 secondary_number, UINT8 add_underscore)
{
    // Process state - 0 not run, 1 performing first number, 2 drawing forward slash, 3 drawing secondary number
    UINT8 process_state;
    UINT8 digit_count;
    UINT16 overflow;
    UINT8 remainder;
    unsigned char tile_to_insert[16U];
    UINT8 source_tile_offset;
    UINT8 source_data_mask;
    UINT8 destination_data_mask;
    UINT8 byte_itx;

    for (byte_itx = 0; byte_itx < 16U; byte_itx ++)
    {
      tile_to_insert[byte_itx] = 0U;
    }
    destination_data_mask = 0x0FU;
    
    process_state = 0;

    digit_count = 0;
    overflow = number;

   // Iterate over number to display, until number is reduced to single digit
   // Use has_run to handle showing 0
    while (1) {
        if (overflow == 0U && process_state != 0) {
            if (process_state == 1 && secondary_number != 0)
            {
                process_state = 2;
            }
            else if (process_state == 2)
            {
                overflow = secondary_number;
                process_state = 3;
            }
            else
            {
                break;
            }
        }
        if (process_state == 0)
        {
            process_state = 1;
        }
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
        
        // If process state is 2 (drawing forward slash), set source data mask and offset for it
        if (process_state == 2)
        {
            source_tile_offset = 5;
            source_data_mask = 0xF0;
        }
        bf_wrt_dgt_to_scr(tile_x, tile_y, source_tile_offset, source_data_mask, destination_data_mask, &tile_to_insert, add_underscore, current_map_index);

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

            // Increment map index for next tile
            current_map_index += 1;

            // Move x position 1 to left to draw next tile
            tile_x -= 1;
        }
    }

    return current_map_index;
}

// Update selected action on screen
void update_selected_item(bar_fight_state_t* bar_fight_state, UINT8 new_x, UINT8 new_y)
{
    UINT8 itx_action_x;
    UINT8 itx_action_y;
    UINT8 itx_tile_x;
    UINT8 itx_tile_y;
    unsigned char original_data;
    // Reset palette on all actions
    
    // Iterate through actions
    VBK_REG = 1;
    for (itx_action_x = 0; itx_action_x != 3; itx_action_x ++)
    {
        for (itx_action_y = 0; itx_action_y != 2; itx_action_y ++)
        {
            // Iterate through tiles in x
            for (itx_tile_x = 0; itx_tile_x != 4; itx_tile_x ++)
            {
                for (itx_tile_y = 0; itx_tile_y != 2; itx_tile_y ++)
                {
                    get_bkg_tiles(2U + (itx_action_x * 6U) + itx_tile_x, 11U + (itx_action_y * 3U) + itx_tile_y, 1U, 1U, &original_data);
                    // Set color palette to 0
                    original_data &= 0xF8;
                    set_bkg_tiles(2U + (itx_action_x * 6U) + itx_tile_x, 11U + (itx_action_y * 3U) + itx_tile_y, 1U, 1U, &original_data);
                }
            }
        }
    }
    
    // Iterate through tiles in x
    for (itx_tile_x = 0; itx_tile_x != 4; itx_tile_x ++)
    {
        for (itx_tile_y = 0; itx_tile_y != 2; itx_tile_y ++)
        {
            get_bkg_tiles(2U + (new_x * 6U) + itx_tile_x, 11U + (new_y * 3U) + itx_tile_y, 1U, 1U, &original_data);
            // Set color palette to 1
            original_data &= 0xF8;
            original_data += 1U;
            set_bkg_tiles(2U + (new_x * 6U) + itx_tile_x, 11U + (new_y * 3U) + itx_tile_y, 1U, 1U, &original_data);
        }
    }
    VBK_REG = 0;
    
    bar_fight_state->selected_menu_item_x = new_x;
    bar_fight_state->selected_menu_item_y = new_y;
}

void update_barfight_state(bar_fight_state_t* bar_fight_state)
{
    UINT8 new_menu_item_x = bar_fight_state->selected_menu_item_x;
    UINT8 new_menu_item_y = bar_fight_state->selected_menu_item_y;

    if (joypad_state.travel_x != 0 || joypad_state.travel_y != 0)
    {
        // Limit to max x/y menu items and, if not reached, update value
        if (!(bar_fight_state->selected_menu_item_x == 0 && joypad_state.travel_x == -1) &&
            !(bar_fight_state->selected_menu_item_x == 2 && joypad_state.travel_x == 1))
        {
            new_menu_item_x += joypad_state.travel_x;
        }
        if (!(bar_fight_state->selected_menu_item_y == 0 && joypad_state.travel_y == -1) &&
            !(bar_fight_state->selected_menu_item_y == 1 && joypad_state.travel_y == 1))
        {
            new_menu_item_y += joypad_state.travel_y;
        }
        // Update selected item
        update_selected_item(bar_fight_state, new_menu_item_x, new_menu_item_y);

        // Sleep to stop double pressed
        delay(DELAY_MENU_ITEM_MOVE);
    }
    else if (joypad_state.a_pressed)
    {
        if (bar_fight_state->selected_menu_item_y == 1)
        {
            // Check for run away
            if (bar_fight_state->selected_menu_item_x == 2)
            {
                    bar_fight_state->in_game = 0U;
            }
        }
    }
}

void enter_bar_fight()
{
    UINT16 number_tile_index = BAR_FIGHT_TILE_SCRATCH;
    bar_fight_state_t bar_fight_state;

    if (game_state.hour > 21U)
    {
        return;
    }
    game_state.hour += 3U;

    bar_fight_state.in_game = 1U;
    game_state.karma -= 2U;


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

    // Add points for actions
    // punch
    number_tile_index = add_number(number_tile_index, 4U, 12U, 1U, 0U, 1U);
    number_tile_index ++;
    // Fireball
    number_tile_index = add_number(number_tile_index, 10U, 12U, 2U, 0U, 1U);
    number_tile_index ++;
    // Kick
    number_tile_index = add_number(number_tile_index, 4U, 15U, 3U, 0U, 1U);
    number_tile_index ++;
    // Energy
    number_tile_index = add_number(number_tile_index, 10U, 15U, 4U, 0U, 1U);
    number_tile_index ++;
    
    // Show player health
    number_tile_index = add_number(number_tile_index, 5U, 1U, game_state.max_hp, game_state.hp, 0U);
    
    update_selected_item(&bar_fight_state, 0, 0);

    main_check_joy(ROM_BANK_BAR_FIGHT);

    while (bar_fight_state.in_game == 1U)
    {
        main_check_joy(ROM_BANK_BAR_FIGHT);
        
        update_barfight_state(&bar_fight_state);
        
        wait_vbl_done();
    }
}
