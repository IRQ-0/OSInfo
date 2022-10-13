@echo off

gcc.exe -c dllmain.c -o dllmain.o
rem compiling cpuload.dll file
if not %errorlevel% == 0 (goto error)

gcc.exe -c cpuload.c -o cpuload.o
rem compiling cpuload.dll file
if not %errorlevel% == 0 (goto error)

gcc.exe -shared dllmain.o cpuload.o -o cpuload.dll
rem creating cpuload.dll file
if not %errorlevel% == 0 (goto error)
   
gcc.exe -c main.c -std=c99 -o main.o
rem cpomiling main.c to main.o
if not %errorlevel% == 0 (goto error)

gcc.exe -c osinfo.c -std=c99 -o osinfo.o
rem compiling osinfo.c to osinfo.o
if not %errorlevel% == 0 (goto error)

gcc.exe -c graph.c -std=c99 -o graph.o
rem compiling graph.c to graph.o
if not %errorlevel% == 0 (goto error)

gcc.exe main.o osinfo.o graph.o -o Osinfo.exe "cpuload.dll"
rem compiling everything to osinfo.exe
if not %errorlevel% == 0 (goto error)
goto endok

:error
echo Error while compiling

:endok
del *.o
echo Compilation successful
