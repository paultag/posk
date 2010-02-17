//
// isr.c -- High level interrupt service routines and interrupt request handlers.
//          Part of this code is modified from Bran's kernel development tutorials.
//          Rewritten for JamesM's kernel development tutorials.
//

#include <posk/common.h>
#include <posk/isr.h>

// This gets called from our ASM interrupt handler stub.
void isr_handler(registers_t regs) {
    return;
}
