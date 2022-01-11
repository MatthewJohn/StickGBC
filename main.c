/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */


/*#include <gb/drawing.h>*/
#include <stdio.h>
#include <stdlib.h>
#include <gb/gb.h>
#include <gb/drawing.h>

#include "main_map_tileset.h"
#include "main_map.h"
#include "main_map_palette.h"
#include "main_map_boundaries.h"
#include "main_game.h"

#include "building_menu_tiles.h"
#include "building_menu_map.h"
#include "building_menu_palette.h"

#include "main_map_sprite_tileset.h"
#include "main_map_sprite_palette.h"

#include "opening_screen.h"

#include "background_time_colors.h"

#include "game_constants.h"
#include "game_state.c"
#include "menu_config.h"
#include "screen_state.c"
#include "window.h"
#include "sprite.h"
#include "joy.h"

#include "main.h"

UBYTE * debug_address;

// Location of user in world.
// This is not the sprites position on the screen
unsigned int user_pos_x;
unsigned int user_pos_y;

// Temporary storege for transfer of tile data and tile data vram1 data
UBYTE tile_data[1];
UWORD word_data[4];

// Storage for scratch palette data
UWORD scratch_palette_data[3][4];

joypad_state_t joypad_state;
UINT8 sprite_traveling_x;

// Game state
game_state_t game_state;
screen_state_t screen_state;

// Define global instance of menu config
menu_config_t *menu_config;
menu_state_t menu_state;

// Variables to store current main map location when
// changing to another map
unsigned int background_palette_itx_x;
unsigned int background_palette_itx_y;

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
unsigned int tile_data_offset;

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
    ROM_BANK_TILE_DATA_SWITCH;
    palette_data[0U] = background_time_colors[game_state.hour],
    palette_data[1U] = main_map_palette[1U];
    palette_data[2U] = main_map_palette[2U];
    palette_data[3U] = main_map_palette[3U];
    ROM_BANK_RESET;

    set_bkg_palette(0U, 1U, &palette_data);
}

void setup_globals()
{
    game_state.current_building = S_B_NO_BUILDING;
    game_state.last_movement_time = 0x0U;
    // @TODO make sure display works after 999
    game_state.days_passed = 0U;
    game_state.hour = S_HOUR_WAKEUP_NORMAL;

    // Start with $100
    game_state.balance = 100U;

    game_state.intelligence = 0U;
    game_state.strength = 0U;
    game_state.charm = 0U;
    game_state.karma = 0;

    game_state.hobo_given_money = 0U;
    game_state.hobo_given_beer = 0U;

    game_state.max_hp = S_INITIAL_BASE_HP + game_state.strength;
    game_state.hp = S_INITIAL_BASE_HP + game_state.strength;

    screen_state.displayed_sprites_x[skater_sprite.sprite_display_bit] = 0U;
    screen_state.displayed_sprites_y[skater_sprite.sprite_display_bit] = 1U;
    screen_state.displayed_sprites_x[dealer_sprite.sprite_display_bit] = 0U;
    screen_state.displayed_sprites_y[dealer_sprite.sprite_display_bit] = 0U;

    // Setup buildings that do not transition in some axis
    // and those that are displayed on start of game.
    screen_state.displayed_buildings_x = SC_HOUSE | SC_RESTAURANT | SC_SHOP | SC_PAWN;
    screen_state.displayed_buildings_y = SC_HOUSE | SC_UNIVERSITY | SC_NLI;

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

    screen_state.screen_location_x = 0x00U;
    screen_state.screen_location_x_tiles = 0x00U;
    screen_state.screen_location_y = 0x00U;
    screen_state.screen_location_y_tiles = 0x00U;
    sprite_traveling_x = 0;
    user_pos_x = 0x70U;
    user_pos_y = 0x70U;

#ifdef IN_TESTING
    // Add hacks for testing
    game_state.inventory[S_INVENTORY_SKATEBOARD] = 0x1U;
    game_state.inventory[S_INVENTORY_SMOKES] = 0x1U;
    game_state.balance = 1000U;
    game_state.max_hp = 100U;
    game_state.intelligence = 250U;
#endif
}

void update_ai_positions()
{
    ROM_BANK_SPRITE_SWITCH;
    move_ai_sprite(&screen_state, &skater_sprite);
    move_ai_sprite(&screen_state, &dealer_sprite);
    ROM_BANK_RESET;
}

void set_background_tiles(unsigned int tile_data_bank, unsigned int return_bank) NONBANKED
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
    SWITCH_ROM_MBC5(tile_data_bank);
    set_bkg_palette(0, 8, screen_state.background_color_palette);

    VBK_REG = 0;
    set_bkg_data(0, 8, screen_state.background_tiles);

    ROM_BANK_BUILDING_MENU_SWITCH;
    // Load in digits/symbols from building menu tiles, including clock tiles before it
    set_bkg_data(MENU_ROW_2_TILE_DATA_OFFSET, 31U, &(buildingmenutiles[(MENU_ROW_2_TILE_DATA_OFFSET) << 4U]));
    ROM_BANK_RESET;

    for (background_palette_itx_x = screen_state.draw_offset_x;
           background_palette_itx_x != max_x;
           background_palette_itx_x ++)
    {

#ifdef DEBUG_SET_BACKGROUND_SKIP
        // TEMP HACK TO NOT DRAW MOST OF BACKGROUND IN VRAM
        if (background_palette_itx_x == 0x10U)
            break;
#endif

        for (background_palette_itx_y = screen_state.draw_offset_y;
               background_palette_itx_y != max_y;
               background_palette_itx_y ++)
        {
            // Temp Test
            current_tile_itx = ((background_palette_itx_y) * screen_state.background_width) + background_palette_itx_x;

#ifdef DEBUG_SET_BACKGROUND_SKIP
            // TEMP HACK TO NOT DRAW MOST OF BACKGROUND IN VRAM
            if (background_palette_itx_y == 0x10U)
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

            SWITCH_ROM_MBC5(tile_data_bank);
            tile_data[0] = screen_state.background_tile_map[current_tile_data_itx] & 0x7F;
            ROM_BANK_RESET;

           VBK_REG = 0;
            // Set map data
            set_bkg_tiles(
                background_palette_itx_x & BACKGROUND_BUFFER_MAX_X,
                background_palette_itx_y & BACKGROUND_BUFFER_MAX_Y,
                1, 1,  // Only setting 1 tile
                 // Lookup tile from background tile map
                 &(tile_data[0])
            );

            VBK_REG = 1;

            SWITCH_ROM_MBC5(tile_data_bank);
            // Lookup tile from background tile map
            tile_data[0] = screen_state.background_tile_map[current_tile_palette_itx] & 0x07;

            // Check if current tile is flipped
            if (screen_state.background_tile_map[current_tile_palette_itx] & 0x08)
                tile_data[0] |= S_FLIPY;

            if (screen_state.background_tile_map[current_tile_palette_itx] & 0x10)
                tile_data[0] |= S_FLIPX;

            ROM_BANK_RESET;

            // Set palette data in VBK_REG1 for tile
            set_bkg_tiles(
                background_palette_itx_x & BACKGROUND_BUFFER_MAX_X,
                background_palette_itx_y & BACKGROUND_BUFFER_MAX_Y,
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

// Check if next position will hit a boundary
void check_boundary_hit() NONBANKED
{
    unsigned int new_x;
    unsigned int new_y;
    unsigned int new_tile_itx;

    new_x = user_pos_x + (signed int)joypad_state.travel_x;
    new_y = user_pos_y + (signed int)joypad_state.travel_y;

    // Check if traveling to new tile
    if ((joypad_state.travel_x == 1 && (new_x & 0x07U) == 0x00U) ||
        (joypad_state.travel_x == -1 && (new_x & 0x07U) == 0x07U) ||
        (joypad_state.travel_y == 1 && (new_y & 0x07U) == 0x00U) ||
        (joypad_state.travel_y == -1 && (new_y & 0x07U) == 0x07U))
    {
            new_tile_itx = X_Y_TO_TILE_INDEX(
                PIXEL_LOCATION_TO_TILE_COUNT(new_x),
                PIXEL_LOCATION_TO_TILE_COUNT(new_y)
            );

            ROM_BANK_TILE_DATA_SWITCH;
            // Check if new tile is a boundary
            if (TILE_INDEX_BIT_MAP_VALUE(MAIN_MAP_BOUNDARIES, new_tile_itx))
            {
                // Reset travel directions, acting as if user is not moving.
                joypad_state.travel_x = 0;
                joypad_state.travel_y = 0;
            }
            ROM_BANK_RESET;
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
    screen_state.draw_max_x = BACKGROUND_BUFFER_SIZE_X;
    screen_state.draw_max_y = BACKGROUND_BUFFER_SIZE_Y;

    set_background_tiles(ROM_BANK_TILE_DATA, 1U);
    ROM_BANK_SPRITE_SWITCH;
    setup_sprites(&skater_sprite, &dealer_sprite);
    ROM_BANK_RESET;

    // Move background to screen location
    scroll_bkg(
        screen_state.screen_location_x & BACKGROUND_BUFFER_SIZE_PIXELS_MAX_X,
        screen_state.screen_location_y & BACKGROUND_BUFFER_SIZE_PIXELS_MAX_Y
    );

    // Load additional tiles required for main map
    ROM_BANK_TILE_DATA_SWITCH;
    set_bkg_data(8U, 5U, &(mainmaptiles[8U << 4]));

    // Load currently displayed buildings
    load_building_tile_data(&screen_state);

    ROM_BANK_RESET;

    update_background_color();

    DISPLAY_ON;
}

void load_menu_tiles() NONBANKED
{
    unsigned int menu_item_itx;
    move_bkg(0, 0);

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
                    tile_data_index += tile_data_offset;

                    ROM_BANK_BUILDING_MENU_SWITCH;

                    // Load tile data for menu item based on tile data offset
                    // in menu config and tile config in menu tile array
                    set_bkg_data(
                        tile_data_index,
                        1,
                        &(buildingmenutiles[tile_data_index << 4])
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
}

void setup_building_menu()
{
    DISPLAY_OFF;
    // Update globals for references to map/tile information
    screen_state.background_tile_map = buildingmenumap;
    screen_state.background_tiles = buildingmenutiles;
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
        // Default to hand gun
        menu_state.current_item_x = 0U;
        menu_state.current_item_y = 1U;
        menu_config = &menu_config_pawn;
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

    HIDE_SPRITES;
    // Reload background tiles
    set_background_tiles(ROM_BANK_BUILDING_MENU, 1U);

    load_menu_tiles();

    // Highlight currently selected item
    ROM_BANK_MENU_CONFIG_SWITCH;
    set_menu_item_color(&menu_state, menu_config, MENU_ITEM_SELECTED_PALETTE);
    ROM_BANK_RESET;

    DISPLAY_ON;
}

// Attempt to 'enter' a building if user is in
// interaction zone
void check_building_enter()
{
    unsigned int tile_itx = X_Y_TO_TILE_INDEX(
        PIXEL_LOCATION_TO_TILE_COUNT(user_pos_x),
        PIXEL_LOCATION_TO_TILE_COUNT(user_pos_y)
    );

    // Check for entering house
    if (tile_itx == 0x321U)
    {
        game_state.current_building = S_B_HOUSE;
        setup_building_menu();
    }
    // Check for entering restaurant
    else if (tile_itx == 0x76D)
    {
        game_state.current_building = S_B_RESTAURANT;
        setup_building_menu();
    }
    // Check for entering shop, through either door
    else if (tile_itx == 0xB69U || tile_itx == 0xBB1U)
    {
        game_state.current_building = S_B_SHOP;
        setup_building_menu();
    }
    // Check for entering pawn shop
    else if (tile_itx == 0xDF1U)
    {
        game_state.current_building = S_B_PAWN;
        setup_building_menu();
    }
    else if (tile_itx == 0x6B1U || tile_itx == 0x6B2U)
    {
        game_state.current_building = S_B_UNIVERSITY;
        setup_building_menu();
    }
    else if (tile_itx == 0x37BU || tile_itx == 0x37CU || tile_itx == 0x37DU)
    {
        game_state.current_building = S_B_SKATER;
        setup_building_menu();
    }
    else if (tile_itx == 0x4A9U || tile_itx == 0x4F1)
    {
        game_state.current_building = S_B_NLI;
        setup_building_menu();
    }
    else if (tile_itx == 0xD19U || tile_itx == 0xD61U)
    {
        game_state.current_building = S_B_DEALER;
        setup_building_menu();
    }
    else if (tile_itx == 0x8D6U || tile_itx == 0x91EU)
    {
        game_state.current_building = S_B_HOBO;
        setup_building_menu();
    }
    else if (tile_itx == 0x964U || tile_itx == 0x9ACU)
    {
        game_state.current_building = S_B_BAR;
        setup_building_menu();
    }
//
//    // Temporary jump to building
//    game_state.current_building = S_B_HOBO;
//    setup_building_menu();
}

// Check if win/lose conditions have been met
void check_end_game()
{

}

void purchase_food(UINT8 cost, UINT8 gained_hp)
{
    // Breaking the rules using >=, but
    // only performed when buying an item
    // and currency is decimal, making very difficult
    // to do using bit shifting (and at least probably
    // less CPU intensive)
    if (HAS_MONEY(cost))
    {
        game_state.balance -= cost;

        // If new HP would exeed max HP, limit new HP to difference
        if (gained_hp >= (game_state.max_hp - game_state.hp))
            game_state.hp = game_state.max_hp;
        else
            // Otherwise, add new HP to HP
            game_state.hp += gained_hp;

        ROM_BANK_BUILDING_MENU_SWITCH;
        update_window(&game_state);
        ROM_BANK_RESET;
    }
}

void modify_karma(INT8 karma_change)
{
    game_state.karma += karma_change;
}

void increase_intelligence(UINT8 cost, UINT8 number_of_hours, UINT8 intelligence)
{
    if (
        HAS_MONEY(cost) &&
        game_state.intelligence != S_MAX_INTELLIGENCE &&
        (S_HOURS_PER_DAY - game_state.hour) >= number_of_hours
    )
    {
        game_state.balance -= cost;
        game_state.hour += number_of_hours;
        game_state.intelligence += intelligence;

        modify_karma(1);

        ROM_BANK_BUILDING_MENU_SWITCH;
        update_window(&game_state);
        ROM_BANK_RESET;
    }
}

UINT8 increase_charm(UINT8 cost, UINT8 number_of_hours, UINT8 charm)
{
    if (
        HAS_MONEY(cost) &&
        game_state.charm != S_MAX_CHARM &&
        (S_HOURS_PER_DAY - game_state.hour) >= number_of_hours
    )
    {
        game_state.balance -= cost;
        game_state.hour += number_of_hours;
        game_state.charm += charm;

        ROM_BANK_BUILDING_MENU_SWITCH;
        update_window(&game_state);
        ROM_BANK_RESET;
        return 1U;
    }
    return 0U;
}

void increase_strength(UINT8 cost, UINT8 number_of_hours, UINT8 strength)
{
    if (
        HAS_MONEY(cost) &&
        game_state.strength != S_MAX_STRENGTH &&
        (S_HOURS_PER_DAY - game_state.hour) >= number_of_hours
    )
    {
        game_state.balance -= cost;
        game_state.hour += number_of_hours;
        game_state.strength += strength;
        game_state.max_hp += strength;

        modify_karma(1);

        ROM_BANK_BUILDING_MENU_SWITCH;
        update_window(&game_state);
        ROM_BANK_RESET;
    }
}

UINT8 purchase_item(unsigned int cost, UINT8 inventory_item)
{
    // Breaking the rules using >=, but
    // only performed when buying an item
    // and currency is decimal, making very difficult
    // to do using bit shifting (and at least probably
    // less CPU intensive)

    if (HAS_MONEY(cost) && game_state.inventory[inventory_item] != S_MAX_INVENTORY_ITEM)
    {
        game_state.balance -= cost;
        game_state.inventory[inventory_item] += 1U;

        ROM_BANK_BUILDING_MENU_SWITCH;
        update_window(&game_state);
        ROM_BANK_RESET;

        return 0x1U;
    }

    // If item not purchased, return 0
    return 0x0U;
}

void do_work(unsigned int pay_per_hour, unsigned int number_of_hours)
{
    if ((S_HOURS_PER_DAY - game_state.hour) >= number_of_hours)
    {
        // Increase balance and increase time of day
        game_state.balance += (pay_per_hour * number_of_hours);
        game_state.hour += number_of_hours;

        modify_karma(1);
    }

    ROM_BANK_BUILDING_MENU_SWITCH;
    update_window(&game_state);
    ROM_BANK_RESET;
}

// Move selected menu item to new value and update highlighting
void move_to_menu_item(UINT8 new_x, UINT8 new_y)
{
    // Deselect currently selected item
    ROM_BANK_MENU_CONFIG_SWITCH;
    set_menu_item_color(&menu_state, menu_config, MENU_ITEM_DEFAULT_PALETTE);
    ROM_BANK_RESET;

    menu_state.current_item_x = new_x;
    menu_state.current_item_y = new_y;

    // Highlight new menu item
    ROM_BANK_MENU_CONFIG_SWITCH;
    set_menu_item_color(&menu_state, menu_config, MENU_ITEM_SELECTED_PALETTE);
    ROM_BANK_RESET;
}

void apply_for_job_promotion()
{
    // Check current if applying for job
    if (
        menu_config->items[MENU_NLI_PROMOTION_ITEM] == MENU_ITEM_INDEX_APPLY_FOR_JOB &&
        game_state.intelligence >= 20U
    )
    {
        menu_config_restaurant.items[3U] = MENU_ITEM_INDEX_EMPTY;
        menu_config->items[MENU_NLI_PROMOTION_ITEM] = MENU_ITEM_INDEX_APPLY_FOR_PROMOTION;
        menu_config->items[MENU_NLI_WORK_ITEM] = MENU_ITEM_INDEX_WORK_JANITOR;
        modify_karma(1);
    }
    else if (
        menu_config->items[MENU_NLI_WORK_ITEM] == MENU_ITEM_INDEX_WORK_JANITOR &&
        game_state.intelligence >= 40U
    )
    {
        menu_config->items[MENU_NLI_WORK_ITEM] = MENU_ITEM_INDEX_WORK_MAIL_CLERK;
        modify_karma(3);
    }
    else if (
        menu_config->items[MENU_NLI_WORK_ITEM] == MENU_ITEM_INDEX_WORK_MAIL_CLERK &&
        game_state.intelligence >= 75U
    )
    {
        menu_config->items[MENU_NLI_WORK_ITEM] = MENU_ITEM_INDEX_WORK_SALESMAN;
        modify_karma(3);
    }
    else if (
        menu_config->items[MENU_NLI_WORK_ITEM] == MENU_ITEM_INDEX_WORK_SALESMAN &&
        game_state.intelligence >= 120U
    )
    {
        menu_config->items[MENU_NLI_WORK_ITEM] = MENU_ITEM_INDEX_WORK_EXECUTIVE;
        modify_karma(3);
    }
    else if (
        menu_config->items[MENU_NLI_WORK_ITEM] == MENU_ITEM_INDEX_WORK_EXECUTIVE &&
        game_state.intelligence >= 180U
    )
    {
        menu_config->items[MENU_NLI_WORK_ITEM] = MENU_ITEM_INDEX_WORK_VP;
        modify_karma(3);
    }
    else if (
        menu_config->items[MENU_NLI_WORK_ITEM] == MENU_ITEM_INDEX_WORK_VP &&
        game_state.intelligence >= 250U
    )
    {
        menu_config->items[MENU_NLI_WORK_ITEM] = MENU_ITEM_INDEX_WORK_CEO;
        menu_config->items[MENU_NLI_PROMOTION_ITEM] = MENU_ITEM_INDEX_EMPTY;
        modify_karma(3);
    }
    else
    {
        // If no job available, return early
        return;
    }

    // Update menu with tiles for new job
    load_menu_tiles();

    // Select 'work' item for new job
    move_to_menu_item(1U, 3U);
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

// Move current menu item to exit
void move_menu_to_exit()
{
    move_to_menu_item(1U, 0U);
}

// Show stats screen
void show_stats_screen() NONBANKED
{
    game_state.current_building = S_B_STATS;
    setup_building_menu();

    // Update tiles for each of the stats to display the current values

    // Intelligence
    ROM_BANK_BUILDING_MENU_SWITCH;
    // MENU_ITEM_SCREEN_OFFSET_LEFT, MENU_ITEM_SCREEN_OFFSET_TOP + 3U (for second item)
    show_number(3U, 6U, 3U, game_state.intelligence);
    show_number(11U, 6U, 3U, game_state.strength);
    show_number(3U, 9U, 3U, game_state.charm);
    show_signed_number(11U, 9U, 3U, game_state.karma);
    ROM_BANK_RESET;
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

    setup_building_menu();

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
    UINT8 main_player_tileset;

    if (game_state.current_building == S_B_NO_BUILDING)
    {
        check_boundary_hit();

        if (game_state.inventory[S_INVENTORY_SKATEBOARD] && joypad_state.b_pressed)
        {
            movement_bit_push = SKATEBOARD_SPEED_DELAY;
            main_player_tileset = SPRITE_TILESET_SKATEBOARD;
        }
        else
        {
            movement_bit_push = WALK_SPEED_DELAY;
            main_player_tileset = SPRITE_TILESET_WALK;
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
        user_screen_pos_x = user_pos_x - screen_state.screen_location_x;
        user_screen_pos_y = user_pos_y - screen_state.screen_location_y;

        user_pos_x += (signed int)joypad_state.travel_x;
        user_pos_y += (signed int)joypad_state.travel_y;

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
            user_screen_pos_x = user_pos_x - screen_state.screen_location_x;
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
            user_screen_pos_y = user_pos_y - screen_state.screen_location_y;
            move_y = 0;
        }

        // Temporary fix to help with diagonal movement
        // move_background(0, move_y);
        if (move_x != 0)
        {
            move_background(move_x, 0);

            // Check when on tile boundary (NOTE this only works for movement in positive directions,
            // but doesn't matter for now).
            if (screen_state.screen_location_x_tilepixel == 0U)
            {
                ROM_BANK_TILE_DATA_SWITCH;
                if (move_x == 1)
                    load_buildings_x_right(&screen_state, &skater_sprite, &dealer_sprite);
                else
                    load_buildings_x_left(&screen_state, &skater_sprite, &dealer_sprite);
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
                    load_buildings_y_down(&screen_state, &skater_sprite, &dealer_sprite);
                else
                    load_buildings_y_up(&screen_state, &skater_sprite, &dealer_sprite);
                ROM_BANK_RESET;
            }
        }

        // Move sprite to new location
        move_sprite(
            0,
            user_screen_pos_x + SPRITE_OFFSET_X,
            user_screen_pos_y + SPRITE_OFFSET_Y
        );

        ROM_BANK_SPRITE_SWITCH;
        set_sprite_direction(
            PLAYER_SPRITE_INDEX,
            main_player_tileset,
            PLAYER_SPRITE_PALETTE,
            joypad_state.travel_x,
            joypad_state.travel_y
        );
        ROM_BANK_RESET;

        if (joypad_state.a_pressed)
            check_building_enter();

        else if (joypad_state.select_pressed) {
            show_stats_screen();
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
            // to new tile
            game_state.last_movement_time = 0;

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
                    move_to_menu_item(new_menu_x, menu_state.current_item_y);
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
                        move_to_menu_item(new_menu_x, itx);
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
                        move_to_menu_item(new_menu_x, itx - 1U);
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

        // Check if moving menu item
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
            if ((game_state.last_movement_time >> PURCHASE_ITEM_WAIT_PERIOD_BIT_SHIFT)  ==
                (sys_time >> PURCHASE_ITEM_WAIT_PERIOD_BIT_SHIFT))
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
            if (game_state.current_building == S_B_HOUSE && menu_state.current_item_y == 3U)
            {
                // Set intiial wakeup time
                game_state.hour = S_HOUR_WAKEUP_NORMAL;

                // Check if user has caffeine
                if (game_state.inventory[S_INVENTORY_CAFFEINE_PILLS])
                {
                    game_state.inventory[S_INVENTORY_CAFFEINE_PILLS] -= 1U;
                    game_state.hour -= S_HOUR_CAFFEINE_TIME_GAIN;
                }

                // Check if alarm clock is owned
                if (game_state.inventory[S_INVENTORY_ALARM_CLOCK])
                {
                    game_state.hour -= S_HOUR_ALARM_CLOCK_TIME_GAIN;
                }
                game_state.days_passed ++;
                check_end_game();

                DISPLAY_OFF;

                // 'Purchase food' to increase HP by 20
                purchase_food(0U, 20U);

                ROM_BANK_BUILDING_MENU_SWITCH;
                update_window(&game_state);
                ROM_BANK_RESET;

                // Wait for 1 second 1 second
                delay(DELAY_SLEEP);
                DISPLAY_ON;
            }
            // Handle menu selections from restaurant
            else if (game_state.current_building == S_B_RESTAURANT)
            {
                if (menu_state.current_item_x == 0U)
                {
                    if (menu_state.current_item_y == 0U)  // Milkshake
                    {
                        purchase_food(8U, 12U);
                    }
                    else if (menu_state.current_item_y == 1U)  // Fries
                    {
                        purchase_food(12U, 20U);
                    }
                    else if (menu_state.current_item_y == 2U)  // Cheeseburger
                    {
                        purchase_food(25U, 40U);
                    }
                    else if (menu_state.current_item_y == 3U)  // Triple Burger
                    {
                        purchase_food(50U, 80U);
                    }
                }
                else  // x row 1
                {
                    if (menu_state.current_item_y == 1U)  // Work
                    {
                        do_work(6U, 6U);
                    }
                }
            }
            else if (game_state.current_building == S_B_SHOP)
            {
                if (menu_state.current_item_x == 0U)
                {
                    if (menu_state.current_item_y == 1U)  // Slushee
                    {
                        purchase_food(1U, 1U);
                    }
                    else if (menu_state.current_item_y == 2U)  // Candy Bar
                    {
                        purchase_food(2U, 3U);
                    }
                    else if (menu_state.current_item_y == 3U)  // Nachos
                    {
                        purchase_food(4U, 7U);
                    }
                }
                else  // x row 1
                {
                    if (menu_state.current_item_y == 1U)  // Smokes
                    {
                        purchase_item(10U, S_INVENTORY_SMOKES);
                    }
                    else if (menu_state.current_item_y == 2U)  // Caffeine Pills
                    {
                        purchase_item(45U, S_INVENTORY_CAFFEINE_PILLS);
                    }
                }
            }

            else if (game_state.current_building == S_B_PAWN)
            {
                if (menu_state.current_item_x == 0U)
                {
                    if (menu_state.current_item_y == 1U)  // Handgun
                    {
                        // Attempt to purchase item
                        if (purchase_item(400U, S_INVENTORY_HAND_GUN))
                        {
                            // Remove from menu, if successful and reload menu tiles
                            menu_config->items[2U] = MENU_ITEM_INDEX_EMPTY;
                            load_menu_tiles();
                            move_menu_to_exit();
                        }
                    }
                    else if (menu_state.current_item_y == 2U)  // Knife
                    {
                        if (purchase_item(100U, S_INVENTORY_KNIFE))
                        {
                            menu_config->items[4U] = MENU_ITEM_INDEX_EMPTY;
                            load_menu_tiles();
                            move_menu_to_exit();
                        }
                    }
                    else if (menu_state.current_item_y == 3U)  // Alarm Clock
                    {
                        if (purchase_item(200U, S_INVENTORY_ALARM_CLOCK))
                        {
                            menu_config->items[6U] = MENU_ITEM_INDEX_EMPTY;
                            load_menu_tiles();
                            move_menu_to_exit();
                        }
                    }
                }
                else  // x row 1
                {
                    if (menu_state.current_item_y == 1U)  // Cellphone
                    {
                        if (purchase_item(200U, S_INVENTORY_CELL_PHONE))
                        {
                            menu_config->items[3U] = MENU_ITEM_INDEX_EMPTY;
                            load_menu_tiles();
                            move_menu_to_exit();
                        }
                    }
                }
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
                if (menu_state.current_item_x == 0U && menu_state.current_item_y == 0U)
                {
                    if (game_state.inventory[S_INVENTORY_SMOKES])
                    {
                        // Remove smokes and give skateboard
                        if (DAY_TIME_REMAINING >= 1U)
                        {
                            game_state.hour += 1U;
                            game_state.inventory[S_INVENTORY_SMOKES] -= 1U;
                            game_state.inventory[S_INVENTORY_SKATEBOARD] = 1U;
                            ROM_BANK_BUILDING_MENU_SWITCH;
                            update_window(&game_state);
                            ROM_BANK_RESET;

                            // Decrease karma
                            modify_karma(-2);
                        }
                    }
                }
            }
            else if (game_state.current_building == S_B_NLI)
            {
                if (menu_state.current_item_x == 1U)
                {
                    if (menu_state.current_item_y == 2U)
                    {
                        // Check if applying for job
                        apply_for_job_promotion();
                    }
                    else if (menu_state.current_item_y == 3U)
                    {
                        do_nli_work();
                    }
                }
            }
            else if (game_state.current_building == S_B_DEALER)
            {
                if (menu_state.current_item_x == 0U && menu_state.current_item_y == 2U)
                    purchase_item(400U, S_INVENTORY_COCAINE);
            }
            else if (game_state.current_building == S_B_HOBO)
            {
                if (menu_state.current_item_x == 0U && menu_state.current_item_y == 2U)
                {
                    if (game_state.hobo_given_money == 0U)
                    {
                        if (increase_charm(10U, 1U, 6U))
                        {
                            // Mark as having visited hobo, so he doesn't give us charm again.
                            game_state.hobo_given_money = 1U;

                            // Give 2 karma
                            modify_karma(2);
                        }
                    }
                    else  // Paying money and not getting charm
                    {
                        if (HAS_MONEY(10U))
                        {
                            game_state.balance -= 10U;
                            ROM_BANK_BUILDING_MENU_SWITCH;
                            update_window(&game_state);
                            ROM_BANK_RESET;

                            // Give 2 karma
                            modify_karma(2);
                        }
                    }
                }
                else if (menu_state.current_item_x == 1U && menu_state.current_item_y == 2U)
                {
                    // Give bottle of beer
                    if (game_state.inventory[S_INVENTORY_BOTTLE_OF_BEER] && DAY_TIME_REMAINING >= 1U)
                    {
                        if (game_state.hobo_given_beer == 0U)
                        {
                            increase_charm(0U, 1U, 8U);
                            game_state.hobo_given_beer = 1U;
                        }
                        else
                        {
                            game_state.hour += 1U;
                        }
                        game_state.inventory[S_INVENTORY_BOTTLE_OF_BEER] -= 1U;
                    }
                }
            }
            else if (game_state.current_building == S_B_BAR)
            {
                if (menu_state.current_item_x == 0U && menu_state.current_item_y == 1U)
                {
                    increase_charm(20U, 2U, 2U);
                }
                else if (menu_state.current_item_x == 1U && menu_state.current_item_y == 1U)
                {
                    purchase_item(30U, S_INVENTORY_BOTTLE_OF_BEER);
                    // Enable give bottle of beer in hobo menu
                    menu_config_hobo.items[5U] = MENU_ITEM_INDEX_GIVE_BEER;
                }
            }
        }
    }
}

// Switch to JOY rom and update joypad state
void main_check_joy(unsigned int return_bank)
{
    ROM_BANK_JOY_CONFIG_SWITCH;
    check_user_input(&joypad_state);

    SWITCH_ROM_MBC5(return_bank);
}

void main()
{
    debug_address = 0xFFFA;

    DISPLAY_OFF;
    setup_globals();

    wait_vbl_done();

    // Enter opening screen loop
    ROM_BANK_OPENING_SCREEN_SWITCH;
    opening_screen_loop(&screen_state, &joypad_state);
    SHOW_BKG;

    // Initial setup of window and update with starting stats
    ROM_BANK_BUILDING_MENU_SWITCH;
    setup_window();
    update_window(&game_state);
    ROM_BANK_RESET;
    SHOW_WIN;

    // Load background tiles. This turns display on, so run last
    setup_main_map();

    // And open the curtains!
    DISPLAY_ON;

        while(1) {
                wait_vbl_done();

                main_check_joy(ROM_BANK_DEFAULT);

                update_ai_positions();
                update_state();

                // Temporarily remove delay to speed debugging
                //delay(50);
        }
}
