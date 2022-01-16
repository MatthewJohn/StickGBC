/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */

#pragma bank=4

#include "game_constants.h"
#include "sprite.h"
#include "main_map_sprite_tileset.h"
#include "main_map_sprite_palette.h"
#include "main.h"

UINT8 sprite_prop_data;

void setup_sprites(ai_sprite *player_sprite, ai_sprite *skater_sprite, ai_sprite *dealer_sprite, ai_sprite *house_car_sprite, ai_sprite *road_car_sprite)
{
    // Load single sprite tile
    HIDE_SPRITES;

    VBK_REG = 0;

    // Load spirte tile data into VRAM
    set_sprite_data(0U, 13U, mainmapspritetiles);

    // Load sprite palette into VRAM
    set_sprite_palette(0U, 4U, main_map_sprite_palette);

    VBK_REG = 0;

    // Configure sprite to sprite tile
    //  Main player
    set_sprite_tile(player_sprite->sprite_index, player_sprite->sprite_tile);
    //  Skater
    set_sprite_tile(skater_sprite->sprite_index, 0U);

    set_sprite_direction(skater_sprite);

    // Dealer
    set_sprite_tile(dealer_sprite->sprite_index, 0U);

    // Set sprite directions
    set_sprite_direction(dealer_sprite);
    set_sprite_direction(house_car_sprite);
    set_sprite_direction(road_car_sprite);

    SHOW_SPRITES;
}

void set_sprite_direction(ai_sprite *sprite)
{
    UINT8 tile_index_offset;
    UINT8 itx_x;
    UINT8 itx_y;
    UINT8 itx;

    itx = sprite->sprite_index;
    for (itx_x = 0; itx_x != sprite->sprite_count_x; itx_x ++)
    {
        for (itx_y = 0; itx_y != sprite->sprite_count_y; itx_y ++)
        {
            // Update flip of sprite tile
            sprite_prop_data = sprite->color_palette & 0x07U;
            tile_index_offset = sprite->sprite_tile;

            // Check for just vertical movement
            if (sprite->travel_direction_y != 0)
            {
                if (sprite->travel_direction_x == 0)
                {
                    // If travelling up, flip Y
                    if (sprite->travel_direction_y == 1)
                        sprite_prop_data |= S_FLIPY;


                    if (sprite->sprite_count_y == 2U)
                    {
                        // If there are multiple tiles in Y,
                        // for the first row to use 'back' tiles (second set of 3)
                        if (sprite->travel_direction_y == 1)
                            tile_index_offset += ((1 - itx_y) * 3);
                        else
                            tile_index_offset += (itx_y * 3);
                        // If on second row of tiles, flip in X to
                        // make up second half of sprite
                        if (itx_x == 1U)
                            sprite_prop_data |= S_FLIPX;
                    }

                } else {
                    // Handle diagonal movement
                    if (sprite->travel_direction_y == 1)
                        sprite_prop_data |= S_FLIPY;
                    if (sprite->travel_direction_x == -1)
                        sprite_prop_data |= S_FLIPX;
                    tile_index_offset += 2U;
                }
            }
            else if (sprite->travel_direction_x != 0)
            {
                tile_index_offset += 1U;
                if (sprite->travel_direction_x == -1)
                    sprite_prop_data |= S_FLIPX;

                // If there are multiple tiles in X,
                // for the first column to use 'back' tiles (second set of 3)
                if (sprite->sprite_count_x == 2U)
                {
                    if (sprite->travel_direction_x == 1)
                        tile_index_offset += ((1 - itx_x) * 3);
                    else
                        tile_index_offset += (itx_x * 3);
                    // If on second row of tiles, flip in Y to
                    // make up second half of sprite
                    if (itx_y == 1U)
                        sprite_prop_data |= S_FLIPY;
                }
            }
            // Only update flipping if actually moving
            if (sprite->travel_direction_x != 0 || sprite->travel_direction_y != 0)
                set_sprite_prop(sprite->sprite_index, sprite_prop_data);

            set_sprite_tile(itx, tile_index_offset);

            itx += 1U;
        }
    }
}

void move_ai_sprite(screen_state_t* screen_state, ai_sprite* sprite_to_move)
{
    UINT8 itx;
    UINT8 itx_x;
    UINT8 itx_y;

    // Check if sprite should be disabled
    if (! (
        screen_state->displayed_sprites_y[sprite_to_move->sprite_display_bit] &&
        screen_state->displayed_sprites_x[sprite_to_move->sprite_display_bit]
    ))
    {
        // Move sprite off-screen
        itx = sprite_to_move->sprite_index;
        for (itx_x = 0; itx_x != sprite_to_move->sprite_count_x; itx_x ++)
        {
            for (itx_y = 0; itx_y != sprite_to_move->sprite_count_y; itx_y ++)
            {
                move_sprite(itx, 0, 0);
                itx += 1U;
            }
        }
        return;
    }

    if (sprite_to_move->move_speed != 0U && (sys_time % sprite_to_move->move_speed) == 0U)
    {
        if (sprite_to_move->current_pause)
        {
            sprite_to_move->current_pause -= 1U;

            if (sprite_to_move->current_pause == 0U)
                // Check if now at 0 current pause and change direction ready for travel
                set_sprite_direction(sprite_to_move);
        }
        // Check if moving right
        else if (sprite_to_move->travel_direction_x == 1)
        {
            // Check if hit max
            if (sprite_to_move->current_location_x == sprite_to_move->max_location_x)
            {
                // Switch direction and set pause period
                sprite_to_move->travel_direction_x = -1;
                sprite_to_move->current_pause = sprite_to_move->pause_period;
                // Update direction of sprite movement
                set_sprite_direction(sprite_to_move);
            }
            else
                sprite_to_move->current_location_x += 1;
        }
        else if (sprite_to_move->travel_direction_x == -1)
        {
            if (sprite_to_move->current_location_x == sprite_to_move->min_location_x)
            {
                // Switch direction and set pause period
                sprite_to_move->travel_direction_x = 1;
                sprite_to_move->current_pause = sprite_to_move->pause_period;
                // Update direction of sprite
                set_sprite_direction(sprite_to_move);
            }
            else
                sprite_to_move->current_location_x -= 1;
        }
        else if (sprite_to_move->travel_direction_y == 1)
        {
            // Check if hit max
            if (sprite_to_move->current_location_y == sprite_to_move->max_location_y)
            {
                // Switch direction and set pause period
                sprite_to_move->travel_direction_y = -1;
                sprite_to_move->current_pause = sprite_to_move->pause_period;
                // Update direction of sprite movement
                set_sprite_direction(sprite_to_move);
            }
            else
                sprite_to_move->current_location_y += 1;
        }
        else if (sprite_to_move->travel_direction_y == -1)
        {
            if (sprite_to_move->current_location_y == sprite_to_move->min_location_y)
            {
                // Switch direction and set pause period
                sprite_to_move->travel_direction_y = 1;
                sprite_to_move->current_pause = sprite_to_move->pause_period;
                // Update direction of sprite
                set_sprite_direction(sprite_to_move);
            }
            else
                sprite_to_move->current_location_y -= 1;
        }

        set_ai_sprt_scrn_loc(screen_state, sprite_to_move);
    }
    else if (screen_state->screen_has_moved == 1U)
    {
        set_ai_sprt_scrn_loc(screen_state, sprite_to_move);
    }
}

void set_ai_sprt_scrn_loc(screen_state_t* screen_state, ai_sprite* sprite_to_move)
{
    UINT8 itx;
    UINT8 itx_x;
    UINT8 itx_y;

    // Move AI sprites
    // This must always be done, as it is required when the screen moves
    itx = sprite_to_move->sprite_index;
    for (itx_x = 0; itx_x != sprite_to_move->sprite_count_x; itx_x ++)
    {
        for (itx_y = 0; itx_y != sprite_to_move->sprite_count_y; itx_y ++)
        {
            move_sprite(
                itx,
                (sprite_to_move->current_location_x - screen_state->screen_location_x) + SPRITE_OFFSET_X + (itx_x * 8),
                (sprite_to_move->current_location_y - screen_state->screen_location_y) + SPRITE_OFFSET_Y + (itx_y * 8)
            );
            itx += 1U;
        }
    }
}
