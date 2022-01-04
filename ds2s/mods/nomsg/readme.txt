~ nomsg ~
no offline mode messages
nologo included

~ RE ~
scan for values changed with msg open and close
filter down as possible to ~40 values
find the single value controlling it
FOWA on creating msg (1)
BP
observe stack trace for several messages
find the level where it differs (2)
patch

~
(1)
DarkSoulsII.exe+5095A0 - mov qword ptr [rcx+000000B8],00000001 { 1 }
(2)
Go Online DarkSoulsII.exe+4F714D
Change Res DarkSoulsII.exe+4F6EA2
but both call DarkSoulsII.exe+51D50