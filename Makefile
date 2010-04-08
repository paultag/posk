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

