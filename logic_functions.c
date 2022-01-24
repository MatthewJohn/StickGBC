/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */

#pragma bank=2

#include "logic_functions.h"
#include "window_text_data.h"

void bus_sell_goods(menu_state_t *menu_state, game_state_t *game_state)
{
    UINT8 cost;
    UINT16 offer;
    UINT8 rnd_3 = sys_time % 3;
    BOOLEAN no_deal;
    UINT8 item_selection = sys_time % 2;
    UINT8 strength_modulus;
    UINT8 max_product = 50U;

    // Check time of day - must be midnight (morning - 0)
    if (game_state->hour != 0)
    {
        main_show_window_text(&win_txt_bus_statn_late, ROM_BANK_LOGIC_FUNCTIONS);
        return;
    }

    if (menu_state->current_item_x == 0U && menu_state->current_item_y == 1U)  // Brooklyn
    {
        cost = 115U;
        strength_modulus = 125U;
        max_product = 49U;
    }
    else if (menu_state->current_item_x == 1U && menu_state->current_item_y == 1U)  // Chicago
    {
        cost = 115U;
        strength_modulus = 125U;
        // Always sell beer
        item_selection = 0U;
    }
    else if (menu_state->current_item_x == 0U && menu_state->current_item_y == 2U)  // Detroit
    {
        cost = 100U;
        strength_modulus = 150U;
        // Always sell cocaine
        item_selection = 1U;
    }
    else if (menu_state->current_item_x == 1U && menu_state->current_item_y == 2U)  // Camden
    {
        cost = 130U;
        strength_modulus = 110U;
        // Always sell beer
        item_selection = 0U;
    }
    else if (menu_state->current_item_x == 0U && menu_state->current_item_y == 3U)  // LA
    {
        cost = 100U;
        strength_modulus = 150U;
        // Always sell cocaine
        item_selection = 1U;
    }
    else if (menu_state->current_item_x == 1U && menu_state->current_item_y == 3U)  // Vegas
    {
        cost = 130U;
        strength_modulus = 110U;
    }

    // Check if user has enough money
    if (! HAS_MONEY_P(cost))
    {
        main_show_window_text(&win_txt_bus_statn_no_mon, ROM_BANK_LOGIC_FUNCTIONS);
        return;
    }
    game_state->balance -= cost;

    // Set time of day to 24 hours
    game_state->hour = 24;

    // If player hasn't got any booze or cocaine, leave
    if (game_state->inventory[S_INVENTORY_COCAINE] == 0 && game_state->inventory[S_INVENTORY_BOTTLE_OF_BEER] == 0)
    {
        main_update_window(ROM_BANK_LOGIC_FUNCTIONS);
        main_show_window_text(&win_txt_bus_statn_no_inv, ROM_BANK_LOGIC_FUNCTIONS);
        return;
    }

    // If player hasn't got a gun or ammo, lose booze, cocaine and money
    if (game_state->inventory[S_INVENTORY_HAND_GUN] == 0U || game_state->inventory[S_INVENTORY_AMMO] == 0U)
    {
        game_state->balance = 0;
        game_state->inventory[S_INVENTORY_COCAINE] = 0;
        game_state->inventory[S_INVENTORY_BOTTLE_OF_BEER] = 0;
        main_update_window(ROM_BANK_LOGIC_FUNCTIONS);

        if (game_state->inventory[S_INVENTORY_HAND_GUN] == 0U)
        {
            if (rnd_3 == 0)
                main_show_window_text(&win_txt_bus_statn_no_gun_1, ROM_BANK_LOGIC_FUNCTIONS);
            else if (rnd_3 == 1)
                main_show_window_text(&win_txt_bus_statn_no_gun_2, ROM_BANK_LOGIC_FUNCTIONS);
            else
                main_show_window_text(&win_txt_bus_statn_no_gun_3, ROM_BANK_LOGIC_FUNCTIONS);
        }
        else
        {
            main_show_window_text(&win_txt_bus_statn_no_ammo, ROM_BANK_LOGIC_FUNCTIONS);
        }
        return;
    }

    // If strength is lower than random number between 100-225...
    if ((100 + (sys_time % strength_modulus)) > game_state->strength)
    {
        // Lose cocaine, booze and money
        game_state->balance = 0;
        game_state->inventory[S_INVENTORY_COCAINE] = 0;
        game_state->inventory[S_INVENTORY_BOTTLE_OF_BEER] = 0;
        main_update_window(ROM_BANK_LOGIC_FUNCTIONS);

        if (rnd_3 == 0)
            main_show_window_text(&win_txt_bus_statn_rob_1, ROM_BANK_LOGIC_FUNCTIONS);
        else if (rnd_3 == 1)
            main_show_window_text(&win_txt_bus_statn_rob_2, ROM_BANK_LOGIC_FUNCTIONS);
        else
            main_show_window_text(&win_txt_bus_statn_rob_3, ROM_BANK_LOGIC_FUNCTIONS);
        return;
    }

    // If cell phone not owned, leave
    if (game_state->inventory[S_INVENTORY_CELL_PHONE] == 0U)
    {
        main_update_window(ROM_BANK_LOGIC_FUNCTIONS);
        main_show_window_text(&win_txt_bus_statn_no_phone, ROM_BANK_LOGIC_FUNCTIONS);
        return;
    }

    // If player has more than 50 cocaine OR 50 booze, 'go to jail' for 5 days, losing gun, ammo, cocaine, booze
    if (game_state->inventory[S_INVENTORY_COCAINE] > max_product || game_state->inventory[S_INVENTORY_BOTTLE_OF_BEER] > max_product)
    {
        game_state->days_passed += 5U;
        game_state->inventory[S_INVENTORY_COCAINE] = 0;
        game_state->inventory[S_INVENTORY_BOTTLE_OF_BEER] = 0;
        game_state->inventory[S_INVENTORY_HAND_GUN] = 0;
        game_state->inventory[S_INVENTORY_AMMO] = 0;

        main_update_window(ROM_BANK_LOGIC_FUNCTIONS);

        main_show_window_text(&win_txt_bus_statn_bust, ROM_BANK_LOGIC_FUNCTIONS);

        return;
    }

    // 1 in 10 chance that contact takes stash
    if (sys_time % 10 == 0U)
    {
        game_state->inventory[S_INVENTORY_COCAINE] = 0;
        game_state->inventory[S_INVENTORY_BOTTLE_OF_BEER] = 0;

        main_show_window_text(&win_txt_bus_statn_bad, ROM_BANK_LOGIC_FUNCTIONS);
        main_update_window(ROM_BANK_LOGIC_FUNCTIONS);
        return;
    }

    // SELL!

    // Half chance of selling cocaine or booze
    if (item_selection == 0U)
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

        if (game_state->inventory[S_INVENTORY_BOTTLE_OF_BEER] == 0U)
            no_deal = 1U;
        else
        {
            offer = game_state->inventory[S_INVENTORY_BOTTLE_OF_BEER]  * offer;

            // Update window before showing offer
            main_update_window(ROM_BANK_LOGIC_FUNCTIONS);

            // Write offer values to screen
            main_show_number(0, 3, 5, (unsigned int)offer, ROM_BANK_LOGIC_FUNCTIONS);
            main_show_number(
                10, 3, 2,
                ((unsigned int)game_state->inventory[S_INVENTORY_BOTTLE_OF_BEER] & 0xFFU),
                ROM_BANK_LOGIC_FUNCTIONS
            );

            // Request user input for offer
            main_show_window_text(&win_txt_bus_statn_beer_deal, ROM_BANK_LOGIC_FUNCTIONS);

            if (joypad_state.a_pressed)
            {
                game_state->balance += offer;
                game_state->inventory[S_INVENTORY_BOTTLE_OF_BEER] = 0U;
            }
            no_deal = 0U;
        }
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

        if (game_state->inventory[S_INVENTORY_COCAINE] == 0)
        {
            no_deal = 1U;
        }
        else
        {
            offer = game_state->inventory[S_INVENTORY_COCAINE]  * offer;

            // Update window before showing offer
            main_update_window(ROM_BANK_LOGIC_FUNCTIONS);

            // Write offer values to screen
            main_show_number(0, 3, 5, (unsigned int)offer, ROM_BANK_LOGIC_FUNCTIONS);
            main_show_number(
                10, 3, 2,
                ((unsigned int)game_state->inventory[S_INVENTORY_COCAINE] & 0xFFU),
                ROM_BANK_LOGIC_FUNCTIONS
            );

            // Request user input for offer
            main_show_window_text(&win_txt_bus_statn_coke_deal, ROM_BANK_LOGIC_FUNCTIONS);

            if (joypad_state.a_pressed)
            {
                game_state->balance += offer;
                game_state->inventory[S_INVENTORY_COCAINE] = 0U;
            }
            no_deal = 0U;
        }
    }

    // Update main window before returning
    main_update_window(ROM_BANK_LOGIC_FUNCTIONS);

    if (no_deal)
        main_show_window_text(&win_txt_bus_statn_no_deal, ROM_BANK_LOGIC_FUNCTIONS);
}

/*
 * apply_fro_job_promotion
 * 
 * Check for intelligence and promote job at NLI
 */
void apply_for_job_promotion(game_state_t *game_state, menu_config_t *menu_config, menu_config_t *menu_config_restaurant)
{
    // Check current if applying for job
    if (menu_config->items[MENU_NLI_PROMOTION_ITEM] == MENU_ITEM_INDEX_APPLY_FOR_JOB)
    {
        if (game_state->intelligence >= 20U)
        {
            menu_config_restaurant->items[3U] = MENU_ITEM_INDEX_EMPTY;
            menu_config->items[MENU_NLI_PROMOTION_ITEM] = MENU_ITEM_INDEX_APPLY_FOR_PROMOTION;
            menu_config->items[MENU_NLI_WORK_ITEM] = MENU_ITEM_INDEX_WORK_JANITOR;
            modify_karma(1);
            // Select 'work' item for new job
            move_to_menu_item(1U, 3U, ROM_BANK_LOGIC_FUNCTIONS);
            main_show_window_text(&win_txt_nli_jan, ROM_BANK_LOGIC_FUNCTIONS);
        }
        else
        {
            // Show unsuccessful message
            main_show_window_text(&win_txt_nli_no_int, ROM_BANK_LOGIC_FUNCTIONS);
        }
    }
    else if (menu_config->items[MENU_NLI_WORK_ITEM] == MENU_ITEM_INDEX_WORK_JANITOR)
    {
        if (game_state->intelligence >= 40U)
        {
            menu_config->items[MENU_NLI_WORK_ITEM] = MENU_ITEM_INDEX_WORK_MAIL_CLERK;
            modify_karma(3);
            // Select 'work' item for new job
            move_to_menu_item(1U, 3U, ROM_BANK_LOGIC_FUNCTIONS);
            main_show_window_text(&win_txt_nli_mail, ROM_BANK_LOGIC_FUNCTIONS);
        }
        else
        {
            // Show unsuccessful message
            main_show_window_text(&win_txt_nli_no_int, ROM_BANK_LOGIC_FUNCTIONS);
        }
    }
    else if (menu_config->items[MENU_NLI_WORK_ITEM] == MENU_ITEM_INDEX_WORK_MAIL_CLERK)
    {
        if (game_state->intelligence >= 75U)
        {
            menu_config->items[MENU_NLI_WORK_ITEM] = MENU_ITEM_INDEX_WORK_SALESMAN;
            modify_karma(3);
            // Select 'work' item for new job
            move_to_menu_item(1U, 3U, ROM_BANK_LOGIC_FUNCTIONS);
            main_show_window_text(&win_txt_nli_sales, ROM_BANK_LOGIC_FUNCTIONS);
        }
        else
        {
            // Show unsuccessful message
            main_show_window_text(&win_txt_nli_no_int, ROM_BANK_LOGIC_FUNCTIONS);
        }
    }
    else if (menu_config->items[MENU_NLI_WORK_ITEM] == MENU_ITEM_INDEX_WORK_SALESMAN)
    {
        if (game_state->intelligence >= 120U)
        {
            menu_config->items[MENU_NLI_WORK_ITEM] = MENU_ITEM_INDEX_WORK_EXECUTIVE;
            modify_karma(3);
            // Select 'work' item for new job
            move_to_menu_item(1U, 3U, ROM_BANK_LOGIC_FUNCTIONS);
            main_show_window_text(&win_txt_nli_exec, ROM_BANK_LOGIC_FUNCTIONS);
        }
        else
        {
            // Show unsuccessful message
            main_show_window_text(&win_txt_nli_no_int, ROM_BANK_LOGIC_FUNCTIONS);
        }
    }
    else if (menu_config->items[MENU_NLI_WORK_ITEM] == MENU_ITEM_INDEX_WORK_EXECUTIVE)
    {
        if (game_state->intelligence >= 180U)
        {
            menu_config->items[MENU_NLI_WORK_ITEM] = MENU_ITEM_INDEX_WORK_VP;
            modify_karma(3);
            // Select 'work' item for new job
            move_to_menu_item(1U, 3U, ROM_BANK_LOGIC_FUNCTIONS);
            main_show_window_text(&win_txt_nli_vp, ROM_BANK_LOGIC_FUNCTIONS);
        }
        else
        {
            // Show unsuccessful message
            main_show_window_text(&win_txt_nli_no_int, ROM_BANK_LOGIC_FUNCTIONS);
        }
    }
    else if (menu_config->items[MENU_NLI_WORK_ITEM] == MENU_ITEM_INDEX_WORK_VP)
    {
        if (game_state->intelligence >= 250U)
        {
            menu_config->items[MENU_NLI_WORK_ITEM] = MENU_ITEM_INDEX_WORK_CEO;
            menu_config->items[MENU_NLI_PROMOTION_ITEM] = MENU_ITEM_INDEX_EMPTY;
            modify_karma(3);
            // Select 'work' item for new job
            move_to_menu_item(1U, 3U, ROM_BANK_LOGIC_FUNCTIONS);
            main_show_window_text(&win_txt_nli_ceo, ROM_BANK_LOGIC_FUNCTIONS);
        }
        else
        {
            // Show unsuccessful message
            main_show_window_text(&win_txt_nli_no_int, ROM_BANK_LOGIC_FUNCTIONS);
        }
    }
    else
    {
        // If no job available, return early
        return;
    }

    // Reload menu to cover message
    setup_building_menu(1, ROM_BANK_LOGIC_FUNCTIONS);
}
