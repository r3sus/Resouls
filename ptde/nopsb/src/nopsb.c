#include <windows.h>

//#define DEBUG
#include <stdio.h>

 #ifdef DEBUG
#define DEBUG_PRINT printf
 #else
#define DEBUG_PRINT(...)
 #endif

#include "mmr.c"

#include "d8w.c"

void asm_psb_sig() { asm ("mov [esi+0x118],bl; .byte 0xC6; "); };

void asm_nopsb() { asm ("mov byte ptr [esi+0x10c],01; ret 4; "); }

void asm_nomsg() { asm ("mov [eax+0x60],edi; ret 8; "); }

void attach_hook(void)
{

#ifdef DEBUG
 AllocConsole(); freopen("CONOUT$", "w", stdout);
#endif

void *x = sigscan(asm_psb_sig, 0);

wp(x-0xFD+0x4E, asm_nopsb, 0);

if(fopen("nomsg","r") ) {

DEBUG_PRINT("\nnomsg");

DWORD msg_sig = 0x581C46C7;

x = sigscan(&msg_sig, 4);

wp(x-0x96+0x55, asm_nomsg, 0);
}

}

BOOL APIENTRY DllMain(HMODULE mod, DWORD reason, LPVOID res)
{
    switch (reason) {
    case DLL_PROCESS_ATTACH:
	attach_hook();
        FreeLibrary(mod);
	break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
	break;
    }
    return TRUE;
}
