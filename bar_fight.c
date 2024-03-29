/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */

#pragma bank=2

#include "bar_fight_map.h"
#include "bar_fight_tiles.h"
#include "bar_fight_palette.h"
#include "game_constants.h"
#include "window_text_data.h"
#include "bar_fight.h"
#include "main.h"
#include "balance.h"

#define BAR_FIGHT_TILE_SCRATCH 68U
#define BAR_FIGHT_NUMERIC_TILE_START 63U


// Update selected action on screen
void bf_update_selected_item(bar_fight_state_t* bar_fight_state, UINT8 new_x, UINT8 new_y, BOOLEAN hide_active)
{
    UINT8 itx_action_x;
    UINT8 itx_action_y;
    UINT8 itx_tile_x;
    UINT8 itx_tile_y;
    unsigned char original_data;
    // Reset palette on all actions

    // Iterate through actions
    VBK_REG = 1;
    for (itx_action_x = 0; itx_action_x != 3; itx_action_x ++)
    {
        for (itx_action_y = 0; itx_action_y != 2; itx_action_y ++)
        {
            // Iterate through tiles in x
            for (itx_tile_x = 0; itx_tile_x != 4; itx_tile_x ++)
            {
                for (itx_tile_y = 0; itx_tile_y != 2; itx_tile_y ++)
                {
                    get_bkg_tiles(2U + (itx_action_x * 6U) + itx_tile_x, 11U + (itx_action_y * 3U) + itx_tile_y, 1U, 1U, &original_data);
                    // Set color palette to 0
                    original_data &= 0xF8;
                    set_bkg_tiles(2U + (itx_action_x * 6U) + itx_tile_x, 11U + (itx_action_y * 3U) + itx_tile_y, 1U, 1U, &original_data);
                }
            }
        }
    }

    if (hide_active == 0U)
    {
        // Set palette of active action
        for (itx_tile_x = 0; itx_tile_x != 4; itx_tile_x ++)
        {
            for (itx_tile_y = 0; itx_tile_y != 2; itx_tile_y ++)
            {
                get_bkg_tiles(2U + (new_x * 6U) + itx_tile_x, 11U + (new_y * 3U) + itx_tile_y, 1U, 1U, &original_data);
                // Set color palette to 1
                original_data &= 0xF8;
                original_data += 1U;
                set_bkg_tiles(2U + (new_x * 6U) + itx_tile_x, 11U + (new_y * 3U) + itx_tile_y, 1U, 1U, &original_data);
            }
        }
    }
    VBK_REG = 0;

    // Update bar fight state active tile to new tile
    bar_fight_state->selected_menu_item_x = new_x;
    bar_fight_state->selected_menu_item_y = new_y;
}

/*
 *  bar_fight_write_digit_to_screen
 */
void bf_wrt_dgt_to_scr(UINT8 tile_x, UINT8 tile_y, UINT8 source_tile_offset, UINT8 source_data_mask, UINT8 destination_data_mask, unsigned char* tile_to_insert, UINT8 add_underscore, UINT16 current_map_index)
{
    UINT8 byte_itx2;
    UINT16 source_tile_index;
    unsigned char map_reference_data;
    UINT8 number_data;

    // Iterate through each line, copying the byte to the tile data to insert.
    for (byte_itx2 = 0; byte_itx2 < 16U; byte_itx2 ++)
    {
        source_tile_index = BAR_FIGHT_NUMERIC_TILE_START + source_tile_offset;
        source_tile_index = source_tile_index << 4;
        source_tile_index += byte_itx2;
        // Remove the currently character side of destination data
        number_data = barfighttiles[source_tile_index] & source_data_mask;

        // Bit shift part of source tile data to match mask of destination tile number position,
        // pushing number to the right or left to match the destination location
        if (source_data_mask != destination_data_mask)
        {
            if (source_data_mask == 0xF0U)
            {
                number_data = number_data >> 4;
            }
            else
            {
                number_data = number_data << 4;
            }
        }
        if (byte_itx2 == 14U && add_underscore == 1U)
        {
            // Set entire row to black if underscoring and on final line
            tile_to_insert[byte_itx2] = 0xFFU;
        }
        else
        {
            // Combine previous tile data with new tile data
            tile_to_insert[byte_itx2] = tile_to_insert[byte_itx2] | number_data;
        }
    }

    set_bkg_data(current_map_index, 1U, tile_to_insert);

    // Create map data for tile
    map_reference_data = current_map_index;

    set_bkg_tiles(tile_x, tile_y, 1, 1, &map_reference_data);
    VBK_REG = 1;
    // Bank 0, not flipped and no priority flag
    map_reference_data = 0U;
    set_bkg_tiles(tile_x, tile_y, 1, 1, &map_reference_data);
    VBK_REG = 0;
}

/*
 * add_number
 *
 * Draw a number to the screen, combining number tiles to provide 2 numbers per tile
 * Add optional underscoring for placement of numbers in action box
 *
 * @param current_map_index The current tile index to create tile to
 * @param tile_x rightmost X coordinate for tile placement on map. Numbers are drawn to the left
 * @param tile_y Y coordinate for tile placement on map
 * @param number Number to br drawn to screen
 * @param secondary_number Number to be drawn before a forward slash
 * @param use_secondary Whether secondary number should be shown
 * @param add_underscore Whether to add bottom line to fill in action box
 * @param rewrite_count Number of tiles to optionally rewrite if text doesn't use all of the tiles
 *
 * @returns The highest tile index that was used to write to.
 */
UINT8 bf_add_number(UINT8 current_map_index, UINT8 tile_x, UINT8 tile_y, UINT16 number, UINT16 secondary_number, BOOLEAN use_secondary, UINT8 add_underscore, UINT8 rewrite_count)
{
    // Process state - 0 not run, 1 performing first number, 2 drawing forward slash, 3 drawing secondary number
    UINT8 process_state;
    UINT16 overflow;
    UINT8 remainder;
    unsigned char tile_to_insert[16U];
    UINT8 source_tile_offset;
    UINT8 source_data_mask;
    UINT8 destination_data_mask;
    UINT8 byte_itx;
    UINT8 tile_count;
    unsigned char map_reference_data;

    // Blank out tile_to_insert array
    for (byte_itx = 0; byte_itx < 16U; byte_itx ++)
    {
      tile_to_insert[byte_itx] = 0U;
    }
    destination_data_mask = 0x0FU;

    process_state = 0;

    tile_count = 1;
    overflow = number;

    while (1) {
        // If overflow is empty, there will not be a number
        // to process. Ignore if not yet processed any numbers
        // so that  0 can be drawn.
        if (overflow == 0U && process_state != 0) {
            // If there's a secondary number, move state to drawing
            // forward slash
            if (process_state == 1 && use_secondary == 1U)
            {
                process_state = 2;
            }
            // If forward slash has been draw, move to drawing
            // secondary number
            else if (process_state == 2)
            {
                overflow = secondary_number;
                process_state = 3;
            }
            else
            {
                break;
            }
        }

        // Move from initial state to processing first number
        if (process_state == 0)
        {
            process_state = 1;
        }
        remainder = (overflow & 0xFFU) % 10U;
        overflow = overflow / 10U;

        // Each source tile contains 2 numbers,
        // so source tile is tile main offset with an offset of number to use / 2
        source_tile_offset = remainder / 2U;
        // Each line in tile is made of 2 chars, meaing each line of a number is 1 byte.
        // Offset for first number (0, 2, etc.) is 0 (start of tile) and odd numbers are on the right
        // hand side, so each line offset is 1
        if (remainder % 2U == 0U)
        {
            source_data_mask = 0xF0U;
        }
        else
        {
            source_data_mask = 0x0FU;
        }

        // If process state is 2 (drawing forward slash), set source data mask and offset for it
        if (process_state == 2)
        {
            source_tile_offset = 5;
            source_data_mask = 0xF0;
        }
        bf_wrt_dgt_to_scr(tile_x, tile_y, source_tile_offset, source_data_mask, destination_data_mask, &tile_to_insert, add_underscore, current_map_index);

        // Flip the destination file offset on each number
        if (destination_data_mask == 0x0FU)
        {
            destination_data_mask = 0xF0U;
        }
        else
        {
            // If going abck to first digit, blank the tile data
            destination_data_mask = 0x0FU;
            // Reset file data
            for (byte_itx = 0; byte_itx < 16U; byte_itx ++)
            {
              tile_to_insert[byte_itx] = 0U;
            }

            // Increment map index for next tile
            current_map_index += 1;
            tile_count ++;

            // Move x position 1 to left to draw next tile
            tile_x -= 1;
        }
    }

    // Prepare for blanking tiles,
    // if on first digit, move to next x tile to blank
    // (known becuase the mask has been flipped in preparation
    // for second digit)
    if (destination_data_mask == 0xF0U)
    {
        tile_x -= 1;
        tile_count ++;
    }
    // Blank out any tiles that are left over
    while (tile_count <= rewrite_count)
    {
        // Create map data for tile
        map_reference_data = 0;

        set_bkg_tiles(tile_x, tile_y, 1, 1, &map_reference_data);

        tile_count ++;
        tile_x -= 1;
    }

    return current_map_index;
}

/*
 * bf_draw_player_health
 *
 * Show player health
 */
void bf_draw_player_health()
{
    // Show player health
    bf_add_number(72U, 17U, 9U, game_state.max_hp, game_state.hp, 1U, 0U, 4U);
}

/*
 * bf_draw_enemy_health
 *
 * Show enemy health
 */
void bf_draw_enemy_health(bar_fight_state_t* bar_fight_state)
{
    bf_add_number(76U, 6U, 1U, bar_fight_state->enemy_max_hp, bar_fight_state->enemy_hp, 1U, 0U, 4U);
}

void bf_update_text(bar_fight_state_t* bar_fight_state)
{
    // Add points for actions
    // punch
    bf_add_number(68U, 4U, 12U, 1U, 0U, 0U, 1U, 0U);
    // Kick
    bf_add_number(69U, 4U, 15U, 2U, 0U, 0U, 1U, 0U);
    // Fireball
    bf_add_number(70U, 10U, 12U, 3U, 0U, 0U, 1U, 0U);
    // Energy
    bf_add_number(71U, 10U, 15U, 4U, 0U, 0U, 1U, 0U);

    // Update selected tile palette without changing the selected action
    bf_update_selected_item(bar_fight_state, bar_fight_state->selected_menu_item_x, bar_fight_state->selected_menu_item_y, 0U);

    bf_draw_player_health();
    bf_draw_enemy_health(bar_fight_state);
}

/*
 * bf_load_basic_map
 *
 * Update base tiles/map/text on initial load or after drawing text
 */
void bf_load_basic_map(bar_fight_state_t* bar_fight_state)
{
    set_background_tiles(
        ROM_BANK_BAR_FIGHT,
        ROM_BANK_BAR_FIGHT,
        ROM_BANK_BAR_FIGHT,  // Load tiles from this ROM bank
        ROM_BANK_BAR_FIGHT  // Return to the ROM bank for this function
    );

    bf_update_text(bar_fight_state);
}

/*
 * bf_damage_effect
 *
 * Show screen effect being attacked
 */
void bf_damage_effect()
{
    UINT8 itx;
    UINT8 x;
    INT8 direction;
    for (itx = 0; itx < 2; itx ++)
    {
        direction = 1;
        for (x = 0; x != 12; x++)
        {
            if (x == 3)
            {
                direction = -1;
            }
            else if (x == 9)
            {
                direction = 1;
            }
            scroll_bkg(direction, 0);
            wait_vbl_done();
        }
    }
}

/*
 * bf_attack_effect
 *
 * Show screen effect when attacking
 */
void bf_attack_effect()
{
    UINT8 itx;
    UWORD palette_data[4];
    UWORD red;

    red = 0x001FU;

    for (itx = 0; itx < 8; itx ++)
    {
        // Copy palette 1
        palette_data[0U] = bar_fight_palette[0U],
        palette_data[1U] = bar_fight_palette[1U];
        // Set 3rd color to either red or black to switch enemy color
        palette_data[2U] = red;
        palette_data[3U] = bar_fight_palette[3U];

        set_bkg_palette(0U, 1U, &palette_data);
        wait_vbl_done();
        delay(200);

        if (red == 0x001FU)
        {
            red = 0U;
        }
        else
        {
            red = 0x001FU;
        }
    }
}

/*
 * bf_hide_enemy
 *
 * Fade enemy for defeat sequence
 */
void bf_hide_enemy()
{
    UINT8 itx;
    UWORD palette_data[4];
    UWORD color;

    // Delay before animation
    delay(500);

    // Set color to black
    color = 0x0000U;

    for (itx = 0; itx < 5; itx ++)
    {
        switch (color)
        {
            case 0x0000U:
                color = 0x0421;
                break;
            case 0x0421:
                color = 0x0C63;
                break;
            case 0x0C63:
                color = 0x1CE7;
                break;
            case 0x1CE7:
                color = 0x3DEF;
                break;
            case 0x3DEF:
                color = 0x7FFFU;
                break;
        }
        // Copy palette 1
        palette_data[0U] = bar_fight_palette[0U],
        palette_data[1U] = bar_fight_palette[1U];
        // Set 3rd color to fading black
        palette_data[2U] = color;
        palette_data[3U] = bar_fight_palette[3U];

        set_bkg_palette(0U, 1U, &palette_data);
        wait_vbl_done();
        // Delay animation speed
        delay(300);
    }
}

void bf_perform_enemy_attack(bar_fight_state_t* bar_fight_state)
{
    UINT16 enemy_attack_mode;
    UINT16 enemy_attack_points;

    bf_damage_effect();

    enemy_attack_mode = (sys_time % game_state.strength) + 1U;
    if (enemy_attack_mode > 40U)
    {
        enemy_attack_points = sys_time % (game_state.strength / 2);
    }
    else if (enemy_attack_mode > 20U)
    {
        enemy_attack_points = sys_time % (game_state.strength / 3);
    }
    else if (enemy_attack_mode > 10U)
    {
        enemy_attack_points = sys_time % (game_state.strength / 5);
    }
    else
    {
        enemy_attack_points = (sys_time % (game_state.strength / 10)) + 1;
    }

    // If player is killed, set game HP and set minigame to end
    if (game_state.hp < enemy_attack_points || game_state.hp == enemy_attack_points)
    {
        game_state.hp = 0U;
        bar_fight_state->in_game = 0U;
        bf_draw_player_health();

        // Show end game
        main_check_end_game(ROM_BANK_BAR_FIGHT);
        return;
    }
    else
    {
        game_state.hp -= enemy_attack_points;
    }
    bf_draw_player_health();
}

void bf_do_damage(bar_fight_state_t* bar_fight_state, UINT8 attack_type)
{
    UINT16 damage_amount;
    UINT16 amount_won;

    // Hide selected action
    bf_update_selected_item(bar_fight_state, bar_fight_state->selected_menu_item_x, bar_fight_state->selected_menu_item_y, 1U);

    if (attack_type == 0U)
    {
        damage_amount = 0U;
    }
    // Punch attack
    else if (attack_type == 1U)
    {
        if (bar_fight_state->attack_points < 1U)
        {
            main_show_window_text(&win_txt_barfight_noattckpnts, ROM_BANK_BAR_FIGHT);
            bf_load_basic_map(bar_fight_state);
            return;
        }
        damage_amount = (sys_time % ((game_state.strength + 10) / 10)) + (game_state.inventory[S_INVENTORY_KNIFE] * 2);
    }
    // Kick attack
    else if (attack_type == 2U)
    {
        if (bar_fight_state->attack_points < 2U)
        {
            main_show_window_text(&win_txt_barfight_noattckpnts, ROM_BANK_BAR_FIGHT);
            bf_load_basic_map(bar_fight_state);
            return;
        }
        damage_amount = (sys_time % (game_state.strength / 4)) + (game_state.inventory[S_INVENTORY_KNIFE] * 2);
    }
    // Fireball attack
    else if (attack_type == 3U)
    {
        if (bar_fight_state->attack_points < 3U)
        {
            main_show_window_text(&win_txt_barfight_noattckpnts, ROM_BANK_BAR_FIGHT);
            bf_load_basic_map(bar_fight_state);
            return;
        }
        damage_amount = (sys_time % (game_state.strength / 2));
    }
    // Energy attack
    else if (attack_type == 4U)
    {
        if (bar_fight_state->attack_points < 4U)
        {
            main_show_window_text(&win_txt_barfight_noattckpnts, ROM_BANK_BAR_FIGHT);
            bf_load_basic_map(bar_fight_state);
            return;
        }
        damage_amount = (sys_time % game_state.strength);
    }

    // Skip minimum amount check and attack style, if done (skipped)
    if (attack_type != 0U)
    {
        if (damage_amount == 0U)
        {
            damage_amount = 1U;
        }

        // Show attack animation
        bf_attack_effect();
    }

    // If enemy will still have HP remaining,
    // update the value
    if ((bar_fight_state->enemy_hp - damage_amount) > bar_fight_state->enemy_hp || bar_fight_state->enemy_hp == damage_amount)
    {
        // Otherwise, set HP to 0 and end game
        bar_fight_state->enemy_hp = 0U;
        // Update HP on screen
        bf_draw_enemy_health(bar_fight_state);

        // Hide enemy
        bf_hide_enemy();

        // Increase strength and show initial win text
        main_increase_strength(0U, 0U, 7U, ROM_BANK_BAR_FIGHT);
        main_show_window_text(&win_txt_barfight_win, ROM_BANK_BAR_FIGHT);

        // Calculate win amount and add to balance
        amount_won = (sys_time % (game_state.bar_fight_count * 5)) + (game_state.bar_fight_count * 5);
        main_show_number(9, 0, 4, (unsigned int)amount_won, ROM_BANK_BAR_FIGHT);

        // Show win amount
        add_money(0U, amount_won);
        main_show_window_text(&win_txt_barfight_win2, ROM_BANK_BAR_FIGHT);

        // Redraw map after any window text
        bf_load_basic_map(bar_fight_state);

        // Exit mini game
        bar_fight_state->in_game = 0U;
        return;
    }

    bar_fight_state->enemy_hp -= damage_amount;
    bf_draw_enemy_health(bar_fight_state);

    // Perform enemy attack
    delay(1000);
    bf_perform_enemy_attack(bar_fight_state);

    // Re-activate selected action
    bf_update_selected_item(bar_fight_state, bar_fight_state->selected_menu_item_x, bar_fight_state->selected_menu_item_y, 0U);
}

void bf_update_state(bar_fight_state_t* bar_fight_state)
{
    UINT8 new_menu_item_x = bar_fight_state->selected_menu_item_x;
    UINT8 new_menu_item_y = bar_fight_state->selected_menu_item_y;

    if (joypad_state.travel_x != 0 || joypad_state.travel_y != 0)
    {
        // Limit to max x/y menu items and, if not reached, update value
        if (!(bar_fight_state->selected_menu_item_x == 0 && joypad_state.travel_x == -1) &&
            !(bar_fight_state->selected_menu_item_x == 2 && joypad_state.travel_x == 1))
        {
            new_menu_item_x += joypad_state.travel_x;
        }
        if (!(bar_fight_state->selected_menu_item_y == 0 && joypad_state.travel_y == -1) &&
            !(bar_fight_state->selected_menu_item_y == 1 && joypad_state.travel_y == 1))
        {
            new_menu_item_y += joypad_state.travel_y;
        }
        // Update selected item
        bf_update_selected_item(bar_fight_state, new_menu_item_x, new_menu_item_y, 0U);

        // Sleep to stop double pressed
        delay(DELAY_MENU_ITEM_MOVE);
    }
    else if (joypad_state.a_pressed)
    {
        if (bar_fight_state->selected_menu_item_y == 0U)
        {
            // Punch
            if (bar_fight_state->selected_menu_item_x == 0U)
            {
                bf_do_damage(bar_fight_state, 1U);
            }
            // Fireball
            else if (bar_fight_state->selected_menu_item_x == 1U)
            {
                bf_do_damage(bar_fight_state, 3U);
            }
            // Done (Skip)
            else if (bar_fight_state->selected_menu_item_x == 2U)
            {
                bf_do_damage(bar_fight_state, 0U);
            }
        }
        else if (bar_fight_state->selected_menu_item_y == 1U)
        {
            // Kick
            if (bar_fight_state->selected_menu_item_x == 0U)
            {
                bf_do_damage(bar_fight_state, 2U);
            }
            // Energy
            else if (bar_fight_state->selected_menu_item_x == 1U)
            {
                bf_do_damage(bar_fight_state, 4U);
            }
            // Check for run away
            else if (bar_fight_state->selected_menu_item_x == 2U)
            {
                bar_fight_state->in_game = 0U;
            }
        }
        delay(DELAY_MENU_ITEM_MOVE);
    }
}

void bf_reset_attack_points(bar_fight_state_t* bar_fight_state)
{
    bar_fight_state->attack_points = (game_state.strength / 20U) + 1U;
    if (bar_fight_state->attack_points > 20U)
    {
        bar_fight_state->attack_points = 20U;
    }
}

void enter_bar_fight()
{
    bar_fight_state_t bar_fight_state;

    if (game_state.hour > 21U)
    {
        return;
    }
    game_state.hour += 3U;

    game_state.karma -= 2U;
    game_state.bar_fight_count ++;

    // Setup minigame state
    bar_fight_state.enemy_max_hp = (sys_time % (game_state.bar_fight_count * 5)) + (game_state.bar_fight_count * 5);
    bar_fight_state.enemy_hp = bar_fight_state.enemy_max_hp;
    bar_fight_state.in_game = 1U;
    bar_fight_state.selected_menu_item_x = 0;
    bar_fight_state.selected_menu_item_y = 0;

    bf_reset_attack_points(&bar_fight_state);


    DISPLAY_OFF;

    // Hide sprites
    HIDE_SPRITES;

    // Hide Window
    HIDE_WIN;

    screen_state.background_color_palette = bar_fight_palette;
    screen_state.background_tile_map = barfightmap;
    screen_state.background_tiles = barfighttiles;
    screen_state.background_width = barfightmapWidth;

    screen_state.draw_offset_x = 0U;
    screen_state.draw_offset_y = 0U;
    screen_state.draw_max_x = SCREEN_WIDTH_TILES;
    screen_state.draw_max_y = SCREEN_HEIGHT_TILES;

    bf_load_basic_map(&bar_fight_state);

    // Move background to top left
    move_bkg(0, 0);

    // Load additional tiles required
    set_bkg_data(8U, 60U, &(barfighttiles[8U << 4]));

    DISPLAY_ON;

    main_check_joy(ROM_BANK_BAR_FIGHT);

    while (bar_fight_state.in_game == 1U)
    {
        main_check_joy(ROM_BANK_BAR_FIGHT);

        bf_update_state(&bar_fight_state);

        wait_vbl_done();
    }

    // Reset window before exiting
    main_update_window(ROM_BANK_BAR_FIGHT);

    // Show Window
    SHOW_WIN;
}
