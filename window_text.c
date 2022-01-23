/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */

#pragma bank=8

#include "window_text.h"

void show_window_text(UINT8 *text)
{
    UINT8 itx_x = 3U;
    UINT8 itx_y = 3U;
    UINT8 text_index = 0;
    UBYTE tile_data;

    while (1)
    {
        // Check if reached end of text
        if (text[text_index] == WINDOW_TEXT_END)
        {
            break;
        }
        
        // Load tile into high tile set
        VBK_REG = 1;
        set_bkg_data(text[text_index], 1, &(windowtexttiles[text[text_index] << 4]));
        VBK_REG = 0;

        // Set screen tile to loaded tile
        tile_data = text[text_index];
        set_bkg_tiles(itx_x, itx_y, 1, 1, &(tile_data));

        VBK_REG = 1;
        // Mark as using palette 0 and high bank of tiles
        tile_data = 0x8;
        set_bkg_tiles(itx_x, itx_y, 1, 1, &(tile_data));
        VBK_REG = 0;

        if (itx_x == 10U)
        {
            itx_y += 1U;
            itx_x = 3U;
        }

        text_index += 1U;
    }
}
