
BIN	= main.gb
CC	= ../../bin/lcc
CFLAGS	= -c -o

all:	$(BIN)

main main_map building_menu_map main_map_boundaries building_menu_tiles main_map_tileset window building_menu_palette main_map_palette main_map_sprite_tileset: %.o: %.c
	bash ./scripts/convert_main_main.sh
	$(CC) $(CFLAGS) $@ $<

bank2.o:	bank2.c
	bash ./scripts/convert_main_main.sh
	$(CC) -Wf-bo1 $(CFLAGS) $@ $<

main.gb: main.o main_map.o building_menu_map.o main_map_boundaries.o building_menu_tiles.o main_map_tileset.o window.o building_menu_palette.o main_map_palette.o main_map_sprite_tileset.o bank2.o
	$(CC) -Wl-yt2 -Wl-yo16 -Wl-ya4 -Wl-m -Wl-yp0x143=0x80 -o $@ main.o main_map.o building_menu_map.o main_map_boundaries.o building_menu_tiles.o main_map_tileset.o window.o building_menu_palette.o main_map_palette.o main_map_sprite_tileset.o bank2.o

clean:
	rm -f *.o $(BIN)

