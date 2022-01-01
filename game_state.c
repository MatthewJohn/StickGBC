/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */


#ifndef GAME_STATE_DEF
#define GAME_STATE_DEF 1

// Game state and constants for game state

#define S_HOURS_PER_DAY 24U
// 8AM
#define S_HOUR_WAKEUP_NORMAL 0x08U
#define S_HOUR_CAFFEINE_BONUS 0x04U

// Buildings
#define S_B_NO_BUILDING 0x00U
#define S_B_MAIN_MENU 0x01U
#define S_B_HOUSE 0x02U
#define S_B_RESTAURANT 0x03U
#define S_B_SHOP 0x04U
#define S_B_PAWN 0x05U
#define S_B_UNIVERSITY 0x06U
#define S_B_SKATER 0x07U


// Maximum of 99 of each item.
// This is too high for singleton items (such as alarm clock),
// but rely on the functionality to remove the item from the menu
// after purchase
#define S_MAX_INVENTORY_ITEM 99U

// Inventory items
#define S_INVENTORY_SMOKES 0x0U
#define S_INVENTORY_CAFFEINE_PILLS 0x1U
#define S_INVENTORY_HAND_GUN 0x2U
#define S_INVENTORY_KNIFE 0x3U
#define S_INVENTORY_ALARM_CLOCK 0x4U
#define S_INVENTORY_CELL_PHONE 0x5U

// Maximum intelligence/strenth
#define S_MAX_INTELLIGENCE 999U
#define S_MAX_STRENGTH 999U

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

    // Current amount of strength and intelligence
    unsigned int intelligence;
    unsigned int strength;

    // Money the user has.
    unsigned int balance;

    // Inventory items
    UINT8 inventory[6U];
} game_state_t;


// The sprite is placed into place and moved from min_location to max_location.
// Travel direction that is set to 0 is ignored, meaning that the initla
typedef struct {
    // Modulus of SYSTIME by the speed is used to determine if to move.
    UINT8 move_speed;
    // Sprite number
    UINT8 sprite_itx;
    // These are initially setup to determine initial movement.
    // The direction is inverted when max/min location is reached.
    INT8 travel_direction_x;
    INT8 travel_direction_y;
    INT8 rest_direction_x;
    INT8 rest_direction_y;
    unsigned int current_location_x;
    unsigned int current_location_y;
    unsigned int min_location_x;
    unsigned int max_location_x;
    unsigned int min_location_y;
    unsigned int max_location_y;
    UINT8 pause_period;
    UINT8 current_pause;
} ai_sprite;
