#include <windows.h>
#include "ldlb.c"

typedef HRESULT (WINAPI *dinp8crt_t)(HINSTANCE, DWORD, REFIID, LPVOID *, LPUNKNOWN);
dinp8crt_t oDirectInput8Create;

__attribute__ ((dllexport))
HRESULT WINAPI DirectInput8Create(HINSTANCE inst, DWORD ver, REFIID id, LPVOID *pout, LPUNKNOWN outer)
{
    return oDirectInput8Create(inst, ver, id, pout, outer);
}

void setup_d8proxy(void)
{
    char syspath[320];
    GetSystemDirectoryA(syspath, 320);
    strcat(syspath, "\\dinput8.dll");
    HMODULE mod = LoadLibraryA(syspath);
    oDirectInput8Create = (dinp8crt_t)GetProcAddress(mod, "DirectInput8Create");
}

void wb(void *adr, byte val)
{
DWORD op1 = 0x40;
 VirtualProtect(adr, 1, op1, &op1);
*(byte*)(adr) = val;
 VirtualProtect(adr, 1, op1, &op1);
}

void attach_hook(void)
{
void *base_addr = GetModuleHandle(NULL);
while (*(byte*)(base_addr + 0x1DA2054) != 1)
{}
wb(base_addr + 0x70C599, 1);
}

void OnAttach(HMODULE hModule) {
attach_hook();
FreeLibraryAndExitThread( hModule, 0 );
ExitThread( 0 );
}

void chainload()
{
DEBUG_PRINT("chainload ");
loadDLLs("_load_",".dll");
loadDLLs(".","_load_");
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason,
		      LPVOID res)
{
    switch (reason) {
    case DLL_PROCESS_ATTACH:
    setup_d8proxy();
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)OnAttach, hModule, 0, NULL);
    chainload();
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
	break;
    }
    return TRUE;
}