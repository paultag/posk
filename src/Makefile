INC=../include/
BIN=../bin/

SOURCES=boot.o posk.o common.o descriptor_tables.o isr.o interrupt.o gdt.o string.o term.o

CFLAGS=-nostdlib -nostdinc -fno-builtin -fno-stack-protector -I$(INC)
LDFLAGS=-Tlink.ld
ASFLAGS=-felf

all: $(SOURCES) link

clean:
	-rm *.o $(BIN)posk.bin

link:
	ld $(LDFLAGS) -o $(BIN)posk.bin $(SOURCES)

.s.o:
	nasm $(ASFLAGS) $<

