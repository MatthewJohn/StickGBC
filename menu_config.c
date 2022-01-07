/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */


#pragma bank=6

#include "menu_config.h"

// MENU ITEMS

const menu_config_item_t menu_config_items[0x28U] = {
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
            0x11U,  // SL
            0x12U,  // EE
            0x13U,  // P
            MENU_ITEM_NO_TILE, MENU_ITEM_NO_TILE, MENU_ITEM_NO_TILE,
            MENU_BLANK_ITEM_ROW,
            // END
        },
        MENU_BLANK_ITEM_PALETTE,
    },
    {
        {
            0x16U,  // MI
            0x17U,  // LK
            0x18U,  // SH
            0x19U,  // AK
            0x1AU,  // E
            MENU_ITEM_NO_TILE,
            // Row 2
            MENU_TILE_1, // 1
            MENU_TILE_2, // 2
            MENU_TILE_HP, // HP
            MENU_TILE_DOLLAR, // $
            MENU_TILE_8, // 8
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
            0x1BU,  // FR
            0x1CU,  // IE
            0x1DU,  // S
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            // Row 2
            MENU_TILE_2,  // 2
            MENU_TILE_0,  // 0
            MENU_TILE_HP,  // HP
            MENU_TILE_DOLLAR,  // $
            MENU_TILE_1,  // 1
            MENU_TILE_2,  // 2
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
            MENU_TILE_WO,   // WO
            MENU_TILE_RK,   // RK
            MENU_ITEM_NO_TILE, MENU_ITEM_NO_TILE, MENU_ITEM_NO_TILE, MENU_ITEM_NO_TILE,

            MENU_TILE_DOLLAR,  // $
            MENU_TILE_6,  // 6
            MENU_TILE_PER_HOUR,  // /HR
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
            0x1EU,   // CH
            0x1FU,   // EE
            0x20U,   //  SE
            0x21U,   //  BU
            0x22U,   //  RG
            0x23U,   //  ER

            MENU_TILE_4,  // 4
            MENU_TILE_0,  // 0
            MENU_TILE_HP,  // HP
            MENU_TILE_DOLLAR,  // $
            MENU_TILE_2,  // 2
            MENU_TILE_5,  // 5
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
            0x24U,   // TR
            0x25U,   // PL
            0x21U,   //  BU
            0x22U,   //  RG
            0x23U,   //  ER
            MENU_ITEM_NO_TILE,

            MENU_TILE_8,  // 8
            MENU_TILE_0,  // 0
            MENU_TILE_HP,  // HP
            MENU_TILE_DOLLAR,  // $
            MENU_TILE_5,  // 5
            MENU_TILE_0,  // 0
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
    // Slushee
    {
        {
            MENU_TILE_SL,  // SL
            MENU_TILE_US,  // US
            MENU_TILE_HE,  // HE
            MENU_TILE_E,  // E
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            // Row 2
            MENU_TILE_1, // 1
            MENU_TILE_HP, // HP
            MENU_ITEM_NO_TILE,
            MENU_TILE_DOLLAR, // $
            MENU_TILE_1, // 1
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
            MENU_TILE_DOLLAR, // $
            MENU_TILE_1, // 1
            MENU_TILE_0, // 0
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
            MENU_TILE_3, // 3
            MENU_TILE_HP, // HP
            MENU_ITEM_NO_TILE,
            MENU_TILE_DOLLAR, // $
            MENU_TILE_2, // 2
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
            MENU_TILE_DOLLAR, // $
            MENU_TILE_4, // 4
            MENU_TILE_5, // 5
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
            MENU_TILE_7, // 7
            MENU_TILE_HP, // HP
            MENU_ITEM_NO_TILE,
            MENU_TILE_DOLLAR, // $
            MENU_TILE_4, // 4
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
            MENU_TILE_DOLLAR, // $
            MENU_TILE_4, // 4
            MENU_TILE_0, // 0
            MENU_TILE_0, // 0
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
            0x79U,  // CE
            0x76U,  // LL
            0x42U,  // PH
            0x43U,  // ON
            0x1AU,  // E
            MENU_ITEM_NO_TILE,
            // Row 2
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            MENU_TILE_DOLLAR, // $
            MENU_TILE_2, // 2
            MENU_TILE_0, // 0
            MENU_TILE_0, // 0
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
            MENU_TILE_DOLLAR, // $
            MENU_TILE_1, // 1
            MENU_TILE_0, // 0
            MENU_TILE_0, // 0
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
            MENU_TILE_DOLLAR, // $
            MENU_TILE_2, // 2
            MENU_TILE_0, // 0
            MENU_TILE_0, // 0
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
    // STUDY
    {
        {
            0x7AU,  // ST
            0x44U,  // UD
            0x2CU,  // Y
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            // Row 2
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            MENU_TILE_1,  // 1
            MENU_TILE_IN,   // IN
            MENU_TILE_TE,  // TE
            MENU_TILE_LL,  // LL
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_INTELLIGENCE_PALETTE,
            MENU_ITEM_INTELLIGENCE_PALETTE,
            MENU_ITEM_INTELLIGENCE_PALETTE,
            MENU_ITEM_INTELLIGENCE_PALETTE,
        },
    },
    // GO TO GYM
    {
        {
            0x48U,  // GO
            MENU_ITEM_NO_TILE,
            0x49U,  // TO
            MENU_ITEM_NO_TILE,
            0x45U,  // GY
            0x3EU,  // M
            // Row 2
            MENU_ITEM_NO_TILE,
            MENU_TILE_1,  // 1
            MENU_TILE_ST,  // ST
            MENU_TILE_RE, // RE
            MENU_TILE_NG, // NG
            MENU_TILE_TH,  // TH
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_STRENGTH_PALETTE,
            MENU_ITEM_STRENGTH_PALETTE,
            MENU_ITEM_STRENGTH_PALETTE,
            MENU_ITEM_STRENGTH_PALETTE,
            MENU_ITEM_STRENGTH_PALETTE,
        },
    },
    // CLASS
    {
        {
            0x3FU,  // CL
            0x4AU,  // AS
            0x1DU,  // S
            0x6EU,  // $
            0x66U,  // 2
            0x64U,  // 0
            // Row 2
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            MENU_TILE_2,  // 2
            MENU_TILE_IN,  // IN
            MENU_TILE_TE, // TE
            MENU_TILE_LL, // LL
        },
        {
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_INTELLIGENCE_PALETTE,
            MENU_ITEM_INTELLIGENCE_PALETTE,
            MENU_ITEM_INTELLIGENCE_PALETTE,
            MENU_ITEM_INTELLIGENCE_PALETTE,
        },
    },
    // Give Smokes
    {
        {
            0x4BU,  // GI
            0x4CU,  // VE
            MENU_ITEM_NO_TILE,
            0x31U,  // SM
            0x32U,  // OK
            0x33U,  // ES
            // Row 2
            MENU_BLANK_ITEM_ROW,
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_NO_PALETTE_ROW,
        },
    },
    // Apply for job
    {
        {
            MENU_TILE_AP,  // AP
            MENU_TILE_PL,  // PL
            MENU_TILE_Y,  // Y
            MENU_TILE_FO,  // FO
            MENU_TILE_R,  // R
            MENU_ITEM_NO_TILE,
            // Row 2
            MENU_TILE_A,  // A
            MENU_TILE_JO,  // JO
            MENU_TILE_B,  // B
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_NO_PALETTE_ROW,
        },
    },
    // Apply for Promotion
    {
        {
            MENU_TILE_AP,  // AP
            MENU_TILE_PL,  // PL
            MENU_TILE_Y,  // Y
            MENU_ITEM_NO_TILE,
            MENU_TILE_FO,  // FO
            MENU_TILE_R,  // R
            // Row 2
            MENU_TILE_PR,  // PR
            MENU_TILE_OM,  // OM
            MENU_TILE_OT,  // OT
            MENU_TILE_IO,  // IO
            MENU_TILE_N,  // N
            MENU_ITEM_NO_TILE,
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_NO_PALETTE_ROW,
        },
    },
    // Work Janitor
    {
        {
            MENU_TILE_WO,  // WO
            MENU_TILE_RK,  // RK
            MENU_TILE_DASH,  // -
            MENU_TILE_DOLLAR,
            MENU_TILE_8,
            MENU_ITEM_NO_TILE,
            // Row 2
            MENU_TILE_JA,  // JA
            MENU_TILE_NI,  // NI
            MENU_TILE_TO,  // TO
            MENU_TILE_R,  // R
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
        },
        {
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_NO_PALETTE_ROW,
        },
    },
    // Work Mail Clerk
    {
        {
            MENU_TILE_WO,  // WO
            MENU_TILE_RK,  // RK
            MENU_TILE_DASH,  // -
            MENU_TILE_DOLLAR,
            MENU_TILE_1,
            MENU_TILE_0,
            // Row 2
            MENU_TILE_MA,  // MA
            MENU_TILE_IL,  // IL
            MENU_TILE_CL,  // CL
            MENU_TILE_ER,  // ER
            MENU_TILE_K,  // K
            MENU_ITEM_NO_TILE,
        },
        {
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_NO_PALETTE_ROW,
        },
    },
    // Work Salesman
    {
        {
            MENU_TILE_WO,  // WO
            MENU_TILE_RK,  // RK
            MENU_TILE_DASH,  // -
            MENU_TILE_DOLLAR,
            MENU_TILE_1,
            MENU_TILE_5,
            // Row 2
            MENU_TILE_SA,  // SA
            MENU_TILE_LE,  // LE
            MENU_TILE_SM,  // SM
            MENU_TILE_AN,  // AN
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
        },
        {
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_NO_PALETTE_ROW,
        },
    },
    // Work Executive
    {
        {
            MENU_TILE_WO,  // WO
            MENU_TILE_RK,  // RK
            MENU_TILE_DASH,  // -
            MENU_TILE_DOLLAR,
            MENU_TILE_2,
            MENU_TILE_5,
            // Row 2
            MENU_TILE_EX,  // EX
            MENU_TILE_EC,  // EC
            MENU_TILE_UT,  // UT
            MENU_TILE_IV,  // IV
            MENU_TILE_E,  // E
            MENU_ITEM_NO_TILE,
        },
        {
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_NO_PALETTE_ROW,
        },
    },
    // Work VP
    {
        {
            MENU_TILE_WO,  // WO
            MENU_TILE_RK,  // RK
            MENU_TILE_DASH,  // -
            MENU_TILE_DOLLAR,
            MENU_TILE_5,
            MENU_TILE_0,
            // Row 2
            MENU_TILE_VP,  // VP
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
        },
        {
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_NO_PALETTE_ROW,
        },
    },
    // Work CEO
    {
        {
            MENU_TILE_WO,  // WO
            MENU_TILE_RK,  // RK
            MENU_TILE_DASH,  // -
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            // Row 2
            MENU_TILE_CE,
            MENU_TILE_O,
            MENU_TILE_DOLLAR,
            MENU_TILE_1,
            MENU_TILE_0,
            MENU_TILE_0,
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
    // 1g Cocaine
    {
        {
            MENU_TILE_1,  // 1
            MENU_TILE_G,  // G
            MENU_TILE_CO,  // CO
            MENU_TILE_CA,  // CA
            MENU_TILE_IN,  // IN
            MENU_TILE_E,  // E
            // Row 2
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_NO_PALETTE,
            MENU_TILE_DOLLAR,
            MENU_TILE_4,
            MENU_TILE_0,
            MENU_TILE_0,
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

    // Give $10
    {
        {
            MENU_TILE_GI,
            MENU_TILE_VE,
            MENU_ITEM_NO_TILE,
            MENU_TILE_DOLLAR,
            MENU_TILE_1,
            MENU_TILE_0,
            // Row 2
            MENU_BLANK_ITEM_ROW,
        },
        {
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_NO_PALETTE_ROW,
        },
    },

    // Drink Beer
    {
        {
            MENU_TILE_BE,
            MENU_TILE_ER,
            MENU_TILE_DASH,
            MENU_TILE_DOLLAR,
            MENU_TILE_2,
            MENU_TILE_0,
            // Row 2
            MENU_TILE_2,
            MENU_TILE_CH,
            MENU_TILE_AR,
            MENU_TILE_M,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
        },
        {
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_NO_PALETTE_ROW,
        },
    },

    // Bottle of Beer
    {
        {
            MENU_TILE_BO,
            MENU_TILE_TT,
            MENU_TILE_LE,
            MENU_ITEM_NO_TILE,
            MENU_TILE_OF,
            MENU_ITEM_NO_TILE,
            // Row 2
            MENU_TILE_BE,
            MENU_TILE_ER,
            MENU_ITEM_NO_TILE,
            MENU_TILE_DOLLAR,
            MENU_TILE_3,
            MENU_TILE_0,
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

    // Bar Fight
    {
        {
            MENU_TILE_BA,
            MENU_TILE_R,
            MENU_TILE_FI,
            MENU_TILE_GH,
            MENU_TILE_T,
            MENU_ITEM_NO_TILE,
            // Row 2
            MENU_BLANK_ITEM_ROW,
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_NO_PALETTE_ROW,
        },
    },

    // Play Darts
    {
        {
            MENU_TILE_PL,
            MENU_TILE_AY,
            MENU_ITEM_NO_TILE,
            MENU_TILE_DA,
            MENU_TILE_RT,
            MENU_TILE_S,
            // Row 2
            MENU_BLANK_ITEM_ROW,
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_NO_PALETTE_ROW,
        },
    },

    // Give Beer
    {
        {
            MENU_TILE_GI,
            MENU_TILE_VE,
            MENU_ITEM_NO_TILE,
            MENU_TILE_BE,
            MENU_TILE_ER,
            MENU_ITEM_NO_TILE,
            // Row 2
            MENU_TILE_8,
            MENU_TILE_CH,
            MENU_TILE_AR,
            MENU_TILE_M,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_NO_PALETTE_ROW,
        },
    },
    
    // Intelligence
    {
        {
            MENU_BLANK_ITEM_ROW,
            MENU_TILE_IN,
            MENU_TILE_TE,
            MENU_TILE_LL,
            MENU_TILE_IG,
            MENU_TILE_EN,
            MENU_TILE_CE,
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_INTELLIGENCE_PALETTE,
            MENU_ITEM_INTELLIGENCE_PALETTE,
            MENU_ITEM_INTELLIGENCE_PALETTE,
            MENU_ITEM_INTELLIGENCE_PALETTE,
            MENU_ITEM_INTELLIGENCE_PALETTE,
            MENU_ITEM_INTELLIGENCE_PALETTE,
        },
    },

    // Strength
    {
        {
            MENU_BLANK_ITEM_ROW,
            MENU_TILE_ST,
            MENU_TILE_RE,
            MENU_TILE_NG,
            MENU_TILE_TH,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_STRENGTH_PALETTE,
            MENU_ITEM_STRENGTH_PALETTE,
            MENU_ITEM_STRENGTH_PALETTE,
            MENU_ITEM_STRENGTH_PALETTE,
            MENU_ITEM_STRENGTH_PALETTE,
            MENU_ITEM_STRENGTH_PALETTE,
        },
    },

    // Charm
    {
        {
            MENU_BLANK_ITEM_ROW,
            MENU_TILE_CH,
            MENU_TILE_AR,
            MENU_TILE_M,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_CHARM_PALETTE,
            MENU_ITEM_CHARM_PALETTE,
            MENU_ITEM_CHARM_PALETTE,
            MENU_ITEM_CHARM_PALETTE,
            MENU_ITEM_CHARM_PALETTE,
            MENU_ITEM_CHARM_PALETTE,
        },
    },

    // Karma
    {
        {
            MENU_BLANK_ITEM_ROW,
            MENU_TILE_KA,
            MENU_TILE_RM,
            MENU_TILE_A,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_KARMA_PALETTE,
            MENU_ITEM_KARMA_PALETTE,
            MENU_ITEM_KARMA_PALETTE,
            MENU_ITEM_KARMA_PALETTE,
            MENU_ITEM_KARMA_PALETTE,
            MENU_ITEM_KARMA_PALETTE,
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
};

// University
menu_config_t menu_config_university = {
  {
      MENU_ITEM_INDEX_EMPTY,
      MENU_ITEM_INDEX_EXIT,
      MENU_ITEM_INDEX_STUDY,
      MENU_ITEM_INDEX_GYM,
      MENU_ITEM_INDEX_CLASS,
      MENU_ITEM_INDEX_EMPTY,
      MENU_ITEM_INDEX_EMPTY,
      MENU_ITEM_INDEX_EMPTY,
  },
};

// Skater
menu_config_t menu_config_skater = {
  {
      MENU_ITEM_INDEX_GIVE_SMOKES,
      MENU_ITEM_INDEX_EXIT,
      MENU_ITEM_INDEX_EMPTY,
      MENU_ITEM_INDEX_EMPTY,
      MENU_ITEM_INDEX_EMPTY,
      MENU_ITEM_INDEX_EMPTY,
      MENU_ITEM_INDEX_EMPTY,
      MENU_ITEM_INDEX_EMPTY,
  },
};

// NLI
menu_config_t menu_config_nli = {
  {
      MENU_ITEM_INDEX_EMPTY,
      MENU_ITEM_INDEX_EXIT,
      MENU_ITEM_INDEX_EMPTY,
      MENU_ITEM_INDEX_EMPTY,
      MENU_ITEM_INDEX_EMPTY,
      MENU_ITEM_INDEX_APPLY_FOR_JOB,
      MENU_ITEM_INDEX_EMPTY,
      MENU_ITEM_INDEX_EMPTY,
  },
};

// Dealer
menu_config_t menu_config_dealer = {
  {
      MENU_ITEM_INDEX_EMPTY,
      MENU_ITEM_INDEX_EXIT,
      MENU_ITEM_INDEX_EMPTY,
      MENU_ITEM_INDEX_EMPTY,
      MENU_ITEM_INDEX_COCAINE,
      MENU_ITEM_INDEX_EMPTY,
      MENU_ITEM_INDEX_EMPTY,
      MENU_ITEM_INDEX_EMPTY,
  },
};

// Dealer
menu_config_t menu_config_hobo = {
  {
      MENU_ITEM_INDEX_EMPTY,
      MENU_ITEM_INDEX_EXIT,
      MENU_ITEM_INDEX_EMPTY,
      MENU_ITEM_INDEX_EMPTY,
      MENU_ITEM_INDEX_GIVE_10,
      MENU_ITEM_INDEX_EMPTY,
      MENU_ITEM_INDEX_EMPTY,
      MENU_ITEM_INDEX_EMPTY,
  },
};

menu_config_t menu_config_bar = {
    {
      MENU_ITEM_INDEX_EMPTY,
      MENU_ITEM_INDEX_EXIT,
      MENU_ITEM_INDEX_DRINK_BEER,
      MENU_ITEM_INDEX_BOTTLE_OF_BEER,
      MENU_ITEM_INDEX_BAR_FIGHT,
      MENU_ITEM_INDEX_PLAY_DARTS,
      MENU_ITEM_INDEX_EMPTY,
      MENU_ITEM_INDEX_EMPTY,
    }
};

menu_config_t menu_config_stats = {
    {
      MENU_ITEM_INDEX_EMPTY,
      MENU_ITEM_INDEX_EXIT,
      MENU_ITEM_INDEX_INTELLIGENCE,
      MENU_ITEM_INDEX_STRENGTH,
      MENU_ITEM_INDEX_CHARM,
      MENU_ITEM_INDEX_KARMA,
      MENU_ITEM_INDEX_EMPTY,
      MENU_ITEM_INDEX_EMPTY,
    }
};

menu_config_t menu_config_inventory = {
    {
        MENU_ITEM_INDEX_EMPTY,
        MENU_ITEM_INDEX_EMPTY,
        MENU_ITEM_INDEX_EMPTY,
        MENU_ITEM_INDEX_EMPTY,
        MENU_ITEM_INDEX_EMPTY,
        MENU_ITEM_INDEX_EMPTY,
        MENU_ITEM_INDEX_EMPTY,
        MENU_ITEM_INDEX_EMPTY,
    }
};


// Update palette for currently selected menu item
void set_menu_item_color(menu_state_t *menu_state, menu_config_t *menu_config, unsigned char palette)
{
    // Check if current menu item is disabled
    if (menu_state->current_item_x == MENU_SELECTED_ITEM_DISABLED ||
        menu_state->current_item_y == MENU_SELECTED_ITEM_DISABLED)
        return;

    unsigned int itx_y, itx_x, tile_index, menu_item_index;
    unsigned char palette_colors[MENU_ITEM_WIDTH];
    unsigned int menu_item_itx = menu_state->current_item_x + (MENU_MAX_ITEMS_X * menu_state->current_item_y);

    VBK_REG = 1;
    for (itx_y = 0; itx_y != MENU_ITEM_HEIGHT; itx_y ++)
    {
        for (itx_x = 0; itx_x != MENU_ITEM_WIDTH; itx_x ++)
        {
            palette_colors[itx_x] = palette;
            tile_index = itx_x + (itx_y * MENU_ITEM_WIDTH);
            menu_item_index = menu_config->items[menu_item_itx];
            if (menu_config_items[menu_item_index].palette[tile_index] != 0U)
                palette_colors[itx_x] = menu_config_items[menu_item_index].palette[tile_index];
         }
        set_bkg_tiles(
            MENU_ITEM_SCREEN_OFFSET_LEFT + (8U * menu_state->current_item_x),
            itx_y + MENU_ITEM_SCREEN_OFFSET_TOP + (3U * menu_state->current_item_y),
            MENU_ITEM_WIDTH, 1,
            &palette_colors
        );
    }
    VBK_REG = 0;
}
