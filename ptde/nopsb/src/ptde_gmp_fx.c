#include <windows.h>

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

void logo()
{
byte logo_sig [] = {0x8B, 0x86, 0x00, 0x01, 0x00, 0x00, 0x83, 0xF8, 0x03, 0x0F, 0x87},
     logo_fix [] = {0xe9, 0x27, 0x01, 0x00, 0x00, 0x90, 0x90,};
void *x = sigscan(logo_sig, sizeof(logo_sig));
wp(x+0x10, logo_fix, sizeof(logo_fix));
}

void offline()
{
byte offline_sig [] = {0x80, 0xBE, 0x05, 0x01, 0x00, 0x00, 0x00, 0x5F},
     offline_fix [] = {0x74, 0x0d,};
void *x = sigscan(offline_sig, sizeof(offline_sig));
wp(x+0x83-0x7B, offline_fix, sizeof(offline_fix));
}


void attach_hook()
{
#ifdef DEBUG
 AllocConsole(); freopen("CONOUT$", "w", stdout);
#endif

gamepad();
logo();
offline();

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
