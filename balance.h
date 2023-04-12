/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */


#include "gb.h"

BOOLEAN has_money(UINT16 amount_h, UINT16 amount_l);
BOOLEAN remove_money(UINT16 amount_h, UINT16 amount_l);
void add_money(UINT16 amount_h, UINT16 amount_l);