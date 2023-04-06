/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */


#ifndef MUSIC_DEF
#define MUSIC_DEF 1

#define MUSIC_NOTE_C1 0x00U
#define MUSIC_NOTE_C2 0x01U
#define MUSIC_NOTE_D1 0x01U
#define MUSIC_NOTE_D2 0x02U
#define MUSIC_NOTE_D3 0x03U
#define MUSIC_NOTE_E1 0x03U
#define MUSIC_NOTE_E2 0x04U
#define MUSIC_NOTE_F1 0x05U
#define MUSIC_NOTE_F2 0x06U
#define MUSIC_NOTE_G1 0x06U
#define MUSIC_NOTE_G2 0x07U
#define MUSIC_NOTE_G3 0x08U
#define MUSIC_NOTE_A1 0x08U
#define MUSIC_NOTE_A2 0x09U
#define MUSIC_NOTE_A3 0x0AU
#define MUSIC_NOTE_B1 0x0AU

void initialise_music();
void tick_music();