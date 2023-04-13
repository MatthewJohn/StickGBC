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
#include "window_text.h"
#include "endgame.h"
#include "main.h"

void endgame(const UINT8* win_text)
{
    UINT16 total_balance = 0;
    BOOLEAN negative_total = 0;
    UBYTE tile_data;
    UINT8 current_x;
    UINT8 *rank_text;

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
    main_show_signed_number(0x9U, 0xDU, 3, game_state.karma, ROM_BANK_ENDGAME);

    main_show_balance(0x12U, 0xEU, ROM_BANK_ENDGAME);
    tile_data = MENU_TILE_DOLLAR;
    current_x = main_show_number(0xAU, 0xFU, 8, game_state.bank_balance, ROM_BANK_ENDGAME);
    set_bkg_tiles(current_x, 0xFU, 1, 1, &tile_data);
    current_x = main_show_number(0xAU, 0x10U, 8, game_state.loan, ROM_BANK_ENDGAME);
    set_bkg_tiles(current_x, 0x10U, 1, 1, &tile_data);

//    total_balance = game_state.balance;
    total_balance = 0;
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

    // Display rank
    rank_text = &win_txt_rank_hopeless;
    if (negative_total == 0 && total_balance > 0)
    {
        rank_text = &win_txt_rank_utter_failure;

        if (total_balance > 100)
            rank_text = &win_txt_rank_loser;
        if (total_balance > 500)
            rank_text = &win_txt_rank_incompetent;

        if (game_state.karma > 20)
        {
            if (total_balance > 1000)
                rank_text = &win_txt_rank_wuss;
            if (total_balance > 4000)
                rank_text = &win_txt_rank_girl_scout;
            if (total_balance > 10000)
                rank_text = &win_txt_rank_boy_scout;
//            if (total_balance > 250000)
//                rank_text = &win_txt_rank_good_samaritan;
//            if (total_balance > 100000)
//                rank_text = &win_txt_rank_extraordinarily_good;
//            if (total_balance > 1000000)
//                rank_text = &win_txt_rank_selfless_millionaire;
//            if (total_balance > 2000000)
//                rank_text = &win_txt_rank_philanthropist;
//            if (total_balance > 10000000)
//                rank_text = &win_txt_rank_saint;
//            if (total_balance > 100000000)
//                rank_text = &win_txt_rank_apostle;
//            if (total_balance > 1000000000)
//                rank_text = &win_txt_rank_mr_dog;
        }
        else if (game_state.karma < -20)
        {
            if (total_balance > 1000)
                rank_text = &win_txt_rank_juvenile_delinquent;
            if (total_balance > 4000)
                rank_text = &win_txt_rank_white_collar_criminal;
            if (total_balance > 10000)
                rank_text = &win_txt_rank_petty_criminal;
//            if (total_balance > 250000)
//                rank_text = &win_txt_rank_car_jacker;
//            if (total_balance > 100000)
//                rank_text = &win_txt_rank_extraordinarily_evil;
//            if (total_balance > 1000000)
//                rank_text = &win_txt_rank_drug_lord;
//            if (total_balance > 2000000)
//                rank_text = &win_txt_rank_undeniably_wicked;
//            if (total_balance > 10000000)
//                rank_text = &win_txt_rank_genuine_hellraiser;
//            if (total_balance > 100000000)
//                rank_text = &win_txt_rank_seed_of_evil;
//            if (total_balance > 1000000000)
//                rank_text = &win_txt_rank_mr_natas;
        }
        else
        {
            if (total_balance > 1000)
                rank_text = &win_txt_rank_novice;
            if (total_balance > 4000)
                rank_text = &win_txt_rank_mediocre;
            if (total_balance > 10000)
                rank_text = &win_txt_rank_exceptional;
//            if (total_balance > 250000)
//                rank_text = &win_txt_rank_extraordinary;
//            if (total_balance > 100000)
//                rank_text = &win_txt_rank_genius;
//            if (total_balance > 1000000)
//                rank_text = &win_txt_rank_millionaire;
//            if (total_balance > 2000000)
//                rank_text = &win_txt_rank_multimillionaire;
//            if (total_balance > 10000000)
//                rank_text = &win_txt_rank_demi_god;
//            if (total_balance > 100000000)
//                rank_text = &win_txt_rank_god;
//            if (total_balance > 1000000000)
//                rank_text = &win_txt_rank_billionaire_god;
        }
    }

    main_show_window_text_xy(6, 8, rank_text, ROM_BANK_ENDGAME);

    DISPLAY_ON;

    // Show reason, which will wait for input
    main_show_window_text(win_text, ROM_BANK_ENDGAME);

    // Mark game as ended to exit main loop
    game_state.game_ended = 1U;
}
