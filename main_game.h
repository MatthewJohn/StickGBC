/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */


#include "gb.h"
#include "game_state.h"
#include "screen_state.c"

// Functions to aid loading main map
void load_house();
void load_restaurant();
void load_shop();
void load_pawn();
void load_university();
void load_nli();
void load_bar();
void load_building_tile_data(screen_state_t *screen_state, ai_sprite *house_car_sprite);
void load_buildings_x_left(screen_state_t *screen_state, ai_sprite *skater_sprite, ai_sprite *dealer_sprite, ai_sprite *house_car_sprite);
void load_buildings_x_right(screen_state_t *screen_state, ai_sprite *skater_sprite, ai_sprite *dealer_sprite, ai_sprite *house_car_sprite);
void load_buildings_y_up(screen_state_t *screen_state, ai_sprite *skater_sprite, ai_sprite *dealer_sprite, ai_sprite *house_car_sprite);
void load_buildings_y_down(screen_state_t *screen_state, ai_sprite *skater_sprite, ai_sprite *dealer_sprite, ai_sprite *house_car_sprite);
