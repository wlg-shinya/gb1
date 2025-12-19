REM Automatically generated from Makefile
mkdir output\obj
..\lib\gbdk\bin\lcc -Wm-yc -Ires -c -o output\obj\dscan.o src\dscan.c
..\lib\gbdk\bin\lcc -Wm-yc -Ires -c -o output\obj\bkg.o res\bkg.c
..\lib\gbdk\bin\lcc -Wm-yc -Ires -c -o output\obj\bkg_c.o res\bkg_c.c
..\lib\gbdk\bin\lcc -Wm-yc -Ires -c -o output\obj\bkg_m.o res\bkg_m.c
..\lib\gbdk\bin\lcc -Wm-yc -Ires -c -o output\obj\fore.o res\fore.c
mkdir output\rom
..\lib\gbdk\bin\lcc -Wm-yc -Ires -o output\rom\gb1.gb output\obj\dscan.o output\obj\bkg.o output\obj\bkg_c.o output\obj\bkg_m.o output\obj\fore.o 
..\lib\sameboy_winsdl\sameboy.exe output\rom\gb1.gb
