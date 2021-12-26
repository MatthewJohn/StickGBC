/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */


#define MENU_MAX_ITEMS_X 2U
#define MENU_MAX_ITEMS_Y 4U

#define MENU_ITEM_WIDTH 6U
#define MENU_ITEM_HEIGHT 2U
#define MENU_ITEM_TILE_COUNT 12U

#define MENU_ITEM_SCREEN_OFFSET_TOP 0x03U
#define MENU_ITEM_SCREEN_OFFSET_LEFT 0x03U
#define MENU_ITEM_MARGIN 0x02U

#define MENU_FONT_COLOR_PALETTE 0x01U

typedef struct {
    // Menu can contain 8 items each with 12 tiles
    unsigned int menu_item_tiles[8][12];
    unsigned char menu_item_palette[8][12];

    unsigned int current_item_x;
    unsigned int current_item_y;
    unsigned int max_items_x;
    unsigned int max_items_y;
    
    unsigned int tile_offset;
} menu_config_t;


