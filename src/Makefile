CC=gcc
ASM=nasm
INC=../include/
BIN=../bin/

SOURCES=$(shell  ls *.c | sed s/.c$$/.o/g)
SOURCES+=$(shell ls *.s | sed s/.s$$/.o/g)

CFLAGS=-O2 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -I$(INC)
LDFLAGS=-Tlink.ld
ASFLAGS=-felf

all: $(SOURCES) link
	echo $(SOURCES)

clean:
	@rm -f *.o
	@if [ -e $(BIN)posk.bin ]; then rm $(BIN)posk.bin; fi

link:
	@echo "[33mLinking to posk.bin[0m"
	@ld $(LDFLAGS) -o $(BIN)posk.bin $(SOURCES)

.c.o:
	@echo "[33m Building: $< ( $@ ) [0m"
	@$(CC) $(CFLAGS) -c -o $@ $<

.s.o:
	@echo "[33m Building: $< [0m"
	@$(ASM) $(ASFLAGS) $<
