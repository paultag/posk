/**
 * Defines typedefs and some global functions
 * This is from JamesM's Kernel. 
 * @file common.h
 */

#ifndef COMMON_H_
#define COMMON_H_ FOOBAR

// Some nice typedefs, to standardise sizes across platforms.
// These typedefs are written for 32-bit X86.
typedef unsigned int   uint32_t;
typedef          int   int32_t;
typedef unsigned short uint16_t;
typedef          short int16_t;
typedef unsigned char  uint8_t;
typedef          char  int8_t;


void outb(uint16_t port, uint8_t value);
uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);

#define DEBUG asm volatile("xchg %bx,%bx");

#endif // COMMON_H
