# StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
# To view a copy of this license, visit
# http://creativecommons.org/licenses/by-nc-nd/4.0/.


for filename in main_map_palette building_menu_palette main_map_sprite_palette
do
  cat > $filename.c <<EOF
#pragma bank=5

#include "gb.h"

const UWORD $filename[] = {
EOF

  cat $filename.raw | sed 's/\t/, /g' | sed 's/^/  RGB(/g' | sed 's/$/),/g' >> $filename.c

  echo >> $filename.c
  echo '};' >> $filename.c
done
