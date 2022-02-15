/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */


#pragma bank=8

#include "window_text.h"

/* Messages for shop*/
const UINT8 win_txt_shop_int[] = {
    33U, 15U, 22U, 13U, 25U, 23U, 15U, 0U, 30U, 25U, 0U, 16U, 31U, 24U, 21U, 35U, 0U, 30U, 25U, 33U, 24U, 0U, 16U, 19U, 32U, 15U, 44U, 25U, 0U, 13U, 25U, 24U, 32U, 15U, 24U, 19U, 15U, 24U, 13U, 15U, 0U, 29U, 30U, 25U, 28U, 15U, 0U, 33U, 18U, 15U, 28U, 15U, 0U, 19U, 0U, 12U, 15U, 0U, 29U, 15U, 28U, 32U, 19U, 24U, 41U, 0U, 31U, 26U, 0U, 29U, 25U, 23U, 15U, 0U, 27U, 31U, 11U, 22U, 19U, 30U, 35U, 0U, 26U, 28U, 25U, 14U, 31U, 13U, 30U, 0U, 16U, 25U, 28U, 0U, 35U, 25U, 41U, 0U, 30U, 25U, 0U, 12U, 15U, 0U, 17U, 15U, 30U, 30U, 19U, 24U, 41U, 0U, 35U, 25U, 41U, 0U, 14U, 28U, 19U, 24U, 21U, 0U, 11U, 24U, 14U, 0U, 17U, 15U, 30U, 30U, 19U, 24U, 0U, 35U, 25U, 0U, 29U, 24U, 11U, 13U, 21U, 0U, 25U, 24U, 37U, 0U, 18U, 25U, 33U, 0U, 13U, 11U, 24U, 0U, 19U, 0U, 18U, 25U, 25U, 21U, 0U, 11U, 0U, 12U, 28U, 25U, 30U, 18U, 11U, 41U, 0U, 31U, 26U, 43U, WINDOW_TEXT_END,
};

/* Messages for pawn*/
const UINT8 win_txt_pawn_int[] = {
    12U, 31U, 35U, 0U, 29U, 25U, 23U, 15U, 30U, 18U, 19U, 24U, 17U, 0U, 25U, 28U, 0U, 17U, 15U, 30U, 0U, 30U, 18U, 15U, 0U, 18U, 15U, 22U, 22U, 0U, 25U, 31U, 30U, 38U, 0U, 26U, 31U, 24U, 21U, 37U, WINDOW_TEXT_END,
};

/* Messages for rob*/
const UINT8 win_txt_rob_caught[] = {
    35U, 25U, 31U, 0U, 17U, 25U, 30U, 0U, 13U, 11U, 31U, 17U, 18U, 30U, 39U, 39U, 39U, 0U, 35U, 25U, 31U, 28U, 0U, 13U, 18U, 11U, 28U, 23U, 0U, 33U, 11U, 29U, 24U, 41U, 30U, 0U, 15U, 24U, 25U, 31U, 17U, 18U, 0U, 30U, 25U, 0U, 26U, 31U, 22U, 22U, 0U, 19U, 30U, 0U, 25U, 16U, 16U, 38U, 0U, 25U, 28U, 0U, 35U, 25U, 31U, 0U, 20U, 31U, 29U, 30U, 0U, 33U, 15U, 28U, 15U, 24U, 41U, 30U, 0U, 22U, 31U, 13U, 21U, 35U, 0U, 15U, 24U, 25U, 31U, 17U, 18U, 37U, 0U, 19U, 24U, 0U, 15U, 19U, 30U, 18U, 15U, 28U, 0U, 13U, 11U, 29U, 15U, 38U, 0U, 35U, 25U, 31U, 0U, 17U, 25U, 30U, 0U, 30U, 18U, 28U, 25U, 33U, 24U, 0U, 19U, 24U, 0U, 20U, 11U, 19U, 22U, 0U, 16U, 25U, 28U, 0U, 6U, 0U, 14U, 11U, 35U, 29U, 37U, WINDOW_TEXT_END,
};

const UINT8 win_txt_rob_success[] = {
    35U, 25U, 31U, 0U, 14U, 19U, 14U, 0U, 19U, 30U, 39U, 39U, 39U, 0U, 11U, 16U, 30U, 15U, 28U, 0U, 13U, 11U, 29U, 19U, 24U, 17U, 0U, 30U, 18U, 15U, 0U, 20U, 25U, 19U, 24U, 30U, 38U, 0U, 35U, 25U, 31U, 0U, 13U, 11U, 23U, 15U, 0U, 12U, 11U, 13U, 21U, 0U, 11U, 30U, 0U, 23U, 19U, 14U, 24U, 19U, 17U, 18U, 30U, 0U, 30U, 25U, 0U, 13U, 22U, 15U, 11U, 24U, 0U, 30U, 18U, 15U, 0U, 26U, 22U, 11U, 13U, 15U, 0U, 25U, 31U, 30U, 37U, 0U, 35U, 25U, 31U, 0U, 23U, 11U, 14U, 15U, 0U, 25U, 16U, 16U, 0U, 33U, 19U, 30U, 18U, 0U, 40U, WINDOW_TEXT_SKIP, WINDOW_TEXT_SKIP, WINDOW_TEXT_SKIP, WINDOW_TEXT_END,
};

/* Messages for general*/
const UINT8 win_txt_general_unimplemented[] = {
    29U, 25U, 28U, 28U, 35U, 39U, 0U, 30U, 18U, 19U, 29U, 0U, 19U, 29U, 24U, 41U, 30U, 0U, 11U, 32U, 11U, 19U, 22U, 11U, 12U, 22U, 15U, 0U, 35U, 15U, 30U, 38U, 0U, 12U, 28U, 25U, 41U, 39U, 0U, 13U, 18U, 15U, 13U, 21U, 0U, 12U, 11U, 13U, 21U, 0U, 29U, 25U, 25U, 24U, 0U, 11U, 24U, 14U, 0U, 21U, 15U, 15U, 26U, 0U, 11U, 24U, 0U, 15U, 35U, 15U, 0U, 25U, 24U, 0U, 23U, 11U, 30U, 30U, 18U, 15U, 33U, 20U, 25U, 18U, 24U, 0U, 17U, 19U, 30U, 18U, 31U, 12U, 39U, 39U, WINDOW_TEXT_END,
};

/* Messages for nli*/
const UINT8 win_txt_nli_vp[] = {
    13U, 25U, 24U, 17U, 28U, 11U, 30U, 31U, 22U, 11U, 30U, 19U, 25U, 24U, 29U, 39U, 0U, 35U, 25U, 31U, 0U, 11U, 28U, 15U, 0U, 24U, 25U, 33U, 0U, 11U, 0U, 32U, 26U, 37U, 0U, 35U, 25U, 31U, 28U, 0U, 33U, 11U, 17U, 15U, 0U, 19U, 29U, 0U, 24U, 25U, 33U, 0U, 40U, 6U, 1U, 0U, 26U, 15U, 28U, 0U, 18U, 25U, 31U, 28U, 37U, WINDOW_TEXT_END,
};

const UINT8 win_txt_nli_exec[] = {
    13U, 25U, 24U, 17U, 28U, 11U, 30U, 31U, 22U, 11U, 30U, 19U, 25U, 24U, 29U, 39U, 0U, 35U, 25U, 31U, 0U, 11U, 28U, 15U, 0U, 24U, 25U, 33U, 0U, 11U, 0U, 15U, 34U, 15U, 13U, 31U, 30U, 19U, 32U, 15U, 37U, 0U, 35U, 25U, 31U, 28U, 0U, 33U, 11U, 17U, 15U, 0U, 19U, 29U, 0U, 24U, 25U, 33U, 0U, 40U, 3U, 6U, 0U, 26U, 15U, 28U, 0U, 18U, 25U, 31U, 28U, 37U, WINDOW_TEXT_END,
};

const UINT8 win_txt_nli_ceo[] = {
    13U, 25U, 24U, 17U, 28U, 11U, 30U, 31U, 22U, 11U, 30U, 19U, 25U, 24U, 29U, 39U, 0U, 35U, 25U, 31U, 0U, 11U, 28U, 15U, 0U, 24U, 25U, 33U, 0U, 11U, 0U, 13U, 15U, 25U, 37U, 0U, 35U, 25U, 31U, 28U, 0U, 33U, 11U, 17U, 15U, 0U, 19U, 29U, 0U, 24U, 25U, 33U, 0U, 40U, 2U, 1U, 1U, 0U, 26U, 15U, 28U, 0U, 18U, 25U, 31U, 28U, 37U, WINDOW_TEXT_END,
};

const UINT8 win_txt_nli_sales[] = {
    13U, 25U, 24U, 17U, 28U, 11U, 30U, 31U, 22U, 11U, 30U, 19U, 25U, 24U, 29U, 39U, 0U, 35U, 25U, 31U, 0U, 11U, 28U, 15U, 0U, 24U, 25U, 33U, 0U, 11U, 0U, 29U, 11U, 22U, 15U, 29U, 23U, 11U, 24U, 37U, 0U, 35U, 25U, 31U, 28U, 0U, 33U, 11U, 17U, 15U, 0U, 19U, 29U, 0U, 24U, 25U, 33U, 0U, 40U, 2U, 6U, 0U, 26U, 15U, 28U, 0U, 18U, 25U, 31U, 28U, 37U, WINDOW_TEXT_END,
};

const UINT8 win_txt_nli_jan[] = {
    13U, 25U, 24U, 17U, 28U, 11U, 30U, 31U, 22U, 11U, 30U, 19U, 25U, 24U, 29U, 39U, 0U, 35U, 25U, 31U, 0U, 11U, 28U, 15U, 0U, 24U, 25U, 33U, 0U, 11U, 0U, 20U, 11U, 24U, 19U, 30U, 25U, 28U, 37U, 0U, 35U, 25U, 31U, 28U, 0U, 33U, 11U, 17U, 15U, 0U, 19U, 29U, 0U, 24U, 25U, 33U, 0U, 40U, 9U, 0U, 26U, 15U, 28U, 0U, 18U, 25U, 31U, 28U, 37U, WINDOW_TEXT_END,
};

const UINT8 win_txt_nli_mail[] = {
    13U, 25U, 24U, 17U, 28U, 11U, 30U, 31U, 22U, 11U, 30U, 19U, 25U, 24U, 29U, 39U, 0U, 35U, 25U, 31U, 0U, 11U, 28U, 15U, 0U, 24U, 25U, 33U, 0U, 11U, 0U, 23U, 11U, 19U, 22U, 0U, 13U, 22U, 15U, 28U, 21U, 37U, 0U, 35U, 25U, 31U, 28U, 0U, 33U, 11U, 17U, 15U, 0U, 19U, 29U, 0U, 24U, 25U, 33U, 0U, 40U, 2U, 1U, 0U, 26U, 15U, 28U, 0U, 18U, 25U, 31U, 28U, 37U, WINDOW_TEXT_END,
};

const UINT8 win_txt_nli_no_int[] = {
    30U, 18U, 11U, 24U, 21U, 0U, 35U, 25U, 31U, 0U, 16U, 25U, 28U, 0U, 11U, 26U, 26U, 22U, 35U, 19U, 24U, 17U, 37U, 0U, 31U, 24U, 16U, 25U, 28U, 30U, 31U, 24U, 11U, 30U, 15U, 22U, 35U, 38U, 0U, 35U, 25U, 31U, 0U, 16U, 11U, 19U, 22U, 15U, 14U, 0U, 30U, 18U, 15U, 0U, 11U, 26U, 30U, 19U, 30U, 31U, 14U, 15U, 0U, 30U, 15U, 29U, 30U, 37U, 0U, 12U, 15U, 30U, 30U, 15U, 28U, 0U, 22U, 31U, 13U, 21U, 0U, 24U, 15U, 34U, 30U, 0U, 30U, 19U, 23U, 15U, 39U, WINDOW_TEXT_END,
};

/* Messages for dealer*/
const UINT8 win_txt_dealer_int[] = {
    18U, 15U, 35U, 0U, 23U, 11U, 24U, 38U, 0U, 13U, 25U, 23U, 15U, 0U, 25U, 32U, 15U, 28U, 0U, 18U, 15U, 28U, 15U, 0U, 16U, 25U, 28U, 0U, 11U, 0U, 23U, 19U, 24U, 31U, 30U, 15U, 37U, 0U, 35U, 25U, 31U, 0U, 33U, 11U, 24U, 24U, 11U, 0U, 29U, 15U, 15U, 0U, 29U, 25U, 23U, 15U, 0U, 14U, 25U, 26U, 15U, 44U, 16U, 22U, 35U, 0U, 29U, 18U, 19U, 30U, 43U, 0U, 19U, 41U, 23U, 0U, 30U, 15U, 22U, 22U, 19U, 24U, 41U, 0U, 35U, 11U, 41U, 0U, 23U, 11U, 24U, 38U, 0U, 35U, 25U, 31U, 0U, 13U, 11U, 24U, 0U, 23U, 11U, 21U, 15U, 0U, 29U, 25U, 23U, 15U, 0U, 16U, 11U, 30U, 0U, 29U, 30U, 11U, 13U, 21U, 29U, 0U, 25U, 16U, 16U, 0U, 30U, 18U, 19U, 29U, 0U, 26U, 28U, 25U, 14U, 31U, 13U, 30U, 39U, WINDOW_TEXT_END,
};

/* Messages for hobo*/
const UINT8 win_txt_hobo_int[] = {
    13U, 25U, 31U, 22U, 14U, 0U, 35U, 25U, 31U, 0U, 29U, 26U, 11U, 28U, 15U, 0U, 29U, 25U, 23U, 15U, 0U, 13U, 18U, 11U, 24U, 17U, 15U, 43U, WINDOW_TEXT_END,
};

const UINT8 win_txt_hobo_give_1[] = {
    33U, 18U, 35U, 0U, 30U, 18U, 11U, 24U, 21U, 0U, 35U, 25U, 31U, 39U, 0U, 33U, 18U, 11U, 30U, 0U, 11U, 0U, 13U, 18U, 11U, 28U, 23U, 19U, 24U, 17U, 0U, 17U, 15U, 29U, 30U, 31U, 28U, 15U, 37U, 37U, 37U, 0U, 42U, 23U, 31U, 23U, 12U, 22U, 15U, 42U, WINDOW_TEXT_END,
};

const UINT8 win_txt_hobo_give_2[] = {
    30U, 18U, 11U, 24U, 21U, 0U, 35U, 25U, 31U, 0U, 21U, 19U, 24U, 14U, 22U, 35U, 0U, 29U, 19U, 28U, 39U, 0U, 33U, 18U, 19U, 13U, 18U, 0U, 28U, 15U, 23U, 19U, 24U, 14U, 29U, 0U, 23U, 15U, 0U, 25U, 16U, 0U, 11U, 0U, 29U, 30U, 25U, 28U, 35U, 37U, 37U, 37U, 0U, 42U, 23U, 31U, 23U, 12U, 22U, 15U, 42U, 37U, 37U, 0U, 29U, 25U, 0U, 19U, 0U, 29U, 11U, 35U, 29U, 0U, 16U, 28U, 11U, 24U, 21U, 0U, 33U, 11U, 29U, 0U, 13U, 28U, 11U, 36U, 35U, 39U, 0U, 13U, 28U, 11U, 36U, 36U, 35U, 39U, 0U, 42U, 23U, 31U, 23U, 12U, 22U, 15U, 42U, 37U, 37U, 37U, 0U, 11U, 24U, 14U, 0U, 30U, 18U, 11U, 30U, 41U, 29U, 0U, 33U, 18U, 35U, 0U, 19U, 0U, 24U, 15U, 32U, 15U, 28U, 0U, 33U, 15U, 24U, 30U, 0U, 12U, 11U, 13U, 21U, 0U, 30U, 25U, 0U, 32U, 19U, 13U, 15U, 0U, 26U, 25U, 19U, 24U, 30U, 0U, 23U, 11U, 22U, 22U, 37U, WINDOW_TEXT_END,
};

const UINT8 win_txt_hobo_give_3[] = {
    23U, 11U, 24U, 35U, 0U, 30U, 18U, 11U, 24U, 21U, 29U, 39U, 0U, 42U, 23U, 31U, 23U, 12U, 22U, 15U, 42U, 37U, 37U, 37U, 0U, 12U, 11U, 13U, 21U, 0U, 30U, 18U, 15U, 24U, 38U, 0U, 11U, 22U, 22U, 0U, 33U, 15U, 0U, 18U, 11U, 14U, 0U, 33U, 11U, 29U, 0U, 28U, 25U, 13U, 21U, 29U, 0U, 11U, 24U, 14U, 0U, 18U, 11U, 30U, 29U, 0U, 30U, 25U, 0U, 26U, 22U, 11U, 35U, 0U, 33U, 19U, 30U, 18U, 37U, 0U, 11U, 24U, 14U, 0U, 35U, 25U, 31U, 0U, 13U, 11U, 24U, 41U, 30U, 0U, 15U, 11U, 30U, 0U, 28U, 25U, 13U, 21U, 29U, 38U, 0U, 35U, 25U, 31U, 0U, 21U, 24U, 25U, 33U, 37U, WINDOW_TEXT_END,
};

const UINT8 win_txt_hobo_booze_1[] = {
    12U, 25U, 25U, 36U, 15U, 39U, 0U, 26U, 28U, 15U, 13U, 19U, 25U, 31U, 29U, 0U, 12U, 25U, 25U, 36U, 15U, 39U, WINDOW_TEXT_END,
};

const UINT8 win_txt_hobo_booze_3[] = {
    42U, 29U, 22U, 31U, 31U, 31U, 28U, 26U, 42U, 37U, 37U, 0U, 19U, 0U, 30U, 18U, 19U, 24U, 21U, 0U, 19U, 41U, 32U, 15U, 0U, 17U, 25U, 24U, 15U, 0U, 12U, 22U, 19U, 24U, 14U, 37U, 37U, 0U, 42U, 18U, 19U, 13U, 42U, WINDOW_TEXT_END,
};

const UINT8 win_txt_hobo_booze_2[] = {
    42U, 18U, 19U, 13U, 42U, 37U, 37U, 37U, 0U, 19U, 37U, 37U, 19U, 37U, 37U, 37U, 19U, 41U, 23U, 0U, 24U, 25U, 30U, 0U, 11U, 29U, 0U, 30U, 18U, 19U, 24U, 21U, 0U, 11U, 29U, 0U, 35U, 25U, 31U, 0U, 14U, 28U, 31U, 24U, 21U, 0U, 19U, 0U, 11U, 23U, 37U, 37U, 0U, 42U, 12U, 31U, 28U, 26U, 42U, 37U, 37U, 0U, 19U, 0U, 13U, 25U, 31U, 22U, 14U, 0U, 31U, 29U, 15U, 0U, 29U, 25U, 23U, 15U, 0U, 23U, 25U, 28U, 15U, 38U, 0U, 17U, 25U, 25U, 14U, 0U, 29U, 19U, 28U, 37U, 37U, 0U, 42U, 18U, 19U, 13U, 42U, WINDOW_TEXT_END,
};

/* Messages for bar*/
const UINT8 win_txt_bar_int[] = {
    15U, 22U, 22U, 25U, 41U, 38U, 0U, 19U, 41U, 23U, 0U, 29U, 30U, 19U, 13U, 21U, 35U, 37U, 0U, 33U, 18U, 11U, 30U, 41U, 29U, 0U, 35U, 15U, 28U, 41U, 0U, 26U, 25U, 19U, 29U, 25U, 24U, 38U, 0U, 23U, 11U, 30U, 15U, 43U, WINDOW_TEXT_END,
};

/* Messages for restaurant*/
const UINT8 win_txt_restaurant_int[] = {
    33U, 15U, 22U, 13U, 25U, 23U, 15U, 0U, 30U, 25U, 0U, 23U, 13U, 29U, 30U, 19U, 13U, 21U, 29U, 38U, 0U, 23U, 11U, 35U, 0U, 19U, 0U, 30U, 11U, 21U, 15U, 0U, 35U, 25U, 31U, 28U, 0U, 25U, 28U, 14U, 15U, 28U, 43U, WINDOW_TEXT_END,
};

/* Messages for bus_statn*/
const UINT8 win_txt_bus_statn_no_mon[] = {
    35U, 25U, 31U, 0U, 14U, 25U, 0U, 24U, 25U, 30U, 0U, 18U, 11U, 32U, 15U, 0U, 15U, 24U, 25U, 31U, 17U, 18U, 0U, 23U, 25U, 24U, 15U, 35U, 0U, 30U, 25U, 0U, 30U, 28U, 11U, 32U, 15U, 22U, 37U, WINDOW_TEXT_END,
};

const UINT8 win_txt_bus_statn_no_deal[] = {
    35U, 25U, 31U, 41U, 32U, 15U, 0U, 11U, 28U, 28U, 19U, 32U, 15U, 14U, 0U, 19U, 24U, 0U, 30U, 18U, 15U, 0U, 13U, 19U, 30U, 35U, 0U, 12U, 31U, 30U, 0U, 13U, 11U, 24U, 41U, 30U, 0U, 16U, 19U, 24U, 14U, 0U, 11U, 24U, 35U, 25U, 24U, 15U, 0U, 30U, 25U, 0U, 12U, 31U, 35U, 0U, 16U, 28U, 25U, 23U, 0U, 35U, 25U, 31U, 37U, 0U, 0U, 12U, 15U, 30U, 30U, 15U, 28U, 0U, 22U, 31U, 13U, 21U, 0U, 24U, 15U, 34U, 30U, 0U, 30U, 19U, 23U, 15U, 38U, 0U, 13U, 18U, 31U, 23U, 26U, 37U, WINDOW_TEXT_END,
};

const UINT8 win_txt_bus_statn_no_phone[] = {
    11U, 16U, 30U, 15U, 28U, 0U, 11U, 28U, 28U, 19U, 32U, 19U, 24U, 17U, 38U, 0U, 35U, 25U, 31U, 0U, 29U, 26U, 15U, 24U, 14U, 0U, 30U, 18U, 15U, 0U, 15U, 24U, 30U, 19U, 28U, 15U, 0U, 14U, 11U, 35U, 0U, 22U, 25U, 25U, 21U, 19U, 24U, 17U, 0U, 16U, 25U, 28U, 0U, 26U, 15U, 25U, 26U, 22U, 15U, 0U, 33U, 18U, 25U, 0U, 33U, 19U, 22U, 22U, 0U, 12U, 31U, 35U, 0U, 16U, 28U, 25U, 23U, 0U, 35U, 25U, 31U, 38U, 0U, 12U, 31U, 30U, 0U, 24U, 25U, 0U, 25U, 24U, 15U, 0U, 33U, 11U, 24U, 30U, 29U, 0U, 30U, 25U, 0U, 14U, 15U, 11U, 22U, 0U, 33U, 19U, 30U, 18U, 0U, 11U, 0U, 26U, 31U, 24U, 21U, 0U, 33U, 19U, 30U, 18U, 25U, 31U, 30U, 0U, 11U, 0U, 13U, 15U, 22U, 22U, 0U, 26U, 18U, 25U, 24U, 15U, 37U, 0U, 18U, 25U, 33U, 0U, 11U, 28U, 15U, 0U, 30U, 18U, 15U, 35U, 0U, 29U, 31U, 26U, 26U, 25U, 29U, 15U, 14U, 0U, 30U, 25U, 0U, 13U, 11U, 22U, 22U, 0U, 35U, 25U, 31U, 0U, 16U, 25U, 28U, 0U, 29U, 31U, 26U, 26U, 22U, 35U, 0U, 33U, 18U, 15U, 24U, 0U, 41U, 30U, 18U, 15U, 0U, 13U, 28U, 11U, 32U, 19U, 24U, 17U, 41U, 0U, 29U, 15U, 30U, 29U, 0U, 19U, 24U, 43U, 43U, WINDOW_TEXT_END,
};

const UINT8 win_txt_bus_statn_no_ammo[] = {
    11U, 0U, 17U, 11U, 24U, 17U, 0U, 25U, 16U, 0U, 29U, 30U, 28U, 15U, 15U, 30U, 0U, 30U, 25U, 31U, 17U, 18U, 29U, 0U, 33U, 19U, 30U, 18U, 0U, 12U, 11U, 29U, 15U, 12U, 11U, 22U, 22U, 0U, 12U, 11U, 30U, 29U, 0U, 15U, 35U, 15U, 0U, 35U, 25U, 31U, 0U, 31U, 26U, 37U, 0U, 35U, 25U, 31U, 0U, 26U, 31U, 22U, 22U, 0U, 25U, 31U, 30U, 0U, 35U, 25U, 31U, 28U, 0U, 17U, 31U, 24U, 0U, 11U, 24U, 14U, 0U, 16U, 19U, 28U, 15U, 37U, 37U, 37U, 42U, 13U, 22U, 19U, 13U, 21U, 42U, 0U, 0U, 35U, 25U, 31U, 41U, 32U, 15U, 0U, 17U, 25U, 30U, 0U, 24U, 25U, 0U, 12U, 31U, 22U, 22U, 15U, 30U, 29U, 37U, 0U, 30U, 18U, 15U, 35U, 0U, 18U, 11U, 32U, 15U, 0U, 11U, 0U, 18U, 25U, 23U, 15U, 28U, 31U, 24U, 0U, 14U, 15U, 28U, 12U, 35U, 0U, 13U, 25U, 24U, 30U, 15U, 29U, 30U, 0U, 25U, 24U, 0U, 35U, 25U, 31U, 28U, 0U, 11U, 29U, 29U, 0U, 11U, 24U, 14U, 0U, 30U, 11U, 21U, 15U, 0U, 35U, 25U, 31U, 28U, 0U, 29U, 30U, 11U, 29U, 18U, 0U, 11U, 24U, 14U, 0U, 23U, 25U, 24U, 15U, 35U, 37U, WINDOW_TEXT_END,
};

const UINT8 win_txt_bus_statn_bust[] = {
    28U, 25U, 22U, 22U, 19U, 24U, 17U, 0U, 19U, 24U, 30U, 25U, 0U, 30U, 25U, 33U, 24U, 0U, 33U, 19U, 30U, 18U, 0U, 26U, 19U, 22U, 15U, 29U, 0U, 25U, 16U, 0U, 26U, 28U, 25U, 14U, 31U, 13U, 30U, 0U, 11U, 30U, 30U, 11U, 13U, 30U, 15U, 14U, 0U, 26U, 22U, 15U, 24U, 30U, 35U, 0U, 25U, 16U, 0U, 11U, 30U, 30U, 15U, 24U, 30U, 19U, 25U, 24U, 0U, 44U, 0U, 16U, 28U, 25U, 23U, 0U, 30U, 18U, 15U, 0U, 13U, 25U, 26U, 29U, 37U, 0U, 30U, 18U, 15U, 35U, 0U, 13U, 25U, 24U, 16U, 19U, 29U, 13U, 11U, 30U, 15U, 0U, 35U, 25U, 31U, 28U, 0U, 17U, 25U, 25U, 14U, 29U, 38U, 0U, 35U, 25U, 31U, 28U, 0U, 17U, 31U, 24U, 38U, 0U, 11U, 24U, 14U, 0U, 35U, 25U, 31U, 28U, 0U, 16U, 28U, 15U, 15U, 14U, 25U, 23U, 45U, 0U, 35U, 25U, 31U, 0U, 29U, 15U, 28U, 32U, 15U, 0U, 30U, 18U, 15U, 0U, 24U, 15U, 34U, 30U, 0U, 6U, 0U, 14U, 11U, 35U, 29U, 0U, 19U, 24U, 0U, 29U, 30U, 11U, 30U, 15U, 0U, 26U, 15U, 24U, 37U, WINDOW_TEXT_END,
};

const UINT8 win_txt_bus_statn_coke_deal[] = {
    35U, 25U, 31U, 41U, 32U, 15U, 0U, 11U, 28U, 28U, 19U, 32U, 15U, 14U, 0U, 19U, 24U, 0U, 30U, 18U, 15U, 0U, 13U, 19U, 30U, 35U, 0U, 11U, 24U, 14U, 0U, 18U, 11U, 32U, 15U, 0U, 28U, 15U, 13U, 15U, 19U, 32U, 15U, 14U, 0U, 11U, 24U, 0U, 25U, 16U, 16U, 15U, 28U, 0U, 25U, 16U, 0U, 0U, 0U, 0U, 40U, WINDOW_TEXT_SKIP, WINDOW_TEXT_SKIP, WINDOW_TEXT_SKIP, WINDOW_TEXT_SKIP, WINDOW_TEXT_SKIP, 0U, 16U, 25U, 28U, 0U, WINDOW_TEXT_SKIP, WINDOW_TEXT_SKIP, 0U, 13U, 25U, 13U, 11U, 19U, 24U, 15U, 37U, 37U, 37U, 0U, 14U, 25U, 0U, 35U, 25U, 31U, 0U, 11U, 13U, 13U, 15U, 26U, 30U, 43U, 0U, 11U, 0U, 30U, 25U, 0U, 11U, 13U, 13U, 15U, 26U, 30U, 37U, 0U, 12U, 0U, 30U, 25U, 0U, 14U, 15U, 13U, 22U, 19U, 24U, 15U, WINDOW_TEXT_END,
};

const UINT8 win_txt_bus_statn_late[] = {
    12U, 31U, 29U, 0U, 22U, 15U, 11U, 32U, 15U, 29U, 0U, 16U, 19U, 28U, 29U, 30U, 0U, 30U, 18U, 19U, 24U, 17U, 0U, 19U, 24U, 0U, 30U, 18U, 15U, 0U, 23U, 25U, 28U, 24U, 19U, 24U, 17U, 37U, WINDOW_TEXT_END,
};

const UINT8 win_txt_bus_statn_bad[] = {
    35U, 25U, 31U, 0U, 23U, 15U, 15U, 30U, 0U, 29U, 25U, 23U, 15U, 0U, 24U, 15U, 33U, 0U, 13U, 25U, 24U, 30U, 11U, 13U, 30U, 29U, 0U, 12U, 15U, 18U, 19U, 24U, 14U, 0U, 11U, 24U, 0U, 11U, 12U, 11U, 24U, 14U, 25U, 24U, 15U, 14U, 0U, 12U, 31U, 19U, 22U, 14U, 19U, 24U, 17U, 37U, 0U, 29U, 31U, 14U, 14U, 15U, 24U, 22U, 35U, 0U, 35U, 25U, 31U, 0U, 17U, 15U, 30U, 0U, 18U, 19U, 30U, 0U, 16U, 28U, 25U, 23U, 0U, 12U, 15U, 18U, 19U, 24U, 14U, 0U, 12U, 35U, 0U, 11U, 0U, 12U, 22U, 31U, 24U, 30U, 0U, 25U, 12U, 20U, 15U, 13U, 30U, 37U, 0U, 11U, 29U, 0U, 35U, 25U, 31U, 0U, 22U, 19U, 15U, 0U, 25U, 24U, 0U, 30U, 18U, 15U, 0U, 26U, 11U, 32U, 15U, 23U, 15U, 24U, 30U, 38U, 0U, 35U, 25U, 31U, 0U, 28U, 15U, 11U, 22U, 19U, 36U, 15U, 0U, 33U, 18U, 11U, 30U, 0U, 20U, 31U, 29U, 30U, 0U, 18U, 11U, 26U, 26U, 15U, 24U, 15U, 14U, 45U, 0U, 35U, 25U, 31U, 41U, 32U, 15U, 0U, 12U, 15U, 15U, 24U, 0U, 29U, 13U, 28U, 15U, 33U, 15U, 14U, 39U, 0U, 35U, 25U, 31U, 28U, 0U, 29U, 30U, 11U, 29U, 18U, 0U, 17U, 25U, 30U, 0U, 20U, 11U, 13U, 21U, 15U, 14U, 37U, WINDOW_TEXT_END,
};

const UINT8 win_txt_bus_statn_no_gun_3[] = {
    11U, 0U, 26U, 19U, 23U, 26U, 0U, 17U, 19U, 32U, 15U, 29U, 0U, 35U, 25U, 31U, 0U, 14U, 19U, 28U, 15U, 13U, 30U, 19U, 25U, 24U, 29U, 0U, 12U, 11U, 13U, 21U, 0U, 30U, 25U, 0U, 30U, 18U, 15U, 0U, 12U, 31U, 29U, 0U, 29U, 30U, 11U, 30U, 19U, 25U, 24U, 38U, 0U, 30U, 18U, 15U, 24U, 0U, 28U, 25U, 12U, 29U, 0U, 35U, 25U, 31U, 37U, 0U, 35U, 25U, 31U, 41U, 32U, 15U, 0U, 22U, 25U, 29U, 30U, 0U, 11U, 22U, 22U, 0U, 35U, 25U, 31U, 28U, 0U, 23U, 25U, 24U, 15U, 35U, 0U, 11U, 24U, 14U, 0U, 35U, 25U, 31U, 28U, 0U, 29U, 30U, 11U, 29U, 18U, 37U, WINDOW_TEXT_END,
};

const UINT8 win_txt_bus_statn_no_gun_2[] = {
    35U, 25U, 31U, 0U, 11U, 28U, 15U, 0U, 20U, 31U, 23U, 26U, 15U, 14U, 0U, 12U, 35U, 0U, 4U, 0U, 17U, 31U, 35U, 29U, 0U, 11U, 24U, 14U, 0U, 11U, 0U, 13U, 18U, 19U, 13U, 21U, 37U, 0U, 30U, 18U, 15U, 35U, 0U, 30U, 11U, 21U, 15U, 0U, 11U, 22U, 22U, 0U, 35U, 25U, 31U, 28U, 0U, 23U, 25U, 24U, 15U, 35U, 0U, 11U, 24U, 14U, 0U, 35U, 25U, 31U, 28U, 0U, 29U, 30U, 11U, 29U, 18U, 37U, 0U, 23U, 11U, 35U, 12U, 15U, 0U, 35U, 25U, 31U, 0U, 29U, 18U, 25U, 31U, 22U, 14U, 0U, 12U, 15U, 0U, 26U, 11U, 13U, 21U, 19U, 24U, 41U, 0U, 18U, 15U, 11U, 30U, 0U, 24U, 15U, 34U, 30U, 0U, 30U, 19U, 23U, 15U, 37U, WINDOW_TEXT_END,
};

const UINT8 win_txt_bus_statn_no_gun_1[] = {
    35U, 25U, 31U, 0U, 11U, 28U, 15U, 0U, 28U, 25U, 12U, 12U, 15U, 14U, 0U, 25U, 16U, 0U, 11U, 22U, 22U, 0U, 35U, 25U, 31U, 28U, 0U, 23U, 25U, 24U, 15U, 35U, 0U, 11U, 24U, 14U, 0U, 29U, 30U, 11U, 29U, 18U, 0U, 12U, 35U, 0U, 11U, 0U, 30U, 28U, 11U, 32U, 15U, 22U, 19U, 24U, 17U, 0U, 26U, 11U, 13U, 21U, 0U, 25U, 16U, 0U, 22U, 25U, 33U, 44U, 28U, 11U, 30U, 15U, 0U, 22U, 11U, 33U, 35U, 15U, 28U, 29U, 37U, 0U, 0U, 24U, 15U, 34U, 30U, 0U, 30U, 19U, 23U, 15U, 38U, 0U, 26U, 11U, 13U, 21U, 0U, 29U, 25U, 23U, 15U, 0U, 26U, 28U, 25U, 30U, 15U, 13U, 30U, 19U, 25U, 24U, 37U, WINDOW_TEXT_END,
};

const UINT8 win_txt_bus_statn_rob_1[] = {
    35U, 25U, 31U, 0U, 11U, 13U, 13U, 19U, 14U, 15U, 24U, 30U, 11U, 22U, 22U, 35U, 0U, 30U, 28U, 11U, 13U, 21U, 0U, 14U, 25U, 17U, 0U, 13U, 28U, 11U, 26U, 0U, 25U, 24U, 30U, 25U, 0U, 11U, 0U, 17U, 19U, 28U, 22U, 0U, 29U, 13U, 25U, 31U, 30U, 0U, 17U, 28U, 25U, 31U, 26U, 41U, 29U, 0U, 18U, 25U, 26U, 0U, 29U, 13U, 25U, 30U, 13U, 18U, 0U, 22U, 11U, 35U, 25U, 31U, 30U, 37U, 0U, 30U, 28U, 25U, 25U, 26U, 0U, 7U, 2U, 0U, 22U, 15U, 11U, 32U, 15U, 29U, 0U, 35U, 25U, 31U, 0U, 22U, 35U, 19U, 24U, 17U, 0U, 25U, 24U, 0U, 30U, 18U, 15U, 0U, 29U, 30U, 28U, 15U, 15U, 30U, 0U, 33U, 19U, 30U, 18U, 0U, 24U, 25U, 0U, 13U, 11U, 29U, 18U, 0U, 11U, 24U, 14U, 0U, 24U, 25U, 0U, 29U, 30U, 11U, 29U, 18U, 38U, 0U, 11U, 24U, 14U, 0U, 11U, 0U, 23U, 25U, 31U, 30U, 18U, 16U, 31U, 22U, 0U, 25U, 16U, 0U, 29U, 30U, 11U, 22U, 15U, 0U, 13U, 25U, 25U, 21U, 19U, 15U, 29U, 37U, 0U, 23U, 11U, 35U, 12U, 15U, 0U, 35U, 25U, 31U, 0U, 29U, 18U, 25U, 31U, 22U, 14U, 0U, 12U, 31U, 16U, 16U, 0U, 31U, 26U, 0U, 11U, 0U, 12U, 19U, 30U, 0U, 23U, 25U, 28U, 15U, 37U, WINDOW_TEXT_END,
};

const UINT8 win_txt_bus_statn_rob_3[] = {
    24U, 25U, 30U, 0U, 26U, 11U, 35U, 19U, 24U, 17U, 0U, 11U, 30U, 30U, 15U, 24U, 30U, 19U, 25U, 24U, 38U, 0U, 35U, 25U, 31U, 0U, 29U, 22U, 19U, 26U, 0U, 25U, 24U, 0U, 11U, 0U, 31U, 29U, 15U, 14U, 0U, 13U, 25U, 24U, 14U, 25U, 23U, 0U, 11U, 24U, 14U, 0U, 18U, 19U, 30U, 0U, 35U, 25U, 31U, 28U, 0U, 18U, 15U, 11U, 14U, 0U, 25U, 24U, 0U, 11U, 0U, 26U, 11U, 28U, 21U, 0U, 12U, 15U, 24U, 13U, 18U, 37U, 0U, 12U, 22U, 15U, 15U, 14U, 19U, 24U, 17U, 0U, 26U, 28U, 25U, 16U, 31U, 29U, 15U, 22U, 35U, 38U, 0U, 35U, 25U, 31U, 0U, 13U, 11U, 24U, 0U, 25U, 24U, 22U, 35U, 0U, 33U, 11U, 30U, 13U, 18U, 0U, 11U, 29U, 0U, 29U, 27U, 31U, 19U, 28U, 28U, 15U, 22U, 29U, 0U, 23U, 11U, 21U, 15U, 0U, 25U, 16U, 16U, 0U, 33U, 19U, 30U, 18U, 0U, 35U, 25U, 31U, 28U, 0U, 33U, 11U, 22U, 22U, 15U, 30U, 0U, 11U, 24U, 14U, 0U, 29U, 30U, 11U, 29U, 18U, 37U, 0U, 30U, 25U, 31U, 17U, 18U, 15U, 24U, 41U, 0U, 31U, 26U, 39U, WINDOW_TEXT_END,
};

const UINT8 win_txt_bus_statn_rob_2[] = {
    35U, 25U, 31U, 0U, 13U, 25U, 23U, 15U, 0U, 11U, 13U, 28U, 25U, 29U, 29U, 0U, 11U, 0U, 14U, 11U, 28U, 21U, 0U, 11U, 22U, 22U, 15U, 35U, 37U, 0U, 30U, 18U, 28U, 15U, 15U, 0U, 22U, 11U, 28U, 17U, 15U, 0U, 13U, 11U, 30U, 29U, 0U, 11U, 30U, 30U, 11U, 13U, 21U, 0U, 35U, 25U, 31U, 0U, 16U, 28U, 25U, 23U, 0U, 11U, 22U, 22U, 0U, 29U, 19U, 14U, 15U, 29U, 38U, 0U, 22U, 15U, 11U, 32U, 19U, 24U, 17U, 0U, 35U, 25U, 31U, 0U, 31U, 24U, 13U, 25U, 24U, 29U, 13U, 19U, 25U, 31U, 29U, 0U, 24U, 15U, 11U, 28U, 0U, 11U, 0U, 14U, 31U, 23U, 26U, 29U, 30U, 15U, 28U, 37U, 0U, 11U, 0U, 26U, 11U, 29U, 29U, 19U, 24U, 17U, 0U, 12U, 31U, 23U, 0U, 28U, 11U, 19U, 14U, 29U, 0U, 35U, 25U, 31U, 28U, 0U, 33U, 11U, 22U, 22U, 15U, 30U, 0U, 11U, 24U, 14U, 0U, 35U, 25U, 31U, 28U, 0U, 29U, 30U, 11U, 29U, 18U, 37U, 0U, 35U, 25U, 31U, 41U, 28U, 15U, 0U, 33U, 15U, 11U, 21U, 0U, 11U, 29U, 0U, 11U, 0U, 21U, 19U, 30U, 30U, 15U, 24U, 39U, WINDOW_TEXT_END,
};

const UINT8 win_txt_bus_statn_beer_deal[] = {
    35U, 25U, 31U, 41U, 32U, 15U, 0U, 11U, 28U, 28U, 19U, 32U, 15U, 14U, 0U, 19U, 24U, 0U, 30U, 18U, 15U, 0U, 13U, 19U, 30U, 35U, 0U, 11U, 24U, 14U, 0U, 18U, 11U, 32U, 15U, 0U, 28U, 15U, 13U, 15U, 19U, 32U, 15U, 14U, 0U, 11U, 24U, 0U, 25U, 16U, 16U, 15U, 28U, 0U, 25U, 16U, 0U, 0U, 0U, 0U, 40U, WINDOW_TEXT_SKIP, WINDOW_TEXT_SKIP, WINDOW_TEXT_SKIP, WINDOW_TEXT_SKIP, WINDOW_TEXT_SKIP, 0U, 16U, 25U, 28U, 0U, WINDOW_TEXT_SKIP, WINDOW_TEXT_SKIP, 0U, 12U, 15U, 15U, 28U, 37U, 37U, 37U, 0U, 14U, 25U, 0U, 35U, 25U, 31U, 0U, 11U, 13U, 13U, 15U, 26U, 30U, 43U, 0U, 11U, 0U, 30U, 25U, 0U, 11U, 13U, 13U, 15U, 26U, 30U, 37U, 0U, 12U, 0U, 30U, 25U, 0U, 14U, 15U, 13U, 22U, 19U, 24U, 15U, WINDOW_TEXT_END,
};

const UINT8 win_txt_bus_statn_no_inv[] = {
    35U, 25U, 31U, 0U, 11U, 28U, 28U, 19U, 32U, 15U, 0U, 19U, 24U, 0U, 30U, 18U, 15U, 0U, 13U, 19U, 30U, 35U, 0U, 33U, 19U, 30U, 18U, 0U, 24U, 25U, 30U, 18U, 19U, 24U, 17U, 0U, 30U, 25U, 0U, 29U, 15U, 22U, 22U, 37U, WINDOW_TEXT_END,
};

/* Messages for skater*/
const UINT8 win_txt_skater_give[] = {
    29U, 33U, 15U, 15U, 30U, 0U, 23U, 11U, 24U, 39U, 0U, 35U, 25U, 31U, 0U, 11U, 28U, 15U, 0U, 29U, 25U, 25U, 25U, 0U, 13U, 25U, 25U, 22U, 39U, 0U, 18U, 15U, 28U, 15U, 38U, 0U, 35U, 25U, 31U, 0U, 13U, 11U, 24U, 0U, 30U, 11U, 21U, 15U, 0U, 30U, 18U, 19U, 29U, 39U, 0U, 42U, 29U, 21U, 11U, 30U, 15U, 12U, 25U, 11U, 28U, 14U, 0U, 28U, 15U, 13U, 15U, 19U, 32U, 15U, 14U, 42U, WINDOW_TEXT_END,
};

const UINT8 win_txt_skater_int[] = {
    18U, 15U, 35U, 0U, 23U, 11U, 24U, 39U, 0U, 14U, 25U, 0U, 35U, 25U, 31U, 0U, 18U, 11U, 32U, 15U, 11U, 24U, 35U, 0U, 29U, 23U, 25U, 21U, 15U, 29U, 43U, 0U, 19U, 30U, 41U, 29U, 0U, 0U, 0U, 0U, 20U, 31U, 29U, 30U, 37U, 37U, 0U, 19U, 37U, 37U, 0U, 31U, 18U, 37U, 37U, 0U, 15U, 28U, 37U, 37U, 16U, 25U, 28U, 17U, 25U, 30U, 0U, 23U, 35U, 0U, 19U, 14U, 0U, 11U, 30U, 0U, 0U, 0U, 0U, 0U, 18U, 25U, 23U, 15U, 39U, 0U, 26U, 22U, 15U, 11U, 29U, 15U, 43U, WINDOW_TEXT_END,
};

const UINT8 win_txt_skater_thx_1[] = {
    42U, 13U, 25U, 31U, 17U, 18U, 0U, 13U, 25U, 31U, 17U, 18U, 42U, 0U, 29U, 33U, 15U, 15U, 15U, 30U, 37U, 37U, 37U, 0U, 42U, 18U, 11U, 13U, 21U, 42U, WINDOW_TEXT_END,
};

const UINT8 win_txt_skater_thx_2[] = {
    29U, 33U, 15U, 15U, 30U, 38U, 0U, 30U, 18U, 11U, 24U, 21U, 29U, 0U, 14U, 31U, 14U, 15U, 37U, 0U, 18U, 15U, 35U, 38U, 0U, 35U, 25U, 31U, 0U, 30U, 18U, 19U, 24U, 21U, 0U, 35U, 25U, 31U, 0U, 0U, 13U, 25U, 31U, 22U, 14U, 0U, 17U, 15U, 30U, 0U, 29U, 25U, 23U, 15U, 0U, 21U, 19U, 24U, 17U, 29U, 24U, 15U, 34U, 30U, 0U, 30U, 19U, 23U, 15U, 43U, WINDOW_TEXT_END,
};

const UINT8 win_txt_skater_thx_3[] = {
    42U, 18U, 11U, 13U, 21U, 42U, 0U, 25U, 18U, 18U, 0U, 35U, 15U, 11U, 18U, 37U, 37U, 0U, 0U, 0U, 30U, 18U, 11U, 30U, 41U, 29U, 0U, 30U, 18U, 15U, 0U, 17U, 25U, 25U, 14U, 0U, 29U, 30U, 31U, 16U, 16U, 37U, WINDOW_TEXT_END,
};

const UINT8 win_txt_skater_thx_4[] = {
    30U, 18U, 11U, 24U, 21U, 29U, 0U, 14U, 31U, 14U, 15U, 39U, 0U, 11U, 24U, 14U, 0U, 30U, 25U, 0U, 30U, 18U, 19U, 24U, 21U, 38U, 0U, 19U, 0U, 33U, 11U, 29U, 0U, 30U, 18U, 19U, 24U, 21U, 19U, 24U, 17U, 0U, 11U, 12U, 25U, 31U, 30U, 0U, 27U, 31U, 19U, 30U, 30U, 19U, 24U, 17U, 37U, 37U, 0U, 11U, 18U, 0U, 33U, 15U, 22U, 22U, 39U, 0U, 35U, 25U, 31U, 0U, 17U, 25U, 30U, 0U, 11U, 0U, 22U, 19U, 17U, 18U, 30U, 43U, WINDOW_TEXT_END,
};

