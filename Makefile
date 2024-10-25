INCLUDE_DIR=$(SRC_DIR)/include
BIN_DIR = bin
OBJ_DIR = bin/obj
SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

MCU = atmega328p
F_CPU = 16000000
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -g -Os -Wall -I$(INCLUDE_DIR) -I/usr/lib/avr/include
LDFLAGS = -mmcu=$(MCU) 

EXE_NAME = main
EXE = $(BIN_DIR)/$(EXE_NAME).elf

SIM=simavr_sim
SIM_CFLAGS=-I/usr/local/include -L/usr/local/lib -lsimavr

all: $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
	avr-gcc $(CFLAGS) $(LDFLAGS) -o $@ $^


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	avr-gcc $(CFLAGS) $(LDFLAGS) -c -o $@ $<

$(BIN_DIR) $(OBJ_DIR): 
	mkdir bin 
	mkdir bin/obj

clean:
	rm -rf $(BIN_DIR)/* $(BIN_DIR)

run: 
	@echo "Running sim for 30 seconds"
	- timeout 30 simavr -m $(MCU) --trace=simavr_trace.vcd --freq=16000000 $(EXE) 
	@echo "Ran sim for 30 seconds. View output with `gtkwave simavr_trace.vcd`"

debug:
	simavr -g -m $(MCU) --trace=simavr_trace.vcd --clock=16000000 $(EXE) 	

install_deps: 
	./setup.sh
