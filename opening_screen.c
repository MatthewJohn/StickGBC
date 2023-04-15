/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */

#pragma bank=7

#include "opening_screen.h"
#include "opening_screen_map.h"
#include "opening_screen_palette.h"
#include "opening_screen_tiles.h"
#include "splash_screen_map.h"
#include "splash_screen_tiles.h"
#include "splash_screen_palette.h"
#include "game_constants.h"
#include "main.h"

void splash_screen_loop()
{
    DISPLAY_OFF;

    HIDE_SPRITES;
    HIDE_WIN;

    screen_state.background_color_palette = splash_screen_palette;
    screen_state.background_tile_map = splashscreenmap;
    screen_state.background_tiles = splashscreentiles;
    screen_state.background_width = splashscreenmapWidth;

    screen_state.draw_offset_x = 0U;
    screen_state.draw_offset_y = 0U;
    screen_state.draw_max_x = SCREEN_WIDTH_TILES;
    screen_state.draw_max_y = SCREEN_HEIGHT_TILES;

    set_background_tiles(
        ROM_BANK_OPENING_SCREEN,  // Load tiles from this ROM bank
        ROM_BANK_OPENING_SCREEN  // Return to the ROM bank for this function
    );

    // Move background to top left
    move_bkg(0, 0);

    // Load additional tiles required
    set_bkg_data(8U, 120U, &(splashscreentiles[8U << 4]));
    VBK_REG = 1;
    set_bkg_data(0U, 25U, &(splashscreentiles[128U << 4]));
    VBK_REG = 0;

    DISPLAY_ON;

    // Reset values for currently pressed buttons
    joypad_state.a_pressed = 0U;
    joypad_state.start_pressed = 0U;

    // Wait for user to press A or START
    while (joypad_state.a_pressed == 0U && joypad_state.start_pressed == 0U)
    {
        wait_vbl_done();

        main_check_joy(ROM_BANK_OPENING_SCREEN);
    }
}

/* opening_screen_update_selection
 *
 * Checks joypad input to update selected option
 * and redraws tile selection palettes.
 *
 * @param Currently selected option
 *
 * @returns new selected option index
 */
UINT8 opening_scrn_update_sel(UINT8 selected_option)
{
    UINT8 itx;
    UINT8 tile_itx_x;
    UINT8 tile_itx_y;
    unsigned char original_data;

    if (joypad_state.travel_x == 1)
    {
        // Set first bit to 1
        selected_option |= 1U;
    }
    if (joypad_state.travel_x == -1)
    {
        // Set first bit to 0 (mask second bit)
        selected_option &= 0x2U;
    }
    if (joypad_state.travel_y == 1)
    {
        // Set second bit to 1
        selected_option |= 2U;
    }
    if (joypad_state.travel_y == -1)
    {
        // Set second bit to 0 (mask first bit)
        selected_option &= 0x1U;
    }

    // Update palette for selection options
    VBK_REG = 1;
    for (itx = 0; itx != 4; itx ++)
    {
        for (tile_itx_x = 0; tile_itx_x != 6; tile_itx_x ++)
        {
            for (tile_itx_y = 0; tile_itx_y != 3; tile_itx_y ++)
            {
                get_bkg_tiles(
                    2U + ((itx % 2) * 10U) + tile_itx_x,
                    8U + ((itx / 2) * 5U) + tile_itx_y,
                    1U,
                    1U,
                    &original_data
                );
                // Set palette to 0
                original_data &= 0xF8;
                if (itx == selected_option)
                {
                    // Increment palette to 1
                    original_data += 1U;
                }
                set_bkg_tiles(
                    2U + ((itx % 2) * 10U) + tile_itx_x,
                    8U + ((itx / 2) * 5U) + tile_itx_y,
                    1U,
                    1U,
                    &original_data
                );
            }
        }
    }
    VBK_REG = 0;

    return selected_option;
}

void opening_screen_loop()
{
    BOOLEAN last_input_had_input;
    UINT8 selected_option = 0;

    DISPLAY_OFF;

    screen_state.background_color_palette = opening_screen_palette;
    screen_state.background_tile_map = openingscreenmap;
    screen_state.background_tiles = openingscreentiles;
    screen_state.background_width = openingscreenmapWidth;

    screen_state.draw_offset_x = 0U;
    screen_state.draw_offset_y = 0U;
    screen_state.draw_max_x = SCREEN_WIDTH_TILES;
    screen_state.draw_max_y = SCREEN_HEIGHT_TILES;

    set_background_tiles(
        ROM_BANK_OPENING_SCREEN,  // Load tiles from this ROM bank
        ROM_BANK_OPENING_SCREEN  // Return to the ROM bank for this function
    );

    // Move background to top left
    move_bkg(0, 0);

    // Load additional tiles required
    set_bkg_data(8U, 44U, &(openingscreentiles[8U << 4]));

    DISPLAY_ON;

    // Set joypad state to no input
    joypad_state.a_pressed = 0U;
    joypad_state.start_pressed = 0U;
    joypad_state.travel_x = 0;
    joypad_state.travel_y = 0;
    last_input_had_input = 0U;
    // Set initial option to 30 days
    selected_option = 1U;
    opening_scrn_update_sel(selected_option);

    // Wait for user to press A or START
    while (joypad_state.a_pressed == 0U && joypad_state.start_pressed == 0U)
    {
        // Check for user changing selection
        if (joypad_state.travel_x != 0 || joypad_state.travel_y != 0)
        {
            // Only update if they've just pressed the button
            if (last_input_had_input == 0U)
            {
                selected_option = opening_scrn_update_sel(selected_option);
            }
        }
        else
        {
            last_input_had_input = 0U;
        }

        wait_vbl_done();

        main_check_joy(ROM_BANK_OPENING_SCREEN);
    }

    // Update game_state max_days based on selected input
    if (selected_option == 0U)
    {
        game_state.max_days = 15U;
    }
    else if (selected_option == 1U)
    {
        game_state.max_days = 30U;
    }
    else if (selected_option == 2U)
    {
        game_state.max_days = 100U;
    }
    else if (selected_option == 3U)
    {
        game_state.max_days = 0U;
    }
}
