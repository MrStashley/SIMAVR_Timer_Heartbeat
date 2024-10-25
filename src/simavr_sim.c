/*
 * The _MMCU_ macro creates a header in the final elf that lets simavr know what I/O to trace 
 */

#include <simavr/avr/avr_mcu_section.h>
#include <avr/io.h>

AVR_MCU(16000000, "atmega328p");
AVR_MCU_VCD_FILE("simavr_trace.vcd", 1000);

const struct avr_mmcu_vcd_trace_t _mytrace[] _MMCU_ = {
	{ AVR_MCU_VCD_SYMBOL("PIN13"), .mask = (1 << 5), .what = (void*)&PORTB },
	{ AVR_MCU_VCD_SYMBOL("PIN7"), .mask = (1 << 7), .what = (void*)&PORTD },
};

