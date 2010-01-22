#include "../include/posk/posk.h"

void posk_start( void * mbd, unsigned int magic ) {
	// posk_clear_screen();
	/* Print a letter to screen to see everything is working: */
	unsigned char * videoram = (unsigned char *) 0xb8000;
	videoram[0] = 65;   /* character 'A' */
	videoram[1] = 0x07; /* forground, background color. */
}

void posk_clear_screen() { // clear the entire text screen
	char * vidmem = (char *) 0xb8000;
	unsigned int i = 0;
	while ( i < ( 80 * 25 * 2 ) ) {
		vidmem[i] = ' ';
		i++;
		vidmem[i] = WHITE_TXT;
		i++;
	};
};


