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

#define MUSIC_OCTAVE_0 0U
#define MUSIC_OCTAVE_1 12U
#define MUSIC_OCTAVE_2 24U
#define MUSIC_OCTAVE_3 36U
#define MUSIC_OCTAVE_4 48U

const UINT16 music_notes[4] = {
    MUSIC_NOTE_C1 + MUSIC_OCTAVE_1,
    MUSIC_NOTE_C1 + MUSIC_OCTAVE_2,
    MUSIC_NOTE_C1 + MUSIC_OCTAVE_3,
    MUSIC_NOTE_C1 + MUSIC_OCTAVE_0,
};
const UINT8 music_note_length = 4U;

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
//    UINT8 *channel_addr = &NR10_REG;
//    UINT8 *channel_addr = (&NR10_REG) + (MUSIC_CHANNEL * 5);
    UINT8 *channel_addr = (&NR10_REG) + 5;

    // NR0
    //*(channel_addr) = 0U;
    // NR1
    NR21_REG = 0xBF;
    // NR2
    NR22_REG = 0xF6U;  /// Volume and Instrument
    // NR3/4
    NR23_REG = (music_notes[game_state.music_itx] << 8) & 0xFF;
    NR24_REG = 0x80 | ((music_notes[game_state.music_itx] >> 4) & 0x07);
        
    game_state.music_itx ++;
    if (game_state.music_itx == music_note_length)
    {
        game_state.music_itx = 0U;
    }
    
    	//NR10_REG = 0x7D; //or 1E or 1D for louder sound / 2E / 3E / 4E... for more "vibe"
//	NR21_REG = 0xBF;
//	NR22_REG = 0xF6; //B7, C7, D7...F7 for longer sound
//	NR23_REG = 0x7C;
//	NR24_REG = 0x86;
}

void tick_music()
{
    play_next_note();
    delay(2000);
    if (game_state.music_tick == 0U)
    {
        play_next_note();
    }
    
    game_state.music_tick ++;
    if (game_state.music_tick == 32U)
    {
        game_state.music_tick = 0U;
    }
}
