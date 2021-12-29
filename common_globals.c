/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */


// Location of user in world.
// This is not the sprites position on the screen
unsigned int user_pos_x;
unsigned int user_pos_y;

// Temporary storage for transfer of tile data and tile data vram1 data
UBYTE tile_data;
UBYTE tile_data_meta;

// Location of screen compared to map
unsigned int screen_location_x;
unsigned int screen_location_y;
// These are pre-calculated bit shifts of screen_location.
// DO NOT manually change outside of position updating method.
// This is the current user position in tiles.
unsigned short screen_location_x_tiles;
unsigned short screen_location_y_tiles;
// These are pre-calculated ANDs of screen_location
// DO NOT  manually change outside of position updating method.
// This is the current pixel location of user within current tile.
unsigned short screen_location_x_tilepixel;
unsigned short screen_location_y_tilepixel;

// Determine which way user needs to travel
signed short travel_x;
signed short travel_y;
unsigned short a_pressed;
UINT8 sprite_traveling_x;
UINT8 sprite_prop_data;

// Globals used when redrawing map
unsigned char *background_tile_map;
unsigned char *background_tiles;
unsigned char *background_tile_palette;
unsigned char *background_color_palette;
unsigned int background_width;
unsigned char *sprite_tiles;
unsigned char *sprite_palette;
unsigned int DRAW_OFFSET_X;
unsigned int DRAW_OFFSET_Y;
unsigned int DRAW_MAX_X;
unsigned int DRAW_MAX_Y;

// General iterators
unsigned int itx_start;
unsigned int itx_end;
unsigned int itx;


// Bunch of variables from load_menu_tiles.
// This fixed a compiler error, which gave no
// indication of issue and no resources online.
unsigned int itx_x;
unsigned int itx_y;
UINT8 menu_item_index;
unsigned int tile_index;
unsigned int tile_data_index;
UINT8 tile_itx_x_start;
UINT8 tile_itx_y_start;
UINT8 tile_itx_x;
UINT8 tile_itx_y;
UINT8 second_tile_row;
unsigned int tile_data_offset;


UWORD palette_transfer[4];
