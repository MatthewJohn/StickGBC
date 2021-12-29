
BIN	= main.gb
CC	= ../../bin/lcc
CFLAGS	= -c -o

all:	$(BIN)

main main_map building_menu_map main_map_boundaries:	%.c:	%.c
	$(CC) $(CFLAGS) $@ $<

bank2.o:	bank2.c
	$(CC) -Wf-bo1 $(CFLAGS) $@ $<

main.gb: main.o main_map.o building_menu_map.o main_map_boundaries.o bank2.o
	$(CC) -Wl-yt2 -Wl-yo16 -Wl-ya4 -Wl-m -Wl-yp0x143=0x80 -o $@ main.o main_map.o building_menu_map.o main_map_boundaries.o bank2.o

clean:
	rm -f *.o $(BIN)

