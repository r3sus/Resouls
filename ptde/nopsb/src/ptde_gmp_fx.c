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

void nologo1()
{
byte nologo1_sig [] = {0x8B, 0x86, 0x00, 0x01, 0x00, 0x00, 0x83, 0xF8, 0x03, 0x0F, 0x87},
     nologo1_fix [] = {0xe9, 0x27, 0x01, 0x00, 0x00, 0x90, 0x90,};
void *x = sigscan(nologo1_sig, sizeof(nologo1_sig));
wp(x+0x10, nologo1_fix, sizeof(nologo1_fix));
}

void nologo2()
{
byte nologo2_sig [] = {0x80, 0xBE, 0x05, 0x01, 0x00, 0x00, 0x00, 0x5F},
     nologo2_fix [] = {0x74, 0x0d,};
void *x = sigscan(nologo2_sig, sizeof(nologo2_sig));
wp(x+0x83-0x7B, nologo2_fix, sizeof(nologo2_fix));
}

void nologo() // based on DarkSoulsOfflineLogoSkip by NEZ64
{
nologo1();
nologo2();
}

void asm_nopsb() { asm ("mov byte ptr [esi+0x10c],01; ret 4; "); }

void nopsb()
{
if(fopen("nopsb","r") ) {
void *x = sigscan(asm_psb_sig, 0);

wp(x-0xFD+0x4E, asm_nopsb, 0);
}
}

void attach_hook()
{
#ifdef DEBUG
 AllocConsole(); freopen("CONOUT$", "w", stdout);
#endif

gamepad();
nologo();
//nopsb();
}
       
BOOL APIENTRY DllMain(HMODULE mod, DWORD reason, LPVOID res)
{
    switch (reason) {
    case DLL_PROCESS_ATTACH:
	attach_hook();
        chainload();
        FreeLibrary(mod);
	break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
	break;
    }
    return TRUE;
}
