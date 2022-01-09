/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */


# ifndef MENU_CONFIG_DEF
#define MENU_CONFIG_DEF 1

#include "gb.h"
#include "game_constants.h"
#include "game_state.h"

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

// Menu item indexes for NLI
#define MENU_NLI_PROMOTION_ITEM 0x05U
#define MENU_NLI_WORK_ITEM 0x07U

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


// Methods for menu
void set_menu_item_color(menu_state_t *menu_state, menu_config_t *menu_config, unsigned char palette);

// Constants for menu tiles
// 0 Background
#define MENU_TILE_BACKGROUND 0x0
// 4 Ex
#define MENU_TILE_EX 0x4
// 5 it
#define MENU_TILE_IT 0x5
// 6 D
#define MENU_TILE_D 0x6
// 7 AY
#define MENU_TILE_AY 0x7
// 8 RT
#define MENU_TILE_RT 0x8
// 9 FI
#define MENU_TILE_FI 0x9
// 10 BE
#define MENU_TILE_BE 0xa
// 11 BO
#define MENU_TILE_BO 0xb
// 12 TT
#define MENU_TILE_TT 0xc
// 13 OF
#define MENU_TILE_OF 0xd
// 14 HE
#define MENU_TILE_HE 0xe
// 15 G
#define MENU_TILE_G 0xf
// 16 GH
#define MENU_TILE_GH 0x10
// 17 SL
#define MENU_TILE_SL 0x11
// 19 P
#define MENU_TILE_P 0x13
// 20 KA
#define MENU_TILE_KA 0x14
// 21 RM
#define MENU_TILE_RM 0x15
// 22 MI
#define MENU_TILE_MI 0x16
// 23 LK
#define MENU_TILE_LK 0x17
// 24 SH
#define MENU_TILE_SH 0x18
// 25 AK
#define MENU_TILE_AK 0x19
// 26 E
#define MENU_TILE_E 0x1a
// 27 FR
#define MENU_TILE_FR 0x1b
// 28 IE
#define MENU_TILE_IE 0x1c
// 29 S
#define MENU_TILE_S 0x1d
// 30 CH
#define MENU_TILE_CH 0x1e
// 31 EE
#define MENU_TILE_EE 0x1f
// 32 SE
#define MENU_TILE_SE 0x20
// 33 BU
#define MENU_TILE_BU 0x21
// 34 RG
#define MENU_TILE_RG 0x22
// 35 ER
#define MENU_TILE_ER 0x23
// 36 TR'
#define MENU_TILE_TR_APOS 0x24
// 37 PL
#define MENU_TILE_PL 0x25
// 38 WO
#define MENU_TILE_WO 0x26
// 39 RK
#define MENU_TILE_RK 0x27
// 40 CO
#define MENU_TILE_CO 0x28
// 41 US
#define MENU_TILE_US 0x29
// 42 CA
#define MENU_TILE_CA 0x2a
// 43 ND
#define MENU_TILE_ND 0x2b
// 44 Y
#define MENU_TILE_Y 0x2c
// 45 BA
#define MENU_TILE_BA 0x2d
// 46 R
#define MENU_TILE_R 0x2e
// 47 NA
#define MENU_TILE_NA 0x2f
// 48 OS
#define MENU_TILE_OS 0x30
// 49 SM
#define MENU_TILE_SM 0x31
// 50 OK
#define MENU_TILE_OK 0x32
// 51 ES
#define MENU_TILE_ES 0x33
// 52 FF
#define MENU_TILE_FF 0x34
// 53 EI
#define MENU_TILE_EI 0x35
// 54 NE
#define MENU_TILE_NE 0x36
// 55 HA
#define MENU_TILE_HA 0x37
// 56 GU
#define MENU_TILE_GU 0x38
// 57 N
#define MENU_TILE_N 0x39
// 58 KN
#define MENU_TILE_KN 0x3a
// 59 IF
#define MENU_TILE_IF 0x3b
// 60 AL
#define MENU_TILE_AL 0x3c
// 61 AR
#define MENU_TILE_AR 0x3d
// 62 M
#define MENU_TILE_M 0x3e
// 63 CL
#define MENU_TILE_CL 0x3f
// 64 OC
#define MENU_TILE_OC 0x40
// 65 K
#define MENU_TILE_K 0x41
// 66 PH
#define MENU_TILE_PH 0x42
// 67 ON
#define MENU_TILE_ON 0x43
// 68 UD
#define MENU_TILE_UD 0x44
// 69 GY
#define MENU_TILE_GY 0x45
// 70 OU
#define MENU_TILE_OU 0x46
// 71 T
#define MENU_TILE_T 0x47
// 72 GO
#define MENU_TILE_GO 0x48
// 73 TO
#define MENU_TILE_TO 0x49
// 74 AS
#define MENU_TILE_AS 0x4a
// 75 GI
#define MENU_TILE_GI 0x4b
// 76 VE
#define MENU_TILE_VE 0x4c
// 77 AP
#define MENU_TILE_AP 0x4d
// 78 A
#define MENU_TILE_A 0x4e
// 79 JO
#define MENU_TILE_JO 0x4f
// 80 B
#define MENU_TILE_B 0x50
// 81 FO
#define MENU_TILE_FO 0x51
// 82 JA
#define MENU_TILE_JA 0x52
// 83 NI
#define MENU_TILE_NI 0x53
// 84 MA
#define MENU_TILE_MA 0x54
// 85 IL
#define MENU_TILE_IL 0x55
// 86 SA
#define MENU_TILE_SA 0x56
// 87 LE
#define MENU_TILE_LE 0x57
// 88 AN
#define MENU_TILE_AN 0x58
// 89 EC
#define MENU_TILE_EC 0x59
// 90 UT
#define MENU_TILE_UT 0x5a
// 91 IV
#define MENU_TILE_IV 0x5b
// 92 VP
#define MENU_TILE_VP 0x5c
// 93 O
#define MENU_TILE_O 0x5d
// 94 PR
#define MENU_TILE_PR 0x5e
// 95 OM
#define MENU_TILE_OM 0x5f
// 96 OT
#define MENU_TILE_OT 0x60
// 97 IO
#define MENU_TILE_IO 0x61

// 98 Clock face
#define MENU_TILE_CLOCK 0x62
// 99 Colon
#define MENU_TILE_COLON 0x63
// 100 0
#define MENU_TILE_0 0x64
// 101 1
#define MENU_TILE_1 0x65
// 102 2
#define MENU_TILE_2 0x66
// 103 3
#define MENU_TILE_3 0x67
// 104 4
#define MENU_TILE_4 0x68
// 105 5
#define MENU_TILE_5 0x69
// 106 6
#define MENU_TILE_6 0x6a
// 107 7
#define MENU_TILE_7 0x6b
// 108 8
#define MENU_TILE_8 0x6c
// 109 9
#define MENU_TILE_9 0x6d
// 110 $
#define MENU_TILE_DOLLAR 0x6e
// 111 HP
#define MENU_TILE_HP 0x6f
// 112 /HR
#define MENU_TILE_PER_HOUR 0x70
// 113 DA
#define MENU_TILE_DA 0x71
// 114 YS
#define MENU_TILE_YS 0x72
// 115 /
#define MENU_TILE_SLASH 0x73
// 116 IN
#define MENU_TILE_IN 0x74
// 117 TE
#define MENU_TILE_TE 0x75
// 118 LL
#define MENU_TILE_LL 0x76
// 119 IG
#define MENU_TILE_IG 0x77
// 120 EN
#define MENU_TILE_EN 0x78
// 121 CE
#define MENU_TILE_CE 0x79
// 122 ST
#define MENU_TILE_ST 0x7a
// 123 RE
#define MENU_TILE_RE 0x7b
// 124 NG
#define MENU_TILE_NG 0x7c
// 125 TH
#define MENU_TILE_TH 0x7d
// 126 -
#define MENU_TILE_DASH 0x7e
// 127 D
#define MENU_TILE_D 0x7f

