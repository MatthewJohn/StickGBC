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
    UINT16 total_balance = 0;
    BOOLEAN negative_total = 0;
    UBYTE tile_data;
    UINT8 current_x;

    DISPLAY_OFF;

    // Hide sprites
    HIDE_SPRITES;
    
    // Hide Window
    HIDE_WIN;

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
    set_bkg_data(8U, 87U, &(endgametiles[8U << 4]));

    // Write charm number
    main_show_number(0x8U, 0xAU, 3, game_state.charm, ROM_BANK_ENDGAME);

    // Write strength number
    main_show_number(0xAU, 0xBU, 3, game_state.strength, ROM_BANK_ENDGAME);

    // Write intelligence number
    main_show_number(0xBU, 0xCU, 3, game_state.intelligence, ROM_BANK_ENDGAME);

    // Write karma number
    main_show_number_signed(0x9U, 0xDU, 3, game_state.karma, ROM_BANK_ENDGAME);

    tile_data = MENU_TILE_DOLLAR;
    current_x = main_show_number(0xAU, 0xEU, 8, game_state.balance, ROM_BANK_ENDGAME);
    set_bkg_tiles(current_x, 0xEU, 1, 1, &tile_data);
    current_x = main_show_number(0xAU, 0xFU, 8, game_state.bank_balance, ROM_BANK_ENDGAME);
    set_bkg_tiles(current_x, 0xFU, 1, 1, &tile_data);
    current_x = main_show_number(0xAU, 0x10U, 8, game_state.loan, ROM_BANK_ENDGAME);
    set_bkg_tiles(current_x, 0x10U, 1, 1, &tile_data);

    total_balance = game_state.balance;
    total_balance += game_state.bank_balance;
    if (total_balance > game_state.loan)
    {
        total_balance -= game_state.loan;
        negative_total = 0;
    }
    else
    {
        total_balance = game_state.loan - total_balance;
        negative_total = 1;
    }
    current_x = main_show_number(0xAU, 0x11U, 8, total_balance, ROM_BANK_ENDGAME);
    if (negative_total)
    {
        tile_data = MENU_TILE_DASH;
        set_bkg_tiles(current_x, 0x11U, 1, 1, &tile_data);
        current_x -= 1U;
    }
    tile_data = MENU_TILE_DOLLAR;
    set_bkg_tiles(current_x, 0x11U, 1, 1, &tile_data);

    DISPLAY_ON;

    // Wait for user to press A or START
    while (joypad_state.a_pressed == 0U && joypad_state.start_pressed == 0U)
    {
        wait_vbl_done();

        main_check_joy(ROM_BANK_ENDGAME);
    }
}
