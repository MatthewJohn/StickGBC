/*
 * StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-nd/4.0/.
 */


#ifndef MUSIC_DEF
#define MUSIC_DEF 1

#define MUSIC_NOTE_C2 44U
#define MUSIC_NOTE_CS2 157U
#define MUSIC_NOTE_D2 263U
#define MUSIC_NOTE_DS2 363U
#define MUSIC_NOTE_E2 458U
#define MUSIC_NOTE_F2 547U
#define MUSIC_NOTE_FS2 631U
#define MUSIC_NOTE_G2 711U
#define MUSIC_NOTE_GS2 786U
#define MUSIC_NOTE_A2 856U
#define MUSIC_NOTE_AS2 923U
#define MUSIC_NOTE_B2 986U
#define MUSIC_NOTE_C3 1046U
#define MUSIC_NOTE_CS3 1102U
#define MUSIC_NOTE_D3 1155U
#define MUSIC_NOTE_DS3 1205U
#define MUSIC_NOTE_E3 1253U
#define MUSIC_NOTE_F3 1297U
#define MUSIC_NOTE_FS3 1340U
#define MUSIC_NOTE_G3 1379U
#define MUSIC_NOTE_GS3 1417U
#define MUSIC_NOTE_A3 1452U
#define MUSIC_NOTE_AS3 1486U
#define MUSIC_NOTE_B3 1517U
#define MUSIC_NOTE_C4 1547U
#define MUSIC_NOTE_CS4 1575U
#define MUSIC_NOTE_D4 1602U
#define MUSIC_NOTE_DS4 1627U
#define MUSIC_NOTE_E4 1650U
#define MUSIC_NOTE_F4 1673U
#define MUSIC_NOTE_FS4 1694U
#define MUSIC_NOTE_G4 1714U
#define MUSIC_NOTE_GS4 1732U
#define MUSIC_NOTE_A4 1750U
#define MUSIC_NOTE_AS4 1767U
#define MUSIC_NOTE_B4 1783U
#define MUSIC_NOTE_C5 1798U
#define MUSIC_NOTE_CS5 1812U
#define MUSIC_NOTE_D5 1825U
#define MUSIC_NOTE_DS5 1837U
#define MUSIC_NOTE_E5 1849U
#define MUSIC_NOTE_F5 1860U
#define MUSIC_NOTE_FS5 1871U
#define MUSIC_NOTE_G5 1881U
#define MUSIC_NOTE_GS5 1890U
#define MUSIC_NOTE_A5 1899U
#define MUSIC_NOTE_AS5 1907U
#define MUSIC_NOTE_B5 1915U
#define MUSIC_NOTE_C6 1923U
#define MUSIC_NOTE_CS6 1930U
#define MUSIC_NOTE_D6 1936U
#define MUSIC_NOTE_DS6 1943U
#define MUSIC_NOTE_E6 1949U
#define MUSIC_NOTE_F6 1954U
#define MUSIC_NOTE_FS6 1959U
#define MUSIC_NOTE_G6 1964U
#define MUSIC_NOTE_GS6 1969U
#define MUSIC_NOTE_A6 1974U
#define MUSIC_NOTE_AS6 1978U
#define MUSIC_NOTE_B6 1982U
#define MUSIC_NOTE_C7 1985U
#define MUSIC_NOTE_CS7 1989U
#define MUSIC_NOTE_D7 1992U
#define MUSIC_NOTE_DS7 1995U
#define MUSIC_NOTE_E7 1998U
#define MUSIC_NOTE_F7 2001U
#define MUSIC_NOTE_FS7 2004U
#define MUSIC_NOTE_G7 2006U
#define MUSIC_NOTE_GS7 2009U
#define MUSIC_NOTE_A7 2011U
#define MUSIC_NOTE_AS7 2013U
#define MUSIC_NOTE_B7 2015U
#define MUSIC_NOTE_C8 2017U
#define MUSIC_NOTE_CS8 2018U
#define MUSIC_NOTE_D8 2020U
#define MUSIC_NOTE_DS8 2022U
#define MUSIC_NOTE_E8 2023U
#define MUSIC_NOTE_F8 2025U
#define MUSIC_NOTE_FS8 2026U
#define MUSIC_NOTE_G8 2027U
#define MUSIC_NOTE_GS8 2028U
#define MUSIC_NOTE_A8 2029U
#define MUSIC_NOTE_AS8 2030U
#define MUSIC_NOTE_B8 2031U

typedef struct {
    UINT16 *notes;
    UINT8 notes_length;
    UINT8 tick;
    UINT8 note_itx;
    UINT8 wait;
} music_state_t;

music_state_t music_state;

void initialise_music();
void tick_music();
void play_intro_music();