/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */

// Methods to manipulate 32-bit balance

#include "main.h"
#include "balance.h"

/*
 * has_money
 *
 * Whether the player's balance exceeds a certain amount (or is high enough for a purchase)
 *
 * @param amount_h Upper 16-bit value of the amount to check
 * @param amount_l Lower 16-bit value of the amount to check
 *
 * @returns 1 if the user has enough balance. 0 if not.
 */
BOOLEAN has_money(UINT16 amount_h, UINT16 amount_l)
{
    UINT16 remainder = amount_h;

    // If lower balance doesn't contain enough,
    // add 1 to required amount in higher int
    if (amount_l > game_state.balance[0U])
    {
        remainder = amount_h + 1U;
    }

    // If higher balance int doesn't
    // contain enough, return 0
    if (remainder > game_state.balance[1U])
    {
        return 0U;
    }
    // Otherwise, return 1
    return 1U;
}

/*
 * remove_money
 *
 * Removes a 32-bit value from the player's balance
 *
 * @param amount_h Upper 16-bit value of the amount to remove
 * @param amount_l Lower 16-bit value of the amount to remove
 *
 * @returns 1 if the amount was removed. 0 if not.
 */
BOOLEAN remove_money(UINT16 amount_h, UINT16 amount_l)
{
    UINT16 remainder = amount_h;

    // If lower balance doesn't contain enough,
    // add 1 to required amount in higher int
    if (amount_l > game_state.balance[0U])
    {
        remainder = amount_h + 1U;
    }

    // If higher balance int doesn't
    // contain enough, return 0
    if (amount_h > game_state.balance[1U])
    {
        // Check for overflow
        return 0U;
    }
    // Otherwise, remove the money and return:

    // If the lower did not require carrying,
    // remove it from the lower balance
    if (amount_h == remainder)
    {
        game_state.balance[0] -= amount_l;
    }
    else
    {
        // Else, remove the current balance from lower from
        // balance, reset and remove the remainder
        amount_l -= game_state.balance[0];
        game_state.balance[0] = 0xFFFFU - amount_l;
    }
    // Remove the upper balance
    game_state.balance[1] -= remainder;

    return 1U;
}

/*
 * add_money
 *
 * Adds a 32-bit value to the player's balance
 *
 * @param amount_h Upper 16-bit value of the amount to add
 * @param amount_l Lower 16-bit value of the amount to add
 */
void add_money(UINT16 amount_h, UINT16 amount_l)
{
    UINT16 overflow = amount_h;

    // Check for overflow in lower
    if ((game_state.balance[0] + amount_l) < game_state.balance[0])
    {
        // Check for possible overflow of amount_h
        if (overflow == 0xFFFFU)
        {
            game_state.balance[0] = 0xFFFFU;
            game_state.balance[1] = 0xFFFFU;
            return;
        }

        overflow += 1U;
        // Make the lower amount the difference after the overflow and set lower balance
        // to 0
        amount_l = amount_l - (0xFFFFU - game_state.balance[0]);
        game_state.balance[0] = 0U;
    }

    // Check for overflow in higher
    if ((game_state.balance[1] + overflow) < game_state.balance[1])
    {
        game_state.balance[0] = 0xFFFFU;
        game_state.balance[1] = 0xFFFFU;
        return;
    }

    // Increase lower int of balance
    game_state.balance[0] += amount_l;

    game_state.balance[1] += overflow;
}
