#include <asm.h>

/**
 * Write a byte to the port given
 * @param port the port to write ti
 * @param value the value to write to the port
 */
void outb(uint16_t port, uint8_t value) {
	asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

/**
 * Read input from a given port
 * @param port Port to read 
 */
uint8_t inb(uint16_t port) {
	uint8_t ret;
	asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
	return ret;
}

/**
 * read a 16 bit short word from a 16 bit I/O port. 
 * @param port port to read from
 */
uint16_t inw(uint16_t port) {
	uint16_t ret;
	asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
	return ret;
}
