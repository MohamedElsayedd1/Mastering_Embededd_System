CC=arm-none-eabi
CFLAGS=-c -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99
INC=-I .
LIB=
SRC= $(wildcard *.c)
ASS= $(wildcard *.s)
OBJ= $(SRC:.c=.o) $(ASS:.s=.o)
PROJ=PressureController

all : $(PROJ).bin
	@echo "---Application is built successfully----"

%.o : %.c
	$(CC)-gcc $(CFLAGS) $(INC) $< -o $@

%.o : %.s
	$(CC)-gcc $(CFLAGS) $(INC) $< -o $@

$(PROJ).elf : $(OBJ) $(LIB)
	$(CC)-ld -T linkerscript.ld  -Map=$(PROJ).map $(OBJ) $(LIB) -o $@

$(PROJ).bin : PressureController.elf
	$(CC)-objcopy -O binary $< $@

clear : 
	rm *.elf *.o *.bin