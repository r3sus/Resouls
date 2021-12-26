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
byte 01 at DarkSoulsII.exe+1604DFA

Alternative option is code alteration at
DarkSoulsII.exe.text+FC87F - 0F95 C0 - setne al
reverse instruction setne to sete, that is 95 => 94

get familiar how it was figured at REData/

- build -

gcc -m64 -Wall *.c -shared -o DINPUT8.dll

It is recommended to use MinGW-w64 WITH SJLJ, as it can target both 32 and 64 bit executables. 

- thanks -

swag - testing

- credits -

d8 wrapper:
https://github.com/bladecoding/DarkSouls3RemoveIntroScreens

c port gcc:
https://github.com/NEZ64/DarkSoulsOfflineLogoSkip

hint to use mingw64:
https://github.com/pseudostripy/bbj_mod_sotfs