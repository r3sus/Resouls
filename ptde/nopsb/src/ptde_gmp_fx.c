#include <windows.h>

#define DEBUG

 #ifdef DEBUG
#include <stdio.h>
#define DEBUG_PRINT printf
 #else
#define DEBUG_PRINT(...)
 #endif

#include "mmr.c"

#include "d8w.c"

byte byseq [] = { 0x8B, 0x51, 0x10, 0x6A, 0x01, 0x56 };
//                                         ^
void attach_hook(void)
{
#ifdef DEBUG
 AllocConsole(); freopen("CONOUT$", "w", stdout);
#endif

void *x = sigscan(byseq, sizeof(byseq));
byte b1 = 2;
wp(x+4, &b1, 1);
}
       
BOOL APIENTRY DllMain(HMODULE mod, DWORD reason, LPVOID res)
{
    switch (reason) {
    case DLL_PROCESS_ATTACH:
	attach_hook();
        //chainload();
        FreeLibrary(mod);
	break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
	break;
    }
    return TRUE;
}
