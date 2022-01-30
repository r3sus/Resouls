gcc -m32 -masm=intel -Wall -Wl,--enable-stdcall-fixup exports.DEF *dll.c -shared -o ..\DINPUT8.dll
::pause