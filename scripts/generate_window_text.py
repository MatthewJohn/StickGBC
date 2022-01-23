
messages = {
    'bus_statn': {
        'late': 'Bus leaves first thing in the morning.',
        'no_mon': 'You do not have enough money to travel.',
        'no_inv': 'You arrive in the city with nothing to sell.',
        'no_gun_1': 'You are robbed of all your money and stash by a traveling pack of low-rate lawyers.  Next time, pack some protection.',
        'no_gun_2': 'You are jumped by 3 guys and a chick. They take all your money and your stash. Maybe you should be packin\' heat next time.',
        'no_gun_3': 'A pimp gives you directions back to the bus station, then robs you. You\'ve lost all your money and your stash.',
        'no_ammo': 'You strut down the city streets looking for action. A gang of street toughs with baseball bats eye you and walk in your direction. You pull out your gun and fire...*click*  You\'ve got no bullets. They have a homerun derby contest on your ass and take your stash and money.'
    }
}

# Add alphabetic characters
letter_lookup = {
    chr(i): (itx + 11)
    for itx, i in enumerate(range(ord('a'), ord('z') + 1))
}
# Add numbers
letter_lookup.update(
    {
        str(i): i + 1
        for i in range(0, 10)
    }
)
# Add special characters
letter_lookup[' '] = 0
letter_lookup['.'] = 37
letter_lookup[','] = 38
letter_lookup['!'] = 39

# Create file handles
c_file = open('window_text_data.c', 'w')
h_file = open('window_text_data.h', 'w')

h_file.write("""

#include "gb.h"

#define WINDOW_TEXT_END 40U

""")

c_file.write("""
#pragma bank=8

#include "window_text.h"

""")

for area in messages:
    c_file.write('/* Messages for {}*/\n'.format(area))
    for message_name in messages[area]:

        # Add extern to header file for message
        h_file.write('extern const UINT8 win_txt_{}_{}[];\n'.format(area, message_name))

        # Add start of array for message
        c_file.write('const UINT8 win_txt_{}_{}[] = {{\n'.format(area, message_name))

        # Add the tile value for each letter
        for letter in messages[area][message_name]:
            if letter.lower() not in letter_lookup:
                print('WARNING: Character not found for {0}{1}: {2}'.format(area, message_name, letter.lower()))
            else:
                c_file.write('    {}U,\n'.format(letter_lookup[letter.lower()]))

        # Add terminating character
        c_file.write('    WINDOW_TEXT_END,\n')
        c_file.write('};\n\n')

c_file.close()
h_file.close()
