#include <posk/term.h>

int posk_line = 0;

void posk_print_char_tl( char c ) {
	/* Print a letter to screen to see everything is working: */
	unsigned char * videoram = (unsigned char *) 0xb8000;
	videoram[0] = c;
	videoram[1] = POSK_WHITE_TXT; /* forground, background color. */
}

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

void posk_clear_line( int l ) {
	char * vidmem = (char *) 0xb8000;
	int start_ram = ( l * MAX_WIDTH * 2 );
	int i = start_ram;
	while ( i < ( start_ram + MAX_WIDTH * 2 ) ) {
		vidmem[i] = ' ';
		++i;
		vidmem[i] = POSK_GREEN_BG;
		++i;
	};
}

void posk_print_char( int x, int y, char c ) {
	unsigned char * videoram = (unsigned char *) 0xb8000;
	int offset = x * 2 + ( ( y * MAX_WIDTH ) * 2 );
	videoram[offset] = c;
	videoram[offset + 1] = POSK_WHITE_TXT; /* forground, background color. */
}

void posk_clear_screen( int c ) { // clear the entire text screen
	char * vidmem = (char *) 0xb8000;
	unsigned int i = 0;
	while ( i < ( MAX_WIDTH * MAX_HEIGHT * 2 ) ) {
		vidmem[i] = ' ';
		i++;
		vidmem[i] = c;
		i++;
	};
};

