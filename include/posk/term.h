/**
 * Terminal I/O Header declarations 
 * @file term.h
 */

#ifndef TERM_H_
#define TERM_H_

#define MAX_WIDTH    80
#define MAX_HEIGHT   25

#define POSK_BLACK    0x0
#define POSK_BLUE     0x1
#define POSK_GREEN    0x2
#define POSK_CYAN     0x3
#define POSK_RED      0x4
#define POSK_MAGENTA  0x5
#define POSK_BROWN    0x6
#define POSK_GREY     0x7

#define POSK_CURS_X _POSK_CURS_X
#define POSK_CURS_Y _POSK_CURS_Y

#define NEWLINE '\n'

#define POSK_TEXT_RAM_LOC    0xb8000

int _POSK_CURS_X;
int _POSK_CURS_Y;


void              update_cursor();
void              place_cursor( int x, int y );
void              setup_terminal();
void              posk_print_char(
			unsigned char c,
			unsigned char foreground,
			unsigned char background,
			int x,
			int y
);
int               get_posk_tty_offset( int x, int y );
void              shift_tty_up();
void              kprintf( char * c );
void              posk_clear_screen( int c );


#endif
