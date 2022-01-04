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

void *base_addr = GetModuleHandle(NULL);
*(byte*)(base_addr + 0x1604DFA) = 0x01; //nologo

// nomsg
void *jne = base_addr + 0x4F7136;

DWORD op;
VirtualProtect(jne, 1,PAGE_EXECUTE_READWRITE, &op);

*(byte*)jne = 0x74;

VirtualProtect(jne, 1, op, &op);
// end

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
