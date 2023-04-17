/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */

#pragma bank=4

#include "main.h"
#include "window.h"
#include "window_text_data.h"

/*
 * process_casino_menu
 *
 * Process menu selection for casino
 */
void process_casino_menu()
{
    if (menu_state.current_item_x == 0U)
    {
        if (menu_state.current_item_y == 0U)  // Slots
        {
            // Unavailable
            main_show_window_text(&win_txt_general_unimplemented, ROM_BANK_CASINO);
        }
        else if (menu_state.current_item_y == 1U)  // Blackjack
        {
            // Unavailable
            main_show_window_text(&win_txt_general_unimplemented, ROM_BANK_CASINO);
        }
        else if (menu_state.current_item_y == 2U)  // Roulette
        {
            // Unavailable
            main_show_window_text(&win_txt_general_unimplemented, ROM_BANK_CASINO);
        }
    }
    setup_building_menu(2U, ROM_BANK_CASINO);
    move_to_menu_item(1U, 0U, ROM_BANK_CASINO);
}
