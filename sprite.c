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

void setup_sprites(ai_sprite *player_sprite, ai_sprite *skater_sprite, ai_sprite *dealer_sprite, ai_sprite *house_car_sprite)
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
    set_sprite_tile(player_sprite->sprite_index, player_sprite->sprite_tile);
    //  Skater
    set_sprite_tile(skater_sprite->sprite_index, 0U);

    set_sprite_direction(skater_sprite);

    // Dealer
    set_sprite_tile(dealer_sprite->sprite_index, 0U);

    set_sprite_direction(dealer_sprite);

    itx = house_car_sprite->sprite_index;
    for (itx_x = 0; itx_x != house_car_sprite->sprite_count_x; itx_x ++)
    {
        for (itx_y = 0; itx_y != house_car_sprite->sprite_count_y; itx_y ++)
        {
            set_sprite_tile(itx, house_car_sprite->sprite_tile + itx_y);

            set_sprite_direction(house_car_sprite);

            itx += 1U;
        }
    }

    SHOW_SPRITES;
}

void set_sprite_direction(ai_sprite *sprite)
{
    itx = sprite->sprite_index;
    for (itx_x = 0; itx_x != sprite->sprite_count_x; itx_x ++)
    {
        for (itx_y = 0; itx_y != sprite->sprite_count_y; itx_y ++)
        {
            // Update flip of sprite tile
            sprite_prop_data = sprite->color_palette & 0x07U;

            // Check for just vertical movement
            if (sprite->travel_direction_y != 0)
            {
                if (sprite->travel_direction_x == 0)
                {
                    // If travelling up, flip Y
                    if (sprite->travel_direction_y == 1)
                        sprite_prop_data |= S_FLIPY;
                    set_sprite_tile(itx, 0U + sprite->sprite_tile);
                } else {
                    // Handle diagonal movement
                    if (sprite->travel_direction_y == 1)
                        sprite_prop_data |= S_FLIPY;
                    if (sprite->travel_direction_x == -1)
                        sprite_prop_data |= S_FLIPX;
                    set_sprite_tile(itx, 2U + sprite->sprite_tile);
                }
            }
            else if (sprite->travel_direction_x != 0)
            {
                set_sprite_tile(itx, 1U + sprite->sprite_tile);
                if (sprite->travel_direction_x == -1)
                    sprite_prop_data |= S_FLIPX;
            }
            // Only update flipping if actually moving
            if (sprite->travel_direction_x != 0 || sprite->travel_direction_y != 0)
                set_sprite_prop(sprite->sprite_index, sprite_prop_data);

            itx += 1U;
        }
    }
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
