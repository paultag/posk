#include <posk/posk.h>

#include "slab.c"
#include "term.c"

void posk_start( void * mbd, unsigned int magic ) {
	posk_clear_screen( 0x0 );

	setup_k_mm();
	
	char *mychar;
	mychar = kmalloc(100);
	
	char *mychar2;
	mychar2 = kmalloc(50);
	

	posk_print_line("DONE");
	
}

