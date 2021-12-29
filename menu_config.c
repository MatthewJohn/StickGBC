/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */


#pragma bank=5

#include "menu_config.h"

// BUILDING MENU DEFINITIONS

// HOUSE
const menu_config_t menu_config_house = {
    {
        // Blank item 1
        MENU_BLANK_ITEM,
        MENU_BLANK_ITEM,
        MENU_BLANK_ITEM,
        MENU_BLANK_ITEM,
        MENU_BLANK_ITEM,
        MENU_BLANK_ITEM,
        MENU_BLANK_ITEM,
        {
            // Item 7 - SLEEP
            0x1U,  // SL
            0x2U,  // EE
            0x3U,  // P
            MENU_ITEM_NO_TILE, MENU_ITEM_NO_TILE, MENU_ITEM_NO_TILE,
            MENU_BLANK_ITEM_ROW,
            // END
        }
    },
    {
        MENU_BLANK_ITEM_PALETTE,
        MENU_BLANK_ITEM_PALETTE,
        MENU_BLANK_ITEM_PALETTE,
        MENU_BLANK_ITEM_PALETTE,
        MENU_BLANK_ITEM_PALETTE,
        MENU_BLANK_ITEM_PALETTE,
        MENU_BLANK_ITEM_PALETTE,
        MENU_BLANK_ITEM_PALETTE,
    },
    0x82,
    0x10U
};

// RESTAURANT
const menu_config_t menu_config_restaurant = {
    {
        {
            // MILKSHAKE
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
        MENU_BLANK_ITEM,
        {
            // FRIES
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
            // WORK
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
            // CHEESE BURGER
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
        MENU_BLANK_ITEM,
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
        MENU_BLANK_ITEM,
    },
    {
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
        MENU_BLANK_ITEM_PALETTE,
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
        {
            // WORK
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_NO_PALETTE, MENU_ITEM_NO_PALETTE, MENU_ITEM_NO_PALETTE,
        },
        {
            // CHEESE BURGER
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_HP_PALETTE,
            MENU_ITEM_HP_PALETTE,
            MENU_ITEM_HP_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
        },
        MENU_BLANK_ITEM_PALETTE,
        {
            // TRIPLE BURGER
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_HP_PALETTE,
            MENU_ITEM_HP_PALETTE,
            MENU_ITEM_HP_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
        },
        MENU_BLANK_ITEM_PALETTE,
    },
    0x5F,
    0x15U,
};


// SHOP
const menu_config_t menu_config_shop = {
    {
        MENU_BLANK_ITEM,
        MENU_BLANK_ITEM,
        {
            // SLUSHEE
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
            // SMOKES
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
            // CANDY BAR
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
            // CAFFEINE PILLS
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
            // NACHOS
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
        MENU_BLANK_ITEM,
    },
    {
        MENU_BLANK_ITEM_PALETTE,
        MENU_BLANK_ITEM_PALETTE,
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
        {
            // SMOKES
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
        },
        {
            // CANDY BAR
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_HP_PALETTE,
            MENU_ITEM_HP_PALETTE,
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_NO_PALETTE,
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
        {
            // NACHOS
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_HP_PALETTE,
            MENU_ITEM_HP_PALETTE,
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_NO_PALETTE,
        },
        MENU_BLANK_ITEM_PALETTE,
    },
    0x7EU,
    0x00U,
};
