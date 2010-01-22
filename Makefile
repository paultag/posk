CC=gcc

INC=./include/
SRC=./src/
BIN=./bin/
LIB=./lib

KERNEL_FLAGS=-fno-stack-protector -fno-builtin -nostdinc -O2 -g -I $(INC)

KERNEL_CONFIG=$(KERNEL_FLAGS)

include ./posk/config/*

all:
	@echo "---- Building posk ----"
	@echo ""
	@echo "Build requirements force the builder to pour the"
	@echo "blood of an unwed virgin into the CDROM drive."
	@echo "Ensure this step is complete before proceeding."
	@echo ""
	@echo ""
	@gcc $(SRC)posk.c -o $(BIN)main.o
	@ld -T $(SRC)link.ld -o $(BIN)kernel.bin $(BIN)boot.o $(BIN)main.o

