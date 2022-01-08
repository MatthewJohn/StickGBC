/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */

#pragma bank=5

#include "main_game.h"
#include "game_constants.h"
#include "main_map_tileset.h"
#include "external_bank_globals.h"

void load_house()
{
    set_bkg_data(13, 1, &(mainmaptiles[13 << 4]));
}

void load_restaurant()
{
    set_bkg_data(15, 2, &(mainmaptiles[15 << 4]));
    // Set palette data
    word_data[0] = RGB(0, 0, 0);
    word_data[1] = RGB(31, 22, 8);
    word_data[2] = RGB(25, 0, 0);
    word_data[3] = RGB(13, 12, 1 );
    set_bkg_palette(PALETTE_SCRATCH_3, 1, word_data);
}

void load_shop()
{
    set_bkg_data(18U, 5U, &(mainmaptiles[18U << 4]));
    word_data[0] = RGB(31, 21, 5);
    word_data[1] = RGB(1, 0, 2);
    word_data[2] = RGB(4, 20, 0);
    word_data[3] = RGB(26, 16, 0 );
    set_bkg_palette(PALETTE_SCRATCH_2, 1, word_data);
}

void load_pawn()
{
    set_bkg_data(23U, 4U, &(mainmaptiles[23U << 4]));
    scratch_palette_data[2U][0U] = RGB(10U, 1U, 16U);
    scratch_palette_data[2U][1U] = RGB(31U, 31U, 31U);
    scratch_palette_data[2U][3U] = RGB(15U, 6U, 31U);
    set_bkg_palette(PALETTE_SCRATCH_3, 1, &(scratch_palette_data[2U]));
}

void load_university()
{
    set_bkg_data(27U, 3U, &(mainmaptiles[27U << 4]));
    scratch_palette_data[2U][0U] = RGB(15U, 19U, 0U);
    scratch_palette_data[2U][1U] = RGB(31U, 22U, 8U);
    scratch_palette_data[2U][2U] = RGB(31U, 13U, 2U);
    scratch_palette_data[2U][3U] = RGB(30U, 31U, 9U);
    set_bkg_palette(PALETTE_SCRATCH_3, 1, &(scratch_palette_data[2U]));
}

void load_nli()
{
    set_bkg_data(30U, 9U, &(mainmaptiles[30U << 4]));
    scratch_palette_data[1U][0U] = RGB(6U, 6U, 6U);
    scratch_palette_data[1U][1U] = RGB(7U, 3U, 1U);
    set_bkg_palette(PALETTE_SCRATCH_2, 1, &(scratch_palette_data[1U]));
}

void load_bar()
{
    set_bkg_data(39U, 13U, &(mainmaptiles[39U << 4]));
    scratch_palette_data[0U][0U] = RGB(1U, 14U, 1U);
    scratch_palette_data[0U][1U] = RGB(10U, 8U, 1U);
    scratch_palette_data[0U][2U] = RGB(31U, 1U, 1U);
    scratch_palette_data[0U][3U] = RGB(3U, 8U, 1U);
    set_bkg_palette(PALETTE_SCRATCH_1, 1, &(scratch_palette_data[0U]));
}