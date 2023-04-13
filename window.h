/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */


UINT8 show_number(UINT8 start_x, UINT8 start_y, UINT8 max_digits, unsigned int value);
void show_signed_number(UINT8 start_x, UINT8 start_y, UINT8 max_digits, INT8 value);
UINT8 update_window();
void setup_window();
void show_balance(UINT8 itx_x, UINT8 itx_y);
