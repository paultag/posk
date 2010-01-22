#include <posk/posk.h>

#include "slab.c"
#include "term.c"

void posk_start( void * mbd, unsigned int magic ) {
	posk_clear_screen();
	char foo[30];
	char * bar = (char *)&foo;
	bar = "Dynamic Text Support!!!! Paul Rules!\0";

	int i = 0;

	for ( ; bar[i] != '\0'; ++i ) {
		posk_print_char( i, 0, bar[i] );
	}
	
}

