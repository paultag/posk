#include <posk/posk.h>

#include "slab.c"
#include "term.c"

void posk_start( void * mbd, unsigned int magic ) {
	posk_clear_screen( 0x00 );
// 	char foo[30];
// 	char * bar = (char *)&foo;
// 	bar = "POSK Kernel Loading.\0";

// 	int i = 0;

// 	for ( ; bar[i] != '\0'; ++i ) {
// 		posk_print_char( i, 0, bar[i] );
// 	}

	panic( "Error: E1E10", "Main Entry Point", "Planned Kernel Failure." );
	
}

