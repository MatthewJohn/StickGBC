/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */


# ifndef MENU_CONFIG_DEF
#define MENU_CONFIG_DEF 1

#include "gb.h"
#include "game_constants.h"

#define MENU_MAX_ITEMS_X 2U
#define MENU_MAX_ITEMS_Y 4U

#define MENU_ITEM_WIDTH 6U
#define MENU_ITEM_HEIGHT 2U
#define MENU_ITEM_TILE_COUNT 12U

#define MENU_ITEM_SCREEN_OFFSET_TOP 0x03U
#define MENU_ITEM_SCREEN_OFFSET_LEFT 0x03U
#define MENU_ITEM_MARGIN 0x02U

#define MENU_ITEM_NO_TILE 0x00U
#define MENU_BLANK_ITEM_ROW MENU_ITEM_NO_TILE, MENU_ITEM_NO_TILE, \
                                                                 MENU_ITEM_NO_TILE, MENU_ITEM_NO_TILE, \
                                                                 MENU_ITEM_NO_TILE, MENU_ITEM_NO_TILE
#define MENU_BLANK_ITEM {MENU_BLANK_ITEM_ROW, MENU_BLANK_ITEM_ROW}

#define MENU_ITEM_NO_PALETTE 0x00U
#define MENU_ITEM_NO_PALETTE_ROW MENU_ITEM_NO_PALETTE, MENU_ITEM_NO_PALETTE, \
                                                                             MENU_ITEM_NO_PALETTE, MENU_ITEM_NO_PALETTE, \
                                                                             MENU_ITEM_NO_PALETTE, MENU_ITEM_NO_PALETTE
#define MENU_ITEM_DEFAULT_PALETTE 0x01U
#define MENU_ITEM_SELECTED_PALETTE 0x02U
#define MENU_ITEM_COST_PALETTE 0x03U
#define MENU_ITEM_HP_PALETTE 0x04U
#define MENU_ITEM_STRENGTH_PALETTE 0x05U
#define MENU_ITEM_INTELLIGENCE_PALETTE 0x06U
#define MENU_BLANK_ITEM_PALETTE {MENU_ITEM_NO_PALETTE_ROW, MENU_ITEM_NO_PALETTE_ROW}

typedef struct {
    // Item is split into tile data and palette data, each with 12 tiles
    const unsigned short tiles[12];
    const unsigned short palette[12];
} menu_config_item_t;

typedef struct {
    // Menu can contain 8 items
    menu_config_item_t *items[8];
    
    unsigned int tile_offset;
} menu_config_t;

typedef struct {
    unsigned int current_item_x;
    unsigned int current_item_y;
} menu_state_t;


extern const menu_config_item_t menu_config_item_blank;
extern const menu_config_item_t menu_config_item_sleep;
extern const menu_config_item_t menu_config_item_milkshake;
extern const menu_config_item_t menu_config_item_fries;
extern const menu_config_item_t menu_config_item_work;
extern const menu_config_item_t menu_config_item_cheese_burger;
extern const menu_config_item_t menu_config_item_triple_burger;
extern const menu_config_item_t menu_config_item_slushee;
extern const menu_config_item_t menu_config_item_smokes;
extern const menu_config_item_t menu_config_item_candy_bar;
extern const menu_config_item_t menu_config_item_caffeine_pills;
extern const menu_config_item_t menu_config_item_nachos;
extern const menu_config_item_t menu_config_item_hand_gun;
extern const menu_config_item_t menu_config_item_cell_phone;
extern const menu_config_item_t menu_config_item_knife;
extern const menu_config_item_t menu_config_item_alarm_clock;

extern menu_config_t menu_config_house;
extern menu_config_t menu_config_restaurant;
extern menu_config_t menu_config_shop;
extern menu_config_t menu_config_pawn;
