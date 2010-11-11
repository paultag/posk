CC=gcc
ASM=nasm
INC=../include/
BIN=../bin/

SOURCES=boot_s.o gdt_s.o idt_s.o posk.o common.o gdt.o idt.o monitor.o panic.o vsprintf.o timer.o pmm.o vmm.o slab.o task.o sched.o cherrytree.o

CFLAGS=-O2 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -I$(INC)
LDFLAGS=-Tlink.ld
ASFLAGS=-felf

all: $(SOURCES) link

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
