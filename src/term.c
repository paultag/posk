
void posk_print_char_tl( char c ) {
	/* Print a letter to screen to see everything is working: */
	unsigned char * videoram = (unsigned char *) 0xb8000;
	videoram[0] = c;
	videoram[1] = WHITE_TXT; /* forground, background color. */
}

void posk_print_char( int x, int y, char c ) {
	unsigned char * videoram = (unsigned char *) 0xb8000;
	int offset = x + ( y * MAX_WIDTH );
	videoram[offset] = c;
	videoram[offset + 1] = WHITE_TXT; /* forground, background color. */	
}

void posk_clear_screen() { // clear the entire text screen
	char * vidmem = (char *) 0xb8000;
	unsigned int i = 0;
	while ( i < ( MAX_WIDTH * MAX_HEIGHT * 2 ) ) {
		vidmem[i] = ' ';
		i++;
		vidmem[i] = WHITE_TXT;
		i++;
	};
};

