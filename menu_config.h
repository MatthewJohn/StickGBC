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

#define MENU_ITEM_INDEX_EMPTY 0x00U
#define MENU_ITEM_INDEX_EXIT 0x01U
#define MENU_ITEM_INDEX_SLEEP 0x02U
#define MENU_ITEM_INDEX_MILKSHAKE 0x03U
#define MENU_ITEM_INDEX_FRIES 0x04U
#define MENU_ITEM_INDEX_WORK 0x05U
#define MENU_ITEM_INDEX_CHEESE_BURGER 0x06U
#define MENU_ITEM_INDEX_TRIPLE_BURGER 0x07U
#define MENU_ITEM_INDEX_SLUSHEE 0x08U
#define MENU_ITEM_INDEX_SMOKES 0x09U
#define MENU_ITEM_INDEX_CANDY_BAR 0x0AU
#define MENU_ITEM_INDEX_CAFFEINE_PILLS 0x0BU
#define MENU_ITEM_INDEX_NACHOS 0x0CU
#define MENU_ITEM_INDEX_HAND_GUN 0x0DU
#define MENU_ITEM_INDEX_CELL_PHONE 0x0EU
#define MENU_ITEM_INDEX_KNIFE 0x0FU
#define MENU_ITEM_INDEX_ALARM_CLOCK 0x10U
#define MENU_ITEM_INDEX_STUDY 0x11U
#define MENU_ITEM_INDEX_GYM 0x12U
#define MENU_ITEM_INDEX_CLASS 0x13U
#define MENU_ITEM_INDEX_GIVE_SMOKES 0x14U

#define IS_MENU_ITEM_ENABLED(index) (menu_config->items[index] != MENU_ITEM_INDEX_EMPTY)

typedef struct {
    // Item is split into tile data and palette data, each with 12 tiles
    const unsigned short tiles[12];
    const unsigned short palette[12];
} menu_config_item_t;

typedef struct {
    // Menu can contain 8 items
    unsigned short items[8];
} menu_config_t;

typedef struct {
    unsigned short current_item_x;
    unsigned short current_item_y;
} menu_state_t;

extern const menu_config_item_t menu_config_items[];

extern menu_config_t menu_config_house;
extern menu_config_t menu_config_restaurant;
extern menu_config_t menu_config_shop;
extern menu_config_t menu_config_pawn;
extern menu_config_t menu_config_university;
extern menu_config_t menu_config_skater;

#define MENU_TILE_CLOCK 0x62U
#define MENU_TILE_COLON 0x63U
#define MENU_TILE_0 0x64U
#define MENU_TILE_1 0x65U
#define MENU_TILE_2 0x66U
#define MENU_TILE_3 0x67U
#define MENU_TILE_4 0x68U
#define MENU_TILE_5 0x69U
#define MENU_TILE_6 0x6AU
#define MENU_TILE_7 0x6BU
#define MENU_TILE_8 0x6CU
#define MENU_TILE_9 0x6DU
#define MENU_TILE_DOLLAR 0x6EU
#define MENU_TILE_HP 0x6FU
#define MENU_TILE_PER_HOUR 0x70U
#define MENU_TILE_DA 0x71U
#define MENU_TILE_YS 0x72U
#define MENU_TILE_SLASH 0x73U
#define MENU_TILE_IN 0x74U
#define MENU_TILE_TE 0x75U
#define MENU_TILE_LL 0x76U
#define MENU_TILE_IG 0x77U
#define MENU_TILE_EN 0x78U
#define MENU_TILE_CE 0x79U
#define MENU_TILE_ST 0x7AU
#define MENU_TILE_RE 0x7BU
#define MENU_TILE_NG 0x7CU
#define MENU_TILE_TH 0x7DU
