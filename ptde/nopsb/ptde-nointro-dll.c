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

#include "ldlb.c"

void asm_psb_sig() { asm ("mov [esi+0x118],bl; .byte 0xC6; "); };

void asm_nopsb() { asm ("mov byte ptr [esi+0x10c],01; ret 4; "); }

void asm_nomsg() { asm ("mov [eax+0x60],edi; ret 8; "); }

void attach_hook(void)
{

#ifdef DEBUG
 AllocConsole(); freopen("CONOUT$", "w", stdout);
#endif

void *x = sigscan(asm_psb_sig, 'a');

wp(x-0xFD+0x4E, asm_nopsb, 'a');

DWORD msg_sig = 0x581C46C7;

x = sigscan(&msg_sig, 'b');

wp(x-0x96+0x55, asm_nomsg, 'a');

}

void chainload()
{
DEBUG_PRINT("chainload ");
loadDLLs("_load_",".dll");
loadDLLs(".","_load_"); 
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
