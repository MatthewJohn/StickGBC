/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */


#ifndef GAME_CONSTANTS_DEF
#define GAME_CONSTANTS_DEF 1

// Debug definitions
#define DEBUG_JUMP_BUILDING 0
#define DEBUG_JUMP_BUILDING_NUMBER 2
#define DEBUG_BOUNDARIES 0
#define DEBUG_DISABLE_AI_MOVEMENT 0
#define DEBUG_IGNORE_BOUNDARIES 0
#define DEBUG_SET_BACKGROUND_SKIP 0
#define DEBUG_SHOW_BAR_FIGHT 0

// Delays and timings
#define PURCHASE_ITEM_WAIT 0x28  // Wait 30 frames
#define DELAY_SLEEP 1000U
#define DELAY_MENU_ITEM_MOVE 300U

// Get tile pixel within from map-coordinates
#define TO_SUBTILE_PIXEL(location) (location & 0x0FU)
#define PIXEL_LOCATION_TO_TILE_COUNT(location) (location >> 3)
#define X_Y_TO_TILE_INDEX(x, y) ((y * mainmapWidth) + x)
#define TILE_INDEX_BIT_MAP_VALUE(mapping, tile_index) mapping[tile_index >> 3] & (1 << (tile_index & 0x07U))

#define WINDOW_MAX_DIGITS_DAYS 5U
#define WINDOW_VERTICAL_DRAW_OFFSET 0x09U
#define WINDOW_MAX_DIGITS_BALANCE 11U
#define WINDOW_MAX_DIGITS_HP 0x5U
#define BALANCE_BIT_LENGTH 32U

#define MENU_ROW_2_TILE_DATA_OFFSET 0x60U

// Screen size 160x144
#define SCREEN_WIDTH 0xA0U
#define SCREEN_HEIGHT 0x90U

#define SCREEN_TILE_MAX_X 0x13U
#define SCREEN_TILE_MAX_Y 0x11U
#define SCREEN_WIDTH_TILES 0x14U
#define SCREEN_HEIGHT_TILES 0x12U

// Manually calculated by putting sprite into corner of screen and setting until middle
// of character is at 0,0 location
#define SPRITE_OFFSET_X 0x04U
#define SPRITE_OFFSET_Y 0x0dU
#define PLAYER_SPRITE_INDEX 0x00U
#define PLAYER_SPRITE_PALETTE 0x00U
// First tileset is for walking
#define SPRITE_TILESET_WALK 0x00U
// Second tileset is for skateboarding
#define SPRITE_TILESET_SKATEBOARD 0x03U
// Tileset for hurt player
#define SPRITE_TILESET_HURT 0x06U

// Sprite palette index for car
#define CAR_SPRITE_PALETTE_INDEX 0x3U

#define WALK_SPEED_DELAY 0x01U
#define SKATEBOARD_SPEED_DELAY 0x00U

#define CHARACTER_SCREEN_LOCATION_MARGIN 0x18U

// Max address if 0x1F, set to 0x20 for loops that loop whilst
// less than the value (or rather !=)
#define BACKGROUND_BUFFER_SIZE_X 0x20U
#define BACKGROUND_BUFFER_SIZE_Y 0x20U
#define BACKGROUND_BUFFER_MAX_X 0x1FU
#define BACKGROUND_BUFFER_MAX_Y 0x1FU
#define BACKGROUND_BUFFER_SIZE_PIXELS_MAX_X 0xFFU
#define BACKGROUND_BUFFER_SIZE_PIXELS_MAX_Y 0xFFU
#define BACKGROUND_BUFFER_SIZE_PIXELS_X 0x100U
#define BACKGROUND_BUFFER_SIZE_PIXELS_Y 0x100U

#define VRAME_SIZE_TILES_X_MASK 0x1FU
#define VRAME_SIZE_TILES_Y_MASK 0x1FU
// From screen left-top-hand position to half way through unused vram
// x - ( 0x20U (vram width in tiles) - 0x14U (screen width in tiles) / 2) + 0x14U (screen width in tiles)
#define REDRAW_VRAM_OFFSET_X 0x1AU
#define REDRAW_VRAM_OFFSET_Y 0x1AU

#define PALETTE_COLOURS_PER_PALETTE 4U
#define TILE_PATTERN_INDEX_TO_ARRAY_INDEX(index) (index << 4)
#define TILE_PATTERN_SCRATCH_1 0x05U
#define TILE_PATTERN_SCRATCH_2 0x06U
#define TILE_PATTERN_SCRATCH_3 0x07U
#define PALETTE_SCRATCH_0 0x04U
#define PALETTE_SCRATCH_1 0x05U
#define PALETTE_SCRATCH_2 0x06U
#define PALETTE_SCRATCH_3 0x07U

#define MAP_EDGE_LEFT 0x03U
#define MAP_EDGE_RIGHT 0x43U
#define MAP_EDGE_TOP 0x03U
#define MAP_EDGE_BOTTOM 0x36U
