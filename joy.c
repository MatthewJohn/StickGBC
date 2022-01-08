/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */


#pragma bank=6

#include "joy.h"

void check_user_input(joypad_state_t *joypad_state)
{
    UINT8 keys = joypad();
    joypad_state->travel_x = 0;
    joypad_state->travel_y = 0;
    joypad_state->a_pressed = 0U;
    joypad_state->b_pressed = 0U;
    joypad_state->select_pressed = 0U;
    joypad_state->start_pressed = 0U;

    // Check directional 
    if (keys & J_UP)
        joypad_state->travel_y --;
    if (keys & J_DOWN)
        joypad_state->travel_y ++;
    if (keys & J_LEFT)
        joypad_state->travel_x --;
    if (keys & J_RIGHT)
        joypad_state->travel_x ++;
    if (keys & J_A)
        joypad_state->a_pressed = 1U;
    if (keys & J_B)
        joypad_state->b_pressed = 1U;
    if (keys & J_SELECT)
        joypad_state->select_pressed = 1U;
    if (keys & J_START)
        joypad_state->start_pressed = 1U;
}
