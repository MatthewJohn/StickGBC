/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */


#define MENU_MAX_ITEMS_X 2U
#define MENU_MAX_ITEMS_Y 4U

#define MENU_ITEM_WIDTH 7U
#define MENU_ITEM_HEIGHT 2U
#define MENU_ITEM_TILE_COUNT 14U

#define MENU_ITEM_SCREEN_OFFSET_TOP 0x03U
#define MENU_ITEM_SCREEN_OFFSET_LEFT 0x03U
#define MENU_ITEM_MARGIN 0x01U

#define MENU_FONT_COLOR_PALETTE 0x02U

typedef struct {
    // Menu can contain 8 items each with 14 tiles
    unsigned char menu_item_tiles[8][14];
    unsigned char menu_item_palette[8][14];

    unsigned short current_item_x;
    unsigned short current_item_y;
    unsigned short max_items_x;
    unsigned short max_items_y;
    
    unsigned int tile_offset;
} menu_config_t;


