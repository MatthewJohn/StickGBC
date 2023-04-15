/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */

#pragma bank=7

#include "background_time_colors.h"

const UWORD background_time_colors[25U] = {
    RGB(0, 0, 0),  // 0:00
    RGB(1, 2, 2),
    RGB(2, 4, 4),
    RGB(4, 8, 8),
    RGB(6, 12, 12),
    RGB(8, 16, 16),
    RGB(10, 20, 20),
    RGB(11, 22, 22),  // 7AM
    RGB(12, 26, 24),
    RGB(12, 24, 24),
    RGB(13, 26, 26),
    RGB(13, 26, 26),
    RGB(13, 26, 26),
    RGB(13, 26, 26),  // 1PM
    RGB(13, 26, 26),
    RGB(13, 26, 26),
    RGB(13, 26, 26),
    RGB(12, 24, 24),
    RGB(12, 24, 24),
    RGB(24, 28, 18),
    RGB(29, 31, 11),
    RGB(14, 14, 14),
    RGB(7, 7, 7),
    RGB(3, 3, 3),
    RGB(0, 0, 0),
};
