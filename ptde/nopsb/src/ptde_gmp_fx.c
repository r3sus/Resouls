#include <windows.h>
#include "introoffline.c"

//#define DEBUG

 #ifdef DEBUG
#include <stdio.h>
#define DEBUG_PRINT printf
 #else
#define DEBUG_PRINT(...)
 #endif

#include "mmr.c"

#include "d8w.c"

void gamepad()
{
byte b1 = 2, gamepad_sig [] = { 0x8B, 0x51, 0x10, 0x6A, 0x01, 0x56 };                                         
void *x = sigscan(gamepad_sig, sizeof(gamepad_sig));
wp(x+4, &b1, 1);
}

void attach_hook()
{
#ifdef DEBUG
 AllocConsole(); freopen("CONOUT$", "w", stdout);
#endif

gamepad();
introoffline();
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
