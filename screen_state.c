/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */


#ifndef SCREEN_STATE_DEF
#define SCREEN_STATE_DEF

// displayed_buildings
#define SC_HOUSE 0x01U
#define SC_RESTAURANT 0x02U
#define SC_SHOP 0x04U
#define SC_PAWN 0x08U
#define SC_UNIVERSITY 0x10U
#define SC_NLI 0x20U
#define SC_BAR 0x40U
#define SC_BUS 0x80U
// displayed_buildings_2
#define SC_BANK 0x01U
#define SC_APPLIANCE_STORE 0x02U

// Show/remove left-hand buildings when screen position passes this point
#define SC_HOUSE_TRANSITION_X 0x12U
#define SC_RESTAURANT_TRANSITION_Y_MIN 0x7U
#define SC_SHOP_NLI_TRANSITION_Y 0x16U
#define SC_RESTAURANT_PAWN_UNIVERSITY_TRANSITION_Y 0x20U
#define SC_RESTAURANT_UNIVERSITY_TRANSITION_X 0x1DU
#define SC_NLI_BANK_TRANSITION_X_MIN 0x16U
#define SC_NLI_BANK_TRANSITION_X_MAX 0x46U
#define SC_BAR_TRANSITION_Y 0xFU
#define SC_BAR_TRANSITION_X_MIN 0xDU
#define SC_BAR_TRANSITION_X_MAX 0x1EU
#define SC_BUS_TRANSITION_X 0x1EU  // 0x30 - SCREEN_WIDTH_TILES (with a bit of jigging)
#define SC_BUS_TRANSITION_Y_MIN 0x11U
#define SC_BANK_TRANSITION_Y_MAX 0x0CU
#define SC_APPLIANCE_STORE_TRANSITION_X 0x13U
#define SC_APPLIANCE_STORE_TRANSITION_Y 0x09U

#define SC_AI_SPRITE_COUNT 0x04U

typedef struct {
    UINT8 displayed_buildings_x;
    UINT8 displayed_buildings_y;
    UINT8 displayed_buildings_2_x;
    UINT8 displayed_buildings_2_y;
    BOOLEAN displayed_sprites_x[SC_AI_SPRITE_COUNT];
    BOOLEAN displayed_sprites_y[SC_AI_SPRITE_COUNT];

    // Location of screen compared to map
    unsigned int screen_location_x;
    unsigned int screen_location_y;
    // These are pre-calculated bit shifts of screen_location.
    // DO NOT manually change outside of position updating method.
    // This is the current user position in tiles.
    unsigned int screen_location_x_tiles;
    unsigned int screen_location_y_tiles;
    // These are pre-calculated ANDs of screen_location
    // DO NOT  manually change outside of position updating method.
    // This is the current pixel location of user within current tile.
    unsigned int screen_location_x_tilepixel;
    unsigned int screen_location_y_tilepixel;

    // Globals used when redrawing map
    unsigned char *background_tile_map;
    unsigned char *background_tiles;
    unsigned char *background_color_palette;
    unsigned int background_width;
    unsigned short draw_offset_x;
    unsigned short draw_offset_y;
    unsigned short draw_max_x;
    unsigned short draw_max_y;
    // Whether screen has been moved this iteration
    BOOLEAN screen_has_moved;
} screen_state_t;

#endif
