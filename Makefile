CC=gcc
ASM=nasm

INC=./include/
SRC=./src/
BIN=./bin/
LIB=./lib/

KERNEL_CONFIG=-fno-stack-protector -fno-builtin -nostdinc -g -I $(INC)

include ./posk/config/*

docs:
	@doxygen doc/DocumentCode

all:
	@echo "---- Building posk ----"
	@echo ""
	@echo "Build requirements force the builder to pour the"
	@echo "blood of an unwed virgin into the CDROM drive."
	@echo "Ensure this step is complete before proceeding."
	@echo ""
	@echo ""
	@echo -n "Translating ASM to Binary Object"
	@$(ASM) -f aout $(SRC)kernel_start.asm -o $(BIN)kern_start.o
	@echo "\t\t[ ok ]"
	@echo -n "Compiling C to Binary Object    "
	@gcc -c $(SRC)posk.c -o $(BIN)posk.o $(KERNEL_CONFIG)
	@echo "\t\t[ ok ]"
	@echo -n "Linking the C and ASM to posk.bin"
	@ld -T $(SRC)link.ld -o $(BIN)posk.bin $(BIN)kern_start.o $(BIN)posk.o
	@echo "\t\t[ ok ]"
	@echo -n "Cleaning up the object files     "
	@rm -f $(BIN)*.o
	@echo "\t\t[ ok ]"
	@echo ""
	@echo "Kernel is now in $(BIN)posk.bin"
	@echo ""
