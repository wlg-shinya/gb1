REM Automatically generated from Makefile
mkdir output\obj
..\lib\gbdk\bin\lcc   -c -o output\obj\main.o src\main.c
..\lib\gbdk\bin\lcc   -c -o output\obj\dungeon_map.o res\dungeon_map.c
..\lib\gbdk\bin\lcc   -c -o output\obj\dungeon_tiles.o res\dungeon_tiles.c
mkdir output\rom
..\lib\gbdk\bin\lcc   -o output\rom\gb1.gb output\obj\main.o output\obj\dungeon_map.o output\obj\dungeon_tiles.o 
..\lib\bgbw64\bgb64.exe output\rom\gb1.gb
