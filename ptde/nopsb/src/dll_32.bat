gcc -m32 -masm=intel -Wall -Wl,--enable-stdcall-fixup exports.DEF %1 -shared -o %2
::pause
::timeout /t 5