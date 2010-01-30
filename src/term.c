/**
 * Basic terminal I/O routines
 * @file term.c
 */

#ifndef TERM_C_
#define TERM_C_

#include <posk/term.h>
#include "slab.c"
#include "port.c"

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
 *  Offset = Width Y * X +
 * 
 *  Take the point "5, 5"
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
 * Update the cursor's location ( to the graphics card )
 * @vorsicht
 */
void update_cursor() {
    unsigned temp;

    /* The equation for finding the index in a linear
    *  chunk of memory can be represented by:
    *  Index = [(y * width) + x] */
    temp = _POSK_CURS_Y * MAX_WIDTH + _POSK_CURS_X;

    /* This sends a command to indicies 14 and 15 in the
    *  CRT Control Register of the VGA controller. These
    *  are the high and low bytes of the index that show
    *  where the hardware cursor is to be 'blinking'. To
    *  learn more, you should look up some VGA specific
    *  programming documents. A great start to graphics:
    *  http://www.brackeen.com/home/vga */

    outportb(0x3D4, 14);
    outportb(0x3D5, temp >> 8);
    outportb(0x3D4, 15);
    outportb(0x3D5, temp);
}

/**
 * place the cursor at an arbitrary location on the screen
 * @param x x location of the cursor
 * @param y y location of the cursor
 */
void place_cursor( int x, int y ) {
	_POSK_CURS_Y = x;
	_POSK_CURS_X = y;
	update_cursor();
}


/**
 * print a char to the screen, and place cursor at activity
 * @vorsicht
 * @param c char to be printed
 * @param foreground foreground color 
 * @param background background color
 * @param x x location of the char
 * @param y y location of the char
 */
void posk_print_char(
	unsigned char c,
	unsigned char foreground,
	unsigned char background,
	int x,
	int y
) {
	unsigned short attrib = (background << 4) | (foreground & 0x0F);
	volatile unsigned char * where;
	where = (unsigned char *) POSK_TEXT_RAM_LOC;

	where[get_posk_tty_offset(x, y)] = c;
	where[get_posk_tty_offset(x, y) + 1] = attrib;

	update_cursor();
}

/**
 * Startup the terminal hacks.
 * @vorsicht
 */
void setup_terminal() {
	posk_clear_screen( 0x00 ); // black
	place_cursor( 0, 0 );
}

int get_posk_tty_offset( int x, int y ) {
	return (( y * MAX_WIDTH ) + x ) * 2;
}

void shift_tty_up() {
	unsigned char * rloc = (unsigned char *) POSK_TEXT_RAM_LOC;
	int ix = 0;
	int iy = 1;
	for ( ; iy < MAX_HEIGHT; ++iy ) {
		for ( ; ix < MAX_WIDTH * 2; ++ix ) {
			rloc[get_posk_tty_offset(ix, iy - 1)] = rloc[get_posk_tty_offset(ix, iy)]; //lolwut?
		}
	}
}

/**
 * kernel print to the screen.
 * @param c char array to be printed
 */
void kprintf( char * c ) {
	int i = 0;
	for ( ; i < ksize0f( c ); ++i ) {
		if ( _POSK_CURS_X > MAX_WIDTH ) {
			_POSK_CURS_Y++;
			_POSK_CURS_X = 0;
		}
		if ( _POSK_CURS_Y >= MAX_HEIGHT ) {
			shift_tty_up();
			_POSK_CURS_Y = MAX_HEIGHT;
		}
		if ( c[i] == NEWLINE ) {
			_POSK_CURS_Y++;
			_POSK_CURS_X = 0;
		} else {
			posk_print_char( c[i], POSK_GREEN, POSK_BLACK, _POSK_CURS_X, _POSK_CURS_Y );
			POSK_CURS_X++;
		}
	}
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

#endif
