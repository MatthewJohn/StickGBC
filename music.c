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

#define MUSIC_WAIT(n) ((n | 0x8000U) - 1U)
#define MUSIC_NOTE_INTERVAL 1U
#define WAIT_BEAT 32U


//#define MUSIC_KICK 0x1457U
//#define MUSIC_SNARE 0x1450U
#define MUSIC_KICK 0xC190
#define MUSIC_SNARE 0xC140

const UINT16 intro_music_chnl2_notes[] = {
    // BAR 1
    // BEAT 1
    MUSIC_NOTE_G2,
    MUSIC_WAIT(WAIT_BEAT - 1U),

    // BEAT 2
    MUSIC_NOTE_G2,
    MUSIC_WAIT(WAIT_BEAT - 1U),

    // BEAT 3
    MUSIC_NOTE_G2,
    MUSIC_WAIT(WAIT_BEAT - 1U),

    // BEAT 4
    MUSIC_NOTE_G2,
    MUSIC_WAIT(WAIT_BEAT - 9U),
    MUSIC_NOTE_G2,
    MUSIC_WAIT(7U),

    // BAR 2
    // BEAT 1
    MUSIC_NOTE_G2,
    MUSIC_WAIT(WAIT_BEAT - 1U),

    // BEAT 2
    MUSIC_NOTE_G2,
    MUSIC_WAIT(WAIT_BEAT - 1U),

    // BEAT 3
    MUSIC_NOTE_G2,
    MUSIC_WAIT(WAIT_BEAT - 1U),

    // BEAT 4
    MUSIC_NOTE_G2,
    MUSIC_WAIT(WAIT_BEAT - 9U),
    MUSIC_NOTE_G2,
    MUSIC_WAIT(7U),

    // BAR 3
    // BEAT 1
    MUSIC_NOTE_G2,
    MUSIC_WAIT(WAIT_BEAT - 1U),

    // BEAT 2
    MUSIC_NOTE_G2,
    MUSIC_WAIT(WAIT_BEAT - 1U),

    // BEAT 3
    MUSIC_NOTE_G2,
    MUSIC_WAIT(WAIT_BEAT - 1U),

    // BEAT 4
    MUSIC_NOTE_G2,
    MUSIC_WAIT(23U),
    MUSIC_NOTE_A2,
    MUSIC_WAIT(7U),

    // BAR 4
    // BEAT 1
    MUSIC_NOTE_AS2,
    MUSIC_WAIT(WAIT_BEAT - 1),


    // BEAT 2
    MUSIC_NOTE_A2,
    MUSIC_WAIT(23U),

    MUSIC_NOTE_G2,
    MUSIC_WAIT(7U),

    // BEAT 3
    MUSIC_NOTE_F2,
    MUSIC_WAIT(23U),

    MUSIC_NOTE_G2,
    MUSIC_WAIT(7U),

    // BEAT 4
    MUSIC_NOTE_A2,
    MUSIC_WAIT(23U),

    MUSIC_NOTE_D2,
    MUSIC_WAIT(7U)
};

music_channel_t intro_music_chnl_2;

const UINT16 intro_music_chnl_n_notes[] = {
    MUSIC_KICK,
    MUSIC_WAIT(WAIT_BEAT - 1U),
    MUSIC_SNARE,
    MUSIC_WAIT(WAIT_BEAT - 1U),
};
music_channel_t intro_music_chnl_n;

const UINT16 main_music_chnl2_notes[] = {
    MUSIC_NOTE_C3,
    MUSIC_WAIT(31U),
};

music_channel_t main_music_chnl_2;

const UINT16 main_music_chnl_n_notes[] = {
    // 0xXXYY - XX - envelope, YY - frequency
    // BEAT 1
    MUSIC_KICK,
    MUSIC_WAIT(WAIT_BEAT - 7U),
    MUSIC_KICK,
    MUSIC_WAIT(5U),

    // BEAT 2
    MUSIC_SNARE,
    MUSIC_WAIT(9U),
    MUSIC_KICK,
    MUSIC_WAIT(5U),
    MUSIC_KICK,
    MUSIC_WAIT(9U),
    MUSIC_KICK,
    MUSIC_WAIT(5U),

    // BEAT 3
    MUSIC_WAIT(WAIT_BEAT - 6U),
    MUSIC_KICK,
    MUSIC_WAIT(5U),

    // BEAT 4
    MUSIC_SNARE,
    MUSIC_WAIT(9U),
    MUSIC_KICK,
    MUSIC_WAIT(5U),
    MUSIC_KICK,
    MUSIC_WAIT(15U),
};
music_channel_t main_music_chnl_n;

void initialise_music()
{
    NR52_REG = 0x80;
	NR51_REG = 0xFF;
    NR50_REG = 0x77;

    music_state.tick = 0U;
}

void play_intro_music()
{
    intro_music_chnl_2.notes = intro_music_chnl2_notes;
    intro_music_chnl_2.notes_length = (sizeof(intro_music_chnl2_notes)) / (sizeof(UINT16));
    intro_music_chnl_2.note_itx = 0U;
    intro_music_chnl_2.wait = 0U;

    intro_music_chnl_n.notes = intro_music_chnl_n_notes;
    intro_music_chnl_n.notes_length = (sizeof(intro_music_chnl_n_notes)) / (sizeof(UINT16));
    intro_music_chnl_n.note_itx = 0U;
    intro_music_chnl_n.wait = 0U;

    music_state.channel_1 = NULL;
    music_state.channel_2 = &intro_music_chnl_2;
    music_state.channel_noise = &intro_music_chnl_n;

    // Setup voice 2
    NR21_REG = 0xC1;
    NR22_REG = 0xF1U;  /// Volume and Instrument
    // Setup noise
    NR41_REG = 0x2F;
}

void play_main_music()
{
    main_music_chnl_2.notes = main_music_chnl2_notes;
    main_music_chnl_2.notes_length = (sizeof(main_music_chnl2_notes)) / (sizeof(UINT16));
    main_music_chnl_2.note_itx = 0U;
    main_music_chnl_2.wait = 0U;

    main_music_chnl_n.notes = main_music_chnl_n_notes;
    main_music_chnl_n.notes_length = (sizeof(main_music_chnl_n_notes)) / (sizeof(UINT16));
    main_music_chnl_n.note_itx = 0U;
    main_music_chnl_n.wait = 0U;

    music_state.channel_1 = NULL;
    music_state.channel_2 = &main_music_chnl_2;
    music_state.channel_noise = &main_music_chnl_n;

    // Setup voice 2
    NR21_REG = 0xC1U;
    NR22_REG = 0xF1U;  /// Volume and Instrument

    // Setup noise
    NR41_REG = 0x2F;
}

void play_next_note()
{
    UINT8 *channel_addr = (&NR10_REG) + 5;

    // Channel 1
    if (music_state.channel_1 != NULL)
    {
        if (music_state.channel_1->wait != 0U)
        {
            music_state.channel_1->wait --;
        }
        else
        {
            // Check if note is a wait note
            if (music_state.channel_1->notes[music_state.channel_1->note_itx] & 0x8000U)
            {
                music_state.channel_1->wait = music_state.channel_1->notes[music_state.channel_1->note_itx] & 0xFF;
            }
            else
            {
                // Otherwise, play note
                NR13_REG = music_state.channel_1->notes[music_state.channel_1->note_itx] & 0xFF;
                NR14_REG = 0x80 | ((music_state.channel_1->notes[music_state.channel_1->note_itx] >> 8) & 0x07);
            }

            music_state.channel_1->note_itx ++;
            if (music_state.channel_1->note_itx == music_state.channel_1->notes_length)
            {
                music_state.channel_1->note_itx = 0U;
            }
        }
    }

    // Channel 2
    if (music_state.channel_2 != NULL)
    {
        if (music_state.channel_2->wait != 0U)
        {
            music_state.channel_2->wait --;
        }
        else
        {
            // Check if note is a wait note
            if (music_state.channel_2->notes[music_state.channel_2->note_itx] & 0x8000U)
            {
                music_state.channel_2->wait = music_state.channel_2->notes[music_state.channel_2->note_itx] & 0xFF;
            }
            else
            {
                // Otherwise, play note
                NR23_REG = music_state.channel_2->notes[music_state.channel_2->note_itx] & 0xFF;
                NR24_REG = 0x80 | ((music_state.channel_2->notes[music_state.channel_2->note_itx] >> 8) & 0x07);
            }

            music_state.channel_2->note_itx ++;
            if (music_state.channel_2->note_itx == music_state.channel_2->notes_length)
            {
                music_state.channel_2->note_itx = 0U;
            }
        }
    }

    // Noise channel
    if (music_state.channel_noise != NULL)
    {
        if (music_state.channel_noise->wait != 0U)
        {
            music_state.channel_noise->wait --;
        }
        else
        {
            // Check if note is a wait note
            if ((music_state.channel_noise->notes[music_state.channel_noise->note_itx] & 0xFF00U) == 0x8000U)
            {
                music_state.channel_noise->wait = music_state.channel_noise->notes[music_state.channel_noise->note_itx] & 0xFF;
            }
            else
            {
                // Otherwise, play note
                NR42_REG = (music_state.channel_noise->notes[music_state.channel_noise->note_itx] >> 8) & 0xFF;  /// Volume and Instrument
                NR43_REG = music_state.channel_noise->notes[music_state.channel_noise->note_itx] & 0xFFU;
                NR44_REG = 0x80U;  // Or 0xBF
            }

            music_state.channel_noise->note_itx ++;
            if (music_state.channel_noise->note_itx == music_state.channel_noise->notes_length)
            {
                music_state.channel_noise->note_itx = 0U;
            }
        }
    }
}

void tick_music()
{
    if (music_state.tick == 0U)
    {
        play_next_note();
    }

    music_state.tick ++;
    if (music_state.tick == MUSIC_NOTE_INTERVAL)
    {
        music_state.tick = 0U;
    }
}