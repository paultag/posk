CC=gcc

INC=./include/
SRC=./src/
BIN=./bin/
LIB=./lib

KERNEL_FLAGS=-I $(INC)

KERNEL_CONFIG=$(KERNEL_FLAGS)

include ./posk/config/*

all:
	clear
	@echo "$(CC) posk.c --> bin/posk"
	@$(CC) -o $(BIN)posk $(SRC)posk.c $(KERNEL_CONFIG)
