# **Power Subtitling**

An open-source sharing of the software code for *Power-subtitling*, written for MacOS OS9 between 1992 and 2000 by myself.

Initially developed in assembly language for speed, it was progressively rewritten in C/C++ with a major processor change along the way, transitioning from 680xx to PowerPC — a typical developer's journey with an innovative manufacturer.

This software was available in several versions:  

- One to control professional video cards (analog or digital, known as *D1*) via the *NuBus* port.  
- One for QuickTime (Apple's library responsible for subtitle rendering).  
- One simply for marking/cutting subtitles with just two keys.  

- A hardware box based on the **6305** [link](ressources/HD6305X0.pdf) was developed to collect *VITC* (Vertical Interval Time Code) from a video signal.  

(*Note:* I can no longer read disks in the Mac 400K/800K format.)

- A version of the software could interface via *RS 422* with professional Sony VTRs or equivalent to retrieve the time code. [link](https://en.wikipedia.org/wiki/Betacam)

There were some clever programming tricks, assembly code, a bit of real-time processing under extremely precise processor interrupts to synchronize subtitles frame-perfectly with the image.

For fun, I attempted a port to *Windows NT*, but it failed because, in NT user space, Windows' preemptive multitasking scheduler had a fixed, non-modifiable 1-millisecond increment at the time. It was nearly impossible to replicate the same precision. I thank the Windows community that supported me during that attempt.

(*A video frame is every 20ms... with a 2-3ms delay, it simply couldn't work.*)

All of this feels a bit vintage now...

[NuBus](https://www.devx.com/terms/nubus/)  
[NuVista+ Card](https://wiki.preterhuman.net/Truevision_NuVista%2B)

32 bits per pixel with an *alpha channel* — handy for alias-free overlay insertion (*soft edges*) with *oversampling*, resulting in the best possible quality.

[Antialiasing](https://en.wikipedia.org/wiki/Antialiasing)

For those who used to write software for the Mac... the books we had back then were beautiful. And then came color with the *Macintosh II*. It was during this era that I discovered typography.

I remember the NuVista+ card, but the other one… it will come back to me later.

[Link to Classic MacOS Development Books](https://knight.sc/software/2020/04/19/classic-macos-development.html)

If you're curious or just a tinkerer capable of running an OSX emulator, there’s a slim chance this might still work...

For the sake of memory, though completely useless now… if I find usable archives, I’ll post them here. It's quite challenging to read Mac 400K/800K disks nowadays… back then, there were even Jazz1Go or Zip 250KB formats. The archive comes from a Zip disk.

It’s amusing to think this code might someday end up in ChatGPT…
