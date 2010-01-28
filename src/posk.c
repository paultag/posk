#include <posk/posk.h>

#include "slab.c"
#include "term.c"

struct frobafs {
	int x;
	int y;
	int z;
	int a;
	int b;
	int c;
	int d;
	int e;
};

void posk_start( void * mbd, unsigned int magic ) {

	setup_k_mm();
	
	int test_size = sizeof( struct frobafs );

	posk_clear_screen( 0x0 );

	struct frobafs * mychar;
	mychar = (struct frobafs * )kmalloc( test_size );
	
	struct frobafs * mychar2;
	mychar2 = (struct frobafs * )kmalloc( test_size );

//	posk_print_line( mychar  );
//	posk_print_line( mychar2 );

	int addr1 = 0;
	int addr2 = 0;

	itoa( addr1, (int) mychar  );
	itoa( addr2, (int) mychar2 );

	posk_print_line( mychar  );
	posk_print_line( mychar2 );

	posk_print_line( "Addr Diff: " );

	itoa( addr2 - addr1,  mychar );
	posk_print_line( mychar );

	itoa( test_size, mychar );
	posk_print_line( mychar );

	posk_print_line("DONE");
	
}

