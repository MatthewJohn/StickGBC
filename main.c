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

const UWORD bgpal[] = {
    RGB(22, 22, 22),
    RGB(10, 10, 10),
    RGB(14, 6, 1),
    RGB(14, 31, 0),
    RGB(28, 29, 5),
    RGB(22, 22, 22),
    RGB(13, 13, 13),
    RGB(0, 0, 0),
    RGB(28, 29, 5),
    RGB(7, 23, 8),
    RGB(4, 14, 6),
    RGB(0, 7, 5),
    RGB(28, 29, 5),
    RGB(7, 23, 8),
    RGB(4, 14, 6),
    RGB(0, 7, 5),
    RGB(28, 29, 5),
    RGB(7, 23, 8),
    RGB(4, 14, 6),
    RGB(0, 7, 5),
    RGB(28, 29, 5),
    RGB(7, 23, 8),
    RGB(4, 14, 6),
    RGB(0, 7, 5),
    RGB(28, 29, 5),
    RGB(7, 23, 8),
    RGB(4, 14, 6),
    RGB(0, 7, 5),
    RGB(28, 29, 5),
    RGB(7, 23, 8),
    RGB(4, 14, 6),
    RGB(0, 7, 5)
};

void main()
{
/*        printf("Welcome to GAMEBOY\nProgramming");
        printf("\nPress Start");
        waitpad(J_START);  // other keys are J_A, J_UP, J_SELECT, etc.
        printf("\nIsn't it easy!");
  */      
        set_bkg_data(0, 11, mainmaptiles);

      set_bkg_palette(0, 1, &bgpal);

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
