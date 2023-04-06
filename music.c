/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */


#include "gb.h"
#include "game_state.h"
#include "music.h"
#include "main.h"

#define MUSIC_CHANNEL 1U

#define MUSIC_WAIT(n) n | 0x8000U
#define MUSIC_NOTE_INTERVAL 8U

const UINT16 music_notes[] = {
    MUSIC_NOTE_G2,
    MUSIC_WAIT(4),
    MUSIC_NOTE_G2,
    MUSIC_WAIT(4),
    MUSIC_NOTE_G2,
    MUSIC_NOTE_G2,
    MUSIC_NOTE_G2,
    MUSIC_WAIT(4),
    MUSIC_NOTE_G2,
    MUSIC_WAIT(4),
    MUSIC_NOTE_G2,
    MUSIC_NOTE_G2,
    MUSIC_NOTE_G2,
    MUSIC_WAIT(4),
    MUSIC_NOTE_G2,
    MUSIC_WAIT(4),
    MUSIC_NOTE_G2,
    MUSIC_NOTE_G2,
    MUSIC_NOTE_G2,
    MUSIC_WAIT(4),
    MUSIC_NOTE_G2,
    MUSIC_WAIT(4),
    MUSIC_NOTE_G2,
    MUSIC_NOTE_A2,
    MUSIC_NOTE_AS2,
    MUSIC_WAIT(1),
    MUSIC_NOTE_A2,
    MUSIC_NOTE_G2,
    MUSIC_NOTE_F2,
    MUSIC_NOTE_D2,
    MUSIC_WAIT(6)
    

//    MUSIC_WAIT(5),
//    MUSIC_NOTE_E2,
//    MUSIC_NOTE_C2,
//    MUSIC_NOTE_C2,
//    MUSIC_WAIT(4)
//    MUSIC_NOTE_E2,
//    MUSIC_WAIT(2),
//    MUSIC_NOTE_F2,
//    MUSIC_NOTE_G2,
//    MUSIC_NOTE_A2,
//    MUSIC_NOTE_G2,
//    MUSIC_NOTE_D2,
//    MUSIC_NOTE_E2,
//    MUSIC_NOTE_E2,
//    MUSIC_NOTE_E2,
//    MUSIC_WAIT(5),
//    MUSIC_NOTE_C2,
//    MUSIC_NOTE_E2,
//    MUSIC_NOTE_C2,
//    MUSIC_NOTE_C2,
//    MUSIC_WAIT(2),
//    MUSIC_NOTE_C4,
//    MUSIC_NOTE_D4,
//    MUSIC_NOTE_E4,
//    MUSIC_WAIT(5),
};
const UINT8 music_note_length = (sizeof (music_notes)) / (sizeof (UINT16));

void initialise_music()
{
//    NR50_REG = 0x77;
//    NR51_REG = 0x0F;
//    NR52_REG = 0x80;
    NR52_REG = 0x80;
	NR51_REG = 0xFF;
    NR50_REG = 0x77;
}

void play_next_note()
{
    UINT8 *channel_addr = (&NR10_REG) + 5;

    if (game_state.music_wait != 0U)
    {
        game_state.music_wait --;
        return;
    }
    // Check if note is a wait note
    if (music_notes[game_state.music_itx] & 0x8000U)
    {
        game_state.music_wait = music_notes[game_state.music_itx] & 0xFF;
    }
    else
    {
        // Otherwise, play note
        NR21_REG = 0x01;
        NR22_REG = 0xF1U;  /// Volume and Instrument
        NR23_REG = music_notes[game_state.music_itx] & 0xFF;
        NR24_REG = 0x80 | ((music_notes[game_state.music_itx] >> 8) & 0x07);
    }

    game_state.music_itx ++;
    if (game_state.music_itx == music_note_length)
    {
        game_state.music_itx = 0U;
    }
}

void tick_music()
{
    if (game_state.music_tick == 0U)
    {
        play_next_note();
    }
    
    game_state.music_tick ++;
    if (game_state.music_tick == MUSIC_NOTE_INTERVAL)
    {
        game_state.music_tick = 0U;
    }
}
