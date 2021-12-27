- ds2s fast quit -

quit to main menu by setting value with CE
set hotkey to do it fast

- usage -

click on quit, Ctrl + H, edit HK => set yours
save

make sure to setup auto-attach in settings, so CE auto hooks the game, even if you restart

- credits -

Atvaark - scan algho for player base 

- how it was figured -

the idea: the value changes immediately as you press quit, so there should not be much values to filter

and realization:

search for unk 4 byte value (hex) 
changed instantly after you press quit
repeat several times

Notes:
some interm scans are omitted
use freeze process hotkey

get ~10 values (original list is included for reference)
analyze changes after quit
experiment with values

find desired
FOWA
analyze. example:
> movzx eax,byte ptr [rsi+000024B1]
gives us a bindings

- memory map -

for correct understanding of structure

7FFE9F50260 
RTTI Class Instance
GameManagerImp : GameManager

/\ ReClassNET can read them

+0128 
000007FFE9F50388
str ptr 
'Player Heap'

+0148
000007FFE9F503A8
str
'Player Heap'

+24B1
000007FFE9F5271
byte 
06 => quit