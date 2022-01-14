/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */


#include "game_state.h"
#include "screen_state.c"

void set_sprite_direction(ai_sprite *sprite);
void move_ai_sprite(screen_state_t* screen_state, ai_sprite* sprite_to_move);
void setup_sprites(ai_sprite *player_sprite, ai_sprite *skater_sprite, ai_sprite *dealer_sprite, ai_sprite *house_car_sprite);
