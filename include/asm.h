/**
 * XXX: Docme
 */
#ifndef ASM_H_
#define ASM_H_ FOOBAR

#include <types.h>

void    outb ( uint16_t port, uint8_t value );
uint8_t inb  ( uint16_t port );
uint16_t inw ( uint16_t port );

#define DEBUG asm volatile("xchg %bx,%bx");

#endif
