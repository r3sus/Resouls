#include "ldlb.c"

BOOL ld = 1;

typedef HRESULT (WINAPI *dinp8crt_t)(HINSTANCE, DWORD, REFIID, LPVOID *, LPUNKNOWN);
dinp8crt_t oDirectInput8Create;

void setup_d8proxy(void)
{
    char syspath[320];
    GetSystemDirectoryA(syspath, 320);
    strcat(syspath, "\\dinpUt8.dll");
    HMODULE mod = LoadLibraryA(syspath);
    oDirectInput8Create = (dinp8crt_t)GetProcAddress(mod, "DirectInput8Create");
}

void chainload()
{
DEBUG_PRINT("chainload: ");
loadDLLs("_load_",".dll");
loadDLLs(".","_load_"); 
DEBUG_PRINT(" \n");
}

__attribute__ ((dllexport))
HRESULT WINAPI DirectInput8Create(HINSTANCE inst, DWORD ver, REFIID id, LPVOID *pout, LPUNKNOWN outer)
{
    if (ld) {setup_d8proxy(); chainload(); ld = 0;}
    return oDirectInput8Create(inst, ver, id, pout, outer);
}
