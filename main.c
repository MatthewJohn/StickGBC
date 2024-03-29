/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */


/*#include <gb/drawing.h>*/
#include <stdio.h>
#include <stdlib.h>
#include <types.h>
#include <gb/gb.h>
#include <gb/drawing.h>

#include "main_map_tileset.h"
#include "main_map.h"
#include "main_map_palette.h"
#include "main_map_boundaries.h"
#include "main_game.h"
#include "logic_functions.h"
#include "cheat.h"

#include "building_menu_tiles.h"
#include "building_menu_tiles_2.h"
#include "building_menu_map.h"
#include "building_menu_palette.h"

#include "main_map_sprite_tileset.h"
#include "main_map_sprite_palette.h"

#include "opening_screen.h"
#include "endgame.h"
#include "bar_fight.h"

#include "background_time_colors.h"

#include "game_constants.h"
#include "game_state.c"
#include "menu_config.h"
#include "screen_state.c"
#include "window.h"
#include "sprite.h"
#include "joy.h"
#include "window_text.h"
#include "window_text_data.h"
#include "balance.h"
#include "casino.h"

#include "main.h"

UBYTE * debug_address;

// Temporary storege for transfer of tile data and tile data vram1 data
UBYTE tile_data[1];
UWORD word_data[4];

// Storage for scratch palette data
UWORD scratch_palette_data[4][4];

joypad_state_t joypad_state;

// Game state
game_state_t game_state;
screen_state_t screen_state;

// Define global instance of menu config
menu_config_t *menu_config;
menu_state_t menu_state;

// General iterators
unsigned int itx_start;
unsigned int itx_end;
unsigned int itx;


// Bunch of variables from load_menu_tiles.
// This fixed a compiler error, which gave no
// indication of issue and no resources online.
unsigned int itx_x;
unsigned int itx_y;
UINT8 menu_item_index;
unsigned int tile_index;
unsigned int tile_data_index;
UINT8 tile_itx_x_start;
UINT8 tile_itx_y_start;
UINT8 tile_itx_x;
UINT8 tile_itx_y;
UINT8 second_tile_row;

// Main player sprite
ai_sprite player_sprite = {
    // Speed
    0x00U,
    // Sprite index
    0x00U,
    // Sprite bit index
    0x00U,
    // Color palette,
    0x00U,

    // Sprite count
    0x01U,
    0x01U,
    // Sprite base tile
    SPRITE_TILESET_WALK,

    // Fake values, since the
    // main player has different state for these
    // Travel X/Y, rest direction, start location, min/max x, min/max Y
    0x00, 0x00, 0x00, 0x00, 0x0U, 0x0U, 0x0U, 0x0U, 0x0U, 0x0U,
    // Pause period
    0x40U, 0x00U,
};

// Setup skater sprite
ai_sprite skater_sprite = {
    // Speed
    0x05U,
    // Sprite index
    0x01U,
    // Sprite bit index
    0x00U,
    // Color palette,
    0x01U,

    // Sprite count
    0x01U,
    0x01U,
    // Sprite base tile
    SPRITE_TILESET_WALK,

    // Travel X (right)
    0x01,
    // Travel Y
    0x00,
    // Rest direction X/Y (face down)
    0x00,
    0x01,
    // Start location x, y
    0xD8U,
    0x58U,
    // Min/max X location
    0xD8U,
    0xE8U,
    // Min/max Y location
    0x58U,
    0x58U,
    // Pause period and current pause.
    0x0FU,
    0x00U,
};

// Setup dealer sprite
ai_sprite dealer_sprite = {
    // Speed
    0x05U,
    // Sprite index
    0x02U,
    // Sprite bit index
    0x01U,
    // Color palette,
    0x02U,
    // Sprite count
    0x01U,
    0x01U,
    // Sprite base tile
    SPRITE_TILESET_WALK,
    // Travel X
    0x00,
    // Travel Y (down)
    0x01,
    // Rest direction X/Y (face down)
    -1,
    0x00,
    // Start location x, y
    0x157U,
    0x173U,
    // Min/max X location
    0x157U,
    0x157U,
    // Min/max Y location
    0x173U,
    0x17BU,
    // Pause period and current pause.
    0x0FU,
    0x00U,
};

// Setup house car sprite
ai_sprite house_car_sprite = {
    // Speed
    0x00U,
    // Base sprite index (uses 4 (3 through 6) for 2x2 tiles)
    0x03U,
    // Sprite bit index
    0x02U,
    // Color palette,
    0x03U,
    // Sprite count (2 x 2)
    0x02U,
    0x02U,
    // Sprite base tile
    0x08U,
    // Travel X (right)
    0x01,
    // Travel Y
    0x00,
    // Rest direction X/Y (face right)
    0x01,
    0x00,
    // Start location x, y
    0x3BU,
    0x58U,
    // Min/max X location
    0x3BU,
    0x44U,
    // Min/max Y location
    0x58U,
    0x58U,
    // Pause period and current pause.
    0x00U,
    0x00U,
};

// Setup AI road car
ai_sprite road_car_sprite = {
    // Speed
    0x01U,
    // Base sprite index (uses 4 (7 through A) for 2x2 tiles)
    0x07U,
    // Sprite bit index
    0x03U,
    // Color palette,
    0x03U,
    // Sprite count (2 x 2)
    0x02U,
    0x02U,
    // Sprite base tile
    0x08U,
    // Travel X
    0x00,
    // Travel Y (down - though this is randomised)
    0x01,
    // Rest direction X/Y (face down)
    0x00,
    0x01,
    // Start location x, y
    0x110U,
    0x58U,
    // Min/max X location
    0x110U,
    0x110U,
    // Min/max Y location
    0x0U,
    0x1C0U,
    // Pause period and current pause.
    0x80U,
    0x00U,
};


void add_debug(UBYTE val)
{
    *debug_address = val;
    debug_address ++;
}

// Update background color based on time of day
void update_background_color()
{
    UWORD palette_data[4];

    // Copy palette 1
    ROM_BANK_TIME_COLORS_SWITCH;
    palette_data[0U] = background_time_colors[game_state.hour],
    ROM_BANK_TILE_DATA_SWITCH;
    palette_data[1U] = main_map_palette[1U];
    palette_data[2U] = main_map_palette[2U];
    palette_data[3U] = main_map_palette[3U];
    ROM_BANK_RESET;

    set_bkg_palette(0U, 1U, &palette_data);
}

void setup_globals()
{
    game_state.current_building = S_B_NO_BUILDING;
    game_state.sub_menu = S_M_NO_SUBMENU;

    game_state.game_ended = 0;

    game_state.last_movement_time = 0x0U;
    // @TODO make sure display works after 999
    game_state.days_passed = 0U;
    game_state.hour = S_HOUR_WAKEUP_NORMAL;

    // Start with $100
    game_state.balance[0] = 100U;
    game_state.balance[1] = 0U;
    game_state.bank_balance = 0U;
    game_state.loan = 0U;
    game_state.loan_days = 0U;
    game_state.bank_rate = (sys_time % 50) + 1;

    // Randomise initial stats.
    // Use different modulus operands to get different results.
    game_state.intelligence = (sys_time % 10);
    game_state.strength = (sys_time % 11);
    game_state.charm = (sys_time % 12);
    game_state.karma = 0;

    game_state.hobo_given_money = 0U;
    game_state.hobo_given_beer = 0U;

    game_state.intro_shown = 0U;

    // Set HP twice - for some reason, the initial set
    // causes a weird issue. Assigning hp to max_hp works.
    // Then setting hp again from this value fixes the issue.
    game_state.hp = S_INITIAL_BASE_HP + game_state.strength;
    game_state.max_hp = game_state.hp;
    game_state.hp = game_state.max_hp;

    screen_state.displayed_sprites_x[skater_sprite.sprite_display_bit] = 0U;
    screen_state.displayed_sprites_y[skater_sprite.sprite_display_bit] = 1U;
    screen_state.displayed_sprites_x[dealer_sprite.sprite_display_bit] = 0U;
    screen_state.displayed_sprites_y[dealer_sprite.sprite_display_bit] = 0U;
    screen_state.displayed_sprites_x[house_car_sprite.sprite_display_bit] = 1U;
    screen_state.displayed_sprites_y[house_car_sprite.sprite_display_bit] = 1U;
    screen_state.displayed_sprites_x[road_car_sprite.sprite_display_bit] = 0U;
    screen_state.displayed_sprites_y[road_car_sprite.sprite_display_bit] = 1U;

    // Mark screen as having moved, so that sprites are initially placed on-screen
    screen_state.screen_has_moved = 1U;

    // Setup buildings that do not transition in some axis
    // and those that are displayed on start of game.
    screen_state.displayed_buildings_x = SC_HOUSE | SC_RESTAURANT | SC_SHOP | SC_PAWN;
    screen_state.displayed_buildings_y = SC_HOUSE | SC_UNIVERSITY | SC_NLI;
    screen_state.displayed_buildings_2_x = SC_APPLIANCE_STORE | SC_APPLIANCE_STORE_CASINO_SHARED | SC_CASINO;
    screen_state.displayed_buildings_2_y = SC_BANK;

    // Setup inventory items
    game_state.inventory[S_INVENTORY_SMOKES] = 0x0U;
    game_state.inventory[S_INVENTORY_CAFFEINE_PILLS] = 0x0U;
    game_state.inventory[S_INVENTORY_HAND_GUN] = 0x0U;
    game_state.inventory[S_INVENTORY_KNIFE] = 0x0U;
    game_state.inventory[S_INVENTORY_ALARM_CLOCK] = 0x0U;
    game_state.inventory[S_INVENTORY_CELL_PHONE] = 0x0U;
    game_state.inventory[S_INVENTORY_SKATEBOARD] = 0x0U;
    game_state.inventory[S_INVENTORY_COCAINE] = 0x0U;
    game_state.inventory[S_INVENTORY_BOTTLE_OF_BEER] = 0x0U;
    game_state.inventory[S_INVENTORY_BED] = 0x0U;
    game_state.inventory[S_INVENTORY_TV] = 0x0U;
    game_state.inventory[S_INVENTORY_PC] = 0x0U;
    game_state.inventory[S_INVENTORY_DEEP_FREEZE] = 0x0U;
    game_state.inventory[S_INVENTORY_SATELLITE] = 0x0U;
    game_state.inventory[S_INVENTORY_TREADMILL] = 0x0U;
    game_state.inventory[S_INVENTORY_STICKOPEDIA] = 0x0U;
    game_state.inventory[S_INVENTORY_MINIBAR] = 0x0U;

    screen_state.screen_location_x = 0x10U;
    screen_state.screen_location_x_tiles = screen_state.screen_location_x >> 3;
    screen_state.screen_location_y = 0x10U;
    screen_state.screen_location_y_tiles = screen_state.screen_location_y >> 3;
    game_state.user_pos_x = 0x70U;
    game_state.user_pos_y = 0x70U;
    game_state.user_pos_tiles_x = PIXEL_LOCATION_TO_TILE_COUNT(game_state.user_pos_x);
    game_state.user_pos_tiles_y = PIXEL_LOCATION_TO_TILE_COUNT(game_state.user_pos_y);

    game_state.bar_fight_count = 0U;

#ifdef IN_TESTING
    // Add hacks for testing
    game_state.inventory[S_INVENTORY_SKATEBOARD] = 0x1U;
    game_state.inventory[S_INVENTORY_SMOKES] = 0x1U;
    game_state.inventory[S_INVENTORY_COCAINE] = 49U;
    game_state.inventory[S_INVENTORY_BOTTLE_OF_BEER] = 49U;
    game_state.inventory[S_INVENTORY_HAND_GUN] = 0x1U;
    game_state.inventory[S_INVENTORY_AMMO] = 0x10U;
    game_state.inventory[S_INVENTORY_CELL_PHONE] = 0x1U;
    game_state.balance[0U] = 8000U;
    game_state.balance[1U] = 0U;
    game_state.bank_balance = 3000U;
    game_state.max_hp = 100U;
    game_state.intelligence = 250U;
    game_state.strength = 90U;
    game_state.charm = 99U;
    game_state.hour = 0;
    game_state.bar_fight_count = 5U;
#endif
}

void update_ai_positions()
{
#if IN_TESTING && DEBUG_DISABLE_AI_MOVEMENT
    return;
#endif
    ROM_BANK_SPRITE_SWITCH;
    move_ai_sprite(&screen_state, &skater_sprite);
    move_ai_sprite(&screen_state, &dealer_sprite);
    move_ai_sprite(&screen_state, &house_car_sprite);
    move_ai_sprite(&screen_state, &road_car_sprite);
    // Perform special checks for
    check_road_car_onscreen(&screen_state, &road_car_sprite);
    ROM_BANK_RESET;
}

void main_set_bkg_data(UINT8 start_index, UINT8 cnt, unsigned char *data_ptr, UINT8 data_bank, UINT8 return_bank) NONBANKED
{
    // Switch to data bank
    SWITCH_ROM_MBC5(data_bank);

    set_bkg_data(start_index, cnt, data_ptr);

    // Reset ROM bank to original
    SWITCH_ROM_MBC5(return_bank);
}

void set_background_tiles(unsigned int map_data_bank, unsigned int tile_data_bank, unsigned int palette_data_bank, unsigned int return_bank) NONBANKED
{
    // @TODO Fix the increment
    //unsigned long current_tile_itx = FRAME_BUFFER_TILE_POS_X + (FRAME_BUFFER_TILE_POS_Y * mainmapWidth);
    unsigned int current_tile_itx = 0;
    unsigned int current_tile_data_itx = 0;
    unsigned int current_tile_palette_itx = 0;
    unsigned int max_x;
    unsigned int max_y;

    // If loading main map, use screen_location variables
    // to offset tiles
    max_x = screen_state.draw_offset_x + screen_state.draw_max_x;
    max_y = screen_state.draw_offset_y + screen_state.draw_max_y;

    // Load color palette
    SWITCH_ROM_MBC5(palette_data_bank);
    set_bkg_palette(0, 8, screen_state.background_color_palette);

    VBK_REG = 0;
    SWITCH_ROM_MBC5(tile_data_bank);
    set_bkg_data(0, 8, screen_state.background_tiles);

    ROM_BANK_BUILDING_MENU_SWITCH;
    // Load in digits/symbols from building menu tiles, including clock tiles before it
    set_bkg_data(MENU_ROW_2_TILE_DATA_OFFSET, 31U, &(buildingmenutiles[(MENU_ROW_2_TILE_DATA_OFFSET) << 4U]));
    ROM_BANK_RESET;

    for (itx_x = screen_state.draw_offset_x;
           itx_x != max_x;
           itx_x ++)
    {

#if IN_TESTING && DEBUG_SET_BACKGROUND_SKIP
        // TEMP HACK TO NOT DRAW MOST OF BACKGROUND IN VRAM
        if (itx_x == 0x10U)
            break;
#endif

        for (itx_y = screen_state.draw_offset_y;
               itx_y != max_y;
               itx_y ++)
        {
            // Temp Test
            current_tile_itx = ((itx_y) * screen_state.background_width) + itx_x;

#if IN_TESTING && DEBUG_SET_BACKGROUND_SKIP
            // TEMP HACK TO NOT DRAW MOST OF BACKGROUND IN VRAM
            if (itx_y == 0x10U)
                break;
#endif

            // Tile data is split across two bytes. In the layout:
            // 0-6 - tile number
            // 7 - blank
            // 8-A - palette number
            // B - vertical flip
            // C - horizontal flip
            current_tile_data_itx = current_tile_itx * 2;
            current_tile_palette_itx = current_tile_data_itx + 1;

            SWITCH_ROM_MBC5(map_data_bank);
            tile_data[0] = screen_state.background_tile_map[current_tile_data_itx] & 0x7F;
            ROM_BANK_RESET;

#if IN_TESTING && DEBUG_BOUNDARIES
            ROM_BANK_BOUNDARY_DATA_SWITCH;
            // Check if tile is a boundary
            if (TILE_INDEX_BIT_MAP_VALUE(MAIN_MAP_BOUNDARIES, current_tile_itx))
                // Random tile
                tile_data[0] = 0x06;
            ROM_BANK_RESET;
#endif

            VBK_REG = 0;
            // Set map data
            set_bkg_tiles(
                itx_x & BACKGROUND_BUFFER_MAX_X,
                itx_y & BACKGROUND_BUFFER_MAX_Y,
                1, 1,  // Only setting 1 tile
                 // Lookup tile from background tile map
                 &(tile_data[0])
            );

            VBK_REG = 1;

            SWITCH_ROM_MBC5(map_data_bank);
            // Lookup tile palette from background tile map
            tile_data[0] = screen_state.background_tile_map[current_tile_palette_itx] & 0x07;

            // Bit shift last bit of tile index to determine low or high bank (bit 3)
            tile_data[0] |= (screen_state.background_tile_map[current_tile_data_itx] & 0x80U) >> 4;

            // Check if current tile is flipped
            if (screen_state.background_tile_map[current_tile_palette_itx] & 0x08)
                tile_data[0] |= S_FLIPY;

            if (screen_state.background_tile_map[current_tile_palette_itx] & 0x10)
                tile_data[0] |= S_FLIPX;

            ROM_BANK_RESET;

#if IN_TESTING && DEBUG_BOUNDARIES
            ROM_BANK_BOUNDARY_DATA_SWITCH;
            // Check if tile is a boundary
            if (TILE_INDEX_BIT_MAP_VALUE(MAIN_MAP_BOUNDARIES, current_tile_itx))
                // Forth palette
                tile_data[0] = 0x03;
            ROM_BANK_RESET;
#endif

            // Set palette data in VBK_REG1 for tile
            set_bkg_tiles(
                itx_x & BACKGROUND_BUFFER_MAX_X,
                itx_y & BACKGROUND_BUFFER_MAX_Y,
                1, 1,  // Only setting 1 tile
                &(tile_data[0])
            );

            // @TODO Fix this
            //current_tile_itx ++;
        }

        // Add remainig undrawn tiles to itx of tiles
        //current_tile_itx += (mainmapWidth - BACKGROUND_BUFFER_SIZE_Y);
    }

    // Reset VKG_REG to original value
    VBK_REG = 0;

    // Reset ROM bank to original
    SWITCH_ROM_MBC5(return_bank);
}

void move_background(signed int move_x, signed int move_y) NONBANKED
{
    unsigned int itx_x;
    unsigned int itx_y;
    unsigned int base_itx_x;
    unsigned int base_itx_y;
    UINT16 current_tile_itx;
    UINT16 current_tile_data_itx;
    UINT16 current_tile_palette_itx;
    unsigned int itx_x_max;
    unsigned int itx_y_max;


    if (move_x == 0 && move_y == 0)
    {
        delay(20);
        return;
    }

    // Mark screen as having moved, which indicates to AI sprite to move,
    // even if they are not themselves moving
    screen_state.screen_has_moved = 1U;

    scroll_bkg(move_x, move_y);

    screen_state.screen_location_x += move_x;
    screen_state.screen_location_y += move_y;
    screen_state.screen_location_x_tiles = screen_state.screen_location_x >> 3;
    screen_state.screen_location_y_tiles = screen_state.screen_location_y >> 3;
    screen_state.screen_location_x_tilepixel = screen_state.screen_location_x & 0x07U;
    screen_state.screen_location_y_tilepixel = screen_state.screen_location_y & 0x07U;

    // Set current redraw in X to current user position (bit shift to remove pixels within tile) plus
    // current frame buffer size + redraw offset.
    // Mask with vram tile size in X, as a form of cheap modulus (which we can do as it is a power of 2)
    base_itx_x = screen_state.screen_location_x >> 3;
    if (move_x == 1)
        // If moving to right, start redraw tile after
        // Calulate entire width of screen, plus one tile either side.
        base_itx_x += (SCREEN_TILE_MAX_X + 2U);
    else if (move_x == -1)
        // If moving left, redraw tile before
        base_itx_x -= 1U;

    // See X alternative
    base_itx_y = screen_state.screen_location_y >> 3;
    if (move_y == 1)
        // If moving to right, start redraw tile after
        base_itx_y += (SCREEN_TILE_MAX_Y + 2U);
    else if (move_y == -1)
        // If moving left, redraw tile before
        base_itx_y -= 1U;

    // Redraw tiles in unallocated vram
    if (move_x != 0)
    {

        itx_x = base_itx_x;
        // If moving in X, redraw column.
        // The iterator is the frame buffer position (not the map position)
        // Use screen_location_x_subpixel to divide up tile in entire row. Start with 0 on first pixel. Set end of iterator to start of next block of tiles.
        itx_y_max = base_itx_y + (3U * (screen_state.screen_location_x_tilepixel + 1U)) + 1U;
        for (itx_y = base_itx_y + (3U * screen_state.screen_location_x_tilepixel) - 1U;
               itx_y != itx_y_max;
               itx_y ++)
        {
            // Work out current tile - base on tile location in frame buffer plus current map in vram location
            current_tile_itx = (itx_y * mainmapWidth) + itx_x;

            current_tile_data_itx = current_tile_itx * 2;
            current_tile_palette_itx = current_tile_data_itx + 1;

            ROM_BANK_TILE_DATA_SWITCH;
            tile_data[0] = screen_state.background_tile_map[current_tile_data_itx] & 0x7F;
            ROM_BANK_RESET;

#if IN_TESTING && DEBUG_BOUNDARIES
            ROM_BANK_BOUNDARY_DATA_SWITCH;
            // Check if tile is a boundary
            if (TILE_INDEX_BIT_MAP_VALUE(MAIN_MAP_BOUNDARIES, current_tile_itx))
                // Random tile
                tile_data[0] = 0x06;
            ROM_BANK_RESET;
#endif

            VBK_REG = 0;

            // Set map data
            set_bkg_tiles(
                itx_x & BACKGROUND_BUFFER_MAX_X,
                itx_y & BACKGROUND_BUFFER_MAX_Y,
                1, 1,  // Only setting 1 tile
                 // Lookup tile from background tile map
                 &(tile_data[0])
            );

            // Lookup tile from background tile map
            ROM_BANK_TILE_DATA_SWITCH;
            tile_data[0] = screen_state.background_tile_map[current_tile_palette_itx] & 0x07;

            // Check if current tile is flipped
            if (screen_state.background_tile_map[current_tile_palette_itx] & 0x08)
                tile_data[0] |= S_FLIPY;

            if (screen_state.background_tile_map[current_tile_palette_itx] & 0x10)
                tile_data[0] |= S_FLIPX;
            ROM_BANK_RESET;

#if IN_TESTING && DEBUG_BOUNDARIES
            ROM_BANK_BOUNDARY_DATA_SWITCH;
            // Check if tile is a boundary
            if (TILE_INDEX_BIT_MAP_VALUE(MAIN_MAP_BOUNDARIES, current_tile_itx))
                // Forth palette
                tile_data[0] = 0x03;
            ROM_BANK_RESET;
#endif

            VBK_REG = 1;

            // Set palette data in VBK_REG1 for tile
            set_bkg_tiles(
                itx_x & BACKGROUND_BUFFER_MAX_X,
                itx_y & BACKGROUND_BUFFER_MAX_Y,
                1, 1,  // Only setting 1 tile
                &(tile_data[0])
            );

            VBK_REG = 0;
        }
    }

    if (move_y != 0)
    {
        itx_y = base_itx_y;

        // If moving in X, redraw column.
        // The iterator is the frame buffer position (not the map position)
        itx_x_max = base_itx_x + (3U * (screen_state.screen_location_y_tilepixel + 1U)) + 1U;
        for (itx_x = base_itx_x + (3U * screen_state.screen_location_y_tilepixel) - 1U;
               itx_x != itx_x_max;
               itx_x ++)
        {
            // Work out current tile - base on tile location in frame buffer plus current map in vram location
            current_tile_itx = (itx_y  * mainmapWidth) + itx_x;

            current_tile_data_itx = current_tile_itx * 2;
            current_tile_palette_itx = current_tile_data_itx + 1;

            ROM_BANK_TILE_DATA_SWITCH;
            tile_data[0] = screen_state.background_tile_map[current_tile_data_itx] & 0x7F;
            ROM_BANK_RESET;

#if IN_TESTING && DEBUG_BOUNDARIES
            ROM_BANK_BOUNDARY_DATA_SWITCH;
            // Check if tile is a boundary
            if (TILE_INDEX_BIT_MAP_VALUE(MAIN_MAP_BOUNDARIES, current_tile_itx))
                // Random tile
                tile_data[0] = 0x06;
            ROM_BANK_RESET;
#endif

            VBK_REG = 0;
            // Set map data
            set_bkg_tiles(
                itx_x & BACKGROUND_BUFFER_MAX_X,
                itx_y & BACKGROUND_BUFFER_MAX_Y,
                1, 1,  // Only setting 1 tile
                 // Lookup tile from background tile map
                 &(tile_data[0])
            );

            ROM_BANK_TILE_DATA_SWITCH;
            // Lookup tile from background tile map
            tile_data[0] = screen_state.background_tile_map[current_tile_palette_itx] & 0x07;

            // Check if current tile is flipped
            if (screen_state.background_tile_map[current_tile_palette_itx] & 0x08)
                tile_data[0] |= S_FLIPY;

            if (screen_state.background_tile_map[current_tile_palette_itx] & 0x10)
                tile_data[0] |= S_FLIPX;

            ROM_BANK_RESET;

#if IN_TESTING && DEBUG_BOUNDARIES
            ROM_BANK_BOUNDARY_DATA_SWITCH;
            // Check if tile is a boundary
            if (TILE_INDEX_BIT_MAP_VALUE(MAIN_MAP_BOUNDARIES, current_tile_itx))
                // Forth palette
                tile_data[0] = 0x03;
            ROM_BANK_RESET;
#endif

            VBK_REG = 1;

            // Set palette data in VBK_REG1 for tile
            set_bkg_tiles(
                itx_x & BACKGROUND_BUFFER_MAX_X,
                itx_y & BACKGROUND_BUFFER_MAX_Y,
                1, 1,  // Only setting 1 tile
                &(tile_data[0])
            );
           VBK_REG = 0;
        }
    }
}

// Setup globals to draw main map
void setup_main_map()
{
    DISPLAY_OFF;
    game_state.current_building = S_B_NO_BUILDING;

    screen_state.background_color_palette = main_map_palette;
    screen_state.background_tile_map = mainmap;
    screen_state.background_tiles = mainmaptiles;
    screen_state.background_width = mainmapWidth;

    screen_state.draw_offset_x = screen_state.screen_location_x >> 3;
    screen_state.draw_offset_y = screen_state.screen_location_y >> 3;

    // If not starting from the left/top edge of the screen,
    // move offset to top/left by 1, which will begin redraw one tile to the left.
    // This means that the tile to the left and above will be drawn as the left/top
    // (as opposed to being the tiles wrapped around from drawing to the right/down).
    // This means that as the player moves to the left or up, the tiles are already drawn
    // and don't cause incorrect tiles as the movement of the screne expects a buffer of
    // 1 tile to have already been drawn for this direction of travel.
    if (screen_state.draw_offset_x != 0)
    {
        screen_state.draw_offset_x -= 1;
    }
    if (screen_state.draw_offset_y != 0)
    {
        screen_state.draw_offset_y -= 1;
    }

    screen_state.draw_max_x = BACKGROUND_BUFFER_SIZE_X;
    screen_state.draw_max_y = BACKGROUND_BUFFER_SIZE_Y;

    set_background_tiles(ROM_BANK_TILE_DATA, ROM_BANK_MAIN_MAP_TILESET, ROM_BANK_TILE_DATA, 1U);
    ROM_BANK_SPRITE_SWITCH;
    setup_sprites(&player_sprite, &skater_sprite, &dealer_sprite, &house_car_sprite, &road_car_sprite);
    ROM_BANK_RESET;

    // Move background to screen location
    scroll_bkg(
        screen_state.screen_location_x & BACKGROUND_BUFFER_SIZE_PIXELS_MAX_X,
        screen_state.screen_location_y & BACKGROUND_BUFFER_SIZE_PIXELS_MAX_Y
    );

    // Load additional tiles required for main map
    ROM_BANK_MAIN_MAP_TILESET_SWITCH;
    set_bkg_data(8U, 5U, &(mainmaptiles[8U << 4]));

    // Load currently displayed buildings
    ROM_BANK_TILE_DATA_SWITCH;
    load_building_tile_data(&screen_state, &house_car_sprite, &road_car_sprite);

    ROM_BANK_RESET;

    update_background_color();

    DISPLAY_ON;

    // Set last_movement_time to current systime, allowing user to
    // immediately move, in case it has been set to the future by
    // another method
    game_state.last_movement_time = sys_time;
}

/*
 * load_menu_tiles
 *
 * Load each of the menu items on to the screen
 * from the active menu_config, using the
 * two-letter menu tiles.
 */
void load_menu_tiles(unsigned int return_bank) NONBANKED
{
    unsigned int menu_item_itx;

    // Reset VBK_REG
    VBK_REG = 0;

    // Iterate over all menu items and load palette data.
    // Start from 1 , as first item column is 'exit'
    for (itx_x = 0; itx_x != MENU_MAX_ITEMS_X; itx_x ++)
    {
        for (itx_y = 0; itx_y != MENU_MAX_ITEMS_Y; itx_y ++)
        {
            // Work out menu item index, based on co-ords
            menu_item_index = (itx_y * MENU_MAX_ITEMS_X) + itx_x;

            menu_item_itx = menu_config->items[menu_item_index];

            // Ignore top right exit and item is exit
            if (itx_x == 1U && itx_y == 0U && menu_item_itx == MENU_ITEM_INDEX_EXIT)
                continue;

            second_tile_row = 0U;

            // Pad from left with offset on screen. The menu items are 7 + margin of 1, so times with itx_x.
            tile_itx_x_start = MENU_ITEM_SCREEN_OFFSET_LEFT + (8U * itx_x);
            tile_itx_y_start = MENU_ITEM_SCREEN_OFFSET_TOP + (3U * itx_y);

            for (tile_index = 0U; tile_index != MENU_ITEM_TILE_COUNT; tile_index ++)
            {
                // Once second row of menu item data tiles is reached,
                // mark as such
                if (tile_index == MENU_ITEM_WIDTH)
                {
                    tile_itx_x_start -= MENU_ITEM_WIDTH;
                    second_tile_row = 1U;
                }

                ROM_BANK_MENU_CONFIG_SWITCH;
                tile_data_index = menu_config_items[menu_item_itx].tiles[tile_index];

                // Only load data if tile contains data
                if (tile_data_index != 0U)
                {
                    ROM_BANK_BUILDING_MENU_SWITCH;

                    // Load tile data for menu item based on tile data offset
                    // in menu config and tile config in menu tile array
                    set_bkg_data(
                        tile_data_index,
                        1,
                        &(screen_state.background_tiles[tile_data_index << 4])
                    );
                    ROM_BANK_RESET;
                }

                tile_itx_x = tile_itx_x_start + tile_index;
                tile_itx_y = tile_itx_y_start + second_tile_row;
                tile_data[0] = tile_data_index;

                // Set map data
                set_bkg_tiles(
                    tile_itx_x,
                    tile_itx_y,
                    1U, 1U,  // Only setting 1 tile
                    &(tile_data[0])
                );

                if (tile_data_index == MENU_ITEM_NO_TILE)
                    // If tile is empty, use blank palette
                    tile_data[0] = MENU_ITEM_DEFAULT_PALETTE;
                else
                {
                    ROM_BANK_MENU_CONFIG_SWITCH;

                    // Load default palette
                    tile_data[0] = menu_config_items[menu_item_itx].palette[tile_index];
                    ROM_BANK_RESET;

                    // If not palette data, specified, use default
                    if (tile_data[0] == MENU_ITEM_NO_PALETTE)
                        tile_data[0] = MENU_ITEM_DEFAULT_PALETTE;
                }

                VBK_REG = 1;

                // Set palette data in VBK_REG1 for tile
                set_bkg_tiles(
                    tile_itx_x,
                    tile_itx_y,
                    1, 1,  // Only setting 1 tile
                    &(tile_data[0])
                );

                VBK_REG = 0;
            }
        }
    }

    SWITCH_ROM_MBC5(return_bank);
}

void setup_building_menu(UINT8 menu_number, unsigned int return_bank) NONBANKED
{
    DISPLAY_OFF;
    // Update globals for references to map/tile information
    screen_state.background_tile_map = buildingmenumap;

    if (menu_number == 1U)
        screen_state.background_tiles = buildingmenutiles;
    else if (menu_number == 2U)
        screen_state.background_tiles = buildingmenutiles2;

    screen_state.background_width = buildingmenumapWidth;
    screen_state.background_color_palette = building_menu_palette;

    // Draw top left of screen
    screen_state.draw_offset_x = 0U;
    screen_state.draw_offset_y = 0U;
    screen_state.draw_max_x = SCREEN_WIDTH_TILES;
    screen_state.draw_max_y = SCREEN_HEIGHT_TILES;

    if (game_state.current_building == S_B_HOUSE)
    {
        // Menu has 3 items, default to sleep
        menu_state.current_item_x = 1;
        menu_state.current_item_y = 3;
        menu_config = &menu_config_house;
    }
    else if (game_state.current_building == S_B_RESTAURANT)
    {
        // Menu has 3 items, default to fries
        menu_state.current_item_x = 0;
        menu_state.current_item_y = 1;
        menu_config = &menu_config_restaurant;
    }
    else if (game_state.current_building == S_B_SHOP)
    {
        // Default to slushee
        menu_state.current_item_x = 0U;
        menu_state.current_item_y = 1U;
        menu_config = &menu_config_shop;
    }
    else if (game_state.current_building == S_B_PAWN)
    {
        menu_config = &menu_config_pawn;
        // Default to hand gun, if available
        if (menu_config->items[MENU_PAWN_HAND_GUN_ITEM] != MENU_ITEM_INDEX_EMPTY) {
            menu_state.current_item_x = 0U;
            menu_state.current_item_y = 1U;
        } else {
            // Otherwise, default to ammo
            menu_state.current_item_x = 0U;
            menu_state.current_item_y = 0U;
        }
    }
    else if (game_state.current_building == S_B_UNIVERSITY)
    {
        // Default to study
        menu_state.current_item_x = 0U;
        menu_state.current_item_y = 1U;
        menu_config = &menu_config_university;
    }
    else if (game_state.current_building == S_B_SKATER)
    {
        // Default to study
        menu_state.current_item_x = 0U;
        menu_state.current_item_y = 0U;
        menu_config = &menu_config_skater;
    }
    else if (game_state.current_building == S_B_NLI)
    {
        menu_config = &menu_config_nli;

        // If no 'work' item is available, select 'apply for job'
        if (menu_config->items[MENU_NLI_WORK_ITEM] == MENU_ITEM_INDEX_EMPTY)
            menu_state.current_item_y = 2U;

        // Otherwise, select 'work' item
        else
            menu_state.current_item_y = 3U;
        menu_state.current_item_x = 1U;
    }
    else if (game_state.current_building == S_B_DEALER)
    {
        menu_config = &menu_config_dealer;
        menu_state.current_item_x = 0U;
        menu_state.current_item_y = 2U;
    }
    else if (game_state.current_building == S_B_HOBO)
    {
        menu_config = &menu_config_hobo;
        menu_state.current_item_x = 0U;
        menu_state.current_item_y = 2U;
    }
    else if (game_state.current_building == S_B_BAR)
    {
        menu_config = &menu_config_bar;
        menu_state.current_item_x = 0U;
        menu_state.current_item_y = 1U;
    }
    else if (game_state.current_building == S_B_STATS)
    {
        menu_config = &menu_config_stats;
        // Select exit by default
        menu_state.current_item_x = 1U;
        menu_state.current_item_y = 0U;
    }
    else if (game_state.current_building == S_B_INVENTORY)
    {
        // Select exit by default
        menu_state.current_item_x = MENU_SELECTED_ITEM_DISABLED;
        menu_state.current_item_y = MENU_SELECTED_ITEM_DISABLED;
    }
    else if (game_state.current_building == S_B_BUS_STATION)
    {
        menu_config = &menu_config_bus_station;
        menu_state.current_item_x = 0U;
        menu_state.current_item_y = 1U;
    }
    else if (game_state.current_building == S_B_BANK)
    {
        menu_config = &menu_config_bank;
        menu_state.current_item_x = 0U;
        menu_state.current_item_y = 1U;
    }
    else if (game_state.current_building == S_B_REAL_ESTATE)
    {
        menu_config = &menu_config_real_estate;
        menu_state.current_item_x = 1U;
        menu_state.current_item_y = 0U;
    }
    else if (game_state.current_building == S_B_APPLIANCE_STORE)
    {
        menu_config = &menu_config_appliance_store;
        menu_state.current_item_x = 1U;
        menu_state.current_item_y = 0U;
    }
    else if (game_state.current_building == S_B_CASINO)
    {
        menu_config = &menu_config_casino;
        menu_state.current_item_x = 0U;
        menu_state.current_item_y = 0U;
    }

    HIDE_SPRITES;
    // Reload background tiles
    set_background_tiles(ROM_BANK_BUILDING_MENU, ROM_BANK_BUILDING_MENU, ROM_BANK_BUILDING_MENU, 1U);

    // Scroll to top-left
    move_bkg(0, 0);

    load_menu_tiles(ROM_BANK_DEFAULT);

    // Highlight currently selected item
    ROM_BANK_MENU_CONFIG_SWITCH;
    set_menu_item_color(MENU_ITEM_SELECTED_PALETTE);
    ROM_BANK_RESET;

    DISPLAY_ON;

    // Set last_movement_time to current systime, allowing user to
    // immediately select an item, in case it has been set to the future by
    // another method
    game_state.last_movement_time = sys_time;

    SWITCH_ROM_MBC5(return_bank);
}

/*
 * check_end_game
 *
 * Check if win/lose conditions have been met
 */
void check_end_game() NONBANKED
{
    if (game_state.hp == 0 || (game_state.max_days != 0U && game_state.days_passed >= game_state.max_days))
    {
        // Show end game, passing reason for end game reason
        ROM_BANK_ENDGAME_SWITCH;
        if (game_state.hp == 0)
        {
            endgame(&win_txt_end_died);
        }
        else
        {
            endgame(&win_txt_end_time);
        }
        ROM_BANK_RESET;
    }
}

/*
 * main_check_end_game
 *
 * check_end_game wrapper with ROM jumping
 */
 void main_check_end_game(unsigned int return_bank) NONBANKED
 {
    SWITCH_ROM_MBC5(ROM_BANK_DEFAULT);
    check_end_game();
    SWITCH_ROM_MBC5(return_bank);
 }

void modify_karma(INT8 karma_change) NONBANKED
{
    game_state.karma += karma_change;
}

/*
 * decrease_hp
 *
 * Decrease HP and check if player has died
 */
void decrease_hp(UINT8 decrease_amount)
{
    if (game_state.hp > decrease_amount)
    {
        // If not out of HP, decrease and update window.
        game_state.hp -= decrease_amount;
        ROM_BANK_BUILDING_MENU_SWITCH;
        update_window();
        ROM_BANK_RESET;
        return;
    }
    // If run out of HP, set to zero and end game
    game_state.hp = 0;
    check_end_game();
}

void increase_intelligence(UINT8 cost, UINT8 number_of_hours, UINT8 intelligence)
{
    if (
        has_money(0U, cost) &&
        game_state.intelligence != S_MAX_INTELLIGENCE &&
        (S_HOURS_PER_DAY - game_state.hour) >= number_of_hours
    )
    {
        remove_money(0U, cost);
        game_state.hour += number_of_hours;
        game_state.intelligence += intelligence;

        modify_karma(1);

        ROM_BANK_BUILDING_MENU_SWITCH;
        update_window();
        ROM_BANK_RESET;
    }
}

UINT8 increase_charm(UINT8 cost, UINT8 number_of_hours, UINT8 charm, unsigned int return_bank)
{
    if (
        has_money(0U, cost) &&
        game_state.charm != S_MAX_CHARM &&
        (S_HOURS_PER_DAY - game_state.hour) >= number_of_hours
    )
    {
        remove_money(0U, cost);
        game_state.hour += number_of_hours;
        game_state.charm += charm;

        ROM_BANK_BUILDING_MENU_SWITCH;
        update_window();
        SWITCH_ROM_MBC5(return_bank);
        return 1U;
    }
    return 0U;
}

void increase_strength(UINT8 cost, UINT8 number_of_hours, UINT8 strength)
{
    if (
        has_money(0U, cost) &&
        game_state.strength != S_MAX_STRENGTH &&
        (S_HOURS_PER_DAY - game_state.hour) >= number_of_hours
    )
    {
        remove_money(0U, cost);
        game_state.hour += number_of_hours;
        game_state.strength += strength;
        game_state.max_hp += strength;

        modify_karma(1);

        ROM_BANK_BUILDING_MENU_SWITCH;
        update_window();
        ROM_BANK_RESET;
    }
}

void main_increase_strength(UINT8 cost, UINT8 number_of_hours, UINT8 strength, unsigned int return_bank)
{
    increase_strength(cost, number_of_hours, strength);
    SWITCH_ROM_MBC5(return_bank);
}

void do_work(unsigned int pay_per_hour, unsigned int number_of_hours)
{
    if ((S_HOURS_PER_DAY - game_state.hour) >= number_of_hours)
    {
        // Increase balance and increase time of day
        add_money(0U, (pay_per_hour * number_of_hours));
        game_state.hour += number_of_hours;

        modify_karma(1);
    }

    ROM_BANK_BUILDING_MENU_SWITCH;
    update_window();
    ROM_BANK_RESET;
}

/*
 * main_do_work
 *
 * do_work wrapper with ROM jumping
 */
void main_do_work(unsigned int pay_per_hour, unsigned int number_of_hours, unsigned int return_bank)
{
    do_work(pay_per_hour, number_of_hours);
    SWITCH_ROM_MBC5(return_bank);
}

/*
 * move_to_menu_item
 *
 * Move selected menu item to new value and update highlighting
 */
void move_to_menu_item(UINT8 new_x, UINT8 new_y, unsigned int return_bank) NONBANKED
{
    // Deselect currently selected item
    ROM_BANK_MENU_CONFIG_SWITCH;
    set_menu_item_color(MENU_ITEM_DEFAULT_PALETTE);
    ROM_BANK_RESET;

    menu_state.current_item_x = new_x;
    menu_state.current_item_y = new_y;

    // Highlight new menu item
    ROM_BANK_MENU_CONFIG_SWITCH;
    set_menu_item_color(MENU_ITEM_SELECTED_PALETTE);
    SWITCH_ROM_MBC5(return_bank);
}

void do_nli_work()
{
    // Calculate current job
    switch (menu_config->items[MENU_NLI_WORK_ITEM])
    {
        case MENU_ITEM_INDEX_WORK_JANITOR :
            do_work(8U, 6U);
            break;
        case MENU_ITEM_INDEX_WORK_MAIL_CLERK :
            do_work(10U, 6U);
            break;
        case MENU_ITEM_INDEX_WORK_SALESMAN :
            do_work(15U, 6U);
            break;
        case MENU_ITEM_INDEX_WORK_EXECUTIVE :
            do_work(25U, 6U);
            break;
        case MENU_ITEM_INDEX_WORK_VP :
            do_work(50U, 6U);
            break;
        case MENU_ITEM_INDEX_WORK_CEO :
            do_work(100U, 6U);
            break;
    }
}

BOOLEAN is_menu_item_hidden(UINT8 menu_item_index)
{
    UINT8 menu_item_itx = 0;
    for (menu_item_itx = 0; menu_item_itx != HIDDEN_ITEM_COUNT; menu_item_itx ++)
    {
        if (hidden_inventory_items[menu_item_itx] == menu_item_index)
            return 1U;
    }
    return 0U;
}

// Show inventory screen
void show_inventory_screen() NONBANKED
{
    // Initialise array to hold numbers to put against
    // each shown inventory item
    UINT8 item_quantities[8U] = {
        0, 0, 0, 0, 0, 0, 0, 0,
    };

    // Reset inventory menu items
    menu_config_inventory.items[0] = 0U;
    menu_config_inventory.items[1] = 0U;
    menu_config_inventory.items[2] = 0U;
    menu_config_inventory.items[3] = 0U;
    menu_config_inventory.items[4] = 0U;
    menu_config_inventory.items[5] = 0U;
    menu_config_inventory.items[6] = 0U;

    // Assign dynamic menu config as menu config
    // to draw
    menu_config = &menu_config_inventory;

    game_state.current_building = S_B_INVENTORY;

    itx_x = 0;
    itx_y = 0;
    // Iterate over inventory items
    for (itx = 0; itx != S_INVENTORY_ITEM_COUNT; itx ++)
    {
        // Check if inventory item has a value
        if (game_state.inventory[itx] == 0U || is_menu_item_hidden(itx) == 0U)
            // Skip to next inventory item
            continue;

        menu_item_index = itx_x + (itx_y * MENU_MAX_ITEMS_X);

        // Add quantity to quantity array
        item_quantities[menu_item_index] = game_state.inventory[itx];

        // Add inventory item to menu config
        ROM_BANK_MENU_CONFIG_SWITCH;
        menu_config_inventory.items[menu_item_index] = inventory_menu_item_map[itx];
        ROM_BANK_RESET;

        // Go to next item
        itx_x += 1U;
        if (itx_x == MENU_MAX_ITEMS_X)
        {
            itx_x = 0;
            itx_y += 1U;
        }
        // Check if at max items
        if (itx_y == MENU_MAX_ITEMS_Y)
            break;
    }

    setup_building_menu(1U, ROM_BANK_DEFAULT);

    // Iterate over item quantites and print to screen
    ROM_BANK_BUILDING_MENU_SWITCH;
    for (itx_y = 0; itx_y != MENU_MAX_ITEMS_Y; itx_y ++)
    {
        for (itx_x = 0; itx_x != MENU_MAX_ITEMS_X; itx_x ++)
        {
            itx = (itx_y * MENU_MAX_ITEMS_X) + itx_x;
            // If the quantity is empty, assume there are no more items,
            // as inventory items of 0 are not show in the screen
            if (item_quantities[itx] == 0U)
                break;

            show_number(3U + (8U * itx_x), 3U + (3U * itx_y), 3U, item_quantities[itx]);
        }
    }
    ROM_BANK_RESET;
}

/*
 * main_show_window_character
 *
 * show_window_character wrapper with ROM jumping
 */
void main_show_window_character(UINT8 character_number, UINT8 itx, UINT8 ity, unsigned int return_bank)
{
    ROM_BANK_WINDOW_TEXT_SWITCH;
    show_window_character(character_number, itx, ity);
    SWITCH_ROM_MBC5(return_bank);
}

/*
 * main_show_window_text
 *
 * show_window_text wrapper with ROM jumping
 */
void main_show_window_text(UINT8 *text, unsigned int return_bank) NONBANKED
{
    ROM_BANK_WINDOW_TEXT_SWITCH;
    show_window_text(text);
    SWITCH_ROM_MBC5(return_bank);
}

/*
 * main_show_window_text_xy
 *
 * show_window_text_xy wrapper with ROM jumping
 */
void main_show_window_text_xy(UINT8 itx_x, UINT8 itx_y, UINT8 *text, unsigned int return_bank)
{
    ROM_BANK_WINDOW_TEXT_SWITCH;
    show_window_text_xy(itx_x, itx_y, text);
    SWITCH_ROM_MBC5(return_bank);
}

// Called per cycle to update background position and sprite
void update_state()
{
    unsigned short background_moved = 0U;
    unsigned int user_screen_pos_x;
    unsigned int user_screen_pos_y;
    signed int move_x;
    signed int move_y;
    unsigned short new_menu_x;
    unsigned short attempting_x_move;
    UINT8 movement_bit_push;

    if (game_state.current_building == S_B_NO_BUILDING)
    {
        ROM_BANK_BOUNDARY_DATA_SWITCH;
        check_boundary_hit();
        ROM_BANK_RESET;

        // Check if player is hurt and just decrease wait time
        if (player_sprite.current_pause != 0)
        {
            player_sprite.current_pause -= 1U;

            // Check if back to normal movement and reset color palette/sprite
            if (player_sprite.current_pause == 0)
            {
                ROM_BANK_SPRITE_SWITCH;
                set_main_player_normal(&player_sprite);
                ROM_BANK_RESET;

                // Reset player movement, so they don't move based on the input
                joypad_state.travel_x = 0;
                joypad_state.travel_y = 0;

                if (game_state.user_pos_tiles_x == MAP_EDGE_LEFT)
                    // Move player right
                    joypad_state.travel_x = 1;
                if (game_state.user_pos_tiles_x == MAP_EDGE_RIGHT)
                    // Move player left
                    joypad_state.travel_x = -1;
                if (game_state.user_pos_tiles_y == MAP_EDGE_TOP)
                    // Move player down
                    joypad_state.travel_y = 1;
                if (game_state.user_pos_tiles_y == MAP_EDGE_BOTTOM)
                    // Move player up
                    joypad_state.travel_y = -1;
            }
            else
            {
                // Otherwise still in wait period
                return;
            }

        }

        if (game_state.inventory[S_INVENTORY_SKATEBOARD] && joypad_state.b_pressed)
        {
            movement_bit_push = SKATEBOARD_SPEED_DELAY;
            player_sprite.sprite_tile = SPRITE_TILESET_SKATEBOARD;
        }
        else
        {
            movement_bit_push = WALK_SPEED_DELAY;
            player_sprite.sprite_tile = SPRITE_TILESET_WALK;
        }
        // If movement happened too recently, disable movement
        if ((game_state.last_movement_time >> movement_bit_push)  == (sys_time >> movement_bit_push))
        {
            joypad_state.travel_x = 0;
            joypad_state.travel_y = 0;
        }
        else
            // Otherwise, update last movement time
            game_state.last_movement_time = sys_time;


        // Set user screen position based on current location
        user_screen_pos_x = game_state.user_pos_x - screen_state.screen_location_x;
        user_screen_pos_y = game_state.user_pos_y - screen_state.screen_location_y;

        game_state.user_pos_x += (signed int)joypad_state.travel_x;
        game_state.user_pos_y += (signed int)joypad_state.travel_y;
        game_state.user_pos_tiles_x = PIXEL_LOCATION_TO_TILE_COUNT(game_state.user_pos_x);
        game_state.user_pos_tiles_y = PIXEL_LOCATION_TO_TILE_COUNT(game_state.user_pos_y);

        // Check if sprite too close to edge of screen
        // If character at left of screen, begin to scroll, unless at top of map (allowing character
        // to continue moving and not redraw map outside of map tiles)
        if (user_screen_pos_x == CHARACTER_SCREEN_LOCATION_MARGIN && screen_state.screen_location_x != 0)
        {
            // If player hit LHS of screen, move screen to the left
            move_x = -1;
        }
        else if (user_screen_pos_x ==  (SCREEN_WIDTH - CHARACTER_SCREEN_LOCATION_MARGIN))
        {
            // If player hit RHS of screen, move screen to the right
            move_x = 1;
        }
        else
        {
            // If moving sprite, update user screen position X using new user_pos_x
            user_screen_pos_x = game_state.user_pos_x - screen_state.screen_location_x;
            move_x = 0;
        }

        // If character at top of screen, begin to scroll, unless at top of map (allowing character
        // to continue moving and not redraw map outside of map tiles)
        if (user_screen_pos_y == CHARACTER_SCREEN_LOCATION_MARGIN && screen_state.screen_location_y != 0)
        {
            move_y = -1;
        }
        else if (user_screen_pos_y == (SCREEN_HEIGHT - CHARACTER_SCREEN_LOCATION_MARGIN))
        {
            move_y = 1;
        }
        else
        {
            // If moving sprite, update user screen position X using new user_pos_x
            user_screen_pos_y = game_state.user_pos_y - screen_state.screen_location_y;
            move_y = 0;
        }

        // Temporary fix to help with diagonal movement
        // move_background(0, move_y);
        screen_state.screen_has_moved = 0U;
        if (move_x != 0)
        {
            move_background(move_x, 0);

            // Check when on tile boundary (NOTE this only works for movement in positive directions,
            // but doesn't matter for now).
            if (screen_state.screen_location_x_tilepixel == 0U)
            {
                ROM_BANK_TILE_DATA_SWITCH;
                if (move_x == 1)
                    load_buildings_x_right(&screen_state, &skater_sprite, &dealer_sprite, &house_car_sprite, &road_car_sprite);
                else
                    load_buildings_x_left(&screen_state, &skater_sprite, &dealer_sprite, &house_car_sprite, &road_car_sprite);
                ROM_BANK_RESET;
            }
        }
        if (move_y != 0)
        {
            move_background(0, move_y);

            if (screen_state.screen_location_y_tilepixel == 0U)
            {
                ROM_BANK_TILE_DATA_SWITCH;
                if (move_y == 1)
                    load_buildings_y_down(&screen_state, &skater_sprite, &dealer_sprite, &house_car_sprite, &road_car_sprite);
                else
                    load_buildings_y_up(&screen_state, &skater_sprite, &dealer_sprite, &house_car_sprite, &road_car_sprite);
                ROM_BANK_RESET;
            }
        }

        // Move sprite to new location
        move_sprite(
            0,
            user_screen_pos_x + SPRITE_OFFSET_X,
            user_screen_pos_y + SPRITE_OFFSET_Y
        );

        if (joypad_state.travel_x != 0 || joypad_state.travel_y != 0)
        {
            player_sprite.travel_direction_x = joypad_state.travel_x;
            player_sprite.travel_direction_y = joypad_state.travel_y;

            ROM_BANK_SPRITE_SWITCH;
            set_sprite_direction(&player_sprite);
            ROM_BANK_RESET;
        }

        // Check for falling off edge of map
        if (game_state.user_pos_tiles_x == MAP_EDGE_LEFT ||
            game_state.user_pos_tiles_x == MAP_EDGE_RIGHT ||
            game_state.user_pos_tiles_y == MAP_EDGE_TOP ||
            game_state.user_pos_tiles_y == MAP_EDGE_BOTTOM)
        {
            // Decrease HP
            decrease_hp(10);
            ROM_BANK_SPRITE_SWITCH;
            set_main_player_hurt(&player_sprite);
            ROM_BANK_RESET;
            return;
        }

        if (joypad_state.a_pressed)
        {
            ROM_BANK_LOGIC_FUNCTIONS_SWITCH;
            check_building_enter();
            ROM_BANK_RESET;
        }

        else if (joypad_state.select_pressed) {
            ROM_BANK_BUILDING_MENU_SWITCH;
            show_stats_screen();
            ROM_BANK_RESET;
        }

        else if (joypad_state.start_pressed) {
            show_inventory_screen();
        }

    } else {
        // In a building - move through menu

        // Menu layout:
        // 3,3 tile offset for top option.
        // Each option is 7 tiles wide and 2 tiles high.
        // One tile buffer between each option.

        if (joypad_state.travel_x != 0 || joypad_state.travel_y != 0)
        {
            // Update last movement (used for purchase delay) to 0,
            // allowing them to purchase immediately after movement
            // to new tile. If sys_time happens to be overflowing,
            // then this won't help the user and will have to wait for the
            // purchase wait period.
            game_state.last_movement_time = 0U;

            // Setup new Y search to use current X
            new_menu_x = menu_state.current_item_x;
            attempting_x_move = 0U;

            // Check the direction of menu item travel and ensure it doesn't go out of bounds
            // Since there's only two items in X direction of menu, do a simple hard coded check
            if (
                    (joypad_state.travel_x == 1 && menu_state.current_item_x == 0U) ||
                    (joypad_state.travel_x == -1 && menu_state.current_item_x == 1U)
                )
            {
                // Setup new X value that user is attempting to access
                new_menu_x = menu_state.current_item_x + joypad_state.travel_x;

                // This will update item and mean that any checks against new_menu_x vs state will show
                // them as equal
                if (IS_MENU_ITEM_ENABLED(new_menu_x + (menu_state.current_item_y * MENU_MAX_ITEMS_X)))
                    move_to_menu_item(new_menu_x, menu_state.current_item_y, ROM_BANK_DEFAULT);
                else
                    attempting_x_move = 1U;
            }

            // Until I can find a nicer way of doing this. Go in direction of menu travel and
            // check if there is an option available
            // If moving up or attempting to travel in X, but no item directly beside it
            if (joypad_state.travel_y == 1 || attempting_x_move)
            {
                itx_start = menu_state.current_item_y + 1U;
                for (itx = itx_start; itx != MENU_MAX_ITEMS_Y; itx ++)
                    if (IS_MENU_ITEM_ENABLED(new_menu_x + (itx * MENU_MAX_ITEMS_X)))
                    {
                        move_to_menu_item(new_menu_x, itx, ROM_BANK_DEFAULT);
                        attempting_x_move = 0U;
                        break;
                    }
            }
            if ((joypad_state.travel_y == -1 || attempting_x_move) && menu_state.current_item_y != 0U)
            {
                // Since we're going from current itx (Y -1) to 0,
                // to make iteration easier, iterate from Y to 1 and take 1 during calulcation
                for (itx = menu_state.current_item_y; itx != 0U; itx --)
                    if (IS_MENU_ITEM_ENABLED(new_menu_x + ((itx - 1U) * MENU_MAX_ITEMS_X)))
                    {
                        move_to_menu_item(new_menu_x, itx - 1U, ROM_BANK_DEFAULT);
                        break;
                    }
            }

            // Sleep to stop double pressed
            delay(DELAY_MENU_ITEM_MOVE);
        }

        // Check if B or 'start' pressed to exit menu
        if (joypad_state.b_pressed || joypad_state.start_pressed)
        {
            setup_main_map();
            return;
        }

        // Check if selecting menu item
        if (joypad_state.a_pressed)
        {
            // Check if 'exit' selected
            if (menu_state.current_item_y == 0U && menu_state.current_item_x == 1U)
            {
                // If exiting menu, load main map
                setup_main_map();
                return;
            }

            // Check if in wait-period since last time purchase
            // Since sys_time wraps around every 18 mins, if it does,
            // sys_time will be a low number and removing last_movement time will cause
            // an underflow of the difference, which will be very big and immediately allow
            // for another purchase - this isn't _great_, but better than logic that
            // will cause the user to be able to not purchase anything for 18 mins whilst
            // sys_time makes it's way back up...
            if ((sys_time - game_state.last_movement_time) < PURCHASE_ITEM_WAIT)
            {
                // If in wait period, exit early
                return;
            }
            else
            {
                // Otherwise, update last movement time
                game_state.last_movement_time = sys_time;
            }

            // If selected sleep in house
            if (game_state.current_building == S_B_HOUSE)
            {
                ROM_BANK_LOGIC_FUNCTIONS_SWITCH;
                process_house_menu();
                ROM_BANK_RESET;
            }
            // Handle menu selections from restaurant
            else if (game_state.current_building == S_B_RESTAURANT)
            {
                ROM_BANK_LOGIC_FUNCTIONS_SWITCH;
                process_restaurant_menu();
                ROM_BANK_RESET;
            }
            else if (game_state.current_building == S_B_SHOP)
            {
                ROM_BANK_LOGIC_FUNCTIONS_SWITCH;
                process_shop_menu();
                ROM_BANK_RESET;
            }

            else if (game_state.current_building == S_B_PAWN)
            {
                ROM_BANK_LOGIC_FUNCTIONS_SWITCH;
                process_pawn_menu();
                ROM_BANK_RESET;
            }
            else if (game_state.current_building == S_B_UNIVERSITY)
            {
                if (menu_state.current_item_x == 0U)
                {
                    if (menu_state.current_item_y == 1U)  // Study -1 intelligence, 2 hours
                        increase_intelligence(0U, 2U, 1U);
                    else if (menu_state.current_item_y == 2U)  // Class -$20, 1 intelligence, 2 hours
                        increase_intelligence(20U, 2U, 2U);
                }
                else
                {
                    if (menu_state.current_item_y == 1U)
                        increase_strength(0U, 2U, 1U);
                }
            }
            else if (game_state.current_building == S_B_SKATER)
            {
                ROM_BANK_LOGIC_FUNCTIONS_SWITCH;
                process_skater_menu();
                ROM_BANK_RESET;
            }
            else if (game_state.current_building == S_B_NLI)
            {
                if (menu_state.current_item_x == 1U)
                {
                    if (menu_state.current_item_y == 2U)
                    {
                        // Check if applying for job
                        ROM_BANK_MENU_CONFIG_SWITCH;
                        apply_for_job_promotion(&game_state, menu_config, &menu_config_restaurant);
                        ROM_BANK_RESET;
                    }
                    else if (menu_state.current_item_y == 3U)
                    {
                        do_nli_work();
                    }
                }
            }
            else if (game_state.current_building == S_B_DEALER)
            {
                ROM_BANK_LOGIC_FUNCTIONS_SWITCH;
                process_dealer_menu();
                ROM_BANK_RESET;
            }
            else if (game_state.current_building == S_B_HOBO)
            {
                ROM_BANK_LOGIC_FUNCTIONS_SWITCH;
                process_hobo_menu();
                ROM_BANK_RESET;
            }
            else if (game_state.current_building == S_B_BAR)
            {
                ROM_BANK_LOGIC_FUNCTIONS_SWITCH;
                process_bar_menu();
                ROM_BANK_RESET;
            }

            else if (game_state.current_building == S_B_BUS_STATION)
            {
                // If not selecting from top row ('sell goods' or exit),
                // perform sell_goods_city
                if (menu_state.current_item_y != 0U)
                {
                    ROM_BANK_LOGIC_FUNCTIONS_SWITCH;
                    bus_sell_goods(&menu_state, &game_state);
                    ROM_BANK_RESET;

                    // Return to main map once complete
                    setup_main_map();
                    // Since days can pass, check end game
                    check_end_game();
                    return;
                }
            }

            else if (game_state.current_building == S_B_BANK)
            {
                ROM_BANK_LOGIC_FUNCTIONS_SWITCH;
                process_bank_menu();
                ROM_BANK_RESET;
            }

            else if (game_state.current_building == S_B_APPLIANCE_STORE)
            {
                ROM_BANK_LOGIC_FUNCTIONS_SWITCH;
                process_app_store_menu();
                ROM_BANK_RESET;
            }

            else if (game_state.current_building == S_B_REAL_ESTATE)
            {
                ROM_BANK_LOGIC_FUNCTIONS_SWITCH;
                process_rees_menu();
                ROM_BANK_RESET;
            }
            else if (game_state.current_building == S_B_CASINO)
            {
                ROM_BANK_CASINO_SWITCH;
                process_casino_menu();
                ROM_BANK_RESET;
            }
        }
        else
        // If not pressing 'a', reset last_movement_time, so that
        // item can be purchased without delay
        {
            // Update last movement (used for purchase delay) to 0,
            // allowing them to purchase immediately after movement
            // to new tile. If sys_time happens to be overflowing,
            // then this won't help the user and will have to wait for the
            // purchase wait period.
            game_state.last_movement_time = 0U;
        }
    }
}

/*
 * check_car_collision
 *
 * Check if player has collided with car
 */
void check_car_collision()
{
    // Do not check if user is in building or player currently hurt/paused
    if (player_sprite.current_pause != 0 || game_state.current_building != S_B_NO_BUILDING)
        return;

    if (
        game_state.user_pos_tiles_x == road_car_sprite.current_location_x >> 3 &&
        (
            (game_state.user_pos_tiles_y == road_car_sprite.current_location_y >> 3) ||
            (game_state.user_pos_tiles_y == (road_car_sprite.current_location_y >> 3) - 1)
        )
    )
    {
        // Decrease HP
        decrease_hp(10);
        ROM_BANK_SPRITE_SWITCH;
        set_main_player_hurt(&player_sprite);
        ROM_BANK_RESET;
    }
}

/*
 * main_update_window
 *
 * update_window wrapper with ROM jumping
 */
void main_update_window(unsigned int return_bank)
{
    ROM_BANK_BUILDING_MENU_SWITCH;
    update_window();
    SWITCH_ROM_MBC5(return_bank);
}

/*
 * main_check_joy
 *
 * Switch to JOY rom and update joypad state
 */
void main_check_joy(unsigned int return_bank)
{
    ROM_BANK_JOY_CONFIG_SWITCH;
    check_user_input(&joypad_state);

    SWITCH_ROM_MBC5(return_bank);
}

UINT8 main_show_number(UINT8 start_x, UINT8 start_y, UINT8 max_digits, unsigned int value, unsigned int return_bank)
{
    UINT8 return_val;
    ROM_BANK_BUILDING_MENU_SWITCH;
    return_val = show_number(start_x, start_y, max_digits, value);
    SWITCH_ROM_MBC5(return_bank);
    return return_val;
}

/*
 * main_show_balance
 *
 * Call show_balance with rom jumping
 */
UINT8 main_show_balance(UINT8 itx_x, UINT8 itx_y, unsigned int return_bank)
{
    UINT8 return_val;
    ROM_BANK_BUILDING_MENU_SWITCH;
    return_val = show_balance(itx_x, itx_y);
    SWITCH_ROM_MBC5(return_bank);
    return return_val;
}

void main_show_signed_number(UINT8 start_x, UINT8 start_y, UINT8 max_digits, INT8 value, unsigned int return_bank)
{
    ROM_BANK_BUILDING_MENU_SWITCH;
    show_signed_number(start_x, start_y, max_digits, value);
    SWITCH_ROM_MBC5(return_bank);
}

void main_enter_bar_fight(unsigned int return_bank) NONBANKED
{
    ROM_BANK_BAR_FIGHT_SWITCH;
    enter_bar_fight();
    SWITCH_RAM_MBC5(return_bank);
}

void main()
{
    debug_address = 0xFFFA;

    // Set CPU fast to help with re-draw when scrolling
    cpu_fast();

    wait_vbl_done();

    while (1)
    {
        DISPLAY_OFF;

        // Enter splash screen loop
        ROM_BANK_OPENING_SCREEN_SWITCH;
        splash_screen_loop();
        ROM_BANK_RESET;

        // Enter opening screen loop
        ROM_BANK_OPENING_SCREEN_SWITCH;
        opening_screen_loop();
        ROM_BANK_RESET;
        SHOW_BKG;

        // Setup globals once opening screen has passed.
        // This means the randomisation that uses sys_time
        // will be more random based on amount of time
        // it takes player to go through opening screen
        setup_globals();

#if IN_TESTING && DEBUG_SHOW_BAR_FIGHT
        ROM_BANK_BAR_FIGHT_SWITCH;
        enter_bar_fight();
        ROM_BANK_RESET;
#endif

        // Initial setup of window and update with starting stats
        ROM_BANK_BUILDING_MENU_SWITCH;
        setup_window();
        update_window();
        ROM_BANK_RESET;
        SHOW_WIN;

        // Load background tiles. This turns display on, so run last
        setup_main_map();

        // And open the curtains!
        DISPLAY_ON;

        while (1)
        {
            wait_vbl_done();

            main_check_joy(ROM_BANK_DEFAULT);
            check_cheat();

            update_ai_positions();
            update_state();

            // Check for collision with car AI
            check_car_collision();

            if (game_state.game_ended != 0U)
            {
                break;
            }
        }
    }
}
