
BIN	= main.gb
CC	= ../../bin/lcc
ROMUSAGE	= ../../tools/romusage.exe
BGB = "../../bgb(1)/bgb.exe"
CFLAGS	=  -v -c -o

SOURCE	:= main main_game main_map building_menu_map main_map_boundaries building_menu_tiles building_menu_tiles_2 main_map_tileset window building_menu_palette main_map_palette main_map_sprite_tileset menu_config main_map_sprite_palette sprite background_time_colors joy opening_screen_map opening_screen_tiles opening_screen_palette opening_screen logic_functions window_text window_text_data window_text_tiles splash_screen_tiles splash_screen_map splash_screen_palette endgame_tiles endgame_map endgame_palette endgame bar_fight_map bar_fight_tiles bar_fight bar_fight_palette
C_FILES	= $(addsuffix .c,$(SOURCE))
OBJ_FILES	= $(addsuffix .o,$(SOURCE))
I_FILE	= lcc25200.i
ASM_FILE	= lcc25201.asm

DEMO	:= $(filter demo,$(MAKECMDGOALS))

all:	$(BIN)

$(SOURCE) %.o: %.c
	bash -c "if test -f ./scripts/convert_maps.sh; then ./scripts/convert_maps.sh; fi"
	$(CC) $(if $(DEMO),-Wp-DIN_TESTING=1,) $(CFLAGS) $@ $<


main.gb: $(OBJ_FILES)
	$(CC) -Wl-yt2 -Wl-yo16 -Wl-ya4 -Wl-m -Wl-yp0x143=0x80 -v -o $@ $(OBJ_FILES) 

asm:	$(C_FILES)
	rm -f lcc25201.asm
	../../bin/sdcpp -Wall -lang-c++ -DSDCC=1 -DSDCC_PORT=gbz80 -DSDCC_PLAT=gb -DSDCC_MODEL_SMALL -DGB=1 -DGAMEBOY=1 -DINT_16_BITS -D__LCC__ -I..\..\include $< $(I_FILE)
	../../bin/sdcc -mgbz80 --nodebug --model-small --c1mode -v $(I_FILE) $(ASM_FILE)


usage:	$(BIN)
	$(ROMUSAGE) $(BIN) -a

demo:	$(BIN)

run: $(BIN)
	$(BGB) $(BIN)

clean:
	rm -f *.o $(BIN) $(I_FILE) $(ASM_FILE)


