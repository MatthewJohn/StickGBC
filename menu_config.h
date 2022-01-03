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

// Menu item indexes for NLI
#define MENU_NLI_PROMOTION_ITEM 0x05U
#define MENU_NLI_WORK_ITEM 0x07U

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
extern menu_config_t menu_config_nli;
extern menu_config_t menu_config_dealer;
extern menu_config_t menu_config_hobo;
extern menu_config_t menu_config_bar;


#define MENU_TILE_EX 0x04U
#define MENU_TILE_BE 0x0AU
#define MENU_TILE_BO 0x0BU
#define MENU_TILE_TT 0x0CU
#define MENU_TILE_OF 0x0DU
#define MENU_TILE_HE 0x0EU
#define MENU_TILE_G 0x0FU

#define MENU_TILE_SL 0x11U
#define MENU_TILE_E 0x1AU
#define MENU_TILE_CH 0x1EU

#define MENU_TILE_ER 0x23U
#define MENU_TILE_PL 0x25U
#define MENU_TILE_WO 0x26U
#define MENU_TILE_RK 0x27U
#define MENU_TILE_CO 0x28U
#define MENU_TILE_US 0x29U
#define MENU_TILE_CA 0x2AU
#define MENU_TILE_Y 0x2CU
#define MENU_TILE_R 0x2EU

#define MENU_TILE_SM 0x31U
#define MENU_TILE_N 0x39U
#define MENU_TILE_AR 0x3DU
#define MENU_TILE_M 0x3EU
#define MENU_TILE_CL 0x3FU

#define MENU_TILE_K 0x41U
#define MENU_TILE_TO 0x49U
#define MENU_TILE_GI 0x4BU
#define MENU_TILE_VE 0x4CU
#define MENU_TILE_AP 0x4DU
#define MENU_TILE_A 0x4EU
#define MENU_TILE_JO 0x4FU
#define MENU_TILE_B 0x50U
#define MENU_TILE_FO 0x51U
#define MENU_TILE_JA 0x52U
#define MENU_TILE_NI 0x53U
#define MENU_TILE_MA 0x54U
#define MENU_TILE_IL 0x55U
#define MENU_TILE_SA 0x56U
#define MENU_TILE_LE 0x57U
#define MENU_TILE_AN 0x58U
#define MENU_TILE_EC 0x59U
#define MENU_TILE_UT 0x5AU
#define MENU_TILE_IV 0x5BU
#define MENU_TILE_VP 0x5CU
#define MENU_TILE_O 0x5DU
#define MENU_TILE_PR 0x5EU
#define MENU_TILE_OM 0x5FU
#define MENU_TILE_OT 0x60U
#define MENU_TILE_IO 0x61U

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
#define MENU_TILE_DASH 0x7EU
