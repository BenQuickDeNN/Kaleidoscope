REM g++ src/kaleidoscope_main.cpp -o bin/kaleidoscope_main.exe -I include -g
SET src_main=src/kaleidoscope_main.cpp
SET build_main_i=build/kaleidoscope_main.i
SET build_main_s=build/kaleidoscope_main.s
SET build_main_o=build/kaleidoscope_main.o
SET bin_main_e=bin/kaleidoscope_main.exe
REM Ô¤´¦Àí½×¶Î
clang++ -E %src_main% -o %build_main_i% -I include
REM ±àÒë½×¶Î
clang++ -S %build_main_i% -o %build_main_s% -g
REM »ã±à½×¶Î
clang++ -c %build_main_s% -o %build_main_o%
REM Á´½Ó½×¶Î
clang++ %build_main_o% -o %bin_main_e%

REM ±àÒë¹Ù·½´úÂë
REM g++ src/official_kaleidoscope.cpp -o bin/official_kaleidoscope.exe -I include