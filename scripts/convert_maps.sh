# StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
# To view a copy of this license, visit
# http://creativecommons.org/licenses/by-nc-nd/4.0/.


# Convert 2 tiles of 1.5 bytes + empty spare nibble each of map tile to 3 bytes of data
#cat main_map.c | sed -z 's/,\n  /,/g' | sed -E 's/0x([0-9A-F][0-9A-F]),0x([0-9A-F])[0-9A-F],0x([0-9A-F])([0-9A-F]),0x([0-9A-F])[0-9A-F]/QQ\1,QQ\2\3,QQ\4\5/g' | sed 's/QQ/0x/g' > main_map.c

# Convert main_map.c to use const
sed -i 's/^unsigned char/const unsigned char/g' main_map.c main_map_tileset.c building_menu_tiles.c main_map_sprite_tileset.c
sed -i 's/^extern unsigned char/extern const unsigned char/g' main_map.h main_map_tileset.h building_menu_tiles.h main_map_sprite_tileset.h

f_setup_bank() {
    file=$1
    bank=$2
    grep 'pragma bank' $file.c >/dev/null 2>&1 || echo "#pragma bank=$bank" > tmp.c && cat $file.c >> tmp.c && mv tmp.c $file.c;
}

f_setup_bank main_map 5
f_setup_bank building_menu_map 3
f_setup_bank main_map_boundaries 5
f_setup_bank building_menu_tiles 3
f_setup_bank main_map_tileset 5
f_setup_bank main_map_sprite_tileset 4

# Remove end of line whitespace from map files
sed -E -i 's/[ \t]+$//g' main_map.c main_map_tileset.c building_menu_tiles.c main_map_sprite_tileset.c main_map.h main_map_tileset.h building_menu_tiles.h main_map_sprite_tileset.h

