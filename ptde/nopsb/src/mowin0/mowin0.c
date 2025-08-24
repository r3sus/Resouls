#include <windows.h>

void attach_hook(void)
{
HWND h1 = NULL;

while (!h1)
{h1 = FindWindowA("DARK SOULS",NULL);}
SetWindowPos(h1, 0, 0, 0, 0, 0, 1);
}

void OnAttach(HMODULE hModule) {
attach_hook();
FreeLibraryAndExitThread( hModule, 0 );
ExitThread( 0 );
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason,
		      LPVOID res)
{
    switch (reason) {
    case DLL_PROCESS_ATTACH:
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)OnAttach, hModule, 0, NULL);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
	break;
    }
    return TRUE;
}