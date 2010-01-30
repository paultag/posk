/**
 * Port I/O ASM routines
 * @file port.c
 */


#include <posk/port.h>


/**
 * read an IO port. ASM / C bridge
 * @param _port I/O port to "poke"
 *
 * We will use this later on for reading from the I/O ports to get data
 * from devices such as the keyboard. We are using what is called
 * 'inline assembly' in these routines to actually do the work 
 *
 */
unsigned char inportb (unsigned short _port) {
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

/**
 * write to an IO port. ASM / C bridge
 * @param _port I/O port to push data to
 * @param _data data to push into the port.
 *
 * We will use this to write to I/O ports to send bytes to devices. This
 * will be used in the next tutorial for changing the textmode cursor
 * position. Again, we use some inline assembly for the stuff that simply
 * cannot be done in C
 *
 */
void outportb (unsigned short _port, unsigned char _data) {
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

