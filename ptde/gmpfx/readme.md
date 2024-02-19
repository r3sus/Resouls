## PTDE Gamepad Slowing Launch Fix    
 
## Description

Some people experience very long game launch times if the gamepad is plugged in. Simply detaching it makes the game load instantly. The subject project's purpose is to fix that.     

<!-- 
That might be unhandy considering the *sockets fatigue* and possible innacurate insert. That is simplified if the gamepad has soft turn off button like wireless ones. Alternative solution is using hardware manager or external tool to toggle gamepad state. But that might be still inconvinient.  
temp thread is faster ? https://github.com/erfg12/memory.dll/wiki/Inject-a-temporary-DLL-(CPlusPlus)
-->

## Results

Launch Time with Gamepad ON:  
- normal: 44s
- fixed: 10s  

(approx.)

## DLL

[Download](./DiNPUT8.dll/?raw=true) and place in game folder.  
[Source](../nopsb/src/ptde_gmp_fx.c).  
Additional features:  
- Chainload: to use with other `dll`s, add in their name or put in folder `_load_`.  
- nologo: based on [DarkSoulsOfflineLogoSkip by NEZ64](https://github.com/NEZ64/DarkSoulsOfflineLogoSkip).   
- [nopsb](../nopsb/): to skip `Press Start Button` screen - create `nopsb.txt` in game folder.  

## Videos

Demonstation (problem, solution) and usage guides.  

[Video V0 (CT and HxD)](https://youtu.be/G1kuDG4aM_A)

[Video V1.2 (manual, CE, advanced)](https://youtu.be/ahpAS6mDNLQ)  

## Usage:  

Alternatively to DLL, exe-modifying options.  

First, backup exe. Then, options:  

1. automatic:

Cheat Table (CT):  
Place the CT in `movWW` folder and launch script. To restore changes, relaunch.  
To download the CT, hold Alt and Click on this [link](./DARKSOULS_GMP_FX_5.CT?raw=true).  
[Usage Video V0](https://youtu.be/G1kuDG4aM_A?t=88)  
  
2. manual: 

  
- Cheat Engine (CE): see vid V1.2.  

- HxD (V1.1) - [Video V0](https://youtu.be/G1kuDG4aM_A?t=125)  

Signatures to scan: 
- V1.2: `8B 51 10 6A 01 56`: `01 -> 02`. 
- V1.1: `6A 04 50 FF D2 5E`. `04 -> 05`. 
<!--
V1: 04 -> 01.  
V0: Find the "74 0F 8D 46 14" and replace the 74 with EB. The way around to restore back.
-->

V1.2 provides same result as V1.1, just an alternative.  
Replace with +1 or any higher value.  

## Thanks to:  
- Developers of x64dbg and Cheat Engine.
- djlastnight for [KeyboardSplitterXbox](https://github.com/djlastnight/KeyboardSplitterXbox) - Emulates Gamepad with Keyboard. Actually the core of the research, as I don't have the physical. [(alternative)](https://steamcommunity.com/sharedfiles/filedetails/?id=2140751909)  
- JakubMelka for their responsiveness in [this issue](https://github.com/JakubMelka/PDF4QT/issues/38), inspiring for debugging.  
- T0ST for [article](https://nee.lv/2021/02/28/How-I-cut-GTA-Online-loading-times-by-70/) providing method of inspecting bottlenecks with [profiler](https://lukestackwalker.sourceforge.net/). 
- CapitaineToinon and Kahmul.
- [NEZ64](https://github.com/NEZ64) for [DarkSoulsOfflineLogoSkip](https://github.com/NEZ64/DarkSoulsOfflineLogoSkip).   
- zelassin for extensive testing with HxD.  
- Every tester and user.  
- Author of this [SO answer](https://stackoverflow.com/a/62924338) for simple method of downloading raw file on github via browser.  
<!--
## How it was figured:

First off, I used the profiler wrong and realized it only when writing this. I didn't built the calling tree as in the article and I'm still unsure how to do this, otherwise it might have helped a lot. So, it showed me only known functions from modules with symbols. Launching exe with gamepad showed significantly higher use of ZwWaitForSingleObject: 60-70 vs 20-40 %. 
  
The most work is done in x32dbg. Placing breakpoints, figuring regularities: trial and error. It led to some functions that are called 32 times per start - instantly if gamepad is off, else ~1s/cycle, resulting the full load time of ~40s.  

Underneath, the F2 calls `di8->_CDIObj_EnumDevicesW` with F1. di8 calls the F2 for each gamepad, and F1 does some magic with fastprox (related to wbem) making load that long. Simply making the jump deterministic in start of F1 does the trick. Otherwise, the di8 call might be overriden, but presumebly resulting trickier AoB.  

V1: modifying the _last_ argument pushed to di8: 4 -> 1.  

V1.1: 4 -> 5 (or >), thanks to zela for testing.  

V1.2: _first_ arg: 1 -> 2 (or >). 
No CT - DIY edition.  finding just before push 1 and changing to 2 (or higher).  -->