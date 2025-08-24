gcc -m32 -Wall -Wl,--enable-stdcall-fixup mowin0.c -shared -o _load_PTDE_mowin0.dll &&^
gcc -m64 -Wall mowin0.c -shared -o _load_DSR_mowin0.dll