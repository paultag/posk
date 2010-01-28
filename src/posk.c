#include <posk/posk.h>

#include "slab.c"
#include "term.c"

void posk_start( void * mbd, unsigned int magic ) {

	setup_k_mm();
	
	int test_size = sizeof( char ) * 32;

	char * mychar;
	mychar = kmalloc( test_size );
	
	char * mychar2;
	mychar2 = kmalloc( test_size );

	mychar  = "Test MyChar!";
	mychar2 = "Test Mychar2!";

	posk_clear_screen( 0x0 );

	posk_print_line( mychar  );
	posk_print_line( mychar2 );

	itoa( (int)mychar,  mychar );
	itoa( (int)mychar2, mychar2 );

	posk_print_line( mychar  );
	posk_print_line( mychar2 );


	itoa( test_size, mychar );
	posk_print_line( mychar  );

	posk_print_line("DONE");
	
}

