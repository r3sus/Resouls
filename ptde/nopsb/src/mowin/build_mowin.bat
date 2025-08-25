gcc -m32 -Wall -Wl,--enable-stdcall-fixup mowin.c -shared -o _load_PTDE_mowin.dll &&^
gcc -m64 -Wall mowin.c -shared -o _load_DSR_mowin.dll