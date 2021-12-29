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

void update_window(game_state_t* game_state)
{
    unsigned int current_digit, remainder, itx, itx_x;
    unsigned short shown_symbol;
    // 6 hours' worth of positions with X and Y
    // movement vectors about the centre of the clock
    const unsigned short clock_array_positions[6][2] = {
        // 0 - pointing straight up
        {0x0U, 0x8U},
        {0x1U, 0x7U},
        {0x2U, 0x6U},
        {0x3U, 0x5U},
        {0x4U, 0x4U},
        {0x5U, 0x3U},
        {0x6U, 0x2U}
    };
    const unsigned short clock_starting_positions[4][2] = {
        {9U, SCREEN_HEIGHT - 9U},
        {9U, SCREEN_HEIGHT - 8U},
        {8U, SCREEN_HEIGHT - 8U},
        {8U, SCREEN_HEIGHT - 9U}
    };
    unsigned short end_x, end_y;

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
    tile_data[0] = MENU_ROW_2_TILE_DATA_OFFSET - 1U;
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
    
    remainder = game_state->hour / 4;
    current_digit = game_state->hour % 6;

    if (remainder == 0U)
    {
        end_x = clock_starting_positions[current_digit][0U] + clock_array_positions[current_digit][0U];
        end_y = clock_starting_positions[current_digit][1U] - clock_array_positions[current_digit][1U];
    }
    else if (remainder == 1U)
    {
        end_x = clock_starting_positions[current_digit][0U] + clock_array_positions[current_digit][0U];
        end_y = clock_starting_positions[current_digit][1U] + clock_array_positions[current_digit][1U];
    }
    else if (remainder == 2U)
    {
        end_x = clock_starting_positions[current_digit][0U] - clock_array_positions[current_digit][0U];
        end_y = clock_starting_positions[current_digit][1U] + clock_array_positions[current_digit][1U];
    }
    else if (remainder == 3U)
    {
        end_x = clock_starting_positions[current_digit][0U] - clock_array_positions[current_digit][0U];
        end_y = clock_starting_positions[current_digit][1U] - clock_array_positions[current_digit][1U];
    }

    line(
        clock_starting_positions[current_digit][0U],
        clock_starting_positions[current_digit][1U],
        end_x,
        end_y
    );

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
        } else {
            current_digit = remainder % 10U;

            // Update remainder
            remainder = remainder / 10U;
        }
        
        if (remainder == 0U && current_digit == 0U && itx != 0)
            break;

        // Display current digit
        tile_data[0] = MENU_ROW_2_TILE_DATA_OFFSET + 1U + current_digit;
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
                tile_data[0] = MENU_ROW_2_TILE_DATA_OFFSET + 11U;
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
            tile_data[0] = MENU_ROW_2_TILE_DATA_OFFSET + 1U + current_digit;
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
    tile_data[0] = MENU_ROW_2_TILE_DATA_OFFSET + 12U;
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
            // Display dollar symbol, if not already shown
            if (shown_symbol == 0U)
            {
                tile_data[0] = MENU_ROW_2_TILE_DATA_OFFSET + 16U;
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
            tile_data[0] = MENU_ROW_2_TILE_DATA_OFFSET + 1U + current_digit;
        }

        // Display current digit
        set_win_tiles(itx_x, 1U, 1, 1, &(tile_data[0]));

        // Prepare for next digit
        itx_x -= 1U;
    }
}
