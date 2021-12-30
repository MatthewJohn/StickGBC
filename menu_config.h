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

#define MENU_ITEM_INDEX_EMPTY 0xFFU
#define MENU_ITEM_INDEX_EXIT 0x00U
#define MENU_ITEM_INDEX_SLEEP 0x01U
#define MENU_ITEM_INDEX_MILKSHAKE 0x02U
#define MENU_ITEM_INDEX_FRIES 0x03U
#define MENU_ITEM_INDEX_WORK 0x04U
#define MENU_ITEM_INDEX_CHEESE_BURGER 0x05U
#define MENU_ITEM_INDEX_TRIPLE_BURGER 0x06U
#define MENU_ITEM_INDEX_SLUSHEE 0x07U
#define MENU_ITEM_INDEX_SMOKES 0x08U
#define MENU_ITEM_INDEX_CANDY_BAR 0x09U
#define MENU_ITEM_INDEX_CAFFEINE_PILLS 0x0AU
#define MENU_ITEM_INDEX_NACHOS 0x0BU
#define MENU_ITEM_INDEX_HAND_GUN 0x0CU
#define MENU_ITEM_INDEX_CELL_PHONE 0x0DU
#define MENU_ITEM_INDEX_KNIFE 0x0EU
#define MENU_ITEM_INDEX_ALARM_CLOCK 0x0FU

#define IS_MENU_ITEM_ENABLED(index) menu_config->items[index] != MENU_ITEM_INDEX_EMPTY

typedef struct {
    // Item is split into tile data and palette data, each with 12 tiles
    const unsigned short tiles[12];
    const unsigned short palette[12];
} menu_config_item_t;

typedef struct {
    // Menu can contain 8 items
    unsigned short items[8];
    
    unsigned int tile_offset;
} menu_config_t;

typedef struct {
    unsigned int current_item_x;
    unsigned int current_item_y;
} menu_state_t;

extern const menu_config_item_t menu_config_items[0x10U];

extern menu_config_t menu_config_house;
extern menu_config_t menu_config_restaurant;
extern menu_config_t menu_config_shop;
extern menu_config_t menu_config_pawn;
