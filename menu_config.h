/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */


#ifndef MENU_CONFIG_DEF
#define MENU_CONFIG_DEF 1

#include "gb.h"
#include "game_constants.h"
#include "game_state.h"
#include "menu_tile_index.h"

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
#define MENU_ITEM_KARMA_PALETTE 0x07U
#define MENU_ITEM_CHARM_PALETTE 0x03U
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
#define MENU_ITEM_INDEX_APPLY_FOR_JOB 0x15U
#define MENU_ITEM_INDEX_APPLY_FOR_PROMOTION 0x16U
#define MENU_ITEM_INDEX_WORK_JANITOR 0x17U
#define MENU_ITEM_INDEX_WORK_MAIL_CLERK 0x18U
#define MENU_ITEM_INDEX_WORK_SALESMAN 0x19U
#define MENU_ITEM_INDEX_WORK_EXECUTIVE 0x1AU
#define MENU_ITEM_INDEX_WORK_VP 0x1BU
#define MENU_ITEM_INDEX_WORK_CEO 0x1CU
#define MENU_ITEM_INDEX_COCAINE 0x1DU
#define MENU_ITEM_INDEX_GIVE_10 0x1EU
#define MENU_ITEM_INDEX_DRINK_BEER 0x1FU
#define MENU_ITEM_INDEX_BOTTLE_OF_BEER 0x20U
#define MENU_ITEM_INDEX_BAR_FIGHT 0x21U
#define MENU_ITEM_INDEX_PLAY_DARTS 0x22U
#define MENU_ITEM_INDEX_GIVE_BEER 0x23U
#define MENU_ITEM_INDEX_INTELLIGENCE 0x24U
#define MENU_ITEM_INDEX_STRENGTH 0x25U
#define MENU_ITEM_INDEX_CHARM 0x26U
#define MENU_ITEM_INDEX_KARMA 0x27U
#define MENU_ITEM_INDEX_INV_SMOKES 0x28U
#define MENU_ITEM_INDEX_INV_CAFFEINE_PILLS 0x29U
#define MENU_ITEM_INDEX_INV_HAND_GUN 0x2AU
#define MENU_ITEM_INDEX_INV_KNIFE 0x2BU
#define MENU_ITEM_INDEX_INV_CELLPHONE  0x2CU
#define MENU_ITEM_INDEX_INV_SKATEBOARD 0x2DU
#define MENU_ITEM_INDEX_INV_COCAINE  0x2EU
#define MENU_ITEM_INDEX_INV_BOTTLE_OF_BEER 0x2FU
#define MENU_ITEM_INDEX_SELL_GOODS 0x30U
#define MENU_ITEM_INDEX_BROOKLYN 0x31U
#define MENU_ITEM_INDEX_CHICAGO 0x32U
#define MENU_ITEM_INDEX_DETROIT 0x33U
#define MENU_ITEM_INDEX_CAMDEN 0x34U
#define MENU_ITEM_INDEX_LOS_ANGELES 0x35U
#define MENU_ITEM_INDEX_LAS_VEGAS 0x36U
#define MENU_ITEM_INDEX_BULLETS 0x37U
#define MENU_ITEM_INDEX_ROB 0x38U

// Menu item indexes
#define MENU_NLI_PROMOTION_ITEM 0x05U
#define MENU_NLI_WORK_ITEM 0x07U
#define MENU_SHOP_ROB_ITEM 0x7U
#define MENU_PAWN_BULLETS_ITEM 0x0U
#define MENU_PAWN_HAND_GUN_ITEM 0x2U

// Value for current X/Y position to disable highlighting
#define MENU_SELECTED_ITEM_DISABLED 0x8U

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

// Menu items
extern const menu_config_item_t menu_config_items[];

// Mapping for inventory item index to menu item index
extern const UINT8 inventory_menu_item_map[];

// Menu configs
extern menu_config_t menu_config_house;
extern menu_config_t menu_config_restaurant;
extern menu_config_t menu_config_shop;
extern menu_config_t menu_config_pawn;
extern menu_config_t menu_config_university;
extern menu_config_t menu_config_skater;
extern menu_config_t menu_config_nli;
extern menu_config_t menu_config_dealer;
extern menu_config_t menu_config_hobo;
extern menu_config_t menu_config_bar;
extern menu_config_t menu_config_stats;
extern menu_config_t menu_config_inventory;
extern menu_config_t menu_config_bus_station;


// Methods for menu
void set_menu_item_color(unsigned char palette);
void apply_for_job_promotion(game_state_t *game_state, menu_config_t *menu_config, menu_config_t *menu_config_restaurant);

#endif