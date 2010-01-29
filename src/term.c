/**
 * Basic terminal I/O routines
 * @file term.c
 */

#include <posk/term.h>

#define POSK_TEXT_RAM_LOC    0xb8000

int posk_line = 0;

/*
 *
 *       Do you mind if I'll always love you?
 *        Do you mind if I'll always love you?
 *         Do you mind if I'll always love you?
 *
 *            Heaven's gonna burn your eyes
 *          Now Heaven's gonna burn your eyes
 *            Heaven's gonna burn your eyes
 *
 *
 *   Listen to this band. This just cranked up my
 *   code output by about 20 times.
 *
 *   I'm not kidding.
 *     -- Paul
 */


/* Developer's Note
 *
 * A)
 *
 *      0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
 *    +---------------------------------------+
 *  0 | 00| 01| 02| 03| 04| 05| 06| 07| 08| 09| 
 *  1 | 10| 11| 12| 13| 14| 15| 16| 17| 18| 19|
 *  2 | 20| 21| 22| 23| 24| 25| 26| 27| 28| 29|
 *  3 | 30| 31| 32| 33| 34| 35| 36| 37| 38| 39|
 *  4 | 40| 41| 42| 43| 44| 45| 46| 47| 48| 49|
 *  5 | 50| 51| 52| 53| 54| 55| 56| 57| 58| 59|
 *  6 | 60| 61| 62| 63| 64| 65| 66| 67| 68| 69|
 *  7 | 70| 71| 72| 73| 74| 75| 76| 77| 78| 79|
 *  8 | 80| 81| 82| 83| 84| 85| 86| 87| 88| 89|
 *  9 | 90| 91| 92| 93| 94| 95| 96| 97| 98| 99|
 *    +---------------------------------------+
 *
 * B)         N       N+1
 *       +--------+--------+
 *       |   70   |   0x0  |
 *       +--------+--------+ 
 * 
 *  BEHOLD! The Graphics Card RAM! ( kinda ) ( diagram A )
 *
 *  We are using 9 x 9, and not 80 x 16.
 *
 *  One can think of this as a 2D matrix. Each "Cell" ( Diagram B )
 *  has two parts. ASCII value of the char being displayed
 *  and a color code. Color codes are defined in term.h.
 *
 * =============== 
 *
 *  Since RAM is 1D ( Ssssh. Don't tell anyone ) we have to "fake" 2D.
 * 
 *  This is a bit the Dr. Palmer taught me. Freshman year.
 *  I'm using something I learned Freshman Year in a kernel.
 *   Listen to the man.
 * 
 *  Offset = ( X + ( Y * Width )
 * 
 *  Take the point "5, 5"
 * 
 * 
 *  Offset = 10 5 * 5 +
 *  Offset = 50 5 +
 *  Offset = 55
 *
 *  As you can see by the graph ( Diagram A ), this number is spot on.
 *    -- Paul
 *
 */

/*
 * Yes, that last example was in RPN. No I don't have too much time.
 * Just too much work to do.
 *  -- Paul
 *
 */

/**
 * A function to display a char in the top left corner of the screen
 * @param c ASCII char value of the char to print
 */
void posk_print_char_tl( char c ) {
	unsigned char * videoram = (unsigned char *) POSK_TEXT_RAM_LOC;
	videoram[0] = c;
	videoram[1] = POSK_WHITE_TXT;
}

/**
 * A function to display a line of text
 * @param c a char pointer to the string to be printed
 */
void posk_print_line( char * c ) {
	posk_line++;
	if ( posk_line > MAX_HEIGHT ) {
		posk_line = 0;
	}
	int i = 0;
	posk_clear_line( posk_line );
	for ( ; i < ksize0f( c ); ++i ) {
		posk_print_char( i, posk_line, c[i] );
	}
}

/**
 * A function to clear a line of the text-mode screen
 * @param l the int value of the screen. 0 to MAX_HEIGHT, inclusive.
 */
void posk_clear_line( int l ) {
	unsigned char * vidmem = (unsigned char *) POSK_TEXT_RAM_LOC;
	int start_ram = ( l * MAX_WIDTH * 2 );
	int i = start_ram;
	while ( i < ( start_ram + MAX_WIDTH * 2 ) ) {
		vidmem[i] = ' ';
		++i;
		vidmem[i] = POSK_GREEN_BG;
		++i;
	};
}

/**
 * A function to display a char in any position on the screen
 * @param x the X location, from  0 to MAX_WIDTH, inclusive.
 * @param y the Y location, from  0 to MAX_HEIGHT, inclusive.
 * @param c a char array pointer holding the string to be printed, null termintated.
 */
void posk_print_char( int x, int y, char c ) {
	unsigned char * videoram = (unsigned char *) POSK_TEXT_RAM_LOC;
	int offset = x * 2 + ( ( y * MAX_WIDTH ) * 2 );
	videoram[offset] = c;
	videoram[offset + 1] = POSK_WHITE_TXT; /* forground, background color. */
}

/**
 * A function to clear the whole RAM buffer
 * @param c Color code, as spec'ed out in term.h.
 */
void posk_clear_screen( int c ) { // clear the entire text screen
	char * vidmem = (char *) POSK_TEXT_RAM_LOC;
	unsigned int i = 0;
	while ( i < ( ( MAX_WIDTH * MAX_HEIGHT ) * 2 ) ) {
		vidmem[i] = ' ';
		i++;
		vidmem[i] = c;
		i++;
	};
};

