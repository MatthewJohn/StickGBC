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


void main()
{
/*        printf("Welcome to GAMEBOY\nProgramming");
        printf("\nPress Start");
        waitpad(J_START);  // other keys are J_A, J_UP, J_SELECT, etc.
        printf("\nIsn't it easy!");
  */      
        set_bkg_data(0, 11, mainmaptiles);

      set_bkg_palette(0, 8, &bgpal);

        set_bkg_tiles(0, 0, mainmapWidth, mainmapHeight, mainmap);
 wait_vbl_done();
        SHOW_BKG;
        DISPLAY_ON;
        
        while(1) {
                wait_vbl_done();
                scroll_bkg(1, 0);
                delay(100);
        }
}
