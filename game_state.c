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

// Buildings
#define S_B_NO_BUILDING 0x00U
#define S_B_MAIN_MENU 0x01U
#define S_B_HOUSE 0x02U
#define S_B_RESTAURANT 0x03U
#define S_B_SHOP 0x04U

// Maximum of 99 of each item
#define S_MAX_INVENTORY_ITEM 99U

// Inventory items
#define S_INVENTORY_SMOKES 0x0U
#define S_INVENTORY_CAFFEINE_PILLS 0x1U

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
    
    // Money the user has.
    unsigned int balance;

    // Inventory items
    UINT8 inventory[2];
} game_state_t;
