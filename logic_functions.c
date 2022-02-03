/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */

#pragma bank=2

#include "logic_functions.h"
#include "window_text_data.h"

typedef struct {
    UINT8 x;
    UINT8 y;
    UINT8 max_digits;
    UINT16 current_number;
    UINT16 min_value;
    UINT16 max_value;
} number_input_t;

/*
 * remove_ammo
 *
 * Remove ammo from inventory and reset shop menus/state if required
 */
void remove_ammo(UINT8 amount_to_remove)
{
    if (game_state.inventory[S_INVENTORY_AMMO] > amount_to_remove)
        game_state.inventory[S_INVENTORY_AMMO] -= amount_to_remove;
    else
    {
        game_state.inventory[S_INVENTORY_AMMO] = 0;

        // Remove 'rob' from shop
        menu_config_shop.items[MENU_SHOP_ROB_ITEM] = MENU_ITEM_INDEX_EMPTY;
    }
}

/*
 * remove_gun
 *
 * Remove gun from inventory and reset shop menus/state
 */
void remove_gun()
{
    // Remove all ammo
    remove_ammo(game_state.inventory[S_INVENTORY_AMMO]);

    // Add hand gun to pawn menu
    menu_config_pawn.items[MENU_PAWN_HAND_GUN_ITEM] = MENU_ITEM_INDEX_HAND_GUN;

    // Remove bullets from pawn menu
    menu_config_pawn.items[MENU_PAWN_BULLETS_ITEM] = MENU_ITEM_INDEX_EMPTY;
}

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
        remove_gun();

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
 * purchase_food
 *
 * If user has enough money, spend money
 * and gain HP
 */
void purchase_food(UINT8 cost, UINT8 gained_hp)
{
    // Breaking the rules using >=, but
    // only performed when buying an item
    // and currency is decimal, making very difficult
    // to do using bit shifting (and at least probably
    // less CPU intensive)
    if (HAS_MONEY(cost))
    {
        game_state.balance -= cost;

        // If new HP would exeed max HP, limit new HP to difference
        if (gained_hp >= (game_state.max_hp - game_state.hp))
            game_state.hp = game_state.max_hp;
        else
            // Otherwise, add new HP to HP
            game_state.hp += gained_hp;

        main_update_window(ROM_BANK_LOGIC_FUNCTIONS);
    }
}

/*
 * purchase_item
 *
 * Spent money and increase inventory count for item
 */
UINT8 purchase_item(unsigned int cost, UINT8 inventory_item)
{
    // Breaking the rules using >=, but
    // only performed when buying an item
    // and currency is decimal, making very difficult
    // to do using bit shifting (and at least probably
    // less CPU intensive)

    if (HAS_MONEY(cost) && game_state.inventory[inventory_item] != S_MAX_INVENTORY_ITEM)
    {
        game_state.balance -= cost;
        game_state.inventory[inventory_item] += 1U;

        main_update_window(ROM_BANK_LOGIC_FUNCTIONS);

        return 0x1U;
    }

    // If item not purchased, return 0
    return 0x0U;
}

/*
 * move_menu_to_exit
 *
 * Move current menu item to exit
 */
void move_menu_to_exit()
{
    move_to_menu_item(1U, 0U, ROM_BANK_LOGIC_FUNCTIONS);
}

/*
 * perform_robbery
 *
 * Perform robbery on shop
 */
void perform_robbery()
{
    UINT8 amount_robbed;

    if (game_state.hour > 22U)
        return;

    // Remove bullets from inventory
    remove_ammo((UINT8)(sys_time % 5U) + 5U);

    // Set time to midnight
    game_state.hour = 24U;

    // Use charm to generate random number and check that it's ver 40
    if ((sys_time % game_state.charm) > 40U)
    {
        // Add random amount up to 500
        amount_robbed = sys_time % 500U;
        game_state.balance += amount_robbed;

        // Update window
        main_update_window(ROM_BANK_LOGIC_FUNCTIONS);

        // Show amount robbed
        main_show_number(6, 5, 3, (unsigned int)amount_robbed, ROM_BANK_LOGIC_FUNCTIONS);

        // Display message
        main_show_window_text(&win_txt_rob_success, ROM_BANK_LOGIC_FUNCTIONS);
    }
    else
    {
        // Spend 5 days in jail
        game_state.days_passed += 5U;

        // Update window
        main_update_window(ROM_BANK_LOGIC_FUNCTIONS);

        // Display message
        main_show_window_text(&win_txt_rob_caught, ROM_BANK_LOGIC_FUNCTIONS);
    }

    // Reload menu tiles to clear message
    setup_building_menu(1U, ROM_BANK_LOGIC_FUNCTIONS);
    move_menu_to_exit();
}

/*
 * process_house_menu
 *
 * Handle selection of item from house menu
 */
void process_house_menu()
{
     if (menu_state.current_item_y == 3U)
    {
        // Set intiial wakeup time
        game_state.hour = S_HOUR_WAKEUP_NORMAL;

        // Check if user has caffeine
        if (game_state.inventory[S_INVENTORY_CAFFEINE_PILLS])
        {
            game_state.inventory[S_INVENTORY_CAFFEINE_PILLS] -= 1U;
            game_state.hour -= S_HOUR_CAFFEINE_TIME_GAIN;
        }

        // Check if alarm clock is owned
        if (game_state.inventory[S_INVENTORY_ALARM_CLOCK])
        {
            game_state.hour -= S_HOUR_ALARM_CLOCK_TIME_GAIN;
        }
        game_state.days_passed ++;
        check_end_game();

        DISPLAY_OFF;

        // 'Purchase food' to increase HP by 20
        purchase_food(0U, 20U);

        main_update_window(ROM_BANK_LOGIC_FUNCTIONS);

        // Wait for 1 second 1 second
        delay(DELAY_SLEEP);
        DISPLAY_ON;
    }
}

/*
 * process_restaurant_menu
 *
 * Handle selection of item from restaurant menu
 */
void process_restaurant_menu()
{
    if (menu_state.current_item_x == 0U)
    {
        if (menu_state.current_item_y == 0U)  // Milkshake
        {
            purchase_food(8U, 12U);
        }
        else if (menu_state.current_item_y == 1U)  // Fries
        {
            purchase_food(12U, 20U);
        }
        else if (menu_state.current_item_y == 2U)  // Cheeseburger
        {
            purchase_food(25U, 40U);
        }
        else if (menu_state.current_item_y == 3U)  // Triple Burger
        {
            purchase_food(50U, 80U);
        }
    }
    else  // x row 1
    {
        if (menu_state.current_item_y == 1U)  // Work
        {
            main_do_work(6U, 6U, ROM_BANK_LOGIC_FUNCTIONS);
        }
    }
}

/*
 * process_shop_menu
 *
 * Handle selection of item from shop menu
 */
void process_shop_menu()
{
    if (menu_state.current_item_x == 0U)
    {
        if (menu_state.current_item_y == 1U)  // Slushee
        {
            purchase_food(1U, 1U);
        }
        else if (menu_state.current_item_y == 2U)  // Candy Bar
        {
            purchase_food(2U, 3U);
        }
        else if (menu_state.current_item_y == 3U)  // Nachos
        {
            purchase_food(4U, 7U);
        }
    }
    else  // x row 1
    {
        if (menu_state.current_item_y == 1U)  // Smokes
        {
            purchase_item(10U, S_INVENTORY_SMOKES);
        }
        else if (menu_state.current_item_y == 2U)  // Caffeine Pills
        {
            purchase_item(45U, S_INVENTORY_CAFFEINE_PILLS);
        }
        else if (menu_state.current_item_y == 3U)  // Rob
        {
            perform_robbery();
        }
    }
}

void process_pawn_menu()
{
    if (menu_state.current_item_x == 0U)
    {
        if (menu_state.current_item_y == 0U)  // Bullets
        {
            // Attempt to purchase item
            purchase_item(10U, S_INVENTORY_AMMO);

            // Add 'rob' to shop menu
            menu_config_shop.items[MENU_SHOP_ROB_ITEM] = MENU_ITEM_INDEX_ROB;
        }
        else if (menu_state.current_item_y == 1U)  // Handgun
        {
            // Attempt to purchase item
            if (purchase_item(400U, S_INVENTORY_HAND_GUN))
            {
                // Remove from menu, if successful and reload menu tiles
                menu_config->items[MENU_PAWN_HAND_GUN_ITEM] = MENU_ITEM_INDEX_EMPTY;

                // Add bullets to menu
                menu_config->items[MENU_PAWN_BULLETS_ITEM] = MENU_ITEM_INDEX_BULLETS;

                // Reload menu
                load_menu_tiles(ROM_BANK_LOGIC_FUNCTIONS);
                move_menu_to_exit();
            }
        }
        else if (menu_state.current_item_y == 2U)  // Knife
        {
            if (purchase_item(100U, S_INVENTORY_KNIFE))
            {
                menu_config->items[4U] = MENU_ITEM_INDEX_EMPTY;
                load_menu_tiles(ROM_BANK_LOGIC_FUNCTIONS);
                move_menu_to_exit();
            }
        }
        else if (menu_state.current_item_y == 3U)  // Alarm Clock
        {
            if (purchase_item(200U, S_INVENTORY_ALARM_CLOCK))
            {
                menu_config->items[6U] = MENU_ITEM_INDEX_EMPTY;
                load_menu_tiles(ROM_BANK_LOGIC_FUNCTIONS);
                move_menu_to_exit();
            }
        }
    }
    else  // x row 1
    {
        if (menu_state.current_item_y == 1U)  // Cellphone
        {
            if (purchase_item(200U, S_INVENTORY_CELL_PHONE))
            {
                menu_config->items[3U] = MENU_ITEM_INDEX_EMPTY;
                load_menu_tiles(ROM_BANK_LOGIC_FUNCTIONS);
                move_menu_to_exit();
            }
        }
    }
}


void process_dealer_menu()
{
    if (menu_state.current_item_x == 0U && menu_state.current_item_y == 2U)
        purchase_item(400U, S_INVENTORY_COCAINE);
}

void process_bar_menu()
{
    if (menu_state.current_item_x == 0U && menu_state.current_item_y == 1U)
    {
        increase_charm(20U, 2U, 2U, ROM_BANK_LOGIC_FUNCTIONS);
    }
    else if (menu_state.current_item_x == 1U && menu_state.current_item_y == 1U)
    {
        purchase_item(30U, S_INVENTORY_BOTTLE_OF_BEER);
        // Enable give bottle of beer in hobo menu
        menu_config_hobo.items[5U] = MENU_ITEM_INDEX_GIVE_BEER;
    }
}

void process_hobo_menu()
{
    UINT8 rnd;

    if (menu_state.current_item_x == 0U && menu_state.current_item_y == 2U)
    {
        if (HAS_MONEY(10U))
        {
            if (game_state.hobo_given_money == 0U)
            {
                if (increase_charm(10U, 1U, 6U, ROM_BANK_LOGIC_FUNCTIONS))
                {
                    // Mark as having visited hobo, so he doesn't give us charm again.
                    game_state.hobo_given_money = 1U;

                    // Give 2 karma
                    modify_karma(2);
                }
            }
            else  // Paying money and not getting charm
            {
                game_state.balance -= 10U;
                main_update_window(ROM_BANK_LOGIC_FUNCTIONS);

                // Give 2 karma
                modify_karma(2);
            }

            rnd = sys_time % 3;
            if (rnd == 0U)
                main_show_window_text(&win_txt_hobo_give_1, ROM_BANK_LOGIC_FUNCTIONS);
            else if (rnd == 1U)
                main_show_window_text(&win_txt_hobo_give_2, ROM_BANK_LOGIC_FUNCTIONS);
            else
                main_show_window_text(&win_txt_hobo_give_3, ROM_BANK_LOGIC_FUNCTIONS);

            // Reload building menu to clear any text
            setup_building_menu(1U, ROM_BANK_LOGIC_FUNCTIONS);
        }
    }
    else if (menu_state.current_item_x == 1U && menu_state.current_item_y == 2U)
    {
        // Give bottle of beer
        if (game_state.inventory[S_INVENTORY_BOTTLE_OF_BEER] && DAY_TIME_REMAINING >= 1U)
        {
            if (game_state.hobo_given_beer == 0U)
            {
                increase_charm(0U, 1U, 8U, ROM_BANK_LOGIC_FUNCTIONS);
                game_state.hobo_given_beer = 1U;
            }
            else
            {
                game_state.hour += 1U;
            }
            game_state.inventory[S_INVENTORY_BOTTLE_OF_BEER] -= 1U;

            rnd = sys_time % 3;
            if (rnd == 0U)
                main_show_window_text(&win_txt_hobo_booze_1, ROM_BANK_LOGIC_FUNCTIONS);
            else if (rnd == 1U)
                main_show_window_text(&win_txt_hobo_booze_2, ROM_BANK_LOGIC_FUNCTIONS);
            else
                main_show_window_text(&win_txt_hobo_booze_3, ROM_BANK_LOGIC_FUNCTIONS);
        }
    }
}

/*
 * number_entry
 *
 * Allow user to select a number using directional keys
 */
void number_entry(number_input_t *number_input)
{
    UINT16 start_hold_time = 0;
    INT16 new_num;
    UINT16 amount_to_change;

    game_state.last_movement_time = sys_time;

    // Show number on-screen
    main_show_number(
        number_input->x, number_input->y,
        number_input->max_digits,
        (unsigned int)number_input->current_number,
        ROM_BANK_LOGIC_FUNCTIONS
    );

    // Wait for user to release initial A/B presses
    while (joypad_state.a_pressed == 1U || joypad_state.b_pressed == 1U)
    {
        main_check_joy(ROM_BANK_LOGIC_FUNCTIONS);
        wait_vbl_done();
    }

    // Reset joypad state
    joypad_state.a_pressed = 0U;
    joypad_state.b_pressed = 0U;

    // Allow user to use directional keys until A or be is pressed
    while (joypad_state.a_pressed == 0U && joypad_state.b_pressed == 0U)
    {
        main_check_joy(ROM_BANK_LOGIC_FUNCTIONS);

        if (joypad_state.travel_y != 0)
        {
            // If starting to hold direction, set start_hold_time to now
            if (start_hold_time == 0)
                start_hold_time = sys_time;

            // Otherwise, if already holding, check if enough time has passed since
            // last number change
            else if ((sys_time - game_state.last_movement_time) < 0x07)
                continue;

            game_state.last_movement_time = sys_time;

            // Determine the amount the value will change, based on how long user
            // has been holding button
            new_num = number_input->current_number;
            amount_to_change = (((INT16)((UINT16)(sys_time >> 3) - (UINT16)(start_hold_time >> 3)) + 1) * joypad_state.travel_y);
            new_num -= amount_to_change;

            // Rough hack to check if underflow happens. See commit history for more info.
            if (new_num < number_input->min_value ||
                    (joypad_state.travel_y == 1 && new_num > number_input->max_value))
                new_num = number_input->min_value;
            if (joypad_state.travel_y == -1 && new_num > number_input->max_value)
                new_num = number_input->max_value;

            number_input->current_number = new_num;

            // Update displayed digits
            main_show_number(
                number_input->x, number_input->y,
                number_input->max_digits,
                (unsigned int)number_input->current_number,
                ROM_BANK_LOGIC_FUNCTIONS
            );
        }
        // Otherwise reset
        else
        {
            start_hold_time = 0;
        }

        wait_vbl_done();
    }
}

/*
 * show_bank_withdraw
 *
 * Load menu to allow user to withdraw money
 */
void show_bank_withdraw()
{
    UBYTE tile_data[4];
    number_input_t number_input = {
        0x07U, 0x0DU, 6, 0U, 0U, game_state.bank_balance
    };

    // Display 'Amount: ' on screen
    main_set_bkg_data(0x2AU, 3, &(screen_state.background_tiles[0x2A << 4]), ROM_BANK_BUILDING_MENU, ROM_BANK_LOGIC_FUNCTIONS);
    tile_data[0] = 0x2A;
    tile_data[1] = 0x2B;
    tile_data[2] = 0x2C;
    tile_data[3] = 0x63;
    set_bkg_tiles(0x03U, 0x0DU, 4U, 1U,  &tile_data);

    number_entry(&number_input);

    if (joypad_state.a_pressed)
    {
        game_state.bank_balance -= number_input.current_number;
        game_state.balance += number_input.current_number;
    }

    // Reload original menu
    game_state.sub_menu = S_M_NO_SUBMENU;
    main_update_window(ROM_BANK_LOGIC_FUNCTIONS);
    setup_building_menu(2U, ROM_BANK_LOGIC_FUNCTIONS);
}

/*
 * show_bank_deposit
 *
 * Load menu to allow user to deposit money
 */
void show_bank_deposit()
{
    UBYTE tile_data[4];
    number_input_t number_input = {
        0x07U, 0x0DU, 6, 0U, 0U, game_state.balance
    };

    // Display 'Amount: ' on screen
    main_set_bkg_data(0x2AU, 3, &(screen_state.background_tiles[0x2A << 4]), ROM_BANK_BUILDING_MENU, ROM_BANK_LOGIC_FUNCTIONS);
    tile_data[0] = 0x2A;
    tile_data[1] = 0x2B;
    tile_data[2] = 0x2C;
    tile_data[3] = 0x63;
    set_bkg_tiles(0x03U, 0x0DU, 4U, 1U,  &tile_data);

    number_entry(&number_input);

    if (joypad_state.a_pressed)
    {
        game_state.balance -= number_input.current_number;
        game_state.bank_balance += number_input.current_number;
    }

    // Reload original menu
    game_state.sub_menu = S_M_NO_SUBMENU;
    main_update_window(ROM_BANK_LOGIC_FUNCTIONS);
    setup_building_menu(2U, ROM_BANK_LOGIC_FUNCTIONS);
}

/*
 * show_bank_loan
 *
 * Load menu to allow user to deposit money
 */
void show_bank_loan()
{
    UBYTE tile_data[4];
    // Setup values for getting a loan, which has a max of 1000
    number_input_t number_input = {
        0x07U, 0x0DU, 6, 0U, 0U, 1000U
    };

    // If currently have a loan, make the lower of either balance or loan amount
    if (game_state.loan != 0)
    {
        if (game_state.balance < (UINT16)game_state.loan)
            number_input.max_value = game_state.balance;
        else
            number_input.max_value = game_state.loan;

        // Set current amount to highest amount to pay back
        number_input.current_number = number_input.max_value;
    }

    // Display 'Amount: ' on screen
    main_set_bkg_data(0x2AU, 3, &(screen_state.background_tiles[0x2A << 4]), ROM_BANK_BUILDING_MENU, ROM_BANK_LOGIC_FUNCTIONS);
    tile_data[0] = 0x2A;
    tile_data[1] = 0x2B;
    tile_data[2] = 0x2C;
    tile_data[3] = 0x63;
    set_bkg_tiles(0x03U, 0x0DU, 4U, 1U,  &tile_data);

    number_entry(&number_input);

    if (joypad_state.a_pressed)
    {
        // Repay loan
        if (game_state.loan != 0)
        {
            game_state.balance -= number_input.current_number;
            game_state.loan -= number_input.current_number;
        }
        else
        {
            // Get loan
            game_state.balance += number_input.current_number;
            game_state.loan += number_input.current_number;
            game_state.loan_days = 25;
        }

        // Update menu item based on whether
        // there is now a loan
        if (game_state.loan == 0)
            menu_config_bank.items[5] = MENU_ITEM_INDEX_GET_LOAN;
        else
            menu_config_bank.items[5] = MENU_ITEM_INDEX_REPAY_LOAN;
    }

    // Reload original menu
    game_state.sub_menu = S_M_NO_SUBMENU;
    main_update_window(ROM_BANK_LOGIC_FUNCTIONS);
    setup_building_menu(2U, ROM_BANK_LOGIC_FUNCTIONS);
}

