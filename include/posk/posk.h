/**
 * Main POSK kernel loop routines.
 * @file posk.h
 */


#ifndef POSK_H_
#define POSK_H_ FOO

#include <posk/term.h>


/**
 * A function to count the char values in an array
 * @param m char pointer to a char array
 * @return length of the char array
 */
int ksize0f(char*m){int i=0;for(;m[i]!='\0';++i);return i;}
/*
 * Hey. Paul here.
 *   Sorry to any non C programmers who have to work out what
 *   that above method does. My bad!
 *
 * Here is a description
 *   This is dedicated to you, non-c programmer.
 *
 *
 *
 * +---+---+---+---+---/--/   /--/----+
 * | H | E | L | L | O /--/   /--/ \0 |  <== C Char Array "foo"
 * +---+---+---+---+---/--/   /--/----+
 *
 *
 * foo[0] == "H"
 * foo[1] == "E"
 * foo[2] == "L"
 * foo[3] == "L"
 *  ...
 * foo[5] == "\0"
 * 
 *
 *  So, in sudo ( yes, I know it's pseudo ) code, to echo all letters out:
 *
 *
 * while [ not "\0" ]
 *   get next char
 *   echo char
 * done
 *
 *
 * -- OR --
 *
 * foreach char
 *   echo char
 * done
 *
 *  The code above ( ksize0f ) is the same as:
 *
 ****
 *
 *  int counter = 0;
 *  foreach char
 *    counter += 1
 *  done
 *  return counter
 *
 ****
 * 
 * Gotta love the C.
 *   -- Paul
 *
 */

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
