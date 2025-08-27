#include <windows.h>
#include <stdio.h>

void mowin(void)
{
int Z = 0, X, Y, cx, cy, n;
UINT uFlags = SWP_NOSIZE;

char
ont, nom,
*cfg_fn = "_PTDE_fix_mowin.txt",
*fmt = "onTop%c noMove%c moveTo=%dx%d reSize=%dx%d",
*lpClassName = "DARK SOULS",
*lpWindowName = lpClassName;
#ifdef __x86_64
lpWindowName = "DARK SOULS™: REMASTERED";
#endif

FILE* f1 = fopen(cfg_fn,"r");
if (f1)
{
n = fscanf(f1, fmt, &ont, &nom, &X, &Y, &cx, &cy);
}
fclose(f1);

if (n != 6)
{
f1 = fopen(cfg_fn,"w");
ont = nom = '-'; X = Y = cx = cy = 0;
fprintf(f1, fmt, ont, nom, X, Y, cx, cy);
fflush(f1);
fclose(f1);
}

if (cx>1 && cy>1) uFlags = 0; //uFlags & SWP_NOSIZE;
if (ont=='+') Z = -1;
if (nom=='+') uFlags = uFlags | SWP_NOMOVE;

HWND h1 = NULL;

while (!h1)
{
h1 = FindWindowA(lpClassName,lpWindowName);
}
SetWindowPos(h1, (HWND)Z, X, Y, cx, cy, uFlags);
//SetWindowPos(h1, 0, 0, 0, 0, 0, 1);
}