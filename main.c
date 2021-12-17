/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */

#include <gb/gb.h>
/*#include <gb/drawing.h>*/
#include <stdio.h>

#include "main_map_tileset.c"
#include "main_map.c"
#include "main_map_palette.c"


// Max address if 0x1F, set to 0x20 for loops that loop whilst
// less than the value (or rather !=)
#define BACKGROUND_BUFFER_SIZE_X 0x20U
#define BACKGROUND_BUFFER_SIZE_Y 0x20U


unsigned char *background_tile_map;
unsigned char *background_tiles;
unsigned char *background_tile_palette;
unsigned int background_palette_itx_x;
unsigned int background_palette_itx_y;

unsigned int FRAME_BUFFER_TILE_POS_X;
unsigned int FRAME_BUFFER_TILE_POS_Y;



unsigned long MAIN_MAP_VERTICAL_FLIP_TILES[] = {
    // Left hand road, buttom of road marking
    0x0502, 0x0503, 0x0505, 0x0506, 0x0508, 0x0509, 0x050b, 0x050c, 0x050e, 0x050f,
    0x0511, 0x0512, 0x0514, 0x0515, 0x0517, 0x0518, 0x051a, 0x051b, 0x051d, 0x051e
};
unsigned int MAIN_MAP_VERICAL_FLIP_COUNT;

void init_map_variables()
{
    MAIN_MAP_VERICAL_FLIP_COUNT = (sizeof(MAIN_MAP_VERTICAL_FLIP_TILES) / sizeof(MAIN_MAP_VERTICAL_FLIP_TILES[0]));
    FRAME_BUFFER_TILE_POS_X = 0;
    FRAME_BUFFER_TILE_POS_Y = 0;
}

void set_background_tiles()
{
    unsigned int frame_buffer_tile_max_x = FRAME_BUFFER_TILE_POS_X + BACKGROUND_BUFFER_SIZE_X;
    unsigned int frame_buffer_tile_max_y = FRAME_BUFFER_TILE_POS_Y + BACKGROUND_BUFFER_SIZE_Y;
    // @TODO Fix the increment
    //unsigned long current_tile_itx = FRAME_BUFFER_TILE_POS_X + (FRAME_BUFFER_TILE_POS_Y * mainmapWidth);
    unsigned int current_tile_itx = 0;
    unsigned char tile_data = 0x00;
    unsigned int main_map_vertical_flip_itx;

    //set_bkg_tiles(0, 0, mainmapWidth, mainmapHeight, background_tile_map);
    VBK_REG = 0;
    set_bkg_data(0, 8, background_tiles);

    for (background_palette_itx_x = FRAME_BUFFER_TILE_POS_X;
           background_palette_itx_x != frame_buffer_tile_max_x;
           background_palette_itx_x ++)
    {
        for (background_palette_itx_y = FRAME_BUFFER_TILE_POS_Y;
               background_palette_itx_y != frame_buffer_tile_max_y;
               background_palette_itx_y ++)
        {
            // Temp Test
            current_tile_itx = (background_palette_itx_y * mainmapWidth) + background_palette_itx_x;

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
            for (main_map_vertical_flip_itx = 0;
                  main_map_vertical_flip_itx != MAIN_MAP_VERICAL_FLIP_COUNT;
                  main_map_vertical_flip_itx ++)
                if (current_tile_itx == MAIN_MAP_VERTICAL_FLIP_TILES[main_map_vertical_flip_itx])
                {
                    tile_data |= S_FLIPY;
                    break;
                }
   
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

    wait_vbl_done();
    SHOW_BKG;
    DISPLAY_ON;
        
        while(1) {
                wait_vbl_done();
                scroll_bkg(1, 0);
                delay(100);
        }
}
