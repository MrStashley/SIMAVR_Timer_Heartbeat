# SIMAVR_Timer_Heartbeat
This is a program that uses simavr to simulate an atmega238p and manipulates 2 gpio pins using a the builtin timers. I am visiting my parents right now and I didn't have any microcontrollers lying around, so I used simavr to simulate an atmega328p mcu. I used the built in 16 bit timer timer1 as well as the 8 bit timers to turn the led's off after 30ms.

Using the atmega328p timer interrupts, this approach is very fast and performant, but the execution time of the interrupt handler as well as potential variability of when multiple interrupts are handled could cause a non-deterministic delay. If determinism was super important, some other approaches would be to use an RTOS or use the timer specific gpio pins to control the led's directly through hardware. 

# To Install and Compile
This program is meant to be run on a debian based linux system. To install the dependencies 
```
make install_deps
``` 
This will install the necessary dependencies. It was hard to be sure that I didn't miss any of them, so you may need to install some extra things, or change the -I cflags in the makefile. If you are seeing missing libc header errors, you probably need to specifiy -I<path to your avr-libc install>  

I also downloaded and manually built the avr gcc toolchain from here: https://www.microchip.com/en-us/tools-resources/develop/microchip-studio/gcc-compilers, but I don't think it was necessary, I think the avr-libc package covers it as well. 

There is already a compiled elf in the repo, but it can be recompiled with
```
make
```

# To Run
```
make run
```
To run the demo. This will run the simulation for 30 seconds, and then open a gtkwave window which will allow you to view a waveform of the activity of 2 of the gpio pins on the atmega328p that are most commonly used to hook up to led's. 

Within gtkwave, click on the menu item labelled "logic" and then double click on "PIN13" and "PIN7" to load them into the window. Then you will also probably have to zoom out with the square - button on the upper window, and use the bottom horizontal scroll to view the waveform. 

Unfortunately, simavr won't update the trace file until after the simulation finishes running, so you can't view the led's in real time. If I had more time I was thinking I would make a mock interface for the gpio pins using uart and then make a little pyQT ui to show the led's blinking, but I figured I shouldn't spend more than the recommended few hours on this challenge. 
