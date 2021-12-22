
rm main.o main_map.o main.gb
..\..\bin\lcc -Wa-l -c -o main.o main.c
..\..\bin\lcc -Wf-bo1 -c -o main_map.o main_map.c
..\..\bin\lcc -Wf-bo1 -c -o main_map_boundaries.o main_map_boundaries.c
..\..\bin\lcc -Wl-yt2 -Wl-yo16 -Wl-ya4 -Wl-m -Wl-yp0x143=0x80 -o main.gb main.o main_map.o main_map_boundaries.o

