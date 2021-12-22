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
#include "sprite_tileset.c"


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

#define VRAME_SIZE_TILES_X_MASK 0x1FU
#define VRAME_SIZE_TILES_Y_MASK 0x1FU
// From screen left-top-hand position to half way through unused vram
// x - ( 0x20U (vram width in tiles) - 0x14U (screen width in tiles) / 2) + 0x14U (screen width in tiles)
#define REDRAW_VRAM_OFFSET_X 0x1AU
#define REDRAW_VRAM_OFFSET_Y 0x1AU

//unsigned char *MAIN_MAP_VERTICAL_FLIP_TILES = (unsigned char*) calloc((mainmapWidth * mainmapHeight) / 8, 1);
//unsigned char *MAIN_MAP_VERTICAL_FLIP_TILES;
//unsigned char *MAIN_MAP_HORIZONTAL_FLIP_TILES;

// Location of user in world.
// This is not the sprites position on the screen
unsigned int user_pos_x;
unsigned int user_pos_y;

// Location of screen compared to map
unsigned int screen_location_x;
unsigned int screen_location_y;

// Determine which way user needs to travel
signed int travel_x;
signed int travel_y;
UINT8 sprite_traveling_x;
UINT8 sprite_prop_data;


unsigned char *background_tile_map;
unsigned char *background_tiles;
unsigned char *background_tile_palette;
unsigned int background_palette_itx_x;
unsigned int background_palette_itx_y;


void init_map_variables()
{
    //malloc_init();
    //MAIN_MAP_VERTICAL_FLIP_TILES = (unsigned char*) calloc((mainmapWidth * mainmapHeight) / 8, 1);
    //MAIN_MAP_HORIZONTAL_FLIP_TILES = (unsigned char*) calloc((mainmapWidth * mainmapHeight) / 8, 1);

    // Setup flipped tiles
    //  -Left hand road, buttom of road marking
//    MAIN_MAP_HORIZONTAL_FLIP_TILES[159] = 0x48;
//    MAIN_MAP_VERTICAL_FLIP_TILES[159] = 0x6c;
//    MAIN_MAP_VERTICAL_FLIP_TILES[160] = 0xdb;
//    MAIN_MAP_VERTICAL_FLIP_TILES[161] = 0xb6;
//    MAIN_MAP_VERTICAL_FLIP_TILES[162] = 0x6d;

    screen_location_x = 0;
    screen_location_y = 0;
}

void setup_sprite()
{
    // Load single sprite tile
    sprite_traveling_x = 0;
    user_pos_x = 0x50U;
    user_pos_y = 0x50U;
    set_sprite_data(0, 3, spritetiles);
    set_sprite_palette(0, 1, spritetilesCGB);
    set_sprite_tile(0, 0);
    SHOW_SPRITES;
}

void set_background_tiles()
{
    unsigned int frame_buffer_tile_max_x = BACKGROUND_BUFFER_SIZE_X;
    unsigned int frame_buffer_tile_max_y = BACKGROUND_BUFFER_SIZE_Y;
    // @TODO Fix the increment
    //unsigned long current_tile_itx = FRAME_BUFFER_TILE_POS_X + (FRAME_BUFFER_TILE_POS_Y * mainmapWidth);
    unsigned int current_tile_itx = 0;
    unsigned char tile_data = 0x00;

    //set_bkg_tiles(0, 0, mainmapWidth, mainmapHeight, background_tile_map);
    VBK_REG = 0;
    set_bkg_data(0, 8, background_tiles);

    for (background_palette_itx_x = 0U;
           background_palette_itx_x != frame_buffer_tile_max_x;
           background_palette_itx_x ++)
    {
        // UNCOMMENT TO ADD TEMP HACK TO NOT DRAW MOST OF BACKGROUND IN VRAM
//        if (background_palette_itx_x == 0x10U)
//            break;
        for (background_palette_itx_y = 0U;
               background_palette_itx_y != frame_buffer_tile_max_y;
               background_palette_itx_y ++)
        {
            // Temp Test
            current_tile_itx = (background_palette_itx_y * mainmapWidth) + background_palette_itx_x;
            
            // UNCOMMENT TO ADD TEMP HACK TO NOT DRAW MOST OF BACKGROUND IN VRAM
//            if (background_palette_itx_y == 0x10U)
//                break;

            // Map data is 2 bytes per tile.
            // First byte's first 7 bits are tile number
            // next bit is vertical flip
            // first bit of second byte is horizontal flip

           VBK_REG = 0; 
            // Set map data
            set_bkg_tiles(
                background_palette_itx_x, 
                background_palette_itx_y,
                1, 1,  // Only setting 1 tile
                 // Lookup tile from background tile map
                 &background_tile_map[current_tile_itx]
            );
            
            VBK_REG = 1;
            
            tile_data = background_tile_palette[  // From the palette map
                // Lookup tile from background tile map
                background_tile_map[current_tile_itx]
            ];
            
            // Check if current tile is flipped
//            if (
//                (MAIN_MAP_VERTICAL_FLIP_TILES[
//                    // Bit shift current tile ITX by 3 (dividing by 8) to obtain byte
//                    // of flip data that contains this tile's flip and compare to 
//                    current_tile_itx >> 3
//                // Shift 1 by the last byte of the current tile idx and 'and' compare with
//                // tile shift data bit
//                ] & (1 << (current_tile_itx & 0x07))))
//                    tile_data |= S_FLIPY;
                    
// Disabled until malloc issues can be sorted.
//            if (
//                (MAIN_MAP_HORIZONTAL_FLIP_TILES[
//                    current_tile_itx >> 3
//                ] & (1 << (current_tile_itx & 0x07))))
//                    tile_data |= S_FLIPX;

            // Set palette data in VBK_REG1 for tile
            set_bkg_tiles(
                background_palette_itx_x, 
                background_palette_itx_y,
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

    // Check directional 
    if (keys & J_UP)
        travel_y --;
    if (keys & J_DOWN)
        travel_y ++;
    if (keys & J_LEFT)
        travel_x --;
    if (keys & J_RIGHT)
        travel_x ++;
}

void move_background(signed int move_x, signed int move_y)
{
    unsigned int itx_x;
    unsigned int itx_y;
    unsigned int base_itx_x;
    unsigned int base_itx_y;
    unsigned int current_tile_itx;
    unsigned char tile_data;
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

            // Map data is 2 bytes per tile.
            // First byte's first 7 bits are tile number
            // next bit is vertical flip
            // first bit of second byte is horizontal flip

           VBK_REG = 0; 
            // Set map data
            set_bkg_tiles(
                itx_x & BACKGROUND_BUFFER_MAX_X,
                itx_y & BACKGROUND_BUFFER_MAX_Y,
                1, 1,  // Only setting 1 tile
                 // Lookup tile from background tile map
                 &background_tile_map[current_tile_itx]
            );
            
            VBK_REG = 1;
            
            tile_data = background_tile_palette[  // From the palette map
                // Lookup tile from background tile map
                background_tile_map[current_tile_itx]
            ];
            
            // TILE FLIP HERE

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

            // Set map data
            set_bkg_tiles(
                itx_x & BACKGROUND_BUFFER_MAX_X,
                itx_y & BACKGROUND_BUFFER_MAX_Y,
                1, 1,  // Only setting 1 tile
                 // Lookup tile from background tile map
                 &background_tile_map[current_tile_itx]
            );
            
            VBK_REG = 1;
            
            tile_data = background_tile_palette[  // From the palette map
                // Lookup tile from background tile map
                background_tile_map[current_tile_itx]
            ];
            
            // TILE FLIP HERE

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
            new_tile_itx = ((new_y >> 3) * mainmapWidth) + (new_x >> 3);
            // Check if new tile is a boundary
            if (MAIN_MAP_BOUNDARIES[new_tile_itx >> 3] & (1 << (new_tile_itx & 0x07U)))
            {
                // Reset travel directions, acting as if user is not moving.
                travel_x = 0;
                travel_y = 0;
            }
    }
}

// Called per cycle to update background position and sprite
void update_graphics()
{
    unsigned short background_moved = 0U;
    unsigned int user_screen_pos_x;
    unsigned int user_screen_pos_y;
    signed int move_x;
    signed int move_y;

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
}


void main()
{
//        printf("Welcome to GAMEBOY\nProgramming");
//        printf("\nPress Start");
//        waitpad(J_START);  // other keys are J_A, J_UP, J_SELECT, etc.
//        printf("\nIsn't it easy!");
    DISPLAY_OFF;
    init_map_variables();

    // Load color palette
    set_bkg_palette(0, 8, &bgpal);

    // Load background tiles
    background_tile_map = &mainmap;
    background_tiles = &mainmaptiles;
    background_tile_palette = &mainmaptilesCGB;
    set_background_tiles();
    setup_sprite();

    wait_vbl_done();
    SHOW_BKG;
    DISPLAY_ON;
        
        while(1) {
                wait_vbl_done();

                check_user_input();
                update_graphics();
                // Temporarily remove delay to speed debugging
                //delay(50);
        }
}
