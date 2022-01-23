/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */

#pragma bank=2

#include "logic_functions.h"

void bus_sell_goods(menu_state_t *menu_state, game_state_t *game_state)
{
    UINT8 cost;
    UINT16 offer;

    // Check time of day - must be midnight (morning - 0)
    if (game_state->hour != 0)
        return;

    if (menu_state->current_item_x == 0U && menu_state->current_item_y == 1U)  // Brooklyn
    {
        cost = 115U;
    }
    else if (menu_state->current_item_x == 1U && menu_state->current_item_y == 1U)  // Chicago
    {
        cost = 115U;
    }
    else if (menu_state->current_item_x == 0U && menu_state->current_item_y == 2U)  // Detroit
    {
        cost = 100U;
    }
    else if (menu_state->current_item_x == 1U && menu_state->current_item_y == 2U)  // Camden
    {
        cost = 130U;
    }
    else if (menu_state->current_item_x == 0U && menu_state->current_item_y == 3U)  // LA
    {
        cost = 100U;
    }
    else if (menu_state->current_item_x == 1U && menu_state->current_item_y == 3U)  // Vegas
    {
        cost = 130U;
    }

    // Check if user has enough money
    if (! HAS_MONEY_P(cost))
    {
        return;
    }
    game_state->balance -= cost;

    // Set time of day to 24 hours
    game_state->hour = 24;

    // If player hasn't got any booze or cocaine, leave
    if (game_state->inventory[S_INVENTORY_COCAINE] == 0 && game_state->inventory[S_INVENTORY_BOTTLE_OF_BEER] == 0)
        return;

    // If player hasn't got a gun or ammo, lose booze, cocaine and money
    if (game_state->inventory[S_INVENTORY_HAND_GUN] == 0U || game_state->inventory[S_INVENTORY_AMMO] == 0U)
    {
        game_state->balance = 0;
        game_state->inventory[S_INVENTORY_COCAINE] = 0;
        game_state->inventory[S_INVENTORY_BOTTLE_OF_BEER] = 0;
        return;
    }

    // If strength is lower than random number between 100-225...
    if ((100 + (sys_time % 125)) > game_state->strength)
    {
        // Lose cocaine, booze and money
        game_state->balance = 0;
        game_state->inventory[S_INVENTORY_COCAINE] = 0;
        game_state->inventory[S_INVENTORY_BOTTLE_OF_BEER] = 0;
        return;
    }

    // If cell phone not owned, leave
    if (game_state->inventory[S_INVENTORY_CELL_PHONE] == 0U)
        return;

    // If player has more than 50 cocaine OR 50 booze, 'go to jail' for 5 days, losing gun, ammo, cocaine, booze
    if (game_state->inventory[S_INVENTORY_COCAINE] > 50 || game_state->inventory[S_INVENTORY_BOTTLE_OF_BEER] > 50)
    {
        game_state->days_passed += 5U;
        game_state->inventory[S_INVENTORY_COCAINE] = 0;
        game_state->inventory[S_INVENTORY_BOTTLE_OF_BEER] = 0;
        game_state->inventory[S_INVENTORY_HAND_GUN] = 0;
        game_state->inventory[S_INVENTORY_AMMO] = 0;
    }

    // 1 in 10 chance that contact takes stash
    if (sys_time % 10 == 0U)
    {
        game_state->inventory[S_INVENTORY_COCAINE] = 0;
        game_state->inventory[S_INVENTORY_BOTTLE_OF_BEER] = 0;
        return;
    }

    // SELL!

    // Half chance of selling cocaine or booze
    if (sys_time % 1 == 0U)
    {
        // Selling booze
        offer = game_state->charm / 6U;

        if (offer > 50U)
            offer = 50U;

        // Randomly decide whether to add/remove a small amount
        if (sys_time % 1 == 0U)
        {
            offer += (sys_time % 5);
        }
        else if (offer > 5U)
        {
            offer -= (sys_time % 5);
        }

        // Minimum offer of 5
        if (offer < 5U)
            offer = 5U;

        game_state->balance += (game_state->inventory[S_INVENTORY_BOTTLE_OF_BEER] * offer);
        game_state->inventory[S_INVENTORY_BOTTLE_OF_BEER] = 0U;
    }
    else
    {
        // Selling cocaine
        offer = 10 * (game_state->charm / 5U);

        if (offer > 600U)
            offer = 600U;

        // Randomly decide whether to add/remove a small amount
        if (sys_time % 1 == 0U)
        {
            offer += (sys_time % 50);
        }
        else if (offer > 50U)
        {
            offer -= (sys_time % 50);
        }

        // Minimum offer of 5
        if (offer < 50U)
            offer = 50U;

        game_state->balance += (game_state->inventory[S_INVENTORY_COCAINE] * offer);
        game_state->inventory[S_INVENTORY_COCAINE] = 0U;
    }
}

