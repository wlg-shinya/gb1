REM Automatically generated from Makefile
mkdir obj
..\lib\gbdk\bin\lcc   -c -o obj\main.o src\main.c
..\lib\gbdk\bin\lcc   -c -o obj\dungeon_map.o res\dungeon_map.c
..\lib\gbdk\bin\lcc   -c -o obj\dungeon_tiles.o res\dungeon_tiles.c
..\lib\gbdk\bin\lcc   -o obj\gb1.gb obj\main.o obj\dungeon_map.o obj\dungeon_tiles.o 
