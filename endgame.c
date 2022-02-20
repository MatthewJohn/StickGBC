/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */

#pragma bank=7

#include "endgame_map.h"
#include "endgame_tiles.h"
#include "endgame_palette.h"
#include "game_constants.h"
#include "endgame.h"
#include "main.h"

void endgame()
{
    DISPLAY_OFF;

    screen_state.background_color_palette = endgame_palette;
    screen_state.background_tile_map = endgamemap;
    screen_state.background_tiles = endgametiles;
    screen_state.background_width = endgamemapWidth;

    screen_state.draw_offset_x = 0U;
    screen_state.draw_offset_y = 0U;
    screen_state.draw_max_x = SCREEN_WIDTH_TILES;
    screen_state.draw_max_y = SCREEN_HEIGHT_TILES;

    set_background_tiles(
        ROM_BANK_ENDGAME,  // Load tiles from this ROM bank
        ROM_BANK_ENDGAME  // Return to the ROM bank for this function
    );

    // Move background to top left
    move_bkg(0, 0);

    // Load additional tiles required
    set_bkg_data(8U, 86U, &(endgametiles[8U << 4]));

    DISPLAY_ON;

    // Wait for user to press A or START
    while (joypad_state.a_pressed == 0U && joypad_state.start_pressed == 0U)
    {
        wait_vbl_done();

        main_check_joy(ROM_BANK_ENDGAME);
    }
}
