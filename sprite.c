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

void setup_sprites(ai_sprite *skater_sprite, ai_sprite *dealer_sprite, ai_sprite *house_car_sprite)
{
    // Load single sprite tile
    HIDE_SPRITES;

    VBK_REG = 0;

    // Load spirte tile data into VRAM
    set_sprite_data(0U, 12U, mainmapspritetiles);

    // Load sprite palette into VRAM
    set_sprite_palette(0U, 4U, main_map_sprite_palette);

    VBK_REG = 0;

    // Configure sprite to sprite tile
    //  Main player
    set_sprite_tile(0U, 0U);
    //  Skater
    set_sprite_tile(skater_sprite->sprite_index, 0U);

    set_sprite_direction(
        skater_sprite->sprite_index,
        SPRITE_TILESET_WALK,
        skater_sprite->color_palette,
        skater_sprite->travel_direction_x,
        skater_sprite->travel_direction_y
    );

    // Dealer
    set_sprite_tile(dealer_sprite->sprite_index, 0U);

    set_sprite_direction(
        dealer_sprite->sprite_index,
        SPRITE_TILESET_WALK,
        dealer_sprite->color_palette,
        dealer_sprite->travel_direction_x,
        dealer_sprite->travel_direction_y
    );

    itx = house_car_sprite->sprite_index;
    for (itx_x = 0; itx_x != house_car_sprite->sprite_count_x; itx_x ++)
    {
        for (itx_y = 0; itx_y != house_car_sprite->sprite_count_y; itx_y ++)
        {
            set_sprite_tile(itx, house_car_sprite->sprite_tile + itx_y);

            //set_sprite_direction(
            //    house_car_sprite,
            //    house_car_sprite->sprite_tile + itx_y,
            //    house_car_sprite->color_palette,
            //    skater_sprite->travel_direction_x,
            //    skater_sprite->travel_direction_y
            //);

            itx += 1U;
        }
    }

    SHOW_SPRITES;
}

void set_sprite_direction(UINT8 sprite_index, UINT8 sprite_tileset_index, UINT8 color_palette, INT8 direction_x, INT8 direction_y)
{
    UINT8 sprite_tile_offset = sprite_tileset_index * SPRITE_TILESET_COUNT;
    // Update flip of sprite tile
    sprite_prop_data = color_palette & 0x07U;
    // Check for just vertical movement/
    if (direction_y != 0)
    {
        if (direction_x == 0)
        {
            // If travelling up, flip Y
            if (direction_y == 1)
                sprite_prop_data |= S_FLIPY;
            set_sprite_tile(sprite_index, 0U + sprite_tile_offset);
        } else {
            // Handle diagonal movement
            if (direction_y == 1)
                sprite_prop_data |= S_FLIPY;
            if (direction_x == -1)
                sprite_prop_data |= S_FLIPX;
            set_sprite_tile(sprite_index, 2U + sprite_tile_offset);
        }
    }
    else if (direction_x != 0)
    {
        set_sprite_tile(sprite_index, 1U + sprite_tile_offset);
        if (direction_x == -1)
            sprite_prop_data |= S_FLIPX;
    }
    // Only update flipping if actually moving
    if (direction_x != 0 || direction_y != 0)
        set_sprite_prop(sprite_index, sprite_prop_data);
}

void move_ai_sprite(screen_state_t* screen_state, ai_sprite* sprite_to_move)
{
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

    if ((sys_time % sprite_to_move->move_speed) == 0U)
    {
        if (sprite_to_move->current_pause)
        {
            sprite_to_move->current_pause -= 1U;

            if (sprite_to_move->current_pause == 0U)
                // Check if now at 0 current pause and change direction ready for travel
                set_sprite_direction(
                    sprite_to_move->sprite_index,
                    SPRITE_TILESET_WALK,
                    sprite_to_move->color_palette,
                    sprite_to_move->travel_direction_x,
                    sprite_to_move->travel_direction_y
                );
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
                set_sprite_direction(
                    sprite_to_move->sprite_index,
                    SPRITE_TILESET_WALK,
                    sprite_to_move->color_palette,
                    sprite_to_move->rest_direction_x,
                    sprite_to_move->rest_direction_y
                );
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
                set_sprite_direction(
                    sprite_to_move->sprite_index,
                    SPRITE_TILESET_WALK,
                    sprite_to_move->color_palette,
                    sprite_to_move->rest_direction_x,
                    sprite_to_move->rest_direction_y
                );
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
                set_sprite_direction(
                    sprite_to_move->sprite_index,
                    SPRITE_TILESET_WALK,
                    sprite_to_move->color_palette,
                    sprite_to_move->rest_direction_x,
                    sprite_to_move->rest_direction_y
                );
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
                set_sprite_direction(
                    sprite_to_move->sprite_index,
                    SPRITE_TILESET_WALK,
                    sprite_to_move->color_palette,
                    sprite_to_move->rest_direction_x,
                    sprite_to_move->rest_direction_y
                );
            }
            else
                sprite_to_move->current_location_y -= 1;
        }
    }

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
