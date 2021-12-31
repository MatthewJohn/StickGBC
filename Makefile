
BIN	= main.gb
CC	= ../../bin/lcc
ROMUSAGE	= ../../tools/romusage.exe
CFLAGS	=  -v -c -o

SOURCE	:= main main_map building_menu_map main_map_boundaries building_menu_tiles main_map_tileset window building_menu_palette main_map_palette main_map_sprite_tileset menu_config
C_FILES	= $(addsuffix .c,$(SOURCE))
OBJ_FILES	= $(addsuffix .o,$(SOURCE))
I_FILE	= lcc25200.i
ASM_FILE	= lcc25201.asm

all:	$(BIN)

$(SOURCE) %.o: %.c
	bash ./scripts/convert_main_main.sh
	$(CC) $(CFLAGS) $@ $<


main.gb: $(OBJ_FILES)
	$(CC) -Wl-yt2 -Wl-yo16 -Wl-ya4 -Wl-m -Wl-yp0x143=0x80 -o $@ main.o main_map.o building_menu_map.o main_map_boundaries.o building_menu_tiles.o main_map_tileset.o window.o building_menu_palette.o main_map_palette.o main_map_sprite_tileset.o menu_config.o

asm:	$(C_FILES)
	rm -f lcc25201.asm
	../../bin/sdcpp -Wall -lang-c++ -DSDCC=1 -DSDCC_PORT=gbz80 -DSDCC_PLAT=gb -DSDCC_MODEL_SMALL -DGB=1 -DGAMEBOY=1 -DINT_16_BITS -D__LCC__ -I..\..\include $< $(I_FILE)
	../../bin/sdcc -mgbz80 --nodebug --model-small --c1mode -v $(I_FILE) $(ASM_FILE)


usage:	$(BIN)
	$(ROMUSAGE) $(BIN) -a

clean:
	rm -f *.o $(BIN) $(I_FILE) $(ASM_FILE)


