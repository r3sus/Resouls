gcc -Wall -Wl,--out-implib,libmessage.a -Wl,--enable-stdcall-fixup exports.DEF %1 -shared -o DINPUT8.dll
del /q libmessage.a 