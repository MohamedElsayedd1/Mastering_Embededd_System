# @Eng. Mohamed Elsayed 
# Makefile

CC=arm-none-eabi
CFLAGS=-c -gdwarf-2 -mcpu=cortex-m3 -mthumb
INCS=-I .
LIBS=
SRC = $(wildcard *.c)
ASS = $(wildcard *.s)
OBJ = $(SRC:.c=.o) $(ASS:.s=.o)
PROJ=toggle-led

.PHONY: all clean clean_all

all : $(PROJ).bin 
	@echo "App is built successfully"

%.o : %.c
	$(CC)-gcc $(CFLAGS) $(INCS) $< -o $@

%.o : %.s
	$(CC)-gcc $(CFLAGS) $(INCS) $< -o $@

$(PROJ).elf : $(OBJ)
	$(CC)-ld -T linker_script.ld -Map=$(PROJ).map $(OBJ) $(LIBS) -o $@

$(PROJ).bin : $(PROJ).elf
	$(CC)-objcopy -O binary $< $@

clean_all : 
	rm *.elf *.bin *.o

clean : 
	rm *.elf *.bin