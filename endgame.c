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
#include "balance.h"
#include "endgame.h"
#include "main.h"

void endgame(const UINT8* win_text)
{
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

    // Add bank balance to balance
    add_money(0U, game_state.bank_balance);

    // Check if user has enough money to cover loan
    if (has_money(0U, game_state.loan))
    {
        remove_money(0U, game_state.loan);
        negative_total = 0U;
    }
    else
    {
        // Has total NEGATIVE balance.
        // Since loan is currently only 1 int long,
        // set balance to loan - current balance
        negative_total = 1U;
        game_state.balance[0] = 0xFFFF - (game_state.loan - game_state.balance[0]);
    }
    // Show balance in total amount
    current_x = main_show_balance(0x12U, 0x11U, ROM_BANK_ENDGAME);

    if (negative_total)
    {
        // If total is negative, overwrite dollar, replacing with
        // dash and place dollar before
        tile_data = MENU_TILE_DASH;
        set_bkg_tiles(current_x, 0x11U, 1, 1, &tile_data);
        current_x -= 1U;
        tile_data = MENU_TILE_DOLLAR;
        set_bkg_tiles(current_x, 0x11U, 1, 1, &tile_data);
    }

    // Display rank
    rank_text = &win_txt_rank_hopeless;
    if (negative_total == 0 && has_money(0))
    {
        rank_text = &win_txt_rank_utter_failure;

        if (has_money(0U, 100U))
            rank_text = &win_txt_rank_loser;
        if (has_money(0U, 500U))
            rank_text = &win_txt_rank_incompetent;

        if (game_state.karma > 20)
        {
            if (has_money(0U, 1000U))
                rank_text = &win_txt_rank_wuss;
            if (has_money(0U, 4000U))
                rank_text = &win_txt_rank_girl_scout;
            if (has_money(0U, 10000U))
                rank_text = &win_txt_rank_boy_scout;

            // Check 100K (in real game, this is checked in reverse order
            // and could never be achieved)
            if (has_money(1U, 34464U))
                rank_text = &win_txt_rank_extraordinarily_good;
            // Check 250K
            if (has_money(3U, 53392U))
                rank_text = &win_txt_rank_good_samaritan;

            // check 1M
            if (has_money(15U, 16960U))
                rank_text = &win_txt_rank_selfless_millionaire;
            // Check 2M
            if (has_money(30U, 33920U))
                rank_text = &win_txt_rank_philanthropist;
            // Check 10M
            if (has_money(152U, 38528U))
                rank_text = &win_txt_rank_saint;
            // Check 100M
            if (has_money(1525U, 57600U))
                rank_text = &win_txt_rank_apostle;
            // check 1B
            if (has_money(15258U, 51712U))
                rank_text = &win_txt_rank_mr_dog;
        }
        else if (game_state.karma < -20)
        {
            if (has_money(0U, 1000U))
                rank_text = &win_txt_rank_juvenile_delinquent;
            if (has_money(0U, 4000U))
                rank_text = &win_txt_rank_white_collar_criminal;
            if (has_money(0U, 10000U))
                rank_text = &win_txt_rank_petty_criminal;
            // Check 100K (in real game, this is checked in reverse order
            // and could never be achieved)
            if (has_money(1U, 34464U))
                rank_text = &win_txt_rank_extraordinarily_evil;
            // Check 250K
            if (has_money(3U, 53392U))
                rank_text = &win_txt_rank_car_jacker;
            // check 1M
            if (has_money(15U, 16960U))
                rank_text = &win_txt_rank_drug_lord;
            // Check 2M
            if (has_money(30U, 33920U))
                rank_text = &win_txt_rank_undeniably_wicked;
            // Check 10M
            if (has_money(152U, 38528U))
                rank_text = &win_txt_rank_genuine_hellraiser;
            // Check 100M
            if (has_money(1525U, 57600U))
                rank_text = &win_txt_rank_seed_of_evil;
            // check 1B
            if (has_money(15258U, 51712U))
                rank_text = &win_txt_rank_mr_natas;
        }
        else
        {
            if (has_money(0U, 1000U))
                rank_text = &win_txt_rank_novice;
            if (has_money(0U, 4000U))
                rank_text = &win_txt_rank_mediocre;
            if (has_money(0U, 10000U))
                rank_text = &win_txt_rank_exceptional;
            // Check 100K (in real game, this is checked in reverse order
            // and could never be achieved)
            if (has_money(1U, 34464U))
                rank_text = &win_txt_rank_genius;
            // Check 250K
            if (has_money(3U, 53392U))
                rank_text = &win_txt_rank_extraordinary;
            // check 1M
            if (has_money(15U, 16960U))
                rank_text = &win_txt_rank_millionaire;
            // Check 2M
            if (has_money(30U, 33920U))
                rank_text = &win_txt_rank_multimillionaire;
            // Check 10M
            if (has_money(152U, 38528U))
                rank_text = &win_txt_rank_demi_god;
            // Check 100M
            if (has_money(1525U, 57600U))
                rank_text = &win_txt_rank_god;
            // check 1B
            if (has_money(15258U, 51712U))
                rank_text = &win_txt_rank_billionaire_god;
        }
    }

    main_show_window_text_xy(6, 8, rank_text, ROM_BANK_ENDGAME);

    DISPLAY_ON;

    // Show reason, which will wait for input
    main_show_window_text(win_text, ROM_BANK_ENDGAME);

    // Mark game as ended to exit main loop
    game_state.game_ended = 1U;
}
