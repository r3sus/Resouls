#include <windows.h>

#include <stdio.h>

//#define DEBUG

 #ifdef DEBUG
#define DEBUG_PRINT printf
 #else
#define DEBUG_PRINT(...)
 #endif

#include "../mmr.c"

#include "../d8w.c"

void stub_code() { asm ("ret 0x10; "); }

void write_stub()
{
    HMODULE dll_handle = GetModuleHandleA("user32.dll");
    void *fn_adr = (void *) GetProcAddress(dll_handle, "SetWindowsHookExA");
    wp(fn_adr,stub_code,0);
}

void attach_hook(void)
{
#ifdef DEBUG
 AllocConsole(); freopen("CONOUT$", "w", stdout);
#endif
write_stub();
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
