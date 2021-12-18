#include <windows.h>
#include <string.h>

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

void attach_hook(void)
{

*(BYTE*)0x141604DFA = 0x01;
//*(BYTE*)0x1400FD880 = 0x94; -- alternative option: code alteration: setne => sete, use either

}	
BOOL APIENTRY DllMain(HMODULE mod, DWORD reason,
		      LPVOID res)
{
    switch (reason) {
    case DLL_PROCESS_ATTACH:
	setup_d8proxy();
	attach_hook();
	break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
	break;
    }
    return TRUE;
}
