CC=gcc
ASM=nasm

INC=./include/
SRC=./src/
BIN=./bin/
LIB=./lib/

KERNEL_CONFIG=-fno-stack-protector -fno-builtin -nostdinc -g -I $(INC)

include ./posk/config/*

all:
	@echo "---- Building posk ----"
	@echo ""
	@echo "Build requirements force the builder to pour the"
	@echo "blood of an unwed virgin into the CDROM drive."
	@echo "Ensure this step is complete before proceeding."
	@echo ""
	@echo ""
	@echo -n "Building the ASM"
	@$(ASM) -f aout $(SRC)kernel_start.asm -o $(BIN)kern_start.o
	@echo "       [ ok ]"
	@echo -n "Building the C  "
	@gcc -c $(SRC)posk.c -o $(BIN)posk.o $(KERNEL_CONFIG)
	@echo "       [ ok ]"
	@echo -n "Building the LNK"
	@ld -T $(SRC)link.ld -o $(BIN)posk.bin $(BIN)kern_start.o $(BIN)posk.o
	@echo "       [ ok ]"
	@echo -n "Cleaning the bin"
	@rm -f $(BIN)*.o
	@echo "       [ ok ]"
	@echo ""
	@echo "Kernel is now in $(BIN)posk.bin"
	@echo ""
