# StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
# To view a copy of this license, visit
# http://creativecommons.org/licenses/by-nc-nd/4.0/.


f_setup_palette()
{
    filename=$1
    bank=$2

  cat > $filename.c <<EOF
#pragma bank=$bank

#include "gb.h"

const UWORD $filename[] = {
EOF

  cat $filename.raw | sed 's/\t/, /g' | sed 's/^/  RGB(/g' | sed 's/$/),/g' >> $filename.c

  echo >> $filename.c
  echo '};' >> $filename.c
}

f_setup_palette main_map_palette 5
f_setup_palette building_menu_palette 3
f_setup_palette main_map_sprite_palette 4