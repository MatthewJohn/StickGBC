/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */


#include "gb.h"
#include "game_state.h"
#include "main.h"

// Functions for game logic
void bus_sell_goods(menu_state_t *menu_state, game_state_t *game_state);
void process_house_menu();
void process_restaurant_menu();
void process_shop_menu();
void process_pawn_menu();
void process_dealer_menu();
void process_bar_menu();
void process_hobo_menu();
void process_bank_menu();
void show_bank_withdraw();
void show_bank_deposit();
void show_bank_loan();
void process_skater_menu(UINT8 rnd);
void check_building_enter();