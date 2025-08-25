#include <windows.h>
#include <stdio.h>

void attach_hook(void)
{
int X, Y, cx, cy;
UINT uFlags = 1;
char *cfg_fn = "_mowin.txt", *fmt = "%d %d %d %d";
FILE* f1 = fopen(cfg_fn,"r");
if (f1)
{
fscanf(f1,fmt, &X, &Y, &cx, &cy);
fclose(f1);
}
else
{
X = Y = cx = cy = 0;
f1 = fopen(cfg_fn,"w");
fprintf(f1,fmt, X, Y, cx, cy);
fflush(f1);
fclose(f1);
}

if (cx+cy>0) uFlags = 0;

HWND h1 = NULL;

while (!h1)
{h1 = FindWindowA("DARK SOULS",NULL);}
SetWindowPos(h1, 0, X, Y, cx, cy, uFlags);
//SetWindowPos(h1, 0, 0, 0, 0, 0, 1);
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