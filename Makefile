CC=gcc
ASM=nasm

INC=./include/
SRC=./src/
BIN=./bin/
LIB=./lib/

SOURCES=boot_s.o gdt_s.o idt_s.o posk.o common.o gdt.o idt.o monitor.o panic.o vsprintf.o timer.o pmm.o vmm.o slab.o

CFLAGS=-O0 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -I$(INC) -I/usr/lib/gcc/i486-linux-gnu/4.4/include/
LDFLAGS=-Tlink.ld
ASFLAGS=-felf


include ./posk/config/*

docs:
	@doxygen doc/DocumentCode
