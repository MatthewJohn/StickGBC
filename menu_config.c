/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */


#pragma bank=6

#include "menu_config.h"
#include "main.h"
#include "window_text.h"

// MENU ITEMS

const menu_config_item_t menu_config_items[0x4CU] = {
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
            0x1FU,  // EE
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

    // Cell Phone
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

    // KNIFE
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

    // Inventory Smokes
    {
        {
            MENU_BLANK_ITEM_ROW,

            0x31U,  // SM
            0x32U,  // OK
            0x33U,  // ES
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_NO_PALETTE_ROW,
        },
    },

    // Inventory Caffeine Pills
    {
        {
            MENU_BLANK_ITEM_ROW,

            0x2AU,  // CA
            0x34U,  // FF
            0x35U,  // EI
            0x36U,  // NE
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_NO_PALETTE_ROW,
        },
    },

    // Inventory Handgun
    {
        {
            MENU_BLANK_ITEM_ROW,

            0x37U,  // HA
            0x2BU,  // ND
            0x38U,  // GU
            0x39U,  // N
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_NO_PALETTE_ROW,
        },
    },

    // Inventory Knife
    {
        {
            MENU_BLANK_ITEM_ROW,

            0x3AU,  // KN
            0x3BU,  // IF
            0x1AU,  // E
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_NO_PALETTE_ROW,
        },
    },

    // Inventory Cell Phone
    {
        {
            MENU_BLANK_ITEM_ROW,

            0x79U,  // CE
            0x76U,  // LL
            0x42U,  // PH
            0x43U,  // ON
            0x1AU,  // E
            MENU_ITEM_NO_TILE,
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_NO_PALETTE_ROW,
        },
    },

    // Inventory skateboard
    {
        {
            MENU_BLANK_ITEM_ROW,

            MENU_TILE_S,
            MENU_TILE_KA,
            MENU_TILE_TE,
            MENU_TILE_BO,
            MENU_TILE_AR,
            MENU_TILE_D,
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_NO_PALETTE_ROW,
        },
    },

    // Inventory Cocaine
    {
        {
            MENU_BLANK_ITEM_ROW,

            MENU_TILE_1,  // 1
            MENU_TILE_G,  // G
            MENU_TILE_CO,  // CO
            MENU_TILE_CA,  // CA
            MENU_TILE_IN,  // IN
            MENU_TILE_E,  // E
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_NO_PALETTE_ROW,
        },
    },

    // Inventory Bottle of Beer
    {
        {
            MENU_BLANK_ITEM_ROW,

            MENU_TILE_BE,
            MENU_TILE_ER,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_NO_PALETTE_ROW,
        },
    },

    // Bus menu - Sell Good
    {
        {
            MENU_TILE2_SE,
            MENU_TILE2_LL,
            MENU_TILE2__G,
            MENU_TILE2_OO,
            MENU_TILE2_DS,
            MENU_ITEM_NO_TILE,
            MENU_BLANK_ITEM_ROW,
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_NO_PALETTE_ROW,
        }
    },

    // Bus menu - Brooklyn
    {
        {
            MENU_TILE2_BR,
            MENU_TILE2_OO,
            MENU_TILE2_KL,
            MENU_TILE2_YN,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,

            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            MENU_TILE_DOLLAR,
            MENU_TILE_1,
            MENU_TILE_1,
            MENU_TILE_5,
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

    // Bus menu - Chicago
    {
        {
            MENU_TILE2_CH,
            MENU_TILE2_IC,
            MENU_TILE2_AG,
            MENU_TILE2_O,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,

            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            MENU_TILE_DOLLAR,
            MENU_TILE_1,
            MENU_TILE_1,
            MENU_TILE_5,
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

    // Bus menu - Detroit
    {
        {
            MENU_TILE2_DE,
            MENU_TILE2_TR,
            MENU_TILE2_OI,
            MENU_TILE2_T,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,

            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
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


    // Bus menu - Camden
    {
        {
            MENU_TILE2_CA,
            MENU_TILE2_MD,
            MENU_TILE2_EN,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,

            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            MENU_TILE_DOLLAR,
            MENU_TILE_1,
            MENU_TILE_3,
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

    // Bus menu - Los Angeles
    {
        {
            MENU_TILE2_LO,
            MENU_TILE2_S,
            MENU_TILE2_AN,
            MENU_TILE2_GE,
            MENU_TILE2_LE,
            MENU_TILE2_S,

            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
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

    // Bus menu - Las Vegas
    {
        {
            MENU_TILE2_LA,
            MENU_TILE2_S,
            MENU_TILE2_VE,
            MENU_TILE2_GA,
            MENU_TILE2_S,
            MENU_ITEM_NO_TILE,

            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            MENU_TILE_DOLLAR,
            MENU_TILE_1,
            MENU_TILE_3,
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

    // Bullets
    {
        {
            MENU_TILE_5,
            MENU_TILE_BU,
            MENU_TILE_LL,
            MENU_TILE_ET,
            MENU_TILE_S,
            MENU_ITEM_NO_TILE,
            // Row 2
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            MENU_TILE_DOLLAR,
            MENU_TILE_1,
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

    // Rob
    {
        {
            MENU_TILE_R,
            MENU_TILE_O,
            MENU_TILE_B,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            // Row 2
            MENU_TILE_DOLLAR,
            MENU_TILE_DOLLAR,
            MENU_TILE_DOLLAR,
            MENU_TILE_DOLLAR,
            MENU_TILE_DOLLAR,
            MENU_TILE_DOLLAR,
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
        },
    },

    // Withdraw
    {
        {
            MENU_TILE2_WI,
            MENU_TILE2_TH,
            MENU_TILE2_DR,
            MENU_TILE2_AW,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,

            MENU_BLANK_ITEM_ROW,
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_NO_PALETTE_ROW,
        },
    },

    // Deposit
    {
        {
            MENU_TILE2_DE,
            MENU_TILE2_PO,
            MENU_TILE2_SI,
            MENU_TILE2_T,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,

            MENU_BLANK_ITEM_ROW,
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_NO_PALETTE_ROW,
        },
    },

    // Real estate
    {
        {
            MENU_TILE2_RE,
            MENU_TILE2_AL,
            MENU_TILE2_ES,
            MENU_TILE2_TA,
            MENU_TILE2_TE,
            MENU_ITEM_NO_TILE,

            MENU_BLANK_ITEM_ROW,
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_NO_PALETTE_ROW,
        },
    },

    // Get a Loan
    {
        {
            MENU_TILE2_GE,
            MENU_TILE2_T,
            MENU_TILE2_A,
            MENU_TILE2_LO,
            MENU_TILE2_AN,
            MENU_ITEM_NO_TILE,

            MENU_BLANK_ITEM_ROW,
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_NO_PALETTE_ROW,
        },
    },

    // Repay Loan
    {
        {
            MENU_TILE2_RE,
            MENU_TILE2_PA,
            MENU_TILE2_Y,
            MENU_TILE2_LO,
            MENU_TILE2_AN,
            MENU_ITEM_NO_TILE,

            MENU_BLANK_ITEM_ROW,
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_NO_PALETTE_ROW,
        },
    },

    // Rob2 (building menu 2)
    {
        {
            MENU_TILE2_R,
            MENU_TILE2_O,
            MENU_TILE2_B,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            // Row 2
            MENU_TILE2_DOLLAR,
            MENU_TILE2_DOLLAR,
            MENU_TILE2_DOLLAR,
            MENU_TILE2_DOLLAR,
            MENU_TILE2_DOLLAR,
            MENU_TILE2_DOLLAR,
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
        },
    },

    // Inventory bullets
    {
        {
            MENU_BLANK_ITEM_ROW,

            MENU_TILE_BU,
            MENU_TILE_LL,
            MENU_TILE_ET,
            MENU_TILE_S,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_NO_PALETTE_ROW,
        },
    },

    // BED
    {
        {
            MENU_TILE2_BE,  // BE
            MENU_TILE2_D,  // D
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            // Row 2
            MENU_TILE_DOLLAR, // $
            MENU_TILE2_5, // 5
            MENU_TILE2_0, // 0
            MENU_TILE2_0, // 0
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_NO_PALETTE,
        },
    },

    // TV
    {
        {
            MENU_TILE2_TV,  // TV
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            // Row 2
            MENU_TILE_DOLLAR, // $
            MENU_TILE2_2, // 2
            MENU_TILE2_5, // 5
            MENU_TILE2_0, // 0
            MENU_TILE2_0, // 0
            MENU_ITEM_NO_TILE,
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_NO_PALETTE,
        },
    },

    // PC
    {
        {
            MENU_TILE2_PC,  // PC
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            // Row 2
            MENU_TILE_DOLLAR, // $
            MENU_TILE2_2, // 2
            MENU_TILE2_0, // 0
            MENU_TILE2_0, // 0
            MENU_TILE2_0, // 0
            MENU_ITEM_NO_TILE,
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_NO_PALETTE,
        },
    },

    // DEEP FREEZE
    {
        {
            MENU_TILE2_DE,  // DE
            MENU_TILE2_EP,  // EP
            MENU_TILE2_DE,  // FR
            MENU_TILE2_EE,  // EE
            MENU_TILE2_ZE,  // ZE
            MENU_ITEM_NO_TILE,
            // Row 2
            MENU_TILE_DOLLAR, // $
            MENU_TILE2_2, // 2
            MENU_TILE2_5, // 5
            MENU_TILE2_0, // 0
            MENU_TILE2_0, // 0
            MENU_ITEM_NO_TILE,
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_NO_PALETTE,
        },
    },

    // SATELLITE
    {
        {
            MENU_TILE2_SA,  // SA
            MENU_TILE2_TE,  // TE
            MENU_TILE2_LL,  // LL
            MENU_TILE2_IT,  // IT
            MENU_TILE2_E,  // E
            MENU_ITEM_NO_TILE,
            // Row 2
            MENU_TILE_DOLLAR, // $
            MENU_TILE2_3, // 3
            MENU_TILE2_0, // 0
            MENU_TILE2_0, // 0
            MENU_TILE2_0, // 0
            MENU_ITEM_NO_TILE,
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_NO_PALETTE,
        },
    },
    // TREADMILL
    {
        {
            MENU_TILE2_TR,  // TR
            MENU_TILE2_EA,  // EA
            MENU_TILE2_DM,  // DM
            MENU_TILE2_IL,  // IL
            MENU_TILE2_L,  // L
            MENU_ITEM_NO_TILE,
            // Row 2
            MENU_TILE_DOLLAR, // $
            MENU_TILE2_3, // 3
            MENU_TILE2_5, // 5
            MENU_TILE2_0, // 0
            MENU_TILE2_0, // 0
            MENU_ITEM_NO_TILE,
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_NO_PALETTE,
        },
    },

    // Stick-o-pedia
    // @TODO Correct 'ia' on end of name
    {
        {
            MENU_TILE2_ST,  // ST
            MENU_TILE2_IC,  // IC
            MENU_TILE2_K,  // K
            MENU_TILE2_dOd,  // -o-
            MENU_TILE2_PE,  // PE
            MENU_TILE2_DI, // DI
            // Row 2
            MENU_TILE_DOLLAR, // $
            MENU_TILE2_2, // 2
            MENU_TILE2_0, // 0
            MENU_TILE2_0, // 0
            MENU_TILE2_0, // 0
            MENU_ITEM_NO_TILE,
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_NO_PALETTE,
        },
    },

    // Minibar
    {
        {
            MENU_TILE2_MI,  // MI
            MENU_TILE2_NI,  // NI
            MENU_TILE2_BA,  // BA
            MENU_TILE2_R,  // R
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            // Row 2
            MENU_TILE_DOLLAR, // $
            MENU_TILE2_2, // 2
            MENU_TILE2_0, // 0
            MENU_TILE2_0, // 0
            MENU_TILE2_0, // 0
            MENU_ITEM_NO_TILE,
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_NO_PALETTE,
        },
    },
    
    // Apartment
    {
        {
            MENU_TILE2_AP,
            MENU_TILE2_AR,
            MENU_TILE2_TM,
            MENU_TILE2_EN,
            MENU_TILE2_T,
            MENU_ITEM_NO_TILE,
            // Row 2
            MENU_TILE_DOLLAR, // $
            MENU_TILE2_2, // 2
            MENU_TILE2_5, // 5
            MENU_TILE2_K, // K
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_NO_PALETTE,
        },
    },
    
    // Penthouse
    {
        {
            MENU_TILE2_PE,
            MENU_TILE2_NT,
            MENU_TILE2_HO,
            MENU_TILE2_US,
            MENU_TILE2_E,
            MENU_ITEM_NO_TILE,
            // Row 2
            MENU_TILE_DOLLAR, // $
            MENU_TILE2_5, // 5
            MENU_TILE2_0, // 0
            MENU_TILE2_K, // K
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_NO_PALETTE,
            MENU_ITEM_NO_PALETTE,
        },
    },
    
    // Mansion
    {
        {
            MENU_TILE2_MA,
            MENU_TILE2_NS,
            MENU_TILE2_IO,
            MENU_TILE2_N,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            // Row 2
            MENU_TILE_DOLLAR, // $
            MENU_TILE2_1, // 1
            MENU_TILE2_0, // 0
            MENU_TILE2_0, // 0
            MENU_TILE2_K, // K
            MENU_ITEM_NO_TILE,
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_NO_PALETTE,
        },
    },
    
    // Castle
    {
        {
            MENU_TILE2_CA,
            MENU_TILE2_ST,
            MENU_TILE2_LE,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            MENU_ITEM_NO_TILE,
            // Row 2
            MENU_TILE_DOLLAR, // $
            MENU_TILE2_5, // 5
            MENU_TILE2_0, // 0
            MENU_TILE2_0, // 0
            MENU_TILE2_K, // K
            MENU_ITEM_NO_TILE,
        },
        {
            MENU_ITEM_NO_PALETTE_ROW,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_COST_PALETTE,
            MENU_ITEM_NO_PALETTE,
        },
    },
};

const UINT8 inventory_menu_item_map[S_INVENTORY_ITEM_COUNT] = {
    0x28,  // Smokes
    0x29,  // Caffeine pills
    0x2A,  // Handgun
    0x2B,  // Knife
    0x00, // Alarm clock (hidden item)
    0x2C,  // Cell Phone
    0x2D,  // Skateboard
    0x2E,  // Cocaine
    0x2F,  // Bottle of beer
    0x3F // Bullets
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

menu_config_t menu_config_bus_station = {
    {
        MENU_ITEM_INDEX_SELL_GOODS,
        MENU_ITEM_INDEX_EXIT,
        MENU_ITEM_INDEX_BROOKLYN,
        MENU_ITEM_INDEX_CHICAGO,
        MENU_ITEM_INDEX_DETROIT,
        MENU_ITEM_INDEX_CAMDEN,
        MENU_ITEM_INDEX_LOS_ANGELES,
        MENU_ITEM_INDEX_LAS_VEGAS,
    }
};

menu_config_t menu_config_bank = {
    {
        MENU_ITEM_INDEX_EMPTY,
        MENU_ITEM_INDEX_EXIT,
        MENU_ITEM_INDEX_WITHDRAW,
        MENU_ITEM_INDEX_DEPOSIT,
        MENU_ITEM_INDEX_REAL_ESTATE,
        MENU_ITEM_INDEX_GET_LOAN,
        MENU_ITEM_INDEX_EMPTY,
        MENU_ITEM_INDEX_EMPTY,
    }
};

menu_config_t menu_config_appliance_store = {
    {
        MENU_ITEM_INDEX_BED,  // MENU_ITEM_INDEX_MINIBAR
        MENU_ITEM_INDEX_EXIT,
        MENU_ITEM_INDEX_TV,
        MENU_ITEM_INDEX_PC,
        MENU_ITEM_INDEX_DEEP_FREEZE,
        MENU_ITEM_INDEX_STELLITE,
        MENU_ITEM_INDEX_TREADMILL,
        MENU_ITEM_INDEX_STICKOPEDIA,
    }
};

menu_config_t menu_config_real_estate = {
    {
        MENU_ITEM_INDEX_EMPTY,
        MENU_ITEM_INDEX_EXIT,
        MENU_ITEM_INDEX_APARTMENT,
        MENU_ITEM_INDEX_PENTHOUSE,
        MENU_ITEM_INDEX_MANSION,
        MENU_ITEM_INDEX_CASTLE,
        MENU_ITEM_INDEX_EMPTY,
        MENU_ITEM_INDEX_EMPTY,
    }
};


// Update palette for currently selected menu item
void set_menu_item_color(unsigned char palette)
{
    unsigned int itx_y, itx_x, tile_index, menu_item_index;
    unsigned char palette_colors[MENU_ITEM_WIDTH];
    unsigned int menu_item_itx = menu_state.current_item_x + (MENU_MAX_ITEMS_X * menu_state.current_item_y);

    // Check if current menu item is disabled
    if (menu_state.current_item_x == MENU_SELECTED_ITEM_DISABLED ||
        menu_state.current_item_y == MENU_SELECTED_ITEM_DISABLED)
        return;

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
            MENU_ITEM_SCREEN_OFFSET_LEFT + (8U * menu_state.current_item_x),
            itx_y + MENU_ITEM_SCREEN_OFFSET_TOP + (3U * menu_state.current_item_y),
            MENU_ITEM_WIDTH, 1,
            &palette_colors
        );
    }
    VBK_REG = 0;
}

/*
 * apply_for_job_promotion
 *
 * Check for intelligence and promote job at NLI
 */
void apply_for_job_promotion(game_state_t *game_state, menu_config_t *menu_config, menu_config_t *menu_config_restaurant)
{
    // Check current if applying for job
    if (menu_config->items[MENU_NLI_PROMOTION_ITEM] == MENU_ITEM_INDEX_APPLY_FOR_JOB)
    {
        if (game_state->intelligence >= 20U)
        {
            menu_config_restaurant->items[3U] = MENU_ITEM_INDEX_EMPTY;
            menu_config->items[MENU_NLI_PROMOTION_ITEM] = MENU_ITEM_INDEX_APPLY_FOR_PROMOTION;
            menu_config->items[MENU_NLI_WORK_ITEM] = MENU_ITEM_INDEX_WORK_JANITOR;
            modify_karma(1);
            main_show_window_text(&win_txt_nli_jan, ROM_BANK_MENU_CONFIG);
            // Select 'work' item for new job
            move_to_menu_item(1U, 3U, ROM_BANK_MENU_CONFIG);
        }
        else
        {
            // Show unsuccessful message
            main_show_window_text(&win_txt_nli_no_int, ROM_BANK_MENU_CONFIG);
        }
    }
    else if (menu_config->items[MENU_NLI_WORK_ITEM] == MENU_ITEM_INDEX_WORK_JANITOR)
    {
        if (game_state->intelligence >= 40U)
        {
            menu_config->items[MENU_NLI_WORK_ITEM] = MENU_ITEM_INDEX_WORK_MAIL_CLERK;
            modify_karma(3);
            main_show_window_text(&win_txt_nli_mail, ROM_BANK_MENU_CONFIG);
            // Select 'work' item for new job
            move_to_menu_item(1U, 3U, ROM_BANK_MENU_CONFIG);
        }
        else
        {
            // Show unsuccessful message
            main_show_window_text(&win_txt_nli_no_int, ROM_BANK_MENU_CONFIG);
        }
    }
    else if (menu_config->items[MENU_NLI_WORK_ITEM] == MENU_ITEM_INDEX_WORK_MAIL_CLERK)
    {
        if (game_state->intelligence >= 75U)
        {
            menu_config->items[MENU_NLI_WORK_ITEM] = MENU_ITEM_INDEX_WORK_SALESMAN;
            modify_karma(3);
            main_show_window_text(&win_txt_nli_sales, ROM_BANK_MENU_CONFIG);
            // Select 'work' item for new job
            move_to_menu_item(1U, 3U, ROM_BANK_MENU_CONFIG);        }
        else
        {
            // Show unsuccessful message
            main_show_window_text(&win_txt_nli_no_int, ROM_BANK_MENU_CONFIG);
        }
    }
    else if (menu_config->items[MENU_NLI_WORK_ITEM] == MENU_ITEM_INDEX_WORK_SALESMAN)
    {
        if (game_state->intelligence >= 120U)
        {
            menu_config->items[MENU_NLI_WORK_ITEM] = MENU_ITEM_INDEX_WORK_EXECUTIVE;
            modify_karma(3);
            main_show_window_text(&win_txt_nli_exec, ROM_BANK_MENU_CONFIG);
            // Select 'work' item for new job
            move_to_menu_item(1U, 3U, ROM_BANK_MENU_CONFIG);
        }
        else
        {
            // Show unsuccessful message
            main_show_window_text(&win_txt_nli_no_int, ROM_BANK_MENU_CONFIG);
        }
    }
    else if (menu_config->items[MENU_NLI_WORK_ITEM] == MENU_ITEM_INDEX_WORK_EXECUTIVE)
    {
        if (game_state->intelligence >= 180U)
        {
            menu_config->items[MENU_NLI_WORK_ITEM] = MENU_ITEM_INDEX_WORK_VP;
            modify_karma(3);
            main_show_window_text(&win_txt_nli_vp, ROM_BANK_MENU_CONFIG);
            // Select 'work' item for new job
            move_to_menu_item(1U, 3U, ROM_BANK_MENU_CONFIG);
        }
        else
        {
            // Show unsuccessful message
            main_show_window_text(&win_txt_nli_no_int, ROM_BANK_MENU_CONFIG);
        }
    }
    else if (menu_config->items[MENU_NLI_WORK_ITEM] == MENU_ITEM_INDEX_WORK_VP)
    {
        if (game_state->intelligence >= 250U)
        {
            menu_config->items[MENU_NLI_WORK_ITEM] = MENU_ITEM_INDEX_WORK_CEO;
            menu_config->items[MENU_NLI_PROMOTION_ITEM] = MENU_ITEM_INDEX_EMPTY;
            modify_karma(3);
            main_show_window_text(&win_txt_nli_ceo, ROM_BANK_MENU_CONFIG);
            // Select 'work' item for new job
            move_to_menu_item(1U, 3U, ROM_BANK_MENU_CONFIG);
        }
        else
        {
            // Show unsuccessful message
            main_show_window_text(&win_txt_nli_no_int, ROM_BANK_MENU_CONFIG);
        }
    }
    else
    {
        // If no job available, return early
        return;
    }

    // Reload menu to cover message
    setup_building_menu(1, ROM_BANK_MENU_CONFIG);
}

