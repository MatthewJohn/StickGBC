/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */


#define SC_HOUSE 0x1U
#define SC_RESTAURANT 0x2U

// Show/remove left-hand buildings when screen position passes this point
#define SC_HOUSE_TRANSITION_X 0x12U
#define SC_RESTAURANT_TRANSITION_Y 0x1CU;

typedef struct {
    UINT8 displayed_buildings;
} screen_state_t;
