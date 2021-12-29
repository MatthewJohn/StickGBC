
BIN	= main.gb
CC	= ../../bin/lcc
CFLAGS	= -c -o

all: $(BIN)

%.o:	%.c
	$(CC) $(CFLAGS) -c -o $@ $<

main.gb: building_menu_map.o building_menu_palette.o building_menu_tiles.o common_globals.o game_state.o game_state_ext.o main.o main_map.o main_map_boundaries.o main_map_palette.o main_map_sprite_tileset.o main_map_tileset.o menu_config.o menu_config_data.o screen_state.o window.o
	$(CC) -Wl-yt2 -Wl-yo16 -Wl-ya4 -Wl-m -Wl-yp0x143=0x80 -o $@ *.o

clean:
	rm -f *.o $(BIN)

