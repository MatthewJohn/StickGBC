/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */


#include "gb.h"

typedef struct {
    // Determine which way user needs to travel
    INT8 travel_x;
    INT8 travel_y;

    unsigned short a_pressed;
    unsigned short b_pressed;
    BOOLEAN select_pressed;
    BOOLEAN start_pressed;
} joypad_state_t;

void check_user_input(joypad_state_t* joypad_state);
