
rm *.o main.gb
..\..\bin\lcc -Wa-l -v -c -o main.o main.c
..\..\bin\lcc -c -o bank2.o bank2.c
..\..\bin\lcc -c -o bank3.o bank3.c
..\..\bin\lcc -Wl-yt2 -Wl-yo16 -Wl-ya4 -Wl-m -Wl-yp0x143=0x80 -o main.gb main.o bank2.o bank3.o

