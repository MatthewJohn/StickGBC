
messages = {
    'bus_statn': {
        'no_inv': 'You arrive in the city with nothing to sell.'
    }
}

# Add alphabetic characters
letter_lookup = {
    chr(i): (itx + 1)
    for itx, i in enumerate(range(ord('a'), ord('z') + 1))
}
# Add special characters
letter_lookup[' '] = 0
letter_lookup['.'] = 27
letter_lookup[','] = 28
letter_lookup['!'] = 29

# Create file handles
c_file = open('window_text.c', 'w')
h_file = open('window_text.h', 'w')

h_file.write("""

#include "gb.h"

""")

c_file.write("""
#pragma bank=8

#include "window_text.h"

""")

for area in messages:
    c_file.write('/* Messages for {}*/\n'.format(area))
    for message_name in messages[area]:
        h_file.write('extern UINT8 {}_{}[];\n'.format(area, message_name))
    
        c_file.write('UINT8 {}_{}[] = {{\n'.format(area, message_name))
        for letter in messages[area][message_name]:
            c_file.write('    {}U,\n'.format(letter_lookup[letter.lower()]))
        c_file.write('};\n\n')

c_file.close()
h_file.close()
