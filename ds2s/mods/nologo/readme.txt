- ds2s no logo -

no logos at game launch

- usage -

Put the DINPUT8.dll in game folder.

- inspired by -

famous nologo patches for all other souls games. 

get familiar with wulf2k's vision on nologos at 
https://www.reddit.com/r/DarkSoulsMods/comments/a12yuk/comment/ean68au

- technical details -

dinput8.dll proxy 

sets the value so as the logo were already played:
byte 01 at 141604DFA (DarkSoulsII.exe+1604DFA)

Alternative option is code alteration at
DarkSoulsII.exe.text+FC87F - 0F95 C0 - setne al
reverse instruction setne to sete, that is 95 => 94 at 0x1400FD880

get familiar how it was figured at REData/

- build -

To build, you need gcc compiler as part of MinGW-w64. It is provided by many projects and many of them will work:

- version from Sourceforge
- MSYS2/Cygwin + package mingw-w64-x86_64-gcc
- bundled with CodeBlocks/Lite (untested)
- any other 

From the project's terminal:
build.bat ds2s-nologo.c

if you've added mingw-w64\bin to %path% you can also drag and drop .c on .bat

- credits -

This is completely based on excellent project by NEZ64:
https://github.com/NEZ64/DarkSoulsOfflineLogoSkip
with minimum requirements to build, available to all

hint by pseudostripy to use mingw64:
https://github.com/pseudostripy/bbj_mod_sotfs
altho w32 compiles fine, it doesn't works

and the original patching mechanism by bladecoding:
https://github.com/bladecoding/DarkSouls3RemoveIntroScreens