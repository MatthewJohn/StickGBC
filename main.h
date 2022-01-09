/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */


#ifndef MAIN_DEF
#define MAIN_DEF

#include "screen_state.c"

#define ROM_BANK_RESET SWITCH_ROM_MBC5(1)
#define ROM_BANK_TILE_DATA 5
#define ROM_BANK_TILE_DATA_SWITCH SWITCH_ROM_MBC5(ROM_BANK_TILE_DATA)
#define ROM_BANK_BUILDING_MENU 3
#define ROM_BANK_BUILDING_MENU_SWITCH SWITCH_ROM_MBC5(ROM_BANK_BUILDING_MENU)
#define ROM_BANK_SPRITE 4
#define ROM_BANK_SPRITE_SWITCH SWITCH_ROM_MBC5(ROM_BANK_SPRITE)
#define ROM_BANK_MENU_CONFIG 6
#define ROM_BANK_MENU_CONFIG_SWITCH SWITCH_ROM_MBC5(ROM_BANK_MENU_CONFIG)
#define ROM_BANK_JOY_CONFIG 6
#define ROM_BANK_JOY_CONFIG_SWITCH SWITCH_ROM_MBC5(ROM_BANK_JOY_CONFIG)
#define ROM_BANK_OPENING_SCREEN 7
#define ROM_BANK_OPENING_SCREEN_SWITCH SWITCH_ROM_MBC5(ROM_BANK_OPENING_SCREEN)
#define DAY_TIME_REMAINING (S_HOURS_PER_DAY - game_state.hour)
#define HAS_MONEY(cost) (game_state.balance + 1U) > cost

void main_check_joy();
void set_background_tiles(unsigned int tile_data_bank, unsigned int return_bank);

#endif