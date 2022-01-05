/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */


#pragma bank=5

#include <gb/gb.h>
#include <gb/drawing.h>

#include "game_constants.h"
#include "game_state.c"
#include "external_bank_globals.h"
#include "menu_config.h"

void show_number_on_screen(UINT8 start_x, UINT8 start_y, UINT8 max_digits, unsigned int value)
{
    unsigned int current_digit;
    UINT8 itx_x;
    UINT8 itx;

    itx_x = start_x + max_digits;

    for (itx = 0; itx != max_digits; itx ++)
    {
        // If on last iteration, update digit with remainder
        if (value != 0U || current_digit != 0U)
        {
            if (itx == (max_digits - 1U))
            {
                current_digit = value;
            } else {
                current_digit = value % 10U;

                // Update remainder
                value = value / 10U;
            }
        }
    
        if (value == 0U && current_digit == 0U && itx != 0)
        {
            tile_data[0] = 0x00;
        }
        else
        {
            tile_data[0] = MENU_TILE_0 + current_digit;
        }

        // Display current digit
        set_bkg_tiles(itx_x, 0U, 1, 1, &(tile_data[0]));

        // Prepare for next digit
        itx_x -= 1U;
    }
}

void update_window(game_state_t* game_state)
{
    unsigned int current_digit, remainder, itx, itx_x;
    unsigned short shown_symbol;

    // Screen is 20 tiles wide.
    // Window is layed out as:
    // Row 1:
    // 2 tiles for top-half of clock
    // 6 tiles for days passed, 5 numerics with symbol with right padding.
    // 10 tiles for money, left padded (so starts by appearing in last 4 tiles). This allows for 100,000,000 with dollar symbol and 1,000,000,000 without.
    // Row 2:
    // 2 tiles for bottom-half of clock
    // HP:
    // - 5 tiles for HP
    // - 1 tile for '/'
    // - 5 tiles for max HP
    // - 1 tile for HP symbol
    // All of the above HP-stats are left-padded together.

    VBK_REG = 0;

    // CLOCK
    tile_data[0] = MENU_TILE_CLOCK;
    set_win_tiles(0U, 0U, 1, 1, &(tile_data[0]));
    set_win_tiles(0U, 1U, 1, 1, &(tile_data[0]));
    set_win_tiles(1U, 1U, 1, 1, &(tile_data[0]));
    set_win_tiles(1U, 0U, 1, 1, &(tile_data[0]));
    VBK_REG = 1;
    tile_data[0] = 0x21U;
    set_win_tiles(0U, 0U, 1, 1, &(tile_data[0]));
    tile_data[0] = 0x41U;
    set_win_tiles(1U, 1U, 1, 1, &(tile_data[0]));
    tile_data[0] = 0x61U;
    set_win_tiles(0U, 1U, 1, 1, &(tile_data[0]));
    VBK_REG = 0;

    // Set 24 hour time e.g. 17:00
    tile_data[0] = MENU_TILE_0 + game_state->hour / 10U;
    tile_data[1] = MENU_TILE_0 + game_state->hour % 10U;
    tile_data[2] = MENU_TILE_COLON;
    tile_data[3] = MENU_TILE_0;
    tile_data[4] = MENU_TILE_0;
    // Display time
    set_win_tiles(2U, 1U, 5, 1, &tile_data);

    // DAYS PASSED
    remainder = game_state->days_passed;

    // Start at WINDOW_MAX_DIGITS_DAYS + margin from left
    itx_x = WINDOW_MAX_DIGITS_DAYS + 1U;
    for (itx = 0; itx != WINDOW_MAX_DIGITS_DAYS; itx ++)
    {
        // If on last iteration, update digit with remainder
        if (itx == (WINDOW_MAX_DIGITS_DAYS - 1U))
        {
            current_digit = remainder;
        }
        else
        {
            current_digit = remainder % 10U;

            // Update remainder
            remainder = remainder / 10U;
        }
        
        if (remainder == 0U && current_digit == 0U && itx != 0)
            break;

        // Display current digit
        tile_data[0] = MENU_TILE_0 + current_digit;
        set_win_tiles(itx_x, 0U, 1, 1, &(tile_data[0]));

        // Prepare for next digit
        itx_x -= 1U;
    }
    
    // BALANCE
    // Iterate over days passed
    remainder = game_state->balance;

    shown_symbol = 0U;

    // Start at WINDOW_MAX_DIGITS_DAYS + margin from left, days symbols, 1 padding and dollar symbol.
    // Remove 1 as loop iterator starting at 1 
    itx_x = 5U + WINDOW_MAX_DIGITS_DAYS + WINDOW_MAX_DIGITS_BALANCE;

    for (itx = 0; itx != WINDOW_MAX_DIGITS_BALANCE; itx ++)
    {
        // If on last iteration, update digit with remainder
        if (remainder != 0U || current_digit != 0U)
        {
            if (itx == (WINDOW_MAX_DIGITS_BALANCE - 1U))
            {
                current_digit = remainder;
            } else {
                current_digit = remainder % 10U;

                // Update remainder
                remainder = remainder / 10U;
            }
        }
    
        if (remainder == 0U && current_digit == 0U && itx != 0)
        {
            // Display dollar symbol, if not already shown
            if (shown_symbol == 0U)
            {
                tile_data[0] = MENU_TILE_DOLLAR;
                shown_symbol = 1U;
            }
            else
            {
                // Otherwise display blank tile
                tile_data[0] = 0x00;
            }
        }
        else
        {
            tile_data[0] = MENU_TILE_0 + current_digit;
        }

        // Display current digit
        set_win_tiles(itx_x, 0U, 1, 1, &(tile_data[0]));

        // Prepare for next digit
        itx_x -= 1U;
    }
    

    // HP

    // Start at right hand side
    itx_x = SCREEN_WIDTH_TILES - 2U;
    // Draw HP symbol
    tile_data[0] = MENU_TILE_HP;
    set_win_tiles(itx_x, 1U, 1, 1, &(tile_data[0]));
    itx_x -= 1U;
    shown_symbol = 0U;
    remainder = game_state->max_hp;
    for (itx = 0; itx != WINDOW_MAX_DIGITS_HP; itx ++)
    {
        // If on last iteration, update digit with remainder
        if (remainder != 0U || current_digit != 0U)
        {
            if (itx == (WINDOW_MAX_DIGITS_HP - 1U))
            {
                current_digit = remainder;
            } else {
                current_digit = remainder % 10U;

                // Update remainder
                remainder = remainder / 10U;
            }
        }
    
        if (remainder == 0U && current_digit == 0U && itx != 0)
        {
            // Display slash symbol, if not already shown
            if (shown_symbol == 0U)
            {
                tile_data[0] = MENU_TILE_SLASH;
                shown_symbol = 1U;
                
                // Once complete with max_hp, continue to actual HP value
                remainder = game_state->hp;
                // Set itx back to start. When using high number values (5 digits for each), then this may cause an issue
                // with failing to remove the remaining digits.
                itx = 0;
            }
            else
            {
                // Otherwise break
                tile_data[0] = 0x00;
            }
        }
        else
        {
            tile_data[0] = MENU_TILE_0 + current_digit;
        }

        // Display current digit
        set_win_tiles(itx_x, 1U, 1, 1, &(tile_data[0]));

        // Prepare for next digit
        itx_x -= 1U;
    }
}

void setup_window()
{
    UBYTE tile_data[2U];
    unsigned int itx_x, itx_y;

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
    tile_data[0] = MENU_TILE_DA;
    set_win_tiles(WINDOW_MAX_DIGITS_DAYS + 2U, 0U, 1U, 1U, &(tile_data[0]));
    tile_data[0] = MENU_TILE_YS;
    set_win_tiles(WINDOW_MAX_DIGITS_DAYS + 3U, 0U, 1U, 1U, &(tile_data[0]));

    // Move window up to only display 2 rows at top of screen
    move_win(7, (SCREEN_HEIGHT_TILES - 2U) << 3);
}

