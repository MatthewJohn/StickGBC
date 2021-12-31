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

#include "building_menu_tiles.h"
#include "building_menu_map.h"
#include "building_menu_palette.h"

#include "main_map_sprite_tileset.h"

#include "game_constants.h"
#include "game_state.c"
#include "menu_config.h"
#include "screen_state.c"
#include "window.h"

#define ROM_BANK_RESET SWITCH_ROM_MBC5(1)
#define ROM_BANK_TILE_DATA SWITCH_ROM_MBC5(5)
#define ROM_BANK_MENU_CONFIG SWITCH_ROM_MBC5(6)


UBYTE * debug_address;

// Location of user in world.
// This is not the sprites position on the screen
unsigned int user_pos_x;
unsigned int user_pos_y;

// Temporary storege for transfer of tile data and tile data vram1 data
UBYTE tile_data[12];
UWORD word_data[4];

// Storage for scratch palette data
UWORD scratch_palette_data[3][4];

// Location of screen compared to map
unsigned int screen_location_x;
unsigned int screen_location_y;
// These are pre-calculated bit shifts of screen_location.
// DO NOT manually change outside of position updating method.
// This is the current user position in tiles.
unsigned int screen_location_x_tiles;
unsigned int screen_location_y_tiles;
// These are pre-calculated ANDs of screen_location
// DO NOT  manually change outside of position updating method.
// This is the current pixel location of user within current tile.
unsigned int screen_location_x_tilepixel;
unsigned int screen_location_y_tilepixel;

// Determine which way user needs to travel
signed int travel_x;
signed int travel_y;
unsigned short a_pressed;
UINT8 sprite_traveling_x;
UINT8 sprite_prop_data;

// Game state
game_state_t game_state;
screen_state_t screen_state;

// Define global instance of menu config
menu_config_t *menu_config;
menu_state_t menu_state;

// Globals used when redrawing map
unsigned char *background_tile_map;
unsigned char *background_tiles;
unsigned char *background_tile_palette;
unsigned char *background_color_palette;
unsigned int background_width;
unsigned char *sprite_tiles;
unsigned char *sprite_palette;
unsigned int DRAW_OFFSET_X;
unsigned int DRAW_OFFSET_Y;
unsigned int DRAW_MAX_X;
unsigned int DRAW_MAX_Y;
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


void add_debug(UBYTE val)
{
    *debug_address = val;
    debug_address ++;
}

void load_building_tile_data() NONBANKED
{
    // Load house data from tile 8 to tile
    VBK_REG = 0;
    if (screen_state.displayed_buildings & SC_HOUSE)
    {
        ROM_BANK_TILE_DATA;
        set_bkg_data(13, 1, &(mainmaptiles[13 << 4]));
        ROM_BANK_RESET;
    }
    if (screen_state.displayed_buildings & SC_RESTAURANT)
    {
        ROM_BANK_TILE_DATA;
        set_bkg_data(15, 2, &(mainmaptiles[15 << 4]));
        ROM_BANK_RESET;
        // Set palette data
        word_data[0] = RGB(0, 0, 0);
        word_data[1] = RGB(31, 22, 8);
        word_data[2] = RGB(25, 0, 0);
        word_data[3] = RGB(13, 12, 1 );
        set_bkg_palette(PALETTE_SCRATCH_3, 1, word_data);
    }
    if (screen_state.displayed_buildings & SC_SHOP)
    {
        ROM_BANK_TILE_DATA;
        set_bkg_data(18U, 5U, &(mainmaptiles[18U << 4]));
        ROM_BANK_RESET;
        word_data[0] = RGB(31, 21, 5);
        word_data[1] = RGB(1, 0, 2);
        word_data[2] = RGB(4, 20, 0);
        word_data[3] = RGB(26, 16, 0 );
        set_bkg_palette(PALETTE_SCRATCH_2, 1, word_data);
    }
    if (screen_state.displayed_buildings & SC_PAWN)
    {
        ROM_BANK_TILE_DATA;
        set_bkg_data(23U, 4U, &(mainmaptiles[23U << 4]));
        ROM_BANK_RESET;
        scratch_palette_data[0U][0U] = RGB(10U, 1U, 16U);
        scratch_palette_data[0U][1U] = RGB(31U, 31U, 31U);
        scratch_palette_data[0U][3U] = RGB(15U, 6U, 31U);
        set_bkg_palette(PALETTE_SCRATCH_1, 1, &(scratch_palette_data[0]));
    }
}

void setup_globals()
{
    game_state.current_building = S_B_NO_BUILDING;
    // @TODO make sure display works after 999
    game_state.days_passed = 0U;
    game_state.hour = S_HOUR_WAKEUP_NORMAL;
    // Start with $100
    game_state.balance = 100U;

    game_state.max_hp = 23U;
    game_state.hp = 23U;

    screen_state.displayed_buildings = SC_HOUSE;

    // Setup inventory items
    game_state.inventory[S_INVENTORY_SMOKES] = 0x0U;
    game_state.inventory[S_INVENTORY_CAFFEINE_PILLS] = 0x0U;
    game_state.inventory[S_INVENTORY_HAND_GUN] = 0x0U;
    game_state.inventory[S_INVENTORY_KNIFE] = 0x0U;
    game_state.inventory[S_INVENTORY_ALARM_CLOCK] = 0x0U;
    game_state.inventory[S_INVENTORY_CELL_PHONE] = 0x0U;

    screen_location_x = 0x00U;
    screen_location_x_tiles = 0x00U;
    screen_location_y = 0x00U;
    screen_location_y_tiles = 0x00U;
    sprite_traveling_x = 0;
    user_pos_x = 0x70U;
    user_pos_y = 0x70U;
}

void setup_sprite()
{
    // Load single sprite tile
    HIDE_SPRITES;
    ROM_BANK_TILE_DATA;
    set_sprite_data(0, 3, sprite_tiles);
    set_sprite_palette(0, 1, sprite_palette);
    ROM_BANK_RESET;
    set_sprite_tile(0, 0);
    SHOW_SPRITES;
}

void setup_window()
{
    // Set transparency for all tiles
    tile_data[0] = 0x00U;
    // bit 0-2 palette
    // bit 3 - tile bank
    // bit 4 - unused
    // bit 5 - horizontal flip
    // bit 6 - verical flip
    // bit 7 Set piority flag and color palette to 1
    tile_data[1] = 0x81U;
    for (itx_x = 0U; itx_x != SCREEN_WIDTH_TILES; itx_x ++)
    {
        for (itx_y = 0U; itx_y != SCREEN_HEIGHT_TILES; itx_y ++)
        {
            VBK_REG = 0;
            set_win_tiles(itx_x, itx_y, 1, 1, &(tile_data[0]));
            VBK_REG = 1;
            set_win_tiles(itx_x, itx_y, 1, 1, &(tile_data[1]));
        }
    }
    VBK_REG = 0;
    
    // Setup borders
    tile_data[0] = 0U;
    set_win_tiles(0U, 0U, 1U, 1U, &(tile_data[0]));
    set_win_tiles(0U, 1U, 1U, 1U, &(tile_data[0]));
    set_win_tiles(19U, 0U, 1U, 1U, &(tile_data[0]));
    set_win_tiles(19U, 1U, 1U, 1U, &(tile_data[0]));
    
    // Setup 'days''
    tile_data[0] = MENU_ROW_2_TILE_DATA_OFFSET + 14U;
    set_win_tiles(WINDOW_MAX_DIGITS_DAYS + 2U, 0U, 1U, 1U, &(tile_data[0]));
    tile_data[0] = MENU_ROW_2_TILE_DATA_OFFSET + 15U;
    set_win_tiles(WINDOW_MAX_DIGITS_DAYS + 3U, 0U, 1U, 1U, &(tile_data[0]));

    // Move window up to only display 2 rows at top of screen
    move_win(7, (SCREEN_HEIGHT_TILES - 2U) << 3);
}

void set_background_tiles() NONBANKED
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
    max_x = DRAW_OFFSET_X + DRAW_MAX_X;
    max_y = DRAW_OFFSET_Y + DRAW_MAX_Y;

    // Load color palette
    ROM_BANK_TILE_DATA;
    set_bkg_palette(0, 8, background_color_palette);

    VBK_REG = 0;
    set_bkg_data(0, 8, background_tiles);

    // Load in digits/symbols from building menu tiles, including clock tiles before it
    set_bkg_data(MENU_ROW_2_TILE_DATA_OFFSET - 3U, 21U, &(buildingmenutiles[(MENU_ROW_2_TILE_DATA_OFFSET - 3U) << 4U]));
    ROM_BANK_RESET;

    for (background_palette_itx_x = DRAW_OFFSET_X;
           background_palette_itx_x != max_x;
           background_palette_itx_x ++)
    {
        // UNCOMMENT TO ADD TEMP HACK TO NOT DRAW MOST OF BACKGROUND IN VRAM
//        if (background_palette_itx_x == 0x10U)
//            break;
        for (background_palette_itx_y = DRAW_OFFSET_Y;
               background_palette_itx_y != max_y;
               background_palette_itx_y ++)
        {
            // Temp Test
            current_tile_itx = ((background_palette_itx_y) * background_width) + background_palette_itx_x;

            // UNCOMMENT TO ADD TEMP HACK TO NOT DRAW MOST OF BACKGROUND IN VRAM
//            if (background_palette_itx_y == 0x10U/)
//                break;

            // Tile data is split across two bytes. In the layout:
            // 0-6 - tile number
            // 7 - blank
            // 8-A - palette number
            // B - vertical flip
            // C - horizontal flip
            current_tile_data_itx = current_tile_itx * 2;
            current_tile_palette_itx = current_tile_data_itx + 1;

            ROM_BANK_TILE_DATA;
            tile_data[0] = background_tile_map[current_tile_data_itx] & 0x7F;
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

            ROM_BANK_TILE_DATA;
            // Lookup tile from background tile map
            tile_data[0] = background_tile_map[current_tile_palette_itx] & 0x07;

            // Check if current tile is flipped
            if (background_tile_map[current_tile_palette_itx] & 0x08)
                tile_data[0] |= S_FLIPY;

            if (background_tile_map[current_tile_palette_itx] & 0x10)
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
}

void check_user_input()
{
    UINT8 keys = joypad();
    travel_x = 0;
    travel_y = 0;
    a_pressed = 0U;

    // Check directional 
    if (keys & J_UP)
        travel_y --;
    if (keys & J_DOWN)
        travel_y ++;
    if (keys & J_LEFT)
        travel_x --;
    if (keys & J_RIGHT)
        travel_x ++;
    if (keys & J_A)
        a_pressed = 1U;
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

    screen_location_x += move_x;
    screen_location_y += move_y;
    screen_location_x_tiles = screen_location_x >> 3;
    screen_location_y_tiles = screen_location_y >> 3;
    screen_location_x_tilepixel = screen_location_x & 0x07U;
    screen_location_y_tilepixel = screen_location_y & 0x07U;

    // Set current redraw in X to current user position (bit shift to remove pixels within tile) plus
    // current frame buffer size + redraw offset.
    // Mask with vram tile size in X, as a form of cheap modulus (which we can do as it is a power of 2)
    base_itx_x = screen_location_x >> 3;
    if (move_x == 1)
        // If moving to right, start redraw tile after
        // Calulate entire width of screen, plus one tile either side.
        base_itx_x += (SCREEN_TILE_MAX_X + 2U);
    else if (move_x == -1)
        // If moving left, redraw tile before
        base_itx_x -= 1U;

    // See X alternative
    base_itx_y = screen_location_y >> 3;
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
        itx_y_max = base_itx_y + (3U * (screen_location_x_tilepixel + 1U)) + 1U;
        for (itx_y = base_itx_y + (3U * screen_location_x_tilepixel) - 1U;
               itx_y != itx_y_max;
               itx_y ++)
        {
            // Work out current tile - base on tile location in frame buffer plus current map in vram location
            current_tile_itx = (itx_y * mainmapWidth) + itx_x;

            current_tile_data_itx = current_tile_itx * 2;
            current_tile_palette_itx = current_tile_data_itx + 1;

            ROM_BANK_TILE_DATA;
            tile_data[0] = background_tile_map[current_tile_data_itx] & 0x7F;
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
            ROM_BANK_TILE_DATA;
            tile_data[0] = background_tile_map[current_tile_palette_itx] & 0x07;

            // Check if current tile is flipped
            if (background_tile_map[current_tile_palette_itx] & 0x08)
                tile_data[0] |= S_FLIPY;

            if (background_tile_map[current_tile_palette_itx] & 0x10)
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
        itx_x_max = base_itx_x + (3U * (screen_location_y_tilepixel + 1U)) + 1U;
        for (itx_x = base_itx_x + (3U * screen_location_y_tilepixel) - 1U;
               itx_x != itx_x_max;
               itx_x ++)
        {
            // Work out current tile - base on tile location in frame buffer plus current map in vram location
            current_tile_itx = (itx_y  * mainmapWidth) + itx_x;

            current_tile_data_itx = current_tile_itx * 2;
            current_tile_palette_itx = current_tile_data_itx + 1;

            ROM_BANK_TILE_DATA;
            tile_data[0] = background_tile_map[current_tile_data_itx] & 0x7F;
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

            ROM_BANK_TILE_DATA;
            // Lookup tile from background tile map
            tile_data[0] = background_tile_map[current_tile_palette_itx] & 0x07;

            // Check if current tile is flipped
            if (background_tile_map[current_tile_palette_itx] & 0x08)
                tile_data[0] |= S_FLIPY;

            if (background_tile_map[current_tile_palette_itx] & 0x10)
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
    
    new_x = user_pos_x + travel_x;
    new_y = user_pos_y + travel_y;
    // Check if traveling to new tile
    if ((travel_x == 1 && (new_x & 0x07U) == 0x00U) ||
        (travel_x == -1 && (new_x & 0x07U) == 0x07U) ||
        (travel_y == 1 && (new_y & 0x07U) == 0x00U) ||
        (travel_y == -1 && (new_y & 0x07U) == 0x07U))
    {
            new_tile_itx = X_Y_TO_TILE_INDEX(
                PIXEL_LOCATION_TO_TILE_COUNT(new_x),
                PIXEL_LOCATION_TO_TILE_COUNT(new_y)
            );

            ROM_BANK_TILE_DATA;
            // Check if new tile is a boundary
            if (TILE_INDEX_BIT_MAP_VALUE(MAIN_MAP_BOUNDARIES, new_tile_itx))
            {
                // Reset travel directions, acting as if user is not moving.
                travel_x = 0;
                travel_y = 0;
            }
            ROM_BANK_RESET;
    }
}

// Setup globals to draw main map
void setup_main_map()
{
    DISPLAY_OFF;
    game_state.current_building = S_B_NO_BUILDING;

    background_color_palette = main_map_palette;
    background_tile_map = mainmap;
    background_tiles = mainmaptiles;
    background_tile_palette = mainmaptilesCGB;
    background_width = mainmapWidth;
    
    DRAW_OFFSET_X = screen_location_x >> 3;
    DRAW_OFFSET_Y = screen_location_y >> 3;
    DRAW_MAX_X = BACKGROUND_BUFFER_SIZE_X;
    DRAW_MAX_Y = BACKGROUND_BUFFER_SIZE_Y;

    sprite_tiles = mainmapspritetiles;
    sprite_palette = mainmapspritetilesCGB;
    set_background_tiles();
    setup_sprite();
    
    // Move background to screen location
    scroll_bkg(
        screen_location_x & BACKGROUND_BUFFER_SIZE_PIXELS_MAX_X,
        screen_location_y & BACKGROUND_BUFFER_SIZE_PIXELS_MAX_Y
    );
    
    // Load currently displayed buildings
    load_building_tile_data();
    
    DISPLAY_ON;
}

void load_menu_tiles() NONBANKED
{
    unsigned int menu_item_itx;
    move_bkg(0, 0);
    
    // Iterate over all menu items and load palette data.
    // Start from 1 , as first item column is 'exit'
    for (itx_x = 0; itx_x != MENU_MAX_ITEMS_X; itx_x ++)
    {
        for (itx_y = 0; itx_y != MENU_MAX_ITEMS_Y; itx_y ++)
        {
            // Work out menu item index, based on co-ords
            menu_item_index = (itx_y * MENU_MAX_ITEMS_X) + itx_x;

            // Ignore top right exit
            if (itx_x == 1U && itx_y == 0U)
                continue;

            // Check if tile is a valid tile
            if (! IS_MENU_ITEM_ENABLED(menu_item_index))
                continue;

            second_tile_row = 0U;

            // Pad from left with offset on screen. The menu items are 7 + margin of 1, so times with itx_x.
            tile_itx_x_start = MENU_ITEM_SCREEN_OFFSET_LEFT + (8U * itx_x);
            tile_itx_y_start = MENU_ITEM_SCREEN_OFFSET_TOP + (3U * itx_y);
            
            // For tiles on top row, use offset from menu config
            ROM_BANK_MENU_CONFIG;
            tile_data_offset = menu_config->tile_offset;
            ROM_BANK_RESET;

            for (tile_index = 0U; tile_index != MENU_ITEM_TILE_COUNT; tile_index ++)
            {
                // Once second row of menu item data tiles is reached,
                // mark as such
                if (tile_index == MENU_ITEM_WIDTH)
                {
                    tile_itx_x_start -= MENU_ITEM_WIDTH;
                    second_tile_row = 1U;
                    // Use row 2 offset for numbers and symbols
                    tile_data_offset = MENU_ROW_2_TILE_DATA_OFFSET;
                }

                menu_item_itx = menu_config->items[menu_item_index];

                ROM_BANK_MENU_CONFIG;
                if (menu_config_items[menu_item_itx].tiles[tile_index] == 0U)
                {
                    ROM_BANK_RESET;
                    continue;
                }

                tile_data_index = tile_data_offset + menu_config_items[menu_item_itx].tiles[tile_index];

                ROM_BANK_TILE_DATA;

                VBK_REG = 0; 
                // Load tile data for menu item based on tile data offset
                // in menu config and tile config in menu tile array
                set_bkg_data(
                    tile_data_index,
                    1,
                    &(buildingmenutiles[tile_data_index << 4])
                );
                ROM_BANK_RESET;

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

                VBK_REG = 1;

                // Load default palette
                tile_data[0] = MENU_ITEM_DEFAULT_PALETTE;

                // Override color palette from menu_item palette tile overrides
                ROM_BANK_MENU_CONFIG;
                if (menu_config_items[menu_item_itx].palette[tile_index])
                    tile_data[0] = menu_config_items[menu_item_itx].palette[tile_index];
                ROM_BANK_RESET;

                // Set palette data in VBK_REG1 for tile
                set_bkg_tiles(
                    tile_itx_x, 
                    tile_itx_y,
                    1, 1,  // Only setting 1 tile
                    &(tile_data[0])
                );
            }
        }
    }
}


void set_menu_item_color(unsigned char palette)
{
    unsigned int itx_y, itx_x, tile_index, menu_item_index;
    unsigned char palette_colors[MENU_ITEM_WIDTH];
    unsigned int menu_item_itx = menu_state.current_item_x + (MENU_MAX_ITEMS_X * menu_state.current_item_y);

    VBK_REG = 1;
    for (itx_y = 0; itx_y != MENU_ITEM_HEIGHT; itx_y ++)
    {
        for (itx_x = 0; itx_x != MENU_ITEM_WIDTH; itx_x ++)
        {
            palette_colors[itx_x] = palette;
            tile_index = itx_x + (itx_y * MENU_ITEM_WIDTH);
            menu_item_index = menu_config->items[menu_item_itx];
            ROM_BANK_MENU_CONFIG;
            if (menu_config_items[menu_item_index].palette[tile_index] != 0U)
                palette_colors[itx_x] = menu_config_items[menu_item_index].palette[tile_index];
            ROM_BANK_RESET;
         }
        set_bkg_tiles(
            MENU_ITEM_SCREEN_OFFSET_LEFT + (8U * menu_state.current_item_x),
            itx_y + MENU_ITEM_SCREEN_OFFSET_TOP + (3U * menu_state.current_item_y),
            MENU_ITEM_WIDTH, 1,
            &palette_colors
        );
    }
    VBK_REG = 0;
}

void setup_building_menu()
{
    DISPLAY_OFF;
    // Update globals for references to map/tile information
    background_tile_map = buildingmenumap;
    background_tiles = buildingmenutiles;
    background_tile_palette = buildingmenutilesCGB;
    background_width = buildingmenumapWidth;
    background_color_palette = building_menu_palette;

    // Draw top left of screen
    DRAW_OFFSET_X = 0U;
    DRAW_OFFSET_Y = 0U;
    DRAW_MAX_X = SCREEN_WIDTH_TILES;
    DRAW_MAX_Y = SCREEN_HEIGHT_TILES;

    if (game_state.current_building == S_B_HOUSE)
    {
        // Menu has 3 items, default to sleep
        menu_state.current_item_x = 1;
        menu_state.current_item_y = 3;
        menu_config = &menu_config_house;
    }
    else if (game_state.current_building == S_B_RESTAURANT)
    {
        // Menu has 3 items, default to sleep
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

    HIDE_SPRITES;
    // Reload background tiles
    set_background_tiles();
    
    load_menu_tiles();

    set_menu_item_color(MENU_ITEM_SELECTED_PALETTE);

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
    
    // Temporary jump to restaurant
//    game_state.current_building = S_B_RESTAURANT;
//    setup_building_menu();
        
}

// Check if win/lose conditions have been met
void check_end_game()
{
    
}


void load_buildings_x_left()
{
    // Enable house
    if (screen_location_x_tiles == SC_HOUSE_TRANSITION_X)
    {
        screen_state.displayed_buildings |= SC_HOUSE;
        load_building_tile_data();
    }
}
void load_buildings_x_right()
{
    // Disable house
    if (screen_location_x_tiles == SC_HOUSE_TRANSITION_X)
        screen_state.displayed_buildings &= ~SC_HOUSE;
}
void load_buildings_y_up()
{
    // Disable restaurant
    if (screen_location_y_tiles == SC_RESTAURANT_TRANSITION_Y)
        screen_state.displayed_buildings &= ~SC_RESTAURANT;
    if (screen_location_y_tiles == SC_SHOP_TRANSITION_Y)
        screen_state.displayed_buildings &= ~SC_SHOP;
    if (screen_location_y_tiles == SC_PAWN_TRANSITION_Y)
        screen_state.displayed_buildings &= ~SC_PAWN;
}
void load_buildings_y_down()
{
    // Enable restaurant
    if (screen_location_y_tiles == SC_RESTAURANT_TRANSITION_Y)
    {
        screen_state.displayed_buildings |= SC_RESTAURANT;
        load_building_tile_data();
    }
    if (screen_location_y_tiles == SC_SHOP_TRANSITION_Y)
    {
        screen_state.displayed_buildings |= SC_SHOP;
        load_building_tile_data();
    }
    if (screen_location_y_tiles == SC_PAWN_TRANSITION_Y)
    {
        screen_state.displayed_buildings |= SC_PAWN;
        load_building_tile_data();
    }
}

void purchase_food(UINT8 cost, UINT8 gained_hp)
{
    // Breaking the rules using >=, but
    // only performed when buying an item
    // and currency is decimal, making very difficult
    // to do using bit shifting (and at least probably
    // less CPU intensive)
    if (game_state.balance >= cost)
    {
        game_state.balance -= cost;
        
        // If new HP would exeed max HP, limit new HP to difference
        if (gained_hp >= (game_state.max_hp - game_state.hp))
            game_state.hp = game_state.max_hp;
        else
            // Otherwise, add new HP to HP
            game_state.hp += gained_hp;
            
        ROM_BANK_TILE_DATA;
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

    if (game_state.balance >= cost && game_state.inventory[inventory_item] != S_MAX_INVENTORY_ITEM)
    {
        game_state.balance -= cost;
        game_state.inventory[inventory_item] += 1U;

        ROM_BANK_TILE_DATA;
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
    }
    
    ROM_BANK_TILE_DATA;
    update_window(&game_state);
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


    if (game_state.current_building == S_B_NO_BUILDING)
    {
        check_boundary_hit();

        // Set user screen position based on current location
        user_screen_pos_x = user_pos_x - screen_location_x;
        user_screen_pos_y = user_pos_y - screen_location_y;

        user_pos_x += travel_x;
        user_pos_y += travel_y;
        
        // Check if sprite too close to edge of screen
        // If character at left of screen, begin to scroll, unless at top of map (allowing character
        // to continue moving and not redraw map outside of map tiles)
        if (user_screen_pos_x == CHARACTER_SCREEN_LOCATION_MARGIN && screen_location_x != 0)
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
            user_screen_pos_x = user_pos_x - screen_location_x;
            move_x = 0;
        }

        // If character at top of screen, begin to scroll, unless at top of map (allowing character
        // to continue moving and not redraw map outside of map tiles)
        if (user_screen_pos_y == CHARACTER_SCREEN_LOCATION_MARGIN && screen_location_y != 0)
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
            user_screen_pos_y = user_pos_y - screen_location_y;
            move_y = 0;
        }

        // Temporary fix to help with diagonal movement
        // move_background(0, move_y);
        if (move_x != 0)
        {
            move_background(move_x, 0);

            // Check when on tile boundary (NOTE this only works for movement in positive directions,
            // but doesn't matter for now).
            if (screen_location_x_tilepixel == 0U)
                if (move_x == 1)
                    load_buildings_x_right();
                else
                    load_buildings_x_left();
        }
        if (move_y != 0)
        {
            move_background(0, move_y);
            
            if (screen_location_y_tilepixel == 0U)
                if (move_y == 1)
                    load_buildings_y_down();
                else
                    load_buildings_y_up();
        }

        // Move sprite to new location
        move_sprite(
            0,
            user_screen_pos_x + SPRITE_OFFSET_X,
            user_screen_pos_y + SPRITE_OFFSET_Y
        );

        // Update flip of sprite tile
        sprite_prop_data = 0x00;
        // Check for just vertical movement 
        if (travel_y != 0)
        {
            if (travel_x == 0)
            {
                // If travelling up, flip Y
                if (travel_y == 1)
                    sprite_prop_data |= S_FLIPY;
                set_sprite_tile(0, 0);
            } else {
                // Handle diagonal movement
                if (travel_y == 1)
                    sprite_prop_data |= S_FLIPY;
                if (travel_x == -1)
                    sprite_prop_data |= S_FLIPX;
                set_sprite_tile(0, 2);
            }
        }
        else if (travel_x != 0)
        {
            set_sprite_tile(0, 1);
            if (travel_x == -1)
                sprite_prop_data |= S_FLIPX;
        }
        // Only update flipping if actually moving
        if (travel_x != 0 || travel_y != 0)
            set_sprite_prop(0, sprite_prop_data);

        if (a_pressed)
            check_building_enter();

    } else {
        // In a building - move through menu

        // Menu layout:
        // 3,3 tile offset for top option.
        // Each option is 7 tiles wide and 2 tiles high.
        // One tile buffer between each option.

        if (travel_x != 0 || travel_y != 0)
        {
            // Deselect currently selected item
            set_menu_item_color(MENU_ITEM_DEFAULT_PALETTE);
            
            // Check the direction of menu item travel and ensure it doesn't go out of bounds
            // Since there's only two items in X direction of menu, do a simple hard coded check
            if (
                    (
                        (travel_x == 1 && menu_state.current_item_x == 0U) ||
                        (travel_x == -1 && menu_state.current_item_x == 1U)
                    ) &&
                    IS_MENU_ITEM_ENABLED(menu_state.current_item_x + travel_x + (menu_state.current_item_y * MENU_MAX_ITEMS_X))
                )
                menu_state.current_item_x += travel_x;

            // Until I can find a nicer way of doing this. Go in direction of menu travel and
            // check if there is an option available
        
            if (travel_y == 1)
            {
                itx_start = menu_state.current_item_y + 1U;
                for (itx = itx_start; itx != MENU_MAX_ITEMS_Y; itx ++)
                    if (IS_MENU_ITEM_ENABLED(menu_state.current_item_x + (itx * MENU_MAX_ITEMS_X)))
                    {
                        menu_state.current_item_y = itx;
                        break;
                    }
            }
            else if (travel_y == -1 && menu_state.current_item_y != 0U)
            {
                // Since we're going from current itx (Y -1) to 0,
                // to make iteration easier, iterate from Y to 1 and take 1 during calulcation
                for (itx = menu_state.current_item_y; itx != 0U; itx --)
                    if (IS_MENU_ITEM_ENABLED(menu_state.current_item_x + ((itx - 1U) * MENU_MAX_ITEMS_X)))
                    {
                        menu_state.current_item_y = itx - 1U;
                        break;
                    }
            }
                
            set_menu_item_color(MENU_ITEM_SELECTED_PALETTE);

            // Sleep to stop double pressed
            delay(DELAY_MENU_ITEM_MOVE);
        }

        // Check if moving menu item
        if (a_pressed)
        {
            // Check if 'exit' selected
            if (menu_state.current_item_y == 0U && menu_state.current_item_x == 1U)
                // If exiting menu, load main map
                setup_main_map();
                
            // If selected sleep in house
            else if (game_state.current_building == S_B_HOUSE && menu_state.current_item_y == 3U)
            {
                game_state.hour = S_HOUR_WAKEUP_NORMAL;
                game_state.days_passed ++;
                check_end_game();

                ROM_BANK_TILE_DATA;
                update_window(&game_state);
                ROM_BANK_RESET;

                // TURN OFF DISPLAY FOR 1 second
                DISPLAY_OFF;
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
                // Delay after purchasing, to avoid double purchase
                delay(DELAY_PURCHASE_ITEM);
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
                // Delay after purchasing, to avoid double purchase
                delay(DELAY_PURCHASE_ITEM);
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
                            // Remove from menu, if successful
                            menu_config->items[2U] = MENU_ITEM_INDEX_EMPTY;
                        }
                    }
                    else if (menu_state.current_item_y == 2U)  // Knife
                    {
                        if (purchase_item(100U, S_INVENTORY_KNIFE))
                        {
                            menu_config->items[4U] = MENU_ITEM_INDEX_EMPTY;
                        }
                    }
                    else if (menu_state.current_item_y == 3U)  // Alarm Clock
                    {
                        if (purchase_item(200U, S_INVENTORY_ALARM_CLOCK))
                        {
                            menu_config->items[6U] = MENU_ITEM_INDEX_EMPTY;
                        }
                    }
                }
                else  // x row 1
                {
                    if (menu_state.current_item_y == 1U)  // Cellphone
                    {
                        if (purchase_item(200U, S_INVENTORY_CELL_PHONE))
                        {
                            menu_config->items[1U] = MENU_ITEM_INDEX_EMPTY;
                        }
                    }
                }
                // Delay after purchasing, to avoid double purchase
                delay(DELAY_PURCHASE_ITEM);
            }
        }
    }
}


void main()
{
    debug_address = 0xFFFA;

    DISPLAY_OFF;
    setup_globals();

    wait_vbl_done();
    SHOW_BKG;
    
    // Initial setup of window and update with starting stats
    setup_window();
    ROM_BANK_TILE_DATA;
    update_window(&game_state);
    ROM_BANK_RESET;
    SHOW_WIN;
    
    // Load background tiles. This turns display on, so run last
    setup_main_map();

    // And open the curtains!
    DISPLAY_ON;
        
        while(1) {
                wait_vbl_done();

                check_user_input();
                update_state();

                // Temporarily remove delay to speed debugging
                //delay(50);
        }
}
