/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */



# ifndef MENU_CONFIG_DEF
#define MENU_CONFIG_DEF 1

#define MENU_MAX_ITEMS_X 2U
#define MENU_MAX_ITEMS_Y 4U

#define MENU_ITEM_WIDTH 6U
#define MENU_ITEM_HEIGHT 2U
#define MENU_ITEM_TILE_COUNT 12U
#define MENU_ROW_2_TILE_DATA_OFFSET 0x6DU

#define MENU_ITEM_SCREEN_OFFSET_TOP 0x03U
#define MENU_ITEM_SCREEN_OFFSET_LEFT 0x03U
#define MENU_ITEM_MARGIN 0x02U

#define MENU_ITEM_NO_TILE 0x00U
#define MENU_BLANK_ITEM_ROW MENU_ITEM_NO_TILE, MENU_ITEM_NO_TILE, MENU_ITEM_NO_TILE, MENU_ITEM_NO_TILE, MENU_ITEM_NO_TILE, MENU_ITEM_NO_TILE
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
    // Menu can contain 8 items each with 12 tiles
    unsigned int menu_item_tiles[8][12];
    unsigned char menu_item_palette[8][12];

    // Bit mask of menu items. Lower nibble is left column (x = 0), upper nibble is right (x = 1)
    UINT8 menu_items;
    
    unsigned int tile_offset;
} menu_config_t;

typedef struct {
    unsigned int current_item_x;
    unsigned int current_item_y;
} menu_state_t;

// Define global instance of menu config
menu_config_t *menu_config;

menu_state_t menu_state;


// BUILDING MENU DEFINITIONS

// HOUSE
static const menu_config_t menu_config_house = {
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
static const menu_config_t menu_config_restaurant = {
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


