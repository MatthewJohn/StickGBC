/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */


#ifndef COMMON_GLOBALS_DEF
#define COMMON_GLOBALS_DEF

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
unsigned int screen_location_x_tiles;
unsigned int screen_location_y_tiles;
// These are pre-calculated ANDs of screen_location
// DO NOT  manually change outside of position updating method.
// This is the current pixel location of user within current tile.
unsigned int screen_location_x_tilepixel;
unsigned int screen_location_y_tilepixel;

// Determine which way user needs to travel
signed int travel_x;
signed int travel_y;
unsigned short a_pressed;
UINT8 sprite_traveling_x;
UINT8 sprite_prop_data;



#endif