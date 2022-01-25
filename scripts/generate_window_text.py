
messages = {
    'bus_statn': {
        'late': 'Bus leaves first thing in the morning.',
        'no_mon': 'You do not have enough money to travel.',
        'no_inv': 'You arrive in the city with nothing to sell.',
        'no_gun_1': 'You are robbed of all your money and stash by a traveling pack of low-rate lawyers.  Next time, pack some protection.',
        'no_gun_2': 'You are jumped by 3 guys and a chick. They take all your money and your stash. Maybe you should be packin\' heat next time.',
        'no_gun_3': 'A pimp gives you directions back to the bus station, then robs you. You\'ve lost all your money and your stash.',
        'no_ammo': 'A gang of street toughs with baseball bats eye you up. You pull out your gun and fire...*click*  You\'ve got no bullets. They have a homerun derby contest on your ass and take your stash and money.',
        'rob_1': 'You accidentally track dog crap onto a girl scout group\'s hop scotch layout. Troop 61 leaves you lying on the street with no cash and no stash, and a mouthful of stale cookies. Maybe you should buff up a bit more.',
        'rob_2': 'You come across a dark alley. Three large cats attack you from all sides, leaving you unconscious near a dumpster. A passing bum raids your wallet and your stash. You\'re weak as a kitten!',
        'rob_3': 'Not paying attention, you slip on a used condom and hit your head on a park bench. Bleeding profusely, you can only watch as squirrels make off with your wallet and stash. Toughen\' up!',
        'no_phone': 'After arriving, you spend the entire day looking for people who will buy from you, but no one wants to deal with a punk without a cell phone. How are they supposed to call you for supply when \'the craving\' sets in??',
        'bust': 'Rolling into town with piles of product attacted plenty of attention - from the cops. They confiscate your goods, your gun, and your freedom; You serve the next 5 days in state pen.',
        'bad': 'You meet some new contacts behind an abandoned building. Suddenly you get hit from behind by a blunt object. As you lie on the pavement, you realize what just happened; you\'ve been screwed! Your stash got jacked.',
        'no_deal': 'You\'ve arrived in the city but can\'t find anyone to buy from you.  Better luck next time, chump.',
        'coke_deal': 'You\'ve arrived in the city and have received an offer of    $===== for == cocaine... Do you accept? A to accept. B to decline',
        'beer_deal': 'You\'ve arrived in the city and have received an offer of    $===== for == beer... Do you accept? A to accept. B to decline',
    },
    'nli': {
        'no_int': 'Thank you for applying. Unfortunately, you failed the aptitude test. Better luck next time!',
        'jan': 'Congratulations! You are now a: JANITOR. Your wage is now $8 per hour.',
        'mail': 'Congratulations! You are now a: MAIL CLERK. Your wage is now $10 per hour.',
        'sales': 'Congratulations! You are now a: SALESMAN. Your wage is now $15 per hour.',
        'exec': 'Congratulations! You are now a: EXECUTIVE. Your wage is now $25 per hour.',
        'vp': 'Congratulations! You are now a: VP. Your wage is now $50 per hour.',
        'ceo': 'Congratulations! You are now a: CEO. Your wage is now $100 per hour.',
    },
    'skater': {
        'int': 'Hey man! Do you have any smokes? It\'s just.. I.. uh.. er.. forgot my ID at home! Please?',
        'give': 'Sweet Man! You are sooo cool! Here, you can take this! (*Skateboard received*)',
        'thx_1': '*cough cough* Sweeet... *hack*',
        'thx_2': 'Sweet, thanks dude. Hey, you think you could get some kings next time?',
        'thx_3': '*hack* Ohh yeah.. that\'s the good stuff.',
        'thx_4': 'Thanks dude! And to think, I was thinking about quitting.. ah well! You got a light?',
    },
    'dealer': {
        'int': 'Hey man, come over here for a minute. You wanna see some dope-fly shit? I\'m tellin\' ya\' man, you can make some FAT stacks off this product!',
    }
}

# Add alphabetic characters
letter_lookup = {
    chr(i): str(itx + 11) + 'U'
    for itx, i in enumerate(range(ord('a'), ord('z') + 1))
}
# Add numbers
letter_lookup.update(
    {
        str(i): str(i + 1) + 'U'
        for i in range(0, 10)
    }
)
# Add special characters
letter_lookup[' '] = '0U'
letter_lookup['.'] = '37U'
letter_lookup[','] = '38U'
letter_lookup['!'] = '39U'
letter_lookup['$'] = '40U'
letter_lookup['\''] = '41U'
letter_lookup['*'] = '42U'
letter_lookup['?'] = '43U'
letter_lookup['-'] = '44U'
letter_lookup[';'] = '45U'

# Character to leave space blank
letter_lookup['='] = 'WINDOW_TEXT_SKIP'

# Create file handles
c_file = open('window_text_data.c', 'w')
h_file = open('window_text_data.h', 'w')

h_file.write("""

#include "gb.h"

#define WINDOW_TEXT_SKIP 46U
#define WINDOW_TEXT_END 47U

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
                c_file.write('    {},\n'.format(letter_lookup[letter.lower()]))

        # Add terminating character
        c_file.write('    WINDOW_TEXT_END,\n')
        c_file.write('};\n\n')

c_file.close()
h_file.close()
