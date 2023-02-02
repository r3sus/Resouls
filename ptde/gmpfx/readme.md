~ PTDE Gamepad Slowing Launch Fix 

[Video](https://youtu.be/G1kuDG4aM_A)

~ Usage:  

First, backup exe. Then, options:

- using Cheat Engine:  
Place the CT in movWW folder and launch script. To restore changes, relaunch. [Video](https://youtu.be/G1kuDG4aM_A?t=88)

- using HxD:  
Find the "74 0F 8D 46 14" and replace the 74 with EB. The way around to restore back. [Video](https://youtu.be/G1kuDG4aM_A?t=125)

~ Thanks to:  
- Developers of x64dbg and Cheat Engine.
- [djlastnight/KeyboardSplitterXbox](https://github.com/djlastnight/KeyboardSplitterXbox) - Emulates Gamepad with Keyboard. Actually the core of the research, as I don't have the physical. [(alternative)](https://steamcommunity.com/sharedfiles/filedetails/?id=2140751909)  
- [JakubMelka](https://github.com/JakubMelka) for their responsiveness in [this issue](https://github.com/JakubMelka/PDF4QT/issues/38), inspiring me for debugging.  
- [article](https://nee.lv/2021/02/28/How-I-cut-GTA-Online-loading-times-by-70/) providing method of inspecting bottlenecks with [profiler](https://lukestackwalker.sourceforge.net/). 

~ How it was figured:

First off, I used the profiler wrong and realized it only when writing this. I didn't built the calling tree as in the article and I'm still unsure how to do this, otherwise it might have helped a lot. So, it showed me only known functions from modules with symbols. Launching exe with gamepad showed significantly higher use of ZwWaitForSingleObject: 60-70 vs 20-40 %. 
  
The most work is done in x32dbg. Placing breakpoints, figuring regularities: trial and error. It led to some functions that are called 32 times per start - instantly if gamepad is off, else ~1s/cycle, resulting the full load time of ~40s.  

Underneath, the F2 calls `di8->_CDIObj_EnumDevicesW` with F1. di8 calls the F2 for each gamepad, and F1 does some magic with fastprox (related to wbem) making load that long. Simply making the jump deterministic in start of F1 does the trick. Otherwise, the di8 call might be overriden, but presumebly resulting trickier AoB.  