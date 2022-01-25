/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */


#ifndef WINDOW_TEXT_DEF
#define WINDOW_TEXT_DEF

#include "gb.h"
#include "main.h"
#include "window_text_data.h"
#include "window_text_tiles.h"

#define WINDOW_TEXT_CHAR_SPACE 0x00U
#define WINDOW_TEXT_CHAR_0 0x01U
#define WINDOW_TEXT_CHAR_1 0x02U
#define WINDOW_TEXT_CHAR_2 0x03U
#define WINDOW_TEXT_CHAR_3 0x04U
#define WINDOW_TEXT_CHAR_4 0x05U
#define WINDOW_TEXT_CHAR_5 0x06U
#define WINDOW_TEXT_CHAR_6 0x07U
#define WINDOW_TEXT_CHAR_7 0x08U
#define WINDOW_TEXT_CHAR_8 0x09U
#define WINDOW_TEXT_CHAR_9 0x0AU
#define WINDOW_TEXT_CHAR_A 0x0BU
#define WINDOW_TEXT_CHAR_B 0x0CU
#define WINDOW_TEXT_CHAR_C 0x0DU
#define WINDOW_TEXT_CHAR_D 0x0EU
#define WINDOW_TEXT_CHAR_E 0x0FU
#define WINDOW_TEXT_CHAR_F 0x10U
#define WINDOW_TEXT_CHAR_G 0x11U
#define WINDOW_TEXT_CHAR_H 0x12U
#define WINDOW_TEXT_CHAR_I 0x13U
#define WINDOW_TEXT_CHAR_J 0x14U
#define WINDOW_TEXT_CHAR_K 0x15U
#define WINDOW_TEXT_CHAR_L 0x16U
#define WINDOW_TEXT_CHAR_M 0x17U
#define WINDOW_TEXT_CHAR_N 0x18U
#define WINDOW_TEXT_CHAR_O 0x19U
#define WINDOW_TEXT_CHAR_P 0x1AU
#define WINDOW_TEXT_CHAR_Q 0x1BU
#define WINDOW_TEXT_CHAR_R 0x1CU
#define WINDOW_TEXT_CHAR_S 0x1DU
#define WINDOW_TEXT_CHAR_T 0x1EU
#define WINDOW_TEXT_CHAR_U 0x1FU
#define WINDOW_TEXT_CHAR_V 0x20U
#define WINDOW_TEXT_CHAR_W 0x21U
#define WINDOW_TEXT_CHAR_X 0x22U
#define WINDOW_TEXT_CHAR_Y 0x23U
#define WINDOW_TEXT_CHAR_Z 0x24U
#define WINDOW_TEXT_CHAR_DOT 0x25U
#define WINDOW_TEXT_CHAR_COMMA 0x26U
#define WINDOW_TEXT_CHAR_EXCLAMATION 0x27U
#define WINDOW_TEXT_CHAR_DOLLAR 0x28U
#define WINDOW_TEXT_CHAR_QUOTE 0x29U
#define WINDOW_TEXT_CHAR_ASTERISK 0x2AU
#define WINDOW_TEXT_CHAR_QUESTION 0x2BU
#define WINDOW_TEXT_CHAR_DASH 0x2CU
#define WINDOW_TEXT_CHAR_SEMI_COLON 0x2DU

void show_window_character(UINT8 character_number, UINT8 itx, UINT8 ity);
void show_window_text(UINT8 *text);

#endif