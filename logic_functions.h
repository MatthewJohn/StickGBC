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
void apply_for_job_promotion(game_state_t *game_state, menu_config_t *menu_config, menu_config_t *menu_config_restaurant);
