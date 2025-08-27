#include <windows.h>
#include <stdio.h>

// todo

 #ifdef DEBUG
#define DEBUG_PRINT printf
 #else
#define DEBUG_PRINT(...)
 #endif

#include "..\d8w.c"
#include "..\mowin_mdl.c"

void attach_hook()
{
mowin();
}

void OnAttach(HMODULE hModule) {
attach_hook();
FreeLibraryAndExitThread( hModule, 0 );
ExitThread( 0 );
}

BOOL APIENTRY DllMain(HMODULE mod, DWORD reason, LPVOID res)
{
    switch (reason) {
    case DLL_PROCESS_ATTACH:
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)OnAttach, mod, 0, NULL);
	break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
	break;
    }
    return TRUE;
}
