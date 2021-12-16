
# Stick GBC Complete

Stick GBC is a gameboy colour re-implementation of XGen Studio's Stick RPG.

## Background

I played this game a couple of times around 15 years ago and remeber it with fond nastolgia.

I am no designer, nor game developer, so chose this as a first attempt at a Gameboy game.

The second milestone is currently in development. However, Milestone 1 is complete, which implments most core mechanics, with some minigames missing (darts, drunken fight and casino games).

The game is currently locked to 30 day limit, which will be selectable in the next milestone.

Statistics are currently randomly generated (not selectable) in the current milestone.


## Building

### Using original repository

    cd games/stickrpg
    make

### Building from Github

The build as only been tested on Windows XP/Server 2003.

Git bash and GNU Make must be installed.

You will need a copy of GBDK (the sourceforge version: https://sourceforge.net/projects/gbdk/ - v2.96 from 2002).

Clone the source two child directories from the root (e.g. `games/stickgbc`)

Follow `Using original repository` to perform the build.

### Pre-built binaries

Binaries can be found of each version: https://build.dockstudios.co.uk/job/GameboyDev/job/StickGBC

Each build is from the 'main' branch, so pulling the latest should be fine.

To find an individual commit, each commit in the Github repository contains the original commit ID in the description, which is referenced on the build.

The pre-built binary for Milestone 1 can be found here: https://github.com/MatthewJohn/StickGBC/releases/tag/stickgbc-1.0.0

## Build tools

### `scripts/convert_color_palettes.sh`

The `.raw` palette files are directly created from the 'copy all' function of the palette in GBTD (game boy tile designer)

This must be run after any modifications to the `.raw` palette files to regenerate the C files for the palette.

### `scripts/convert_maps.sh`

The `_map.c` and `_map.h` files are created from GBMB (gameboy map builder) and `_tiles.c` and `_tiles.h` files are created by GBTD (gameboy tile designer).

Whenever the files are exported from these applications, this script must be run to add bank pragma and set variables as consts.

### `scripts/generate_window_text.py`

This generates window_text_data from a map of plain-text strings.

The output files should not be modified and window text should be added to this script and rerun.

This requires python to be installed on the development machine.

### `scripts/ci_*.sh`

This contains a selection of scripts that are run by the CI.

Some are run on Windows and others are run on Linux and within docker containers.


## Contributing

See `CONTRIBUTING.md`

## Raising issues

Feel free to raise a Github issue, but keep in mind that they will be migrated to internal Gitlab issues.
As a result, commit messages do not align with Github issues.

## License

<a rel="license" href="http://creativecommons.org/licenses/by-nc-nd/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-nd/4.0/88x31.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc-nd/4.0/">Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License</a>.

Please see `LICENSE` for full license
