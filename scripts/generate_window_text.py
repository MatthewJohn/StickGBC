
messages = {
    'bus_statn': {
        'no_inv': 'You arrive in the city with nothing to sell.'
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
        i: i + 1
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
        h_file.write('extern const UINT8 {}_{}[];\n'.format(area, message_name))

        # Add start of array for message
        c_file.write('const UINT8 {}_{}[] = {{\n'.format(area, message_name))

        # Add the tile value for each letter
        for letter in messages[area][message_name]:
            c_file.write('    {}U,\n'.format(letter_lookup[letter.lower()]))

        # Add terminating character
        c_file.write('    WINDOW_TEXT_END,\n')
        c_file.write('};\n\n')

c_file.close()
h_file.close()
