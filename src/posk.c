#include <posk/posk.h>

#include "term.c"

void posk_start( void * mbd, unsigned int magic ) {
	posk_clear_screen();
	char foo[20];
	char * bar = (char *)&foo;
	bar = "Hello, World!\0";

	int i = 0;

	for ( ; i != 13; ++i ) {
		posk_print_char( i, 0, bar[i] );
	}
	
}

