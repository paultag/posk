/**
 * Common kernel code, global fuctions etc.
 * @file common.c
 */

#include <posk/common.h>

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

/**
 * Copy bytes from src to dest
 * @param dest where to copy data to
 * @param src  where to copy data from
 * @param len  length of data to copy
 */
void memcpy(uint8_t *dest, const uint8_t *src, uint32_t len) {
	const uint8_t *sp = (const uint8_t *)src;
	uint8_t *dp = (uint8_t *)dest;
	for(; len != 0; len--) *dp++ = *sp++;
}

/**
 * Write copies of val into dest of len length
 * @param dest where to write to
 * @param val where to write from
 * @param len length to write
 */
void memset(uint8_t *dest, uint8_t val, uint32_t len) {
	uint8_t *temp = (uint8_t *)dest;
	for ( ; len != 0; len--) *temp++ = val;
}


/**
 * compare two strings.
 * @param str1 first string
 * @param str2 second string
 * @ret str1 < str2, 0 if they are equal or 1 otherwise.
 */
int strcmp(char *str1, char *str2) {
	int i = 0;
	int failed = 0;
	while ( str1[i] != '\0' && str2[i] != '\0' ) {
		if ( str1[i] != str2[i] ) {
			failed = 1;
			break;
		}
		i++;
	}
	if( (str1[i] == '\0' && str2[i] != '\0') || (str1[i] != '\0' && str2[i] == '\0') )
		failed = 1;

	return failed;
}

/**
 * Copy the NULL-terminated string src into dest
 * @param dest where to copy to
 * @param src where to copy from 
 * @ret dest
 */
char * strcpy ( char *dest, const char *src ) {
	do {
		*dest++ = *src++;
	} while (*src != 0);
}

/**
 * Concatenate the NULL-terminated string src onto the end of dest
 * @param dest where to copy to
 * @param src where to copy from 
 * @ret dest
 */
char * strcat ( char *dest, const char *src ) {
	while (*dest != 0) {
		*dest   = *dest++;
	}

	do {
		*dest++ = *src++;
	} while (*src != 0);

	return dest;
}

/**
 * work out the length of a string
 * @param src string to measure
 * @ret length of the string
 */
int strlen ( char *src ) {
	int i = 0;

	while (*src++)
		i++;

	return i;
}
