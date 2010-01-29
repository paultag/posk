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
	posk_clear_screen( POSK_GREEN_BG );

	int i = 0;

	if ( MAX_WIDTH > ksize0f( message ) ) {
		int offset = ( MAX_WIDTH - ksize0f( message ) ) / 2 ;
		for ( ; i < ksize0f( message ); ++i ) {
			posk_print_char( offset + i, 5, message[i] );
		}

		i = 0;

		offset = ( MAX_WIDTH - ksize0f( error_code ) ) / 2 ;
		for ( ; i < ksize0f( error_code ); ++i ) {
			posk_print_char( offset + i, 3, error_code[i] );
		}

	} else {
		posk_clear_screen( POSK_RED_BG );
	}
}

#endif
