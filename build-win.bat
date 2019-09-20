REM g++ src/kaleidoscope_main.cpp -o bin/kaleidoscope_main.exe -I include -g
SET src_main=src/kaleidoscope.cpp
SET build_main_i=build/kaleidoscope.i
SET build_main_s=build/kaleidoscope.s
SET build_main_o=build/kaleidoscope.o
SET bin_main_e=bin/kaleidoscope.exe
SET dir_include=include
SET dir_lib=lib
REM SET lib_option=`llvm-config --cxxflags --ldflags --system-libs --libs core`

REM Ô¤´¦Àí½×¶Î
call clang++ -O3 -E %src_main% -o %build_main_i% -I %dir_include% && (goto prep_succeed) || goto prep_failed

:prep_succeed
REM ±àÒë½×¶Î
call clang++ -S %build_main_i% -o %build_main_s% -g && (goto compile_succeed) || goto compile_failed

:compile_succeed
REM »ã±à½×¶Î
call clang++ -c %build_main_s% -o %build_main_o% && (goto asm_succeed) || goto asm_failed

:asm_succeed
REM Á´½Ó½×¶Î
call clang++ %build_main_o% `llvm-config --cxxflags --ldflags --system-libs --libs core`
 -o %bin_main_e% -L %dir_lib% && (goto link_succed) || goto link_failed

:link_succed
goto compile_official_code

:link_failed
echo linking fail!
goto compile_official_code

:asm_failed
echo asm fail!
goto compile_official_code

:compile_failed
echo compiling fail!
goto compile_official_code

:prep_failed
echo preprocessing fail!
goto compile_official_code

:compile_official_code
REM ±àÒë¹Ù·½´úÂë
REM g++ src/official_kaleidoscope.cpp -o bin/official_kaleidoscope.exe -I include