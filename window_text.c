/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */

#pragma bank=8

#include "window_text.h"

/*
 * show_window_text
 *
 * Show array of text onscreen and wait
 * for user to confirm
 */
void show_window_text(UINT8 *text)
{
    UINT8 itx_x = 2U;
    UINT8 itx_y = 2U;
    UINT8 text_index = 0;
    UINT16 character_number;
    UBYTE tile_data;

    while (1)
    {
        // Check if reached end of text
        if (text[text_index] == WINDOW_TEXT_END)
        {
            break;
        }

        character_number = text[text_index];
        // Load tile into high tile set
        VBK_REG = 1;
        set_bkg_data(character_number, 1, &(windowtexttiles[character_number << 4]));
        VBK_REG = 0;

        // Set screen tile to loaded tile
        set_bkg_tiles(itx_x, itx_y, 1, 1, &(character_number));

        VBK_REG = 1;
        // Mark as using palette 1 and high bank of tiles
        tile_data = 0x9;
        set_bkg_tiles(itx_x, itx_y, 1, 1, &(tile_data));
        VBK_REG = 0;

        if (itx_x == (SCREEN_WIDTH_TILES - 2U))
        {
            itx_y += 1U;
            itx_x = 3U;
        }
        else
            itx_x += 1U;

        text_index += 1U;
    }

    // Load blank tile (may have not been loaded - but seems unlikely)
    VBK_REG = 1;
    set_bkg_data(0, 1, &(windowtexttiles[0]));
    VBK_REG = 0;

    // File up remainder of row with blank tiles
    while (itx_x != (SCREEN_WIDTH_TILES - 2U))
    {
        // Set screen tile to empty tile
        character_number = 0;
        set_bkg_tiles(itx_x, itx_y, 1, 1, &(character_number));

        VBK_REG = 1;
        // Mark as using palette 1 and high bank of tiles
        tile_data = 0x9;
        set_bkg_tiles(itx_x, itx_y, 1, 1, &(tile_data));
        VBK_REG = 0;
        itx_x += 1U;
    }
    
    // Wait for original key press to be let go of
    delay(300);

    // Reset original key pressed
    joypad_state.a_pressed = 0;
    joypad_state.b_pressed = 0;

    // Wait for user to press A or B
    while (joypad_state.a_pressed == 0U && joypad_state.b_pressed == 0U)
    {
        wait_vbl_done();

        main_check_joy(ROM_BANK_WINDOW_TEXT);
    }
}
