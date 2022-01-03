/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */

#pragma bank=5

#include "sprite.h"

void move_ai_sprite(ai_sprite* sprite_to_move) BANKED
{
    // Check if sprite should be disabled
    if (! (
        screen_state.displayed_sprites_y[sprite_to_move->sprite_display_bit] &&
        screen_state.displayed_sprites_x[sprite_to_move->sprite_display_bit]
    ))
    {
        // Move sprite off-screen
        move_sprite(sprite_to_move->sprite_index, 0, 0);
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
    move_sprite(
        sprite_to_move->sprite_index,
        (sprite_to_move->current_location_x - screen_location_x) + SPRITE_OFFSET_X,
        (sprite_to_move->current_location_y - screen_location_y) + SPRITE_OFFSET_Y
    );
}
