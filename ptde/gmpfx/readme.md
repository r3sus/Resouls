~ PTDE Gamepad Slowing Launch Fix V1.2 (DIY) and V1.1 (CT)  

V1.2:  
- provides same result as V1.1, just an alternative.  
- No Cheat Table provided, but the detailed video to do it yourself with Cheat Engine.  

[Video V1.2](https://youtu.be/ahpAS6mDNLQ)  

<!--[Video V0](https://youtu.be/G1kuDG4aM_A)-->

~ Usage:  

First, backup exe. Then, options: using ...

V1.2 and V1.1:  

- Cheat Engine: see vid.  

V1.1:

- Cheat Table:  
Place the CT in movWW folder and launch script. To restore changes, relaunch.  
To download the CT, hold Alt and Click on this [link](./DARKSOULS_GMP_FX_5.CT?raw=true).  
[Video V0](https://youtu.be/G1kuDG4aM_A?t=88)  

- HxD:  
find "6A 04 50 FF D2 5E" and replace 04 -> 05 (or higher) (V1.1).  
<!--
V1: 04 -> 01.  
V0: Find the "74 0F 8D 46 14" and replace the 74 with EB. The way around to restore back. [Video V0](https://youtu.be/G1kuDG4aM_A?t=125)}
-->

~ Thanks to:  
- Developers of x64dbg and Cheat Engine.
- djlastnight for [KeyboardSplitterXbox](https://github.com/djlastnight/KeyboardSplitterXbox) - Emulates Gamepad with Keyboard. Actually the core of the research, as I don't have the physical. [(alternative)](https://steamcommunity.com/sharedfiles/filedetails/?id=2140751909)  
- JakubMelka for their responsiveness in [this issue](https://github.com/JakubMelka/PDF4QT/issues/38), inspiring me for debugging.  
- T0ST for [article](https://nee.lv/2021/02/28/How-I-cut-GTA-Online-loading-times-by-70/) providing method of inspecting bottlenecks with [profiler](https://lukestackwalker.sourceforge.net/). 
- Author of this [SO answer](https://stackoverflow.com/a/62924338) for simple method of downloading raw file on github via browser.  
- Everyone who tried this mod.  
- zelassin for extensive testing.  
 

~ How it was figured:

First off, I used the profiler wrong and realized it only when writing this. I didn't built the calling tree as in the article and I'm still unsure how to do this, otherwise it might have helped a lot. So, it showed me only known functions from modules with symbols. Launching exe with gamepad showed significantly higher use of ZwWaitForSingleObject: 60-70 vs 20-40 %. 
  
The most work is done in x32dbg. Placing breakpoints, figuring regularities: trial and error. It led to some functions that are called 32 times per start - instantly if gamepad is off, else ~1s/cycle, resulting the full load time of ~40s.  

Underneath, the F2 calls `di8->_CDIObj_EnumDevicesW` with F1. di8 calls the F2 for each gamepad, and F1 does some magic with fastprox (related to wbem) making load that long. Simply making the jump deterministic in start of F1 does the trick. Otherwise, the di8 call might be overriden, but presumebly resulting trickier AoB.  

V1: modifying the _last_ argument pushed to di8: 4 -> 1.  

V1.1: 4 -> 5, thanks to zela for testing.  

V1.2: _first_ arg: 1 -> 2 (or >). 
<!--No CT - DIY edition.  finding just before push 1 and changing to 2 (or higher).  -->