/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */


#include "joy.h"
#include "screen_state.c"

#ifndef BAR_FIGHT_DEF
#define BAR_FIGHT_DEF

void enter_bar_fight();

typedef struct {
    UINT8 selected_menu_item_x;
    UINT8 selected_menu_item_y;
    BOOLEAN in_game;
    UINT16 enemy_max_hp;
    UINT16 enemy_hp;
    UINT16 attack_points;
} bar_fight_state_t;

#endif