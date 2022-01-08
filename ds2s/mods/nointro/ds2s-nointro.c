#include <windows.h>

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

void *base = GetModuleHandle(NULL);
*(byte*)(base + 0x1604DFA) = 1; //nologo

wb(base + 0x4F7136, 1); // nomsg

wb(base + 0xFDAA6, 2); // nopsb

wb(base + 0x10EBFFA, '_'); //novid

}

BOOL APIENTRY DllMain(HMODULE mod, DWORD reason,
		      LPVOID res)
{
    switch (reason) {
    case DLL_PROCESS_ATTACH:
	setup_d8proxy();
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
