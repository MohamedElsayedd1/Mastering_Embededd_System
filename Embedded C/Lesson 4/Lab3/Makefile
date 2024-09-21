CC=arm-none-eabi
CFLAGS=-std=c99 -c -gdwarf-2 -mcpu=cortex-m4 -mthumb
INCS=-I .
LIBS=
SRC= $(wildcard *.c)
ASS= $(wildcard *.s)
OBJ= $(SRC:.c=.o) $(ASS:.s=.o)
PROJ= toggle-led

all : $(PROJ).bin
	@echo "=====Application is built successfully====="

%.o : %.s
	$(CC)-gcc $(CFLAGS) $(INCS) $< -o $@

%.o : %.c
	$(CC)-gcc $(CFLAGS) $(INCS) $< -o $@

$(PROJ).elf : $(OBJ) $(LIBS)
	$(CC)-ld -T linker_script.ld -Map=$(PROJ).map $(OBJ) $(LIBS) -o $@
	cp $(PROJ).elf $(PROJ).axf

$(PROJ).bin : $(PROJ).elf
	$(CC)-objcopy -O binary $< $@

clean_all : 
	rm *.elf *.bin *.o

clean : 
	rm *.elf *.bin
