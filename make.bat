
rm main.o main.gb
..\..\bin\lcc -Wa-l -c -o main.o main.c
..\..\bin\lcc -Wl-m -Wl-yp0x143=0x80 -o main.gb main.o

