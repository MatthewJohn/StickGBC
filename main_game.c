/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */

#pragma bank=5

#include "gb.h"
#include "main_game.h"
#include "game_constants.h"
#include "main_map_tileset.h"
#include "game_state.h"
#include "main.h"

const UWORD house_car_palette[4] = {
    RGB(31, 31, 31),
    RGB(0, 2, 1),
    RGB(31, 28, 2),
    RGB(20, 20, 0),
};

void load_house()
{
    main_set_bkg_data(13, 1, &(mainmaptiles[13 << 4]), ROM_BANK_MAIN_MAP_TILESET, ROM_BANK_TILE_DATA);
}

void load_restaurant()
{
    main_set_bkg_data(15, 2, &(mainmaptiles[15 << 4]), ROM_BANK_MAIN_MAP_TILESET, ROM_BANK_TILE_DATA);
    // Set palette data
    word_data[0] = RGB(0, 0, 0);
    word_data[1] = RGB(31, 22, 8);
    word_data[2] = RGB(25, 0, 0);
    word_data[3] = RGB(13, 12, 1 );
    set_bkg_palette(PALETTE_SCRATCH_3, 1, word_data);
}

void load_shop()
{
    main_set_bkg_data(18U, 5U, &(mainmaptiles[18U << 4]), ROM_BANK_MAIN_MAP_TILESET, ROM_BANK_TILE_DATA);
    word_data[0] = RGB(31, 21, 5);
    word_data[1] = RGB(1, 0, 2);
    word_data[2] = RGB(4, 20, 0);
    word_data[3] = RGB(26, 16, 0 );
    set_bkg_palette(PALETTE_SCRATCH_2, 1, word_data);
}

void load_pawn()
{
    main_set_bkg_data(23U, 4U, &(mainmaptiles[23U << 4]), ROM_BANK_MAIN_MAP_TILESET, ROM_BANK_TILE_DATA);
    scratch_palette_data[3U][0U] = RGB(10U, 1U, 16U);
    scratch_palette_data[3U][1U] = RGB(31U, 31U, 31U);
    scratch_palette_data[3U][3U] = RGB(15U, 6U, 31U);
    set_bkg_palette(PALETTE_SCRATCH_3, 1, &(scratch_palette_data[3U]));
}

void load_university()
{
    main_set_bkg_data(27U, 3U, &(mainmaptiles[27U << 4]), ROM_BANK_MAIN_MAP_TILESET, ROM_BANK_TILE_DATA);
    scratch_palette_data[3U][0U] = RGB(15U, 19U, 0U);
    scratch_palette_data[3U][1U] = RGB(31U, 22U, 8U);
    scratch_palette_data[3U][2U] = RGB(31U, 13U, 2U);
    scratch_palette_data[3U][3U] = RGB(30U, 31U, 9U);
    set_bkg_palette(PALETTE_SCRATCH_3, 1, &(scratch_palette_data[3U]));
}

void load_nli()
{
    main_set_bkg_data(30U, 9U, &(mainmaptiles[30U << 4]), ROM_BANK_MAIN_MAP_TILESET, ROM_BANK_TILE_DATA);
    scratch_palette_data[2U][0U] = RGB(6U, 6U, 6U);
    scratch_palette_data[2U][1U] = RGB(7U, 3U, 1U);
    set_bkg_palette(PALETTE_SCRATCH_2, 1, &(scratch_palette_data[2U]));
}

void load_bar()
{
    main_set_bkg_data(39U, 13U, &(mainmaptiles[39U << 4]), ROM_BANK_MAIN_MAP_TILESET, ROM_BANK_TILE_DATA);
    scratch_palette_data[1U][0U] = RGB(1U, 14U, 1U);
    scratch_palette_data[1U][1U] = RGB(10U, 8U, 1U);
    scratch_palette_data[1U][2U] = RGB(31U, 1U, 1U);
    scratch_palette_data[1U][3U] = RGB(3U, 8U, 1U);
    set_bkg_palette(PALETTE_SCRATCH_1, 1, &(scratch_palette_data[1U]));
}

void load_appliance_store()
{
    main_set_bkg_data(67U, 11U, &(mainmaptiles[67U << 4]), ROM_BANK_MAIN_MAP_TILESET, ROM_BANK_TILE_DATA);
    scratch_palette_data[0U][1U] = RGB(0U, 0U, 0U);
    scratch_palette_data[0U][2U] = RGB(16U, 16U, 16U);
    set_bkg_palette(PALETTE_SCRATCH_0, 1, &(scratch_palette_data[0U]));
}

/*
 * load_appliance_casino
 *
 * Load shared palette colors for appliance store and casino
 */
void load_appliance_casino()
{
    scratch_palette_data[0U][0U] = RGB(31U, 31U, 31U);
    // Outer buiding for appliance store and casino dice
    set_bkg_palette(PALETTE_SCRATCH_0, 1, &(scratch_palette_data[0U]));
}

void load_casino()
{
    main_set_bkg_data(78U, 9U, &(mainmaptiles[78U << 4]), ROM_BANK_MAIN_MAP_TILESET, ROM_BANK_TILE_DATA);
    // Light blue
    scratch_palette_data[0U][1U] = RGB(9U, 11U, 31U);
    // Dice black
    scratch_palette_data[0U][2U] = RGB(0U, 0U, 0U);
    // Dark blue
    scratch_palette_data[0U][3U] = RGB(0U, 3U, 28U);
    set_bkg_palette(PALETTE_SCRATCH_0, 1, &(scratch_palette_data[0U]));
}

void load_house_car_sprite()
{
    set_sprite_palette(CAR_SPRITE_PALETTE_INDEX, 4, house_car_palette);
}

/*
  Load palette tiles for road car sprite.

  Randomises the color and applies to palette used by car.
*/
void load_road_car_sprite()
{
    set_sprite_palette(CAR_SPRITE_PALETTE_INDEX, 4, house_car_palette);
}

/*
 * Load palette data and tiles for bus and bus station
 */
void load_bus_station()
{
    main_set_bkg_data(52U, 9U, &(mainmaptiles[52U << 4]), ROM_BANK_MAIN_MAP_TILESET, ROM_BANK_TILE_DATA);
    // Bus palette
    scratch_palette_data[0U][0U] = RGB(31U, 31U, 31U);
    scratch_palette_data[0U][1U] = RGB(0U, 0U, 0U);
    scratch_palette_data[0U][2U] = RGB(0U, 0U, 19U);
    scratch_palette_data[0U][3U] = RGB(8U, 31U, 27U);
    // Bus station
    scratch_palette_data[1U][0U] = RGB(3U, 13U, 31U);
    scratch_palette_data[1U][1U] = RGB(0U, 0U, 0U);
    scratch_palette_data[1U][2U] = RGB(1U, 2U, 8U);
    scratch_palette_data[1U][3U] = RGB(2U, 9U, 31U);
    // Load both palettes into PALETTE_SCRATCH_0 and PALETTE_SCRATCH_1
    set_bkg_palette(PALETTE_SCRATCH_0, 2, &(scratch_palette_data[0U]));
}

/*
 * load_bank
 *
 * Load palette and tiles required for bank
 */
void load_bank()
{
    // Tile for top windows
    main_set_bkg_data(18U, 1U, &(mainmaptiles[18U << 4]), ROM_BANK_MAIN_MAP_TILESET, ROM_BANK_TILE_DATA);
    // Main tiles for bank
    main_set_bkg_data(61U, 6U, &(mainmaptiles[61U << 4]), ROM_BANK_MAIN_MAP_TILESET, ROM_BANK_TILE_DATA);
    scratch_palette_data[1U][0U] = RGB(11U, 2U, 1U);
    scratch_palette_data[1U][1U] = RGB(1U, 0U, 0U);
    scratch_palette_data[1U][2U] = RGB(26U, 26U, 0U);
    scratch_palette_data[1U][3U] = RGB(23U, 2U, 0U);
    set_bkg_palette(PALETTE_SCRATCH_1, 1, &(scratch_palette_data[1U]));
}

void load_building_tile_data(screen_state_t *screen_state, ai_sprite *house_car_sprite, ai_sprite *road_car_sprite)
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

    if (
        screen_state->displayed_sprites_x[house_car_sprite->sprite_display_bit] == 1U &&
        screen_state->displayed_sprites_y[house_car_sprite->sprite_display_bit] == 1U
        )
    {
        load_house_car_sprite();
    }

    if (
        screen_state->displayed_sprites_x[road_car_sprite->sprite_display_bit] == 1U &&
        screen_state->displayed_sprites_y[road_car_sprite->sprite_display_bit] == 1U
        )
    {
        load_road_car_sprite();
    }

    if (
        screen_state->displayed_buildings_x & SC_BUS &&
        screen_state->displayed_buildings_y & SC_BUS
    )
        load_bus_station();

    if (
        screen_state->displayed_buildings_2_x & SC_BANK &&
        screen_state->displayed_buildings_2_y & SC_BANK
    )
    {
        load_bank();
    }

    if (
        screen_state->displayed_buildings_2_x & SC_APPLIANCE_STORE_CASINO_SHARED &&
        screen_state->displayed_buildings_2_y & SC_APPLIANCE_STORE_CASINO_SHARED
    )
    {
        load_appliance_casino();
    }

    if (
        screen_state->displayed_buildings_2_x & SC_APPLIANCE_STORE &&
        screen_state->displayed_buildings_2_y & SC_APPLIANCE_STORE
    )
    {
        load_appliance_store();
    }

    if (
        screen_state->displayed_buildings_2_x & SC_CASINO &&
        screen_state->displayed_buildings_2_y & SC_CASINO
    )
    {
        load_casino();
    }
}

void load_buildings_x_left(screen_state_t *screen_state, ai_sprite *skater_sprite, ai_sprite *dealer_sprite, ai_sprite *house_car_sprite, ai_sprite *road_car_sprite)
{
    // Enable house
    if (screen_state->screen_location_x_tiles == SC_HOUSE_TRANSITION_X)
    {
        screen_state->displayed_buildings_x |= SC_HOUSE;
        if (screen_state->displayed_buildings_y & SC_HOUSE)
            load_house();
    }
    if (screen_state->screen_location_x_tiles == SC_RESTAURANT_UNIVERSITY_TRANSITION_X)
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

    // Check house car
    if ((screen_state->screen_location_x_tiles + SCREEN_WIDTH_TILES) == (house_car_sprite->min_location_x >> 3))
        screen_state->displayed_sprites_x[house_car_sprite->sprite_display_bit] = 0U;
    if (screen_state->screen_location_x_tiles == (house_car_sprite->max_location_x >> 3))
    {
        screen_state->displayed_sprites_x[house_car_sprite->sprite_display_bit] = 1U;
        if (screen_state->displayed_sprites_y[house_car_sprite->sprite_display_bit] == 1U)
            load_house_car_sprite();
    }

    // Check road car
    if ((screen_state->screen_location_x_tiles + SCREEN_WIDTH_TILES) == (road_car_sprite->min_location_x >> 3))
        screen_state->displayed_sprites_x[road_car_sprite->sprite_display_bit] = 0U;
    if (screen_state->screen_location_x_tiles == (road_car_sprite->max_location_x >> 3))
    {
        screen_state->displayed_sprites_x[road_car_sprite->sprite_display_bit] = 1U;
        if (screen_state->displayed_sprites_y[road_car_sprite->sprite_display_bit] == 1U)
            load_road_car_sprite();
    }

    // NLI/Bank
    if (screen_state->screen_location_x_tiles == SC_NLI_BANK_TRANSITION_X_MAX)
    {
        screen_state->displayed_buildings_x |= SC_NLI;
        screen_state->displayed_buildings_2_x |= SC_BANK;

        if (screen_state->displayed_buildings_y & SC_NLI)
            load_nli();
        if (screen_state->displayed_buildings_2_y & SC_BANK)
            load_bank();
    }
    else if (screen_state->screen_location_x_tiles == SC_NLI_BANK_TRANSITION_X_MIN)
    {
        screen_state->displayed_buildings_x &= ~SC_NLI;
        screen_state->displayed_buildings_2_x &= ~SC_BANK;
    }

    // Bar
    if (screen_state->screen_location_x_tiles == SC_BAR_TRANSITION_X_MAX)
    {
        screen_state->displayed_buildings_x |= SC_BAR;
        if (screen_state->displayed_buildings_y & SC_BAR)
            load_bar();
    }
    else if (screen_state->screen_location_x_tiles == SC_BAR_TRANSITION_X_MIN)
        screen_state->displayed_buildings_x &= ~SC_BAR;

    // Bus
    if (screen_state->screen_location_x_tiles == SC_BUS_TRANSITION_X)
        screen_state->displayed_buildings_x &= ~SC_BUS;

    // Load shared appliance store and casino palettes
    if (screen_state->screen_location_x_tiles == SC_APPLIANCE_STORE_CASINO_SHARED_TRANSITION_X)
    {
        screen_state->displayed_buildings_2_x |= SC_APPLIANCE_STORE_CASINO_SHARED;
        if (screen_state->displayed_buildings_2_y & SC_APPLIANCE_STORE_CASINO_SHARED)
            load_appliance_casino();
    }

    // Load Appliance store
    if (screen_state->screen_location_x_tiles == SC_APPLIANCE_STORE_TRANSITION_X)
    {
        screen_state->displayed_buildings_2_x |= SC_APPLIANCE_STORE;
        if (screen_state->displayed_buildings_2_y & SC_APPLIANCE_STORE)
            load_appliance_store();
    }

    // Load casino
    if (screen_state->screen_location_x_tiles == SC_CASINO_TRANSITION_X)
    {
        screen_state->displayed_buildings_2_x |= SC_CASINO;
        if (screen_state->displayed_buildings_2_y & SC_CASINO)
            load_casino();
    }

}
void load_buildings_x_right(screen_state_t *screen_state, ai_sprite *skater_sprite, ai_sprite *dealer_sprite, ai_sprite *house_car_sprite, ai_sprite *road_car_sprite)
{
    // Disable house
    if (screen_state->screen_location_x_tiles == SC_HOUSE_TRANSITION_X)
        screen_state->displayed_buildings_x &= ~SC_HOUSE;
    if (screen_state->screen_location_x_tiles == SC_RESTAURANT_UNIVERSITY_TRANSITION_X)
    {
        screen_state->displayed_buildings_x &= ~SC_RESTAURANT;
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

    // Check house car
    if ((screen_state->screen_location_x_tiles + SCREEN_WIDTH_TILES) == (house_car_sprite->min_location_x >> 3))
    {
        screen_state->displayed_sprites_x[house_car_sprite->sprite_display_bit] = 1U;
        if (screen_state->displayed_sprites_y[house_car_sprite->sprite_display_bit] == 1U)
            load_house_car_sprite();
    }
    if ((screen_state->screen_location_x_tiles - 1U) == (house_car_sprite->max_location_x >> 3))
        screen_state->displayed_sprites_x[house_car_sprite->sprite_display_bit] = 0U;

    // Check road car
    if ((screen_state->screen_location_x_tiles + SCREEN_WIDTH_TILES) == (road_car_sprite->min_location_x >> 3))
    {
        screen_state->displayed_sprites_x[road_car_sprite->sprite_display_bit] = 1U;
        if (screen_state->displayed_sprites_y[road_car_sprite->sprite_display_bit] == 1U)
            load_road_car_sprite();
    }
    if ((screen_state->screen_location_x_tiles - 1U) == (road_car_sprite->max_location_x >> 3))
        screen_state->displayed_sprites_x[road_car_sprite->sprite_display_bit] = 0U;

    // NLI/Bank
    if (screen_state->screen_location_x_tiles == SC_NLI_BANK_TRANSITION_X_MIN)
    {
        screen_state->displayed_buildings_x |= SC_NLI;
        screen_state->displayed_buildings_2_x |= SC_BANK;

        if (screen_state->displayed_buildings_y & SC_NLI)
            load_nli();
        if (screen_state->displayed_buildings_2_y & SC_BANK)
            load_bank();
    }
    else if (screen_state->screen_location_x_tiles == SC_NLI_BANK_TRANSITION_X_MAX)
    {
        screen_state->displayed_buildings_x &= ~SC_NLI;
        screen_state->displayed_buildings_2_x &= ~SC_BANK;
    }

    // Bar
    if (screen_state->screen_location_x_tiles == SC_BAR_TRANSITION_X_MIN)
    {
        screen_state->displayed_buildings_x |= SC_BAR;
        if (screen_state->displayed_buildings_y & SC_BAR)
            load_bar();
    }
    else if (screen_state->screen_location_x_tiles == SC_BAR_TRANSITION_X_MAX)
        screen_state->displayed_buildings_x &= ~SC_BAR;

    if (screen_state->screen_location_x_tiles == SC_BUS_TRANSITION_X)
    {
        screen_state->displayed_buildings_x |= SC_BUS;
        if (screen_state->displayed_buildings_y & SC_BUS)
            load_bus_station();
    }

    // Unload shared appliance store and casino palettes
    if (screen_state->screen_location_x_tiles == SC_APPLIANCE_STORE_CASINO_SHARED_TRANSITION_X)
        screen_state->displayed_buildings_2_x &= ~SC_APPLIANCE_STORE_CASINO_SHARED;

    // Unload casino
    if (screen_state->screen_location_x_tiles == SC_CASINO_TRANSITION_X)
        screen_state->displayed_buildings_2_x &= ~SC_CASINO;

    // Unload Appliance store
    if (screen_state->screen_location_x_tiles == SC_APPLIANCE_STORE_TRANSITION_X)
        screen_state->displayed_buildings_2_x &= ~SC_APPLIANCE_STORE;
}
void load_buildings_y_up(screen_state_t *screen_state, ai_sprite *skater_sprite, ai_sprite *dealer_sprite, ai_sprite *house_car_sprite, ai_sprite *road_car_sprite)
{
    if (screen_state->screen_location_y_tiles == SC_RESTAURANT_TRANSITION_Y_MIN)
        screen_state->displayed_buildings_y &= ~SC_RESTAURANT;

    if (screen_state->screen_location_y_tiles == SC_RESTAURANT_PAWN_UNIVERSITY_TRANSITION_Y)
    {
        screen_state->displayed_buildings_y &= ~SC_PAWN;
        screen_state->displayed_buildings_y |= SC_RESTAURANT;
        screen_state->displayed_buildings_y |= SC_UNIVERSITY;
        if (screen_state->displayed_buildings_x & SC_RESTAURANT)
            load_restaurant();
        if (screen_state->displayed_buildings_x & SC_UNIVERSITY)
            load_university();
    }

    if (screen_state->screen_location_y_tiles == SC_SHOP_NLI_TRANSITION_Y)
    {
        screen_state->displayed_buildings_y |= SC_NLI;
        screen_state->displayed_buildings_y &= ~SC_SHOP;
        if (screen_state->displayed_buildings_x & SC_NLI)
            load_nli();
    }

    // Bank
    if(screen_state->screen_location_y_tiles == SC_BANK_TRANSITION_Y_MAX)
    {
        screen_state->displayed_buildings_2_y |= SC_BANK;
        if (screen_state->displayed_buildings_2_x & SC_BANK)
            load_bank();
    }

    // Unload Bus
    if (screen_state->screen_location_y_tiles == SC_BUS_TRANSITION_Y_MIN)
        screen_state->displayed_buildings_y &= ~SC_BUS;

    // Unload Bar
    if (screen_state->screen_location_y_tiles == SC_BAR_TRANSITION_Y)
        screen_state->displayed_buildings_y &= ~SC_BAR;

    // Load/unload Appliance store/casino
    if (screen_state->screen_location_y_tiles == SC_APPLIANCE_STORE_TRANSITION_Y_MIN)
        screen_state->displayed_buildings_2_y &= ~SC_APPLIANCE_STORE;
    if (screen_state->screen_location_y_tiles == SC_APPLIANCE_STORE_CASINO_TRANSITION_Y)
    {
        screen_state->displayed_buildings_2_y &= ~SC_CASINO;
        screen_state->displayed_buildings_2_y |= SC_APPLIANCE_STORE;
        if (screen_state->displayed_buildings_2_x & SC_APPLIANCE_STORE)
            load_appliance_store();
    }

    // Unload shared appliance store and casino palettes
    if (screen_state->screen_location_y_tiles == SC_APPLIANCE_STORE_CASINO_SHARED_TRANSITION_Y)
        screen_state->displayed_buildings_2_y &= ~SC_APPLIANCE_STORE_CASINO_SHARED;

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

    if ((screen_state->screen_location_y_tiles + SCREEN_HEIGHT_TILES) == (house_car_sprite->min_location_y >> 3U))
        screen_state->displayed_sprites_y[house_car_sprite->sprite_display_bit] = 0U;
    if (screen_state->screen_location_y_tiles == (house_car_sprite->max_location_y >> 3U))
    {
        screen_state->displayed_sprites_y[house_car_sprite->sprite_display_bit] = 1U;
        if (screen_state->displayed_sprites_x[house_car_sprite->sprite_display_bit] == 1U)
            load_house_car_sprite();
    }

    // Check road car
    if ((screen_state->screen_location_y_tiles + SCREEN_HEIGHT_TILES) == (road_car_sprite->min_location_y >> 3U))
        screen_state->displayed_sprites_y[road_car_sprite->sprite_display_bit] = 0U;
    if (screen_state->screen_location_y_tiles == (road_car_sprite->max_location_y >> 3U))
    {
        screen_state->displayed_sprites_y[road_car_sprite->sprite_display_bit] = 1U;
        if (screen_state->displayed_sprites_x[road_car_sprite->sprite_display_bit] == 1U)
            load_road_car_sprite();
    }
}
void load_buildings_y_down(screen_state_t *screen_state, ai_sprite *skater_sprite, ai_sprite *dealer_sprite, ai_sprite *house_car_sprite, ai_sprite *road_car_sprite)
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

    if (screen_state->screen_location_y_tiles == SC_BUS_TRANSITION_Y_MIN)
    {
        screen_state->displayed_buildings_y |= SC_BUS;
        if (screen_state->displayed_buildings_x & SC_BUS)
            load_bus_station();
    }

    if(screen_state->screen_location_y_tiles == SC_BANK_TRANSITION_Y_MAX)
    {
        screen_state->displayed_buildings_2_y &= ~SC_BANK;
    }

    if (screen_state->screen_location_y_tiles == SC_RESTAURANT_PAWN_UNIVERSITY_TRANSITION_Y)
    {
        screen_state->displayed_buildings_y &= ~SC_RESTAURANT;
        screen_state->displayed_buildings_y &= ~SC_UNIVERSITY;
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

    // Load shared appliance store and casino palettes
    if (screen_state->screen_location_y_tiles == SC_APPLIANCE_STORE_CASINO_SHARED_TRANSITION_Y)
    {
        screen_state->displayed_buildings_2_y |= SC_APPLIANCE_STORE_CASINO_SHARED;
        if (screen_state->displayed_buildings_2_x & SC_APPLIANCE_STORE_CASINO_SHARED)
            load_appliance_casino();
    }

    // Load/unload appliance store/casino
    if (screen_state->screen_location_y_tiles == SC_APPLIANCE_STORE_CASINO_TRANSITION_Y)
    {
        screen_state->displayed_buildings_2_y &= ~SC_APPLIANCE_STORE;
        screen_state->displayed_buildings_2_y |= SC_CASINO;
        if (screen_state->displayed_buildings_2_x & SC_CASINO)
            load_casino();
    }
    if (screen_state->screen_location_y_tiles == SC_APPLIANCE_STORE_TRANSITION_Y_MIN)
    {
        screen_state->displayed_buildings_2_y |= SC_APPLIANCE_STORE;
        if (screen_state->displayed_buildings_2_x & SC_APPLIANCE_STORE)
            load_appliance_store();
    }

    // Load casino
    if (screen_state->screen_location_y_tiles == SC_APPLIANCE_STORE_CASINO_SHARED_TRANSITION_Y)
    {
        screen_state->displayed_buildings_2_y |= SC_APPLIANCE_STORE_CASINO_SHARED;
        if (screen_state->displayed_buildings_2_x & SC_APPLIANCE_STORE_CASINO_SHARED)
            load_appliance_casino();
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

    if ((screen_state->screen_location_y_tiles + SCREEN_HEIGHT_TILES) == (house_car_sprite->min_location_y >> 3U))
    {
        screen_state->displayed_sprites_y[house_car_sprite->sprite_display_bit] = 1U;
        if (screen_state->displayed_sprites_x[house_car_sprite->sprite_display_bit] == 1U)
            load_house_car_sprite();
    }
    if ((screen_state->screen_location_y_tiles - 1U) == (house_car_sprite->max_location_y >> 3U))
        screen_state->displayed_sprites_y[house_car_sprite->sprite_display_bit] = 0U;

    if ((screen_state->screen_location_y_tiles + SCREEN_HEIGHT_TILES) == (road_car_sprite->min_location_y >> 3U))
    {
        screen_state->displayed_sprites_y[road_car_sprite->sprite_display_bit] = 1U;
        if (screen_state->displayed_sprites_x[road_car_sprite->sprite_display_bit] == 1U)
            load_road_car_sprite();
    }
    if ((screen_state->screen_location_y_tiles - 1U) == (road_car_sprite->max_location_y >> 3U))
        screen_state->displayed_sprites_y[road_car_sprite->sprite_display_bit] = 0U;
}
