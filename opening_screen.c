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

    // Wait for user to press A or START
    while (joypad_state.a_pressed == 0U && joypad_state.start_pressed == 0U)
    {
        wait_vbl_done();

        main_check_joy(ROM_BANK_OPENING_SCREEN);
    }
}


void opening_screen_loop()
{
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
    set_bkg_data(8U, 19U, &(openingscreentiles[8U << 4]));

    DISPLAY_ON;

    joypad_state.a_pressed = 0U;
    joypad_state.start_pressed = 0U;

    // Wait for user to press A or START
    while (joypad_state.a_pressed == 0U && joypad_state.start_pressed == 0U)
    {
        wait_vbl_done();

        main_check_joy(ROM_BANK_OPENING_SCREEN);
    }
}
