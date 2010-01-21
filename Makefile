CC=gcc

INC=./include/
SRC=./src/
BIN=./bin/
LIB=./lib


KERNEL_FLAGS=-I $(INC)

all:
	$(CC) -o $(BIN)posk $(SRC)posk.c $(KERNEL_FLAGS)
