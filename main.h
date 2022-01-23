/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */


#ifndef MAIN_DEF
#define MAIN_DEF

#include "screen_state.c"
#include "game_state.h"
#include "joy.h"
#include "menu_config.h"

#define ROM_BANK_DEFAULT 1
#define ROM_BANK_RESET SWITCH_ROM_MBC5(ROM_BANK_DEFAULT)
#define ROM_BANK_LOGIC_FUNCTIONS 2
#define ROM_BANK_LOGIC_FUNCTIONS_SWITCH SWITCH_ROM_MBC5(ROM_BANK_LOGIC_FUNCTIONS)
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
#define ROM_BANK_WINDOW_TEXT 8
#define ROM_BANK_WINDOW_TEXT_SWITCH SWITCH_ROM_MBC5(ROM_BANK_WINDOW_TEXT)

#define DAY_TIME_REMAINING (S_HOURS_PER_DAY - game_state.hour)
#define HAS_MONEY(cost) (game_state.balance + 1U) > cost
#define HAS_MONEY_P(cost) (game_state->balance + 1U) > cost

void main_check_joy(unsigned int return_bank);
void set_background_tiles(unsigned int tile_data_bank, unsigned int return_bank);
void main_show_window_text(UINT8 *text, unsigned int return_bank);

extern screen_state_t screen_state;
extern joypad_state_t joypad_state;
extern game_state_t game_state;
extern menu_config_t *menu_config;
extern menu_state_t menu_state;

extern UBYTE tile_data[];
extern UWORD word_data[4];
extern UWORD scratch_palette_data[4][4];

extern unsigned int itx_x;
extern unsigned int itx_y;
extern unsigned int itx;

#endif