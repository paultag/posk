#include <posk/posk.h>

#include "slab.c"
#include "term.c"

void posk_start( void * mbd, unsigned int magic ) {
	posk_clear_screen( 0x00 );

	panic( "Puke",  "System is crunching the setup" );

	setup_k_mm();

	panic( "Error: E1E10", "Planned Kernel Failure." );
	
}

