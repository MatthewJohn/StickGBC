/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */


/*#include <gb/drawing.h>*/
#include <stdio.h>
#include <stdlib.h>
#include <gb/gb.h>

#include "main_map_tileset.c"
#include "main_map.h"
#include "main_map_palette.c"
#include "main_map_boundaries.h"

#include "building_menu_tiles.c"
#include "building_menu_map.h"
#include "building_menu_palette.c"

#include "main_map_sprite_tileset.c"

#include "game_state.c"
#include "menu_config.c"

// Get tile pixel within from map-coordinates
#define TO_SUBTILE_PIXEL(location) (location & 0x0FU)
#define PIXEL_LOCATION_TO_TILE_COUNT(location) (location >> 3)
#define X_Y_TO_TILE_INDEX(x, y) ((y * mainmapWidth) + x)
#define TILE_INDEX_BIT_MAP_VALUE(mapping, tile_index) mapping[tile_index >> 3] & (1 << (tile_index & 0x07U))

//#define DEBUG_HIGHLIGHT_TILE_BOUNDARY 1U
//#define DEBUG_HIGHLIGHT_VERTICAL_FLIP_TILE 1U
#define DEBUG_HIGHLIGHT_HORIZONTAL_FLIP_TILE 1U

// Screen size 160x168
#define SCREEN_WIDTH 0xA8U
#define SCREEN_HEIGHT 0xA0U

#define SCREEN_TILE_MAX_X 0x13U
#define SCREEN_TILE_MAX_Y 0x11U
#define SCREEN_WIDTH_TILES 0x14U
#define SCREEN_HEIGHT_TILES 0x12U

// Manually calculated by putting sprite into corner of screen and setting until middle
// of character is at 0,0 location
#define SPRITE_OFFSET_X 0x04U
#define SPRITE_OFFSET_Y 0x0dU

#define CHARACTER_SCREEN_LOCATION_MARGIN 0x20U

// Max address if 0x1F, set to 0x20 for loops that loop whilst
// less than the value (or rather !=)
#define BACKGROUND_BUFFER_SIZE_X 0x20U
#define BACKGROUND_BUFFER_SIZE_Y 0x20U
#define BACKGROUND_BUFFER_MAX_X 0x1FU
#define BACKGROUND_BUFFER_MAX_Y 0x1FU
#define BACKGROUND_BUFFER_SIZE_PIXELS_MAX_X 0xFFU
#define BACKGROUND_BUFFER_SIZE_PIXELS_MAX_Y 0xFFU
#define BACKGROUND_BUFFER_SIZE_PIXELS_X 0x100U
#define BACKGROUND_BUFFER_SIZE_PIXELS_Y 0x100U

#define VRAME_SIZE_TILES_X_MASK 0x1FU
#define VRAME_SIZE_TILES_Y_MASK 0x1FU
// From screen left-top-hand position to half way through unused vram
// x - ( 0x20U (vram width in tiles) - 0x14U (screen width in tiles) / 2) + 0x14U (screen width in tiles)
#define REDRAW_VRAM_OFFSET_X 0x1AU
#define REDRAW_VRAM_OFFSET_Y 0x1AU

#define TILE_PATTERN_INDEX_TO_ARRAY_INDEX(index) (index << 4)
#define TILE_PATTERN_SCRATCH_1 0x05U
#define TILE_PATTERN_SCRATCH_2 0x06U
#define TILE_PATTERN_SCRATCH_3 0x07U

UBYTE * debug_address;

// Location of user in world.
// This is not the sprites position on the screen
unsigned int user_pos_x;
unsigned int user_pos_y;

UBYTE tile_data;

// Location of screen compared to map
unsigned int screen_location_x;
unsigned int screen_location_y;

// Determine which way user needs to travel
signed int travel_x;
signed int travel_y;
unsigned short a_pressed;
UINT8 sprite_traveling_x;
UINT8 sprite_prop_data;

// Game state
game_state_t game_state;
menu_config_t menu_config;

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


void add_debug(UBYTE val)
{
    *debug_address = val;
    debug_address ++;
}

void load_house_tile_data()
{
    // Load house data from tile 8 to tile
    VBK_REG = 0;
    set_bkg_data(TILE_PATTERN_SCRATCH_1, 1, &(mainmaptiles[13 * 16]));
}

void setup_globals()
{
    game_state.current_building = S_B_NO_BUILDING;

    screen_location_x = 0;
    screen_location_y = 0;
    sprite_traveling_x = 0;
    user_pos_x = 0x70U;
    user_pos_y = 0x70U;
}

void setup_sprite()
{
    // Load single sprite tile
    HIDE_SPRITES;
    set_sprite_data(0, 3, sprite_tiles);
    set_sprite_palette(0, 1, sprite_palette);
    set_sprite_tile(0, 0);
    SHOW_SPRITES;
}

void set_background_tiles()
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
    set_bkg_palette(0, 8, background_color_palette);

    VBK_REG = 0;
    set_bkg_data(0, 8, background_tiles);

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

            tile_data = background_tile_map[current_tile_data_itx] & 0x07;

           VBK_REG = 0; 
            // Set map data
            set_bkg_tiles(
                background_palette_itx_x & BACKGROUND_BUFFER_MAX_X,
                background_palette_itx_y & BACKGROUND_BUFFER_MAX_Y,
                1, 1,  // Only setting 1 tile
                 // Lookup tile from background tile map
                 &tile_data
            );
            
            VBK_REG = 1;

            // Lookup tile from background tile map
            tile_data = background_tile_map[current_tile_palette_itx] & 0x07;

            // Check if current tile is flipped
            if (background_tile_map[current_tile_palette_itx] & 0x08)
                tile_data |= S_FLIPY;

            if (background_tile_map[current_tile_palette_itx] & 0x10)
                tile_data |= S_FLIPX;

            // Set palette data in VBK_REG1 for tile
            set_bkg_tiles(
                background_palette_itx_x & BACKGROUND_BUFFER_MAX_X,
                background_palette_itx_y & BACKGROUND_BUFFER_MAX_Y,
                1, 1,  // Only setting 1 tile
                &tile_data
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

void move_background(signed int move_x, signed int move_y)
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
    signed int direction_tile_offset_x;
    signed int direction_tile_offset_y;

    // Last 3 bits of screen position X
    unsigned int screen_location_pixel_count_x;
    unsigned int screen_location_pixel_count_y;

    if (move_x == 0 && move_y == 0)
    {
        delay(20);
        return;
    }

    scroll_bkg(move_x, move_y);

    screen_location_x += move_x;
    screen_location_y += move_y;

    screen_location_pixel_count_x = screen_location_x & 0x07U;
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

    screen_location_pixel_count_y = screen_location_y & 0x07U;

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
        // Use screen_location_pixel_count_x to divide up tile in entire row. Start with 0 on first pixel. Set end of iterator to start of next block of tiles.
        itx_y_max = base_itx_y + (3U * (screen_location_pixel_count_x + 1U)) + 1U;
        for (itx_y = base_itx_y + (3U * screen_location_pixel_count_x) - 1U;
               itx_y != itx_y_max;
               itx_y ++)
        {
            // Work out current tile - base on tile location in frame buffer plus current map in vram location
            current_tile_itx = (itx_y * mainmapWidth) + itx_x;

            current_tile_data_itx = current_tile_itx * 2;
            current_tile_palette_itx = current_tile_data_itx + 1;

            tile_data = background_tile_map[current_tile_data_itx] & 0x07;

           VBK_REG = 0; 
            // Set map data
            set_bkg_tiles(
                itx_x & BACKGROUND_BUFFER_MAX_X,
                itx_y & BACKGROUND_BUFFER_MAX_Y,
                1, 1,  // Only setting 1 tile
                 // Lookup tile from background tile map
                 &tile_data
            );

            // Lookup tile from background tile map
            tile_data = background_tile_map[current_tile_palette_itx] & 0x07;

            // Check if current tile is flipped
            if (background_tile_map[current_tile_palette_itx] & 0x08)
                tile_data |= S_FLIPY;

            if (background_tile_map[current_tile_palette_itx] & 0x10)
                tile_data |= S_FLIPX;

          VBK_REG = 1;

            // Set palette data in VBK_REG1 for tile
            set_bkg_tiles(
                itx_x & BACKGROUND_BUFFER_MAX_X,
                itx_y & BACKGROUND_BUFFER_MAX_Y,
                1, 1,  // Only setting 1 tile
                &tile_data
            );

            VBK_REG = 0; 
        }
    }

    if (move_y != 0)
    {
        itx_y = base_itx_y;

        // If moving in X, redraw column.
        // The iterator is the frame buffer position (not the map position)
        itx_x_max = base_itx_x + (3U * (screen_location_pixel_count_y + 1U)) + 1U;
        for (itx_x = base_itx_x + (3U * screen_location_pixel_count_y) - 1U;
               itx_x != itx_x_max;
               itx_x ++)
        {
            // Work out current tile - base on tile location in frame buffer plus current map in vram location
            current_tile_itx = (itx_y  * mainmapWidth) + itx_x;

            current_tile_data_itx = current_tile_itx * 2;
            current_tile_palette_itx = current_tile_data_itx + 1;

            tile_data = background_tile_map[current_tile_data_itx] & 0x07;

           VBK_REG = 0; 
            // Set map data
            set_bkg_tiles(
                itx_x & BACKGROUND_BUFFER_MAX_X,
                itx_y & BACKGROUND_BUFFER_MAX_Y,
                1, 1,  // Only setting 1 tile
                 // Lookup tile from background tile map
                 &tile_data
            );

            // Lookup tile from background tile map
            tile_data = background_tile_map[current_tile_palette_itx] & 0x07;

            // Check if current tile is flipped
            if (background_tile_map[current_tile_palette_itx] & 0x08)
                tile_data |= S_FLIPY;

            if (background_tile_map[current_tile_palette_itx] & 0x10)
                tile_data |= S_FLIPX;

            VBK_REG = 1;

            // Set palette data in VBK_REG1 for tile
            set_bkg_tiles(
                itx_x & BACKGROUND_BUFFER_MAX_X,
                itx_y & BACKGROUND_BUFFER_MAX_Y,
                1, 1,  // Only setting 1 tile
                &tile_data
            );        
           VBK_REG = 0; 
    
        }
    }
}

// Check if next position will hit a boundary
void check_boundary_hit()
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

            // Check if new tile is a boundary
            if (TILE_INDEX_BIT_MAP_VALUE(MAIN_MAP_BOUNDARIES, new_tile_itx))
            {
                // Reset travel directions, acting as if user is not moving.
                travel_x = 0;
                travel_y = 0;
            }
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
    
    DISPLAY_ON;
}

void clear_menu_config()
{
    int itx_x;
    int itx_y;
    // Clear tile and palette arrays -
    // entire array is 8 * 14
    // Iterate over menu items
    for (itx_x = 0U; itx_x != 0x8U; itx_x ++)
        // Iterate over menu item tiles
        for (itx_y = 0U; itx_y != 0x14U; itx_y ++)
            menu_config.menu_item_tiles[itx_x][itx_y] = 0U;
    //memset(menu_config.menu_item_tiles, 0, 112);
    //memset(menu_config.menu_item_palette, 0, 112);
}

void load_menu_tiles()
{
    unsigned int itx_x;
    unsigned int itx_y;
    unsigned int menu_item_x;
    unsigned int menu_item_y;
    unsigned int menu_item_index;
    unsigned int tile_index;
    unsigned int tile_data_index;
    unsigned int tile_start_itx_x;
    unsigned int tile_start_itx_y;
    unsigned int tile_itx_x;
    unsigned int tile_itx_y;
    unsigned int second_tile_row;
    
    move_bkg(0, 0);
    
    // Iterate over all menu items and load palette data.
    // Start from 1 , as first item column is 'exit'
    for (menu_item_x = 0; menu_item_x != menu_config.max_items_x; menu_item_x ++)
    {
        for (menu_item_y = 1; menu_item_y != menu_config.max_items_y; menu_item_y ++)
        {
            itx_y = menu_item_y + (MENU_MAX_ITEMS_Y - menu_config.max_items_y);
                
            // If only 1 column of items, so it in the second column
            if (menu_config.max_items_x == 1)
                itx_x = 1;
            else
                itx_x = menu_item_x;

            // Work out menu item index, based on co-ords
            menu_item_index = (menu_item_y * menu_config.max_items_x) + menu_item_x;

            second_tile_row = 0U;

            // Pad from left with offset on screen. The menu items are 7 + margin of 1, so times with itx_x.
            tile_start_itx_x = MENU_ITEM_SCREEN_OFFSET_LEFT + (8U * itx_x);
            tile_start_itx_y = MENU_ITEM_SCREEN_OFFSET_TOP + (3U * itx_y);

            for (tile_index = 0U; tile_index != MENU_ITEM_TILE_COUNT; tile_index ++)
            {
                // Once second row of menu item data tiles is reached,
                // mark as such
                if (tile_index == MENU_ITEM_WIDTH)
                    second_tile_row = 1U;

                if (menu_config.menu_item_tiles[menu_item_index][tile_index] != 0U)
                {
                    tile_data_index = menu_config.tile_offset + menu_config.menu_item_tiles[menu_item_index][tile_index];

                    VBK_REG = 0; 
                    // Load tile data for menu item based on tile data offset
                    // in menu config and tile config in menu tile array
                    set_bkg_data(
                        tile_data_index,
                        1,
                        &(buildingmenutiles[tile_data_index << 4])
                    );
                    
                    tile_itx_y = tile_start_itx_y + second_tile_row;
                    if (second_tile_row == 1U)
                    {
                        tile_itx_x = tile_start_itx_x + (tile_index - MENU_ITEM_WIDTH);
                    } else {
                        tile_itx_x = tile_start_itx_x + tile_index;
                    }

                    tile_data = tile_data_index;

                    // Set map data
                    set_bkg_tiles(
                        tile_itx_x, 
                        tile_itx_y,
                        1, 1,  // Only setting 1 tile
                        &tile_data
                    );

                    VBK_REG = 1;

                    // Lookup tile from background tile map
                    tile_data = MENU_ITEM_DEFAULT_PALETTE;

                    // Set palette data in VBK_REG1 for tile
                    set_bkg_tiles(
                        tile_itx_x, 
                        tile_itx_y,
                        1, 1,  // Only setting 1 tile
                        &tile_data
                    );
                }
            }
        }
    }
}

//#define MENU_ITEM_X_TO_MAP_X(map_c, itx) ((map_c.max_items_x == 1U ? 1U : itx) * 8U) + MENU_ITEM_SCREEN_OFFSET_LEFT

void set_menu_item_color(unsigned char palette)
{
    unsigned int itx_x, itx_y, current_item_x, current_item_y;

    if (menu_config.max_items_x == 1)
        current_item_x = 1;
    else
        current_item_x = menu_config.current_item_x;
    current_item_y = menu_config.current_item_y;
    if (menu_config.current_item_y != 0U)
    {
        current_item_y = menu_config.current_item_y + (MENU_MAX_ITEMS_Y - menu_config.max_items_y);
    }
    VBK_REG = 1;
    for (itx_x = 0; itx_x != MENU_ITEM_WIDTH; itx_x ++)
        for (itx_y = 0; itx_y != MENU_ITEM_HEIGHT; itx_y ++)
            set_bkg_tiles(
                itx_x + MENU_ITEM_SCREEN_OFFSET_LEFT + (8U * current_item_x),
                itx_y + MENU_ITEM_SCREEN_OFFSET_TOP + (3U * current_item_y),
                1, 1,
                &palette
            );
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
    
    // Setup config for main menu
    clear_menu_config();

    // Menu has 3 items, default to sleep
    menu_config.current_item_x = 0;
    menu_config.current_item_y = 1;
    menu_config.max_items_x = 1;
    menu_config.max_items_y = 2;
    
    menu_config.menu_item_tiles[1][0] = 0x1U;  // SL
    menu_config.menu_item_tiles[1][1] = 0x2U;  // EE
    menu_config.menu_item_tiles[1][2] = 0x3U;  // P
    
    // Number of tiles offset for palette data
    menu_config.tile_offset = 0x10U;

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
    // TEMP disable check to always enter house to make testing quicket
    if (tile_itx == 0x321U)
    {
        game_state.current_building = S_B_HOUSE;
        setup_building_menu();
    }
        
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
        if (user_screen_pos_x == CHARACTER_SCREEN_LOCATION_MARGIN)
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
            
        if (user_screen_pos_y == CHARACTER_SCREEN_LOCATION_MARGIN)
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
            move_background(move_x, 0);
        if (move_y != 0)
            move_background(0, move_y);

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
            if ((travel_x == 1 && (menu_config.current_item_x + 1) != menu_config.max_items_x) ||
                    (travel_x == -1 && (menu_config.current_item_x != 0)))
                menu_config.current_item_x += travel_x;
            if ((travel_y == 1 && (menu_config.current_item_y + 1) != menu_config.max_items_y) ||
                    (travel_y == -1 && (menu_config.current_item_y != 0)))
                menu_config.current_item_y += travel_y;
                
            set_menu_item_color(MENU_ITEM_SELECTED_PALETTE);
        }

        // Check if moving menu item
        if (a_pressed)
        {
            // Check if 'exit' selected
            if (menu_config.current_item_y == 0U &&
                ((menu_config.max_items_x == 1U && menu_config.current_item_x == 0U) ||
                (menu_config.max_items_x == 2U && menu_config.current_item_x == 1U)))
                // If exiting menu, load main map
                setup_main_map();
        }
    }
}


void main()
{
    debug_address = 0xFFFA;

    DISPLAY_OFF;
    setup_globals();

    // Load background tiles
    setup_main_map();
    
    // Load buildings at top-left on startup
    load_house_tile_data();

    wait_vbl_done();
    SHOW_BKG;
    DISPLAY_ON;
        
        while(1) {
                wait_vbl_done();

                check_user_input();
                update_state();

                // Temporarily remove delay to speed debugging
                //delay(50);
        }
}
