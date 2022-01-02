/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */


#define SC_HOUSE 0x01U
#define SC_RESTAURANT 0x02U
#define SC_SHOP 0x04U
#define SC_PAWN 0x08U
#define SC_UNIVERSITY 0x10U
#define SC_NLI 0x20U

// Show/remove left-hand buildings when screen position passes this point
#define SC_HOUSE_TRANSITION_X 0x12U
#define SC_RESTAURANT_TRANSITION_Y 0x7U
#define SC_SHOP_NLI_TRANSITION_Y 0x16U
#define SC_PAWN_TRANSITION_Y 0x20U
#define SC_UNIVERSITY_TRANSITION_X 0x1DU
#define SC_NLI_TRANSITION_X_MIN 0x16U
#define SC_NLI_TRANSITION_X_MAX 0x46U


typedef struct {
    UINT8 displayed_buildings_x;
    UINT8 displayed_buildings_y;
    UBYTE displayed_sprites_x;
    UBYTE displayed_sprites_y;
} screen_state_t;
