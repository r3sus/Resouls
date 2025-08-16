gcc -m32 -masm=intel -static-libgcc -Wall -Wl,--enable-stdcall-fixup ..\exports.DEF dehook.c -shared -o dinput8.dll
::pause
::timeout /t 5