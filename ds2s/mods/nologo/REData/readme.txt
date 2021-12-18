- ds2s no logo mod -

skip the 3 logos at game launch

- how to -

write byte = 1 and logo wouldn't appear

DarkSoulsII.exe+1604DFA (141604DFA)

- usage - 

Simply set value to 1 after launching the game. 
In order to make it work automatically after game restart:
 add game process name * to auto-attach list in CE settings and tick 'Even ...'. 
 * or part of it, I use 'dark'.
Freeze the value at 1. 

- further actions -

The more convinient would be the DLL that alters the code or just changes the value after image unpacking. 
That would be also nice to make it work by static PE patch.

The logos appear only once as you launch the game, the real annoying element is never ending messages when you play game in offline mode.

- inspired by -
famous nologo patches for all other souls games. 
get familiar with wulf2k's vision on nologos at 
https://www.reddit.com/r/DarkSoulsMods/comments/a12yuk/comment/ean68au

- normal execution routine - 

DarkSoulsII.exe.text+FC870:
 xor eax,eax
 cmp [DarkSoulsII.exe+1604DFA],al
 mov byte ptr [DarkSoulsII.exe+1604DFA],01
 setne al

- how it was figured - 

Launch the game, wait for initial load - window resize, pause process. [1]
Find RTTI class instances with 'logo' in name. [2]
Fill CE memory scan limits so they're fully in it: 
 Start = first class offset, Stop = Last + (instance size). 
 Scan for unknown Byte value. [3]
 After first logo, scan for 'Changed'. Might repeat several times.
 Look what accesses values, observe nearby instructions. I've included director's cut log of my actions. 
Upon looking, very suspicious procedure was found floating in betwixt of int3 at DarkSoulsII.exe.text+FDB20:
mov byte ptr [DarkSoulsII.exe+1604DFA],00; ret
Altho, the procedure itself doesn't reached normally, it was found to be a 'Logos' boolean. Setting it to 1 before the logos started allows you to skip them.

[1] The more accurate way is to 'Start process' from CE so it stop on entry point. 
[2] you could use CE_RTTI_Scanner or Sam's CD2.
https://github.com/r3sus/CE_RTTI_Scanner
https://github.com/samsonpianofingers/ClassDumper2 (inject DLL with CE)
[3] Altho it was more reasonable to scan for booleans: either 0 or 1, that toggles after certain action. Altho the golden rule * is to never search for zero's as first scan, we could've gone for it, since memory limits are narrow. * Figured by BadEcho