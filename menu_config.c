/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */


#pragma bank=6

#include "menu_config.h"

// MENU ITEMS

const menu_config_item_t menu_config_items[0x12] = {
    // Exit
    {
        MENU_BLANK_ITEM,
        MENU_BLANK_ITEM_PALETTE,
    },
    {
        MENU_BLANK_ITEM,
        MENU_BLANK_ITEM_PALETTE,
    },
    {
        {
            // Item 7 - SLEEP
            0x1U,  // SL
            0x2U,  // EE
            0x3U,  // P
            MENU_ITEM_NO_TILE, MENU_ITEM_NO_TILE, MENU_ITEM_NO_TILE,
            MENU_BLANK_ITEM_ROW,
            // END
        },
        MENU_BLANK_ITEM_PALETTE,
    },
    {
        {
            0x1U,  // MI
            0x2U,  // LK
            0x3U,  // SH
            0x4U,  // AK
            0x5U,  // E
            MENU_ITEM_NO_TILE,
            // Row 2
            0x2U, // 1
            0x3U, // 2
            0xCU, // HP
            0xBU, // $
            0x9U, // 8
            MENU_ITEM_NO_TILE,
        },
        {
            // MILKSHAKE
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_HP_PALETTE,
            MENU_ITEM_HP_PALETTE,
            MENU_ITEM_HP_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_NO_PALETTE,
        },
    },
    {
        {
            0x6U,  // FR
            0x7U,  // IE
            0x8U,  // S
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            // Row 2
            0x3U,  // 2
            0x1U,  // 0
            0xCU,  // HP
            0xBU,  // $
            0x2U,  // 1
            0x3U,  // 2
        },
        {
            // FRIES
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_HP_PALETTE,
            MENU_ITEM_HP_PALETTE,
            MENU_ITEM_HP_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
        },
    },
    {
        {
            0x11U,   // WO
            0x12U,   // RK
            0x13U,   //  K
            MENU_ITEM_NO_TILE, MENU_ITEM_NO_TILE, MENU_ITEM_NO_TILE,

            0xBU,  // $
            0x7U,  // 6
            0xDU,  // /HR
            MENU_ITEM_NO_TILE, MENU_ITEM_NO_TILE, MENU_ITEM_NO_TILE,
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_NO_PALETTE, MENU_ITEM_NO_PALETTE, MENU_ITEM_NO_PALETTE,
        },
    },
    {
        {
            0x9U,   // CH
            0xAU,   // EE
            0xBU,   //  SE
            0xCU,   //  BU
            0xDU,   //  RG
            0xEU,   //  ER

            0x5U,  // 4
            0x1U,  // 0
            0xCU,  // HP
            0xBU,  // $
            0x3U,  // 2
            0x6U,  // 5
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_HP_PALETTE,
            MENU_ITEM_HP_PALETTE,
            MENU_ITEM_HP_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
        },
    },
    {
        {
            // TRIPLE BURGER
            0xFU,   // TR
            0x10U,   // PL
            0xCU,   //  BU
            0xDU,   //  RG
            0xEU,   //  ER
            MENU_ITEM_NO_TILE,

            0x9U,  // 8
            0x1U,  // 0
            0xCU,  // HP
            0xBU,  // $
            0x6U,  // 5
            0x1U,  // 0
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_HP_PALETTE,
            MENU_ITEM_HP_PALETTE,
            MENU_ITEM_HP_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
        },
    },
    {
        {
            0x11U,  // SL
            0x29U,  // US
            0x1FU,  // EE
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            // Row 2
            0x2U, // 1
            0xCU, // HP
            MENU_ITEM_NO_TILE,
            0xBU, // $
            0x2U, // 1
            MENU_ITEM_NO_TILE,
        },
        {
            // MILKSHAKE
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_HP_PALETTE,
            MENU_ITEM_HP_PALETTE,
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_NO_PALETTE,
        },
    },
    {
        {
            0x31U,  // SM
            0x32U,  // OK
            0x33U,  // ES
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            // Row 2
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            0xBU, // $
            0x2U, // 1
            0x1U, // 0
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
        },
    },
    {
        {
            0x2AU,  // CA
            0x2BU,  // ND
            0x2CU,  // Y
            0x2DU,  // BA
            0x2E,  // R
            MENU_ITEM_NO_TILE,
            // Row 2
            0x4U, // 3
            0xCU, // HP
            MENU_ITEM_NO_TILE,
            0xBU, // $
            0x3U, // 2
            MENU_ITEM_NO_TILE,
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_HP_PALETTE,
            MENU_ITEM_HP_PALETTE,
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_NO_PALETTE,
        },
    },
    {
        {
            0x2AU,  // CA
            0x34U,  // FF
            0x35U,  // EI
            0x36U,  // NE
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            // Row 2
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            0xBU, // $
            0x5U, // 4
            0x6U, // 5
        },
        {
            // CAFFEINE PILLS
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
        },
    },
    {
        {
            0x2FU,  // NA
            0x1EU,  // CH
            0x30U,  // OS
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            // Row 2
            0x8U, // 7
            0xCU, // HP
            MENU_ITEM_NO_TILE,
            0xBU, // $
            0x5U, // 4
            MENU_ITEM_NO_TILE,
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_HP_PALETTE,
            MENU_ITEM_HP_PALETTE,
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_NO_PALETTE,
        },
    },
    {
        {
            0x37U,  // HA
            0x2BU,  // ND
            0x38U,  // GU
            0x39U,  // N
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            // Row 2
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            0xBU, // $
            0x5U, // 4
            0x1U, // 0
            0x1U, // 0
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
        },
    },
    {
        {
            0x42U,  // CE
            0x43U,  // LL
            0x44U,  // PH
            0x45U,  // ON
            0x1AU,  // E
            MENU_ITEM_NO_TILE,
            // Row 2
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            0xBU, // $
            0x3U, // 2
            0x1U, // 0
            0x1U, // 0
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
        },
    },
    {
        {
            0x3AU,  // KN
            0x3BU,  // IF
            0x1AU,  // E
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            // Row 2
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            0xBU, // $
            0x2U, // 1
            0x1U, // 0
            0x1U, // 0
        },
        {
            // KNIFE
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
        },
    },
    {
        {
            0x3CU,  // AL
            0x3DU,  // AR
            0x3EU,  // M
            0x3FU,  // CL
            0x40U,  // OC
            0x41U,  // K
            // Row 2
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            0xBU, // $
            0x3U, // 2
            0x1U, // 0
            0x1U, // 0
        },
        {
            // ALARM CLOCK
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
        },
    },
};

// BUILDING MENU DEFINITIONS

// HOUSE
menu_config_t menu_config_house = {
    {
        // Blank item 1
        MENU_ITEM_INDEX_EMPTY,
        MENU_ITEM_INDEX_EXIT,
        MENU_ITEM_INDEX_EMPTY,
        MENU_ITEM_INDEX_EMPTY,
        MENU_ITEM_INDEX_EMPTY,
        MENU_ITEM_INDEX_EMPTY,
        MENU_ITEM_INDEX_EMPTY,
        MENU_ITEM_INDEX_SLEEP,
    },
    0x10U,
};


// RESTAURANT
menu_config_t menu_config_restaurant = {
    {
        MENU_ITEM_INDEX_MILKSHAKE,
        MENU_ITEM_INDEX_EXIT,
        MENU_ITEM_INDEX_FRIES,
        MENU_ITEM_INDEX_WORK,
        MENU_ITEM_INDEX_CHEESE_BURGER,
        MENU_ITEM_INDEX_EMPTY,
        MENU_ITEM_INDEX_TRIPLE_BURGER,
        MENU_ITEM_INDEX_EMPTY,
    },
    0x15U,
};


// SHOP
menu_config_t menu_config_shop = {
    {
        MENU_ITEM_INDEX_EMPTY,
        MENU_ITEM_INDEX_EXIT,
        MENU_ITEM_INDEX_SLUSHEE,
        MENU_ITEM_INDEX_SMOKES,
        MENU_ITEM_INDEX_CANDY_BAR,
        MENU_ITEM_INDEX_CAFFEINE_PILLS,
        MENU_ITEM_INDEX_NACHOS,
        MENU_ITEM_INDEX_EMPTY,
    },
    0x00U,
};


// PAWN SHOP
menu_config_t menu_config_pawn = {
    {
        MENU_ITEM_INDEX_EMPTY,
        MENU_ITEM_INDEX_EXIT,
        MENU_ITEM_INDEX_HAND_GUN,
        MENU_ITEM_INDEX_CELL_PHONE,
        MENU_ITEM_INDEX_KNIFE,
        MENU_ITEM_INDEX_EMPTY,
        MENU_ITEM_INDEX_ALARM_CLOCK,
        MENU_ITEM_INDEX_EMPTY,
    },
    0x00U,
};

