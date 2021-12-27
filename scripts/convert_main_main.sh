# StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
# To view a copy of this license, visit
# http://creativecommons.org/licenses/by-nc-nd/4.0/.


# Convert 2 tiles of 1.5 bytes + empty spare nibble each of map tile to 3 bytes of data
#cat main_map.c | sed -z 's/,\n  /,/g' | sed -E 's/0x([0-9A-F][0-9A-F]),0x([0-9A-F])[0-9A-F],0x([0-9A-F])([0-9A-F]),0x([0-9A-F])[0-9A-F]/QQ\1,QQ\2\3,QQ\4\5/g' | sed 's/QQ/0x/g' > main_map.c

# Convert main_map.c to use const
sed -i 's/^unsigned char/const unsigned char/g' main_map.c main_map_tileset.c building_menu_tiles.c
sed -i 's/^extern unsigned char/extern const unsigned char/g' main_map.h main_map_tileset.h building_menu_tiles.h


