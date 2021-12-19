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
#include "main_map.c"
#include "main_map_palette.c"

#include "sprite_tileset.c"


// Screen size 160x168
#define SCREEN_WIDTH 0xA8U
#define SCREEN_HEIGHT 0xA0U

#define CHARACTER_SCREEN_LOCATION_MARGIN 0x20U

// Max address if 0x1F, set to 0x20 for loops that loop whilst
// less than the value (or rather !=)
#define BACKGROUND_BUFFER_SIZE_X 0x20U
#define BACKGROUND_BUFFER_SIZE_Y 0x20U
#define BACKGROUND_BUFFER_MAX_X 0x1FU
#define BACKGROUND_BUFFER_MAX_Y 0x1FU

#define VRAME_SIZE_TILES_X_MASK 0x1FU
// From screen left-top-hand position to half way through unused vram
// x - ( 0x20U (vram width in tiles) - 0x14U (screen width in tiles) / 2) + 0x14U (screen width in tiles)
#define REDRAW_VRAM_OFFSET_X 0x1AU

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

unsigned int FRAME_BUFFER_TILE_POS_X;
unsigned int FRAME_BUFFER_TILE_POS_Y;


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

    FRAME_BUFFER_TILE_POS_X = 0;
    FRAME_BUFFER_TILE_POS_Y = 0;
    
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
    move_sprite(0, user_pos_x, user_pos_y);
    SHOW_SPRITES;
}

void set_background_tiles()
{
    unsigned int frame_buffer_tile_max_x = FRAME_BUFFER_TILE_POS_X + BACKGROUND_BUFFER_SIZE_X;
    unsigned int frame_buffer_tile_max_y = FRAME_BUFFER_TILE_POS_Y + BACKGROUND_BUFFER_SIZE_Y;
    // @TODO Fix the increment
    //unsigned long current_tile_itx = FRAME_BUFFER_TILE_POS_X + (FRAME_BUFFER_TILE_POS_Y * mainmapWidth);
    unsigned int current_tile_itx = 0;
    unsigned char tile_data = 0x00;

    //set_bkg_tiles(0, 0, mainmapWidth, mainmapHeight, background_tile_map);
    VBK_REG = 0;
    set_bkg_data(0, 8, background_tiles);

    for (background_palette_itx_x = FRAME_BUFFER_TILE_POS_X;
           background_palette_itx_x != frame_buffer_tile_max_x;
           background_palette_itx_x ++)
    {
        // UNCOMMENT TO ADD TEMP HACK TO NOT DRAW MOST OF BACKGROUND IN VRAM
//        if (background_palette_itx_x == 0x10U)
//            break;
        for (background_palette_itx_y = FRAME_BUFFER_TILE_POS_Y;
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
    unsigned int current_tile_itx;
    unsigned char tile_data;
    unsigned int itx_y_max;
    signed int direction_tile_offset;
    
    // Last 3 bits of screen position X
    unsigned int screen_location_pixel_count_x;
    
    scroll_bkg(move_x, move_y);

    screen_location_x += move_x;
    screen_location_y += move_y;
    
    // Redraw tiles in unallocated vram
    if (move_x != 0)
    {
        screen_location_pixel_count_x = screen_location_x & 0x07U;
        // Set current redraw in X to current user position (bit shift to remove pixels within tile) plus
        // current frame buffer size + redraw offset.
        // Mask with vram tile size in X.
        itx_x = ((screen_location_x >> 3) + REDRAW_VRAM_OFFSET_X) & VRAME_SIZE_TILES_X_MASK;
        
        // If processing start of tile (screen location & 0xFF == 0) and If itx is 0,
        // check if wrapped from right side of screen and add farme buffer size to frame buffer tile position,
        // so that tile is used is a continuation from end of vram buffer
        if (itx_x == 0U && screen_location_pixel_count_x == 0U && move_x == 1)
            // If moving right, increment frame buffer pos
            FRAME_BUFFER_TILE_POS_X += BACKGROUND_BUFFER_SIZE_X;
        // Otherwise (since we are moving left), if not at 0, decrease
        else if (itx_x == BACKGROUND_BUFFER_MAX_X && screen_location_pixel_count_x == 7U && move_x == -1)
            FRAME_BUFFER_TILE_POS_X -= BACKGROUND_BUFFER_SIZE_X;

        direction_tile_offset = FRAME_BUFFER_TILE_POS_X;
        // If moving in negative X, decrement actual tiles used so that  the current
        // on-screen background is redrawn.
        if (move_x == -1)
            direction_tile_offset -= BACKGROUND_BUFFER_SIZE_X;

        // If moving in X, redraw column.
        // The iterator is the frame buffer position (not the map position)
        itx_y_max = FRAME_BUFFER_TILE_POS_Y + ((BACKGROUND_BUFFER_SIZE_Y >> 3) * (screen_location_pixel_count_x + 1U)) + 1U;
        for (itx_y = FRAME_BUFFER_TILE_POS_Y + ((BACKGROUND_BUFFER_SIZE_Y >> 3) * screen_location_pixel_count_x);
               itx_y != itx_y_max;
               itx_y ++)
        {
            // Work out current tile - base on tile location in frame buffer plus current map in vram location
            current_tile_itx = ((itx_y + FRAME_BUFFER_TILE_POS_Y) * mainmapWidth) + itx_x + direction_tile_offset;

            // Map data is 2 bytes per tile.
            // First byte's first 7 bits are tile number
            // next bit is vertical flip
            // first bit of second byte is horizontal flip

           VBK_REG = 0; 
            // Set map data
            set_bkg_tiles(
                itx_x, 
                itx_y,
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
                itx_x, 
                itx_y,
                1, 1,  // Only setting 1 tile
                &tile_data
            );            
        }
    }
}

// Called per cycle to update background position and sprite
void update_graphics()
{
    unsigned short background_moved = 0U;
    unsigned int user_screen_pos_x;
    unsigned int user_screen_pos_y;

    // Set user screen position based on current location
    user_screen_pos_x = user_pos_x - screen_location_x;
    user_screen_pos_y = user_pos_y - screen_location_y;

    user_pos_x += travel_x;
    user_pos_y += travel_y;
    
    // Check if sprite too close to edge of screen
    if (user_screen_pos_x == CHARACTER_SCREEN_LOCATION_MARGIN)
        // If player hit LHS of screen, move screen to the left
        move_background(-1, 0);
    else if (user_screen_pos_x ==  (SCREEN_WIDTH - CHARACTER_SCREEN_LOCATION_MARGIN))
        // If player hit RHS of screen, move screen to the right
        move_background(1, 0);
    else
        // If moving sprite, update user screen position X using new user_pos_x
        user_screen_pos_x = user_pos_x - screen_location_x;
        
    if (user_screen_pos_y == CHARACTER_SCREEN_LOCATION_MARGIN)
        move_background(0, -1);
    else if (user_screen_pos_y == (SCREEN_HEIGHT - CHARACTER_SCREEN_LOCATION_MARGIN))
        move_background(0, 1);
    else
        // If moving sprite, update user screen position X using new user_pos_x
        user_screen_pos_y = user_pos_y - screen_location_y;
        
    // Move sprite to new location
    move_sprite(0, user_screen_pos_x, user_screen_pos_y);
    
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
