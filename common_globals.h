/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */


extern unsigned int user_pos_x;
extern unsigned int user_pos_y;

extern UBYTE tile_data;
extern UBYTE tile_data_meta;

extern unsigned int screen_location_x;
extern unsigned int screen_location_y;
extern unsigned int screen_location_x_tiles;
extern unsigned int screen_location_y_tiles;
extern unsigned int screen_location_x_tilepixel;
extern unsigned int screen_location_y_tilepixel;

extern signed int travel_x;
extern signed int travel_y;
extern unsigned short a_pressed;
extern UINT8 sprite_traveling_x;
extern UINT8 sprite_prop_data;

extern unsigned char *background_tile_map;
extern unsigned char *background_tiles;
extern unsigned char *background_tile_palette;
extern unsigned char *background_color_palette;
extern unsigned int background_width;
extern unsigned char *sprite_tiles;
extern unsigned char *sprite_palette;
extern unsigned int DRAW_OFFSET_X;
extern unsigned int DRAW_OFFSET_Y;
extern unsigned int DRAW_MAX_X;
extern unsigned int DRAW_MAX_Y;

extern unsigned int itx_start;
extern unsigned int itx_end;
extern unsigned int itx;


extern unsigned int itx_x;
extern unsigned int itx_y;
extern UINT8 menu_item_index;
extern unsigned int tile_index;
extern unsigned int tile_data_index;
extern UINT8 tile_itx_x_start;
extern UINT8 tile_itx_y_start;
extern UINT8 tile_itx_x;
extern UINT8 tile_itx_y;
extern UINT8 second_tile_row;
extern unsigned int tile_data_offset;

extern UWORD palette_transfer[4];
