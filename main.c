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

unsigned char *background_tile_map;
unsigned char *background_tiles;
unsigned char *background_tile_palette;
unsigned int background_palette_itx_x;
unsigned int background_palette_itx_y;

void set_background_tiles()
{
    set_bkg_tiles(0, 0, mainmapWidth, mainmapHeight, background_tile_map);
    VBK_REG = 0;
    set_bkg_data(0, 8, background_tiles);


    VBK_REG = 1;
    for (background_palette_itx_x = 0; background_palette_itx_x < mainmapWidth; background_palette_itx_x ++)
    {
        for (background_palette_itx_y = 0; background_palette_itx_y < mainmapHeight; background_palette_itx_y ++)
        {
            // Set palette data in VBK_REG1 for tile
            set_bkg_tiles(
                background_palette_itx_x, 
                background_palette_itx_y,
                1, 1,  // Only setting 1 tile
                background_tile_palette[  // From the palette map
                    // Lookup tile from background tile map
                    background_tile_map[
                        background_palette_itx_x + (background_palette_itx_y * mainmapWidth)  // Calculate index based on X, y index
                    ]
                ]
            );
        }
    }

    // Reset VKG_REG to original value
    VBK_REG = 0;
}

void main()
{
/*        printf("Welcome to GAMEBOY\nProgramming");
        printf("\nPress Start");
        waitpad(J_START);  // other keys are J_A, J_UP, J_SELECT, etc.
        printf("\nIsn't it easy!");
  */      

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
