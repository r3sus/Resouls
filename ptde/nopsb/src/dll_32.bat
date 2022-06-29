gcc -m32 -masm=intel -Wall -Wl,--enable-stdcall-fixup exports.DEF no*.c -shared -o ..\DINPUT8.dll
::pause
timeout /t 15