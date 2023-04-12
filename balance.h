/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */


#include "gb.h"

BOOLEAN has_money(unsigned int amount_h, unsigned int amount_l);
BOOLEAN remove_money(unsigned int amount_h, unsigned int amount_l);
void add_money(unsigned int amount_h, unsigned int amount_l);