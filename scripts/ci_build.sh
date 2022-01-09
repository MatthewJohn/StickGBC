# StickGBC by Matt Comben is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
# To view a copy of this license, visit
# http://creativecommons.org/licenses/by-nc-nd/4.0/.


set -e
set -x

make clean
make 2>&1 | tee ./build_output.log

# Check for any compiler warnings
grep '\*\*\*' build_output.log && { echo "Compiler warnings/errors detected" && exit 1; } || true

# Run usage script
make usage

