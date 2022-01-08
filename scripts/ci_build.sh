# StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
# To view a copy of this license, visit
# http://creativecommons.org/licenses/by-nc-nd/4.0/.


set -e
set -x

f_check_git_changes() {
  modified_lines=$(git diff | wc -l)
  if [ "$modified_lines" != "0" ]
  then
      git diff --name-only
      echo "$1"
      exit 1
  fi
}

f_check_git_changes "Local git changes found"

# Convert color palettes
bash ./scripts/convert_color_palette.sh

# Check for any changes to color palettes
f_check_git_changes "Color palettes detected - changes not generated/committed"

# Convert maps
bash ./scripts/convert_maps.sh

# Check for any changes to map source
f_check_git_changes "Map source file changes dected - run conversion script and commit changes"

# Remove end of line whitespace and check for changes
sed -E -i 's/[\t ]+$//g' *.c *.h
f_check_git_changes "End of line whitespace found - please remove"

make clean
make 2>&1 | tee ./build_output.log

# Check for any compiler warnings
grep '\*\*\*' build_output.log && { echo "Compiler warnings/errors detected" && exit 1; } || true

# Run usage script
make usage

