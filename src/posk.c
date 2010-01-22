#define WHITE_TXT 0x07 // white on black text

void          posk_clear_screen();
unsigned int  posk_printf( char * message, unsigned int line );
void          update_cursor(int row, int col);

void posk_start( void* mbd, unsigned int magic ) {
	if ( magic != 0x2BADB002 ) {
		/* Something went not according to specs. Print an error */
		/* message and halt, but do *not* rely on the multiboot */
		/* data structure. */
	}

	posk_clear_screen();
	posk_printf("Hello, World!\n", 0);
}

void posk_clear_screen() { // clear the entire text screen
	char *vidmem = (char *) 0xb8000;
	unsigned int i=0;
	while ( i < (80*25*2) ) {
		vidmem[i]=' ';
		i++;
		vidmem[i]=WHITE_TXT;
		i++;
	};
};

unsigned int posk_printf ( char *message, unsigned int line ) { // the message and then the line #
	char *vidmem = (char *) 0xb8000;
	unsigned int i=0;

	i = (line*80*2);

	while ( * message!=0 ) {
		if(*message=='\n') { // check for a new line
			line++;
			i=(line*80*2);
			*message++;
		} else {
			vidmem[i]=*message;
			*message++;
			i++;
			vidmem[i]=WHITE_TXT;
			i++;
		};
	};

	return(1);
};


