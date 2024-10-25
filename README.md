# SIMAVR_Timer_Heartbeat
This is a program that uses simavr to simulate an atmega238p and manipulates 2 gpio pins using a the builtin timers

#To Install
run `make install_deps`. This will install the necessary dependencies. It was hard to be sure that I didn't miss any of them, so you may need to install some extra things. 

I also downloaded and manually built the avr gcc toolchain from here: https://www.microchip.com/en-us/tools-resources/develop/microchip-studio/gcc-compilers, but I don't think it was necessary, I think the avr-libc package covers it as well. 
