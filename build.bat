REM g++ src/kaleidoscope_main.cpp -o bin/kaleidoscope_main.exe -I include -g
SET src_main=src/kaleidoscope_main.cpp
SET build_main_i=build/kaleidoscope_main.i
SET build_main_s=build/kaleidoscope_main.s
SET build_main_o=build/kaleidoscope_main.o
SET bin_main_e=bin/kaleidoscope_main.exe

REM Ԥ����׶�
call clang++ -E %src_main% -o %build_main_i% -I include && (goto prep_succeed) || goto prep_failed

:prep_succeed
REM ����׶�
call clang++ -S %build_main_i% -o %build_main_s% -g && (goto compile_succeed) || goto compile_failed

:compile_succeed
REM ���׶�
call clang++ -c %build_main_s% -o %build_main_o% && (goto asm_succeed) || goto asm_failed

:asm_succeed
REM ���ӽ׶�
call clang++ %build_main_o% -o %bin_main_e% && (goto link_succed) || goto link_failed

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
REM ����ٷ�����
REM g++ src/official_kaleidoscope.cpp -o bin/official_kaleidoscope.exe -I include