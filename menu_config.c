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

#define MENU_ITEM_DEFAULT_PALETTE 0x01U
#define MENU_ITEM_SELECTED_PALETTE 0x02U
#define MENU_ITEM_COST_PALETTE 0x03U
#define MENU_ITEM_HP_PALETTE 0x04U
#define MENU_ITEM_STRENGTH_PALETTE 0x05U
#define MENU_ITEM_INTELLIGENCE_PALETTE 0x06U

typedef struct {
    // Menu can contain 8 items each with 12 tiles
    unsigned int menu_item_tiles[8][12];
    unsigned char menu_item_palette[8][12];

    unsigned int current_item_x;
    unsigned int current_item_y;
    // Bit mask of menu items. Lower nibble is left column (x = 0), upper nibble is right (x = 1)
    UINT8 menu_items;
    
    unsigned int tile_offset;
} menu_config_t;

// Define global instance of menu config
menu_config_t menu_config;
