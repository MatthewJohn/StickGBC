/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */


#include "game_state.c"
#include "screen_state.c"

void set_sprite_direction(UINT8 sprite_index, UINT8 sprite_tileset_index, UINT8 color_palette, INT8 direction_x, INT8 direction_y);
void move_ai_sprite(screen_state_t* screen_state, ai_sprite* sprite_to_move);
