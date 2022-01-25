/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */


#include "gb.h"

#ifndef GAME_STATE_DEF
#define GAME_STATE_DEF 1

// Game state and constants for game state

#define S_HOURS_PER_DAY 24U
// 8AM
#define S_HOUR_WAKEUP_NORMAL 0x08U
#define S_HOUR_CAFFEINE_TIME_GAIN 0x04U
#define S_HOUR_ALARM_CLOCK_TIME_GAIN 0x04U

#define S_INITIAL_BASE_HP 0xFU

// Buildings
#define S_B_NO_BUILDING 0x00U
#define S_B_MAIN_MENU 0x01U
#define S_B_HOUSE 0x02U
#define S_B_RESTAURANT 0x03U
#define S_B_SHOP 0x04U
#define S_B_PAWN 0x05U
#define S_B_UNIVERSITY 0x06U
#define S_B_SKATER 0x07U
#define S_B_NLI 0x08U
#define S_B_DEALER 0x09U
#define S_B_HOBO 0x0AU
#define S_B_BAR 0x0BU
#define S_B_STATS 0x0CU
#define S_B_INVENTORY 0x0DU
#define S_B_BUS_STATION 0x0E


// Maximum of 99 of each item.
// This is too high for singleton items (such as alarm clock),
// but rely on the functionality to remove the item from the menu
// after purchase
#define S_MAX_INVENTORY_ITEM 99U
#define S_INVENTORY_ITEM_COUNT 0xAU

// Inventory items array index
#define S_INVENTORY_SMOKES 0x0U
#define S_INVENTORY_CAFFEINE_PILLS 0x1U
#define S_INVENTORY_HAND_GUN 0x2U
#define S_INVENTORY_KNIFE 0x3U
#define S_INVENTORY_ALARM_CLOCK 0x4U
#define S_INVENTORY_CELL_PHONE 0x5U
#define S_INVENTORY_SKATEBOARD 0x6U
#define S_INVENTORY_COCAINE 0x7U
#define S_INVENTORY_BOTTLE_OF_BEER 0x8U
#define S_INVENTORY_AMMO 0x9U

// Maximum intelligence/strenth
#define S_MAX_INTELLIGENCE 999U
#define S_MAX_STRENGTH 999U
#define S_MAX_CHARM 999U

typedef struct {
    // Current building
    UINT8 current_building;
    // In-game days passed. Might need to be int (not required for limited game plays).
    unsigned int days_passed;

    // Current hour of day (out of 12).
    UINT8 hour;

    // Max HP the user can have
    UINT8 max_hp;

    // Current amount of HP the user has
    UINT8 hp;

    // Current amount of strength, intelligence and charm
    unsigned int intelligence;
    unsigned int strength;
    unsigned int charm;
    INT8 karma;

    // Money the user has.
    unsigned int balance;

    // Inventory items
    UINT8 inventory[S_INVENTORY_ITEM_COUNT];

    // This is used to hold the systime of the last movement.
    // In building menu, this is used to hold the systime of the
    // last item purchase, which stops accidental double purchsing
    unsigned int last_movement_time;

    // Location of user in world.
    // This is not the sprites position on the screen
    unsigned int user_pos_x;
    unsigned int user_pos_y;
    // Location of user in world in tiles
    unsigned int user_pos_tiles_x;
    unsigned int user_pos_tiles_y;

    BOOLEAN hobo_given_money;
    BOOLEAN hobo_given_beer;

    BOOLEAN skater_intro_shown;
    BOOLEAN dealer_intro_shown;
    BOOLEAN hobo_intro_shown;
    BOOLEAN shop_intro_shown;
    BOOLEAN pawn_intro_shown;
} game_state_t;

// The sprite is placed into place and moved from min_location to max_location.
// Travel direction that is set to 0 is ignored, meaning that the initla
typedef struct {
    // Modulus of SYSTIME by the speed is used to determine if to move.
    UINT8 move_speed;
    // Sprite number
    UINT8 sprite_index;
    // displayed_sprites_x/y bit
    UINT8 sprite_display_bit;
    // Sprite color palette
    UINT8 color_palette;

    // Number of sprites to use in X/Y
    UINT8 sprite_count_x;
    UINT8 sprite_count_y;

    // Initial index for the sprite tile.
    // For two-by-two, the back tiles use
    // sprite_tile + 3
    UINT8 sprite_tile;

    // Sprite tile count - number of r
    // These are initially setup to determine initial movement.
    // The direction is inverted when max/min location is reached.
    INT8 travel_direction_x;
    INT8 travel_direction_y;
    INT8 rest_direction_x;
    INT8 rest_direction_y;
    UINT16 current_location_x;
    UINT16 current_location_y;
    UINT16 min_location_x;
    UINT16 max_location_x;
    UINT16 min_location_y;
    UINT16 max_location_y;
    UINT8 pause_period;
    UINT8 current_pause;
    BOOLEAN already_offscreen;
} ai_sprite;

// Items hidden from inventory menu
#define HIDDEN_ITEM_COUNT 1U
extern const UINT8 hidden_inventory_items[];

#endif
