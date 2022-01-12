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

void load_building_tile_data(screen_state_t *screen_state)
{
    // Load house data from tile 8 to tile
    VBK_REG = 0;

    if (
        screen_state->displayed_buildings_x & SC_HOUSE &&
        screen_state->displayed_buildings_y & SC_HOUSE
    )
        load_house();

    if (
        screen_state->displayed_buildings_x & SC_RESTAURANT &&
        screen_state->displayed_buildings_y & SC_RESTAURANT
    )
        load_restaurant();

    if (
        screen_state->displayed_buildings_x & SC_SHOP &&
        screen_state->displayed_buildings_y & SC_SHOP
    )
        load_shop();

    if (
        screen_state->displayed_buildings_x & SC_PAWN &&
        screen_state->displayed_buildings_y & SC_PAWN
    )
        load_pawn();

    if (
        screen_state->displayed_buildings_x & SC_UNIVERSITY &&
        screen_state->displayed_buildings_y & SC_UNIVERSITY
    )
        load_university();

    if (
        screen_state->displayed_buildings_x & SC_NLI &&
        screen_state->displayed_buildings_y & SC_NLI
    )
        load_nli();

    if (
        screen_state->displayed_buildings_x & SC_BAR &&
        screen_state->displayed_buildings_y & SC_BAR
    )
        load_bar();
}

void load_buildings_x_left(screen_state_t *screen_state, ai_sprite *skater_sprite, ai_sprite *dealer_sprite)
{
    // Enable house
    if (screen_state->screen_location_x_tiles == SC_HOUSE_TRANSITION_X)
    {
        screen_state->displayed_buildings_x |= SC_HOUSE;
        if (screen_state->displayed_buildings_y & SC_HOUSE)
            load_house();
    }
    if (screen_state->screen_location_x_tiles == SC_UNIVERSITY_TRANSITION_X)
    {
        // Disable university and re-enable restaurant
        screen_state->displayed_buildings_x &= ~SC_UNIVERSITY;
        screen_state->displayed_buildings_x |= SC_RESTAURANT;
        if (screen_state->displayed_buildings_y & SC_RESTAURANT)
            load_restaurant();
    }

    // Check skater
    if ((screen_state->screen_location_x_tiles + SCREEN_WIDTH_TILES) == (skater_sprite->min_location_x >> 3))
        screen_state->displayed_sprites_x[skater_sprite->sprite_display_bit] = 0U;
    if (screen_state->screen_location_x_tiles == (skater_sprite->max_location_x >> 3))
        screen_state->displayed_sprites_x[skater_sprite->sprite_display_bit] = 1U;

    // Check dealer
    if ((screen_state->screen_location_x_tiles + SCREEN_WIDTH_TILES) == (dealer_sprite->min_location_x >> 3))
        screen_state->displayed_sprites_x[dealer_sprite->sprite_display_bit] = 0U;
    if (screen_state->screen_location_x_tiles == (dealer_sprite->max_location_x >> 3))
        screen_state->displayed_sprites_x[dealer_sprite->sprite_display_bit] = 1U;

    // NLI
    if (screen_state->screen_location_x_tiles == SC_NLI_TRANSITION_X_MAX)
    {
        screen_state->displayed_buildings_x |= SC_NLI;
        if (screen_state->displayed_buildings_y & SC_NLI)
            load_nli();
    }
    else if (screen_state->screen_location_x_tiles == SC_NLI_TRANSITION_X_MIN)
        screen_state->displayed_buildings_x &= ~SC_NLI;

    // Bar
    if (screen_state->screen_location_x_tiles == SC_BAR_TRANSITION_X_MAX)
    {
        screen_state->displayed_buildings_x |= SC_BAR;
        if (screen_state->displayed_buildings_y & SC_BAR)
            load_bar();
    }
    else if (screen_state->screen_location_x_tiles == SC_BAR_TRANSITION_X_MIN)
        screen_state->displayed_buildings_x &= ~SC_BAR;
}
void load_buildings_x_right(screen_state_t *screen_state, ai_sprite *skater_sprite, ai_sprite *dealer_sprite)
{
    // Disable house
    if (screen_state->screen_location_x_tiles == SC_HOUSE_TRANSITION_X)
        screen_state->displayed_buildings_x &= ~SC_HOUSE;
    if (screen_state->screen_location_x_tiles == SC_UNIVERSITY_TRANSITION_X)
    {
        screen_state->displayed_buildings_x |= SC_UNIVERSITY;
        if (screen_state->displayed_buildings_y & SC_UNIVERSITY)
            load_university();
    }

    // Check skater
    if ((screen_state->screen_location_x_tiles + SCREEN_WIDTH_TILES) == (skater_sprite->min_location_x >> 3))
        screen_state->displayed_sprites_x[skater_sprite->sprite_display_bit] = 1U;
    if ((screen_state->screen_location_x_tiles - 1U) == (skater_sprite->max_location_x >> 3))
        screen_state->displayed_sprites_x[skater_sprite->sprite_display_bit] = 0U;

    // Check dealer
    if ((screen_state->screen_location_x_tiles + SCREEN_WIDTH_TILES) == (dealer_sprite->min_location_x >> 3))
        screen_state->displayed_sprites_x[dealer_sprite->sprite_display_bit] = 1U;
    if ((screen_state->screen_location_x_tiles - 1U) == (dealer_sprite->max_location_x >> 3))
        screen_state->displayed_sprites_x[dealer_sprite->sprite_display_bit] = 0U;

    // NLI
    if (screen_state->screen_location_x_tiles == SC_NLI_TRANSITION_X_MIN)
    {
        screen_state->displayed_buildings_x |= SC_NLI;
        if (screen_state->displayed_buildings_y & SC_NLI)
            load_nli();
    }
    else if (screen_state->screen_location_x_tiles == SC_NLI_TRANSITION_X_MAX)
        screen_state->displayed_buildings_x &= ~SC_NLI;

    // Bar
    if (screen_state->screen_location_x_tiles == SC_BAR_TRANSITION_X_MIN)
    {
        screen_state->displayed_buildings_x |= SC_BAR;
        if (screen_state->displayed_buildings_y & SC_BAR)
            load_bar();
    }
    else if (screen_state->screen_location_x_tiles == SC_BAR_TRANSITION_X_MAX)
        screen_state->displayed_buildings_x &= ~SC_BAR;
}
void load_buildings_y_up(screen_state_t *screen_state, ai_sprite *skater_sprite, ai_sprite *dealer_sprite)
{
    if (screen_state->screen_location_y_tiles == SC_RESTAURANT_TRANSITION_Y_MIN)
        screen_state->displayed_buildings_y &= ~SC_RESTAURANT;

    if (screen_state->screen_location_y_tiles == SC_RESTAURANT_PAWN_TRANSITION_Y)
    {
        screen_state->displayed_buildings_y &= ~SC_PAWN;
        screen_state->displayed_buildings_y |= SC_RESTAURANT;
        if (screen_state->displayed_buildings_x & SC_RESTAURANT)
            load_restaurant();
    }

    if (screen_state->screen_location_y_tiles == SC_SHOP_NLI_TRANSITION_Y)
    {
        screen_state->displayed_buildings_y |= SC_NLI;
        screen_state->displayed_buildings_y &= ~SC_SHOP;
        if (screen_state->displayed_buildings_x & SC_NLI)
            load_nli();
    }

    if (screen_state->screen_location_y_tiles == SC_BAR_TRANSITION_Y)
        screen_state->displayed_buildings_y &= ~SC_BAR;

    // Check skater
    if ((screen_state->screen_location_y_tiles + SCREEN_HEIGHT_TILES) == (skater_sprite->min_location_y >> 3U))
        screen_state->displayed_sprites_y[skater_sprite->sprite_display_bit] = 0U;
    if (screen_state->screen_location_y_tiles == (skater_sprite->max_location_y >> 3U))
        screen_state->displayed_sprites_y[skater_sprite->sprite_display_bit] = 1U;

    // Check dealer
    if ((screen_state->screen_location_y_tiles + SCREEN_HEIGHT_TILES) == (dealer_sprite->min_location_y >> 3U))
        screen_state->displayed_sprites_y[dealer_sprite->sprite_display_bit] = 0U;
    if (screen_state->screen_location_y_tiles == (dealer_sprite->max_location_y >> 3U))
        screen_state->displayed_sprites_y[dealer_sprite->sprite_display_bit] = 1U;
}
void load_buildings_y_down(screen_state_t *screen_state, ai_sprite *skater_sprite, ai_sprite *dealer_sprite)
{
    if (screen_state->screen_location_y_tiles == SC_RESTAURANT_TRANSITION_Y_MIN)
    {
        screen_state->displayed_buildings_y |= SC_RESTAURANT;
        if (screen_state->displayed_buildings_x & SC_RESTAURANT)
            load_restaurant();
    }

    if (screen_state->screen_location_y_tiles == SC_SHOP_NLI_TRANSITION_Y)
    {
        screen_state->displayed_buildings_y &= ~SC_NLI;
        screen_state->displayed_buildings_y |= SC_SHOP;
        if (screen_state->displayed_buildings_x & SC_SHOP)
            load_shop();
    }
    if (screen_state->screen_location_y_tiles == SC_RESTAURANT_PAWN_TRANSITION_Y)
    {
        screen_state->displayed_buildings_y &= ~SC_RESTAURANT;
        screen_state->displayed_buildings_y |= SC_PAWN;
        if (screen_state->displayed_buildings_x & SC_PAWN)
            load_pawn();
    }
    if (screen_state->screen_location_y_tiles == SC_BAR_TRANSITION_Y)
    {
        screen_state->displayed_buildings_y |= SC_BAR;
        if (screen_state->displayed_buildings_x & SC_BAR)
            load_bar();
    }

    // Check skater
    if ((screen_state->screen_location_y_tiles + SCREEN_HEIGHT_TILES) == (skater_sprite->min_location_y >> 3U))
        screen_state->displayed_sprites_y[skater_sprite->sprite_display_bit] = 1U;
    if ((screen_state->screen_location_y_tiles - 1U) == (skater_sprite->max_location_y >> 3U))
        screen_state->displayed_sprites_y[skater_sprite->sprite_display_bit] = 0U;

    // Check dealer
    if ((screen_state->screen_location_y_tiles + SCREEN_HEIGHT_TILES) == (dealer_sprite->min_location_y >> 3U))
        screen_state->displayed_sprites_y[dealer_sprite->sprite_display_bit] = 1U;
    if ((screen_state->screen_location_y_tiles - 1U) == (dealer_sprite->max_location_y >> 3U))
        screen_state->displayed_sprites_y[dealer_sprite->sprite_display_bit] = 0U;
}

