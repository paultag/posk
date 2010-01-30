/**
 * Main POSK kernel loop routines.
 * @file posk.h
 */


#ifndef POSK_H_
#define POSK_H_ FOO

#include <posk/term.h>
#include <posk/slab.h>
#include <string.h>

/**
 * A function to lock up the machine, if we reach an unsafe state
 * @param error_code a char array of the error code.
 * @param message the fatal error's description
 * @return nothing. This will always lock up and block.
 */
void panic ( char * error_code, char * message ) {

	int foreground = POSK_BLACK;
	int background = POSK_GREEN;

	unsigned short attrib = (background << 4) | (foreground & 0x0F); // C-ism!

	posk_clear_screen( attrib );

	int i = 0;

	if ( MAX_WIDTH > ksize0f( message ) ) {

		int offset = ( MAX_WIDTH - ksize0f( message ) ) / 2 ;
		for ( ; i < ksize0f( message ); ++i ) {
			posk_print_char(
				message[i],
				foreground,
				background,
				offset + i,
				5
			);
		}

		i = 0;

		struct mm_slab_report * mem = get_kalloc_report();

		char * error = (char *)kalloc( sizeof( char ) * 32 );
		char tmp[16];

		strcat( error, "Memory [ Free: " );
		itoa( mem->free, tmp ); // int, char
		strcat( error, tmp );

		strcat( error, " Total: " );
		itoa( mem->exist, tmp ); // int, char
		strcat( error, tmp );

		strcat( error, " Start: " );
		itoa( (int)mem->s_addr, tmp ); // int, char
		strcat( error, tmp );

		strcat( error, " End: " );
		itoa( (int)mem->e_addr, tmp ); // int, char
		strcat( error, tmp );

		strcat( error, " ]" );

		offset = ( MAX_WIDTH - ksize0f( error ) ) / 2 ;
		for ( ; i < ksize0f( error ); ++i ) {
			posk_print_char(
				error[i],
				foreground,
				background,
				offset + i,
				10
			);
		}

		i = 0;

		offset = ( MAX_WIDTH - ksize0f( error_code ) ) / 2 ;
		for ( ; i < ksize0f( error_code ); ++i ) {
			posk_print_char(
				error_code[i],
				foreground,
				background,
				offset + i,
				3
			);
		}

	} else {
		background = POSK_RED;
		attrib = (background << 4) | (foreground & 0x0F); // C-ism!
		posk_clear_screen( attrib );
	}

	place_cursor( MAX_WIDTH - 1, MAX_HEIGHT - 1 );

	for(;;); // FFFFFFFUUUUUUUUUUUUUUU
}

#endif
