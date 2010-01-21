CC=gcc

INC=./include/
SRC=./src/
BIN=./bin/
LIB=./lib

KERNEL_FLAGS=-I $(INC)

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
	@echo -n "$(CC) posk.c --> bin/posk"
	@$(CC) -o $(BIN)posk $(SRC)posk.c $(KERNEL_CONFIG)
	@echo "          [ OK ]"
