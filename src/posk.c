/**
 * Kernel entry point, and main source file.
 * @file posk.c
 * @mainpage P.O.S.K.
 * This is POSK, the teaching kernel. It's written from scratch
 * in an effort to help educate future students of John Carroll
 * on the innermost workings of the lowest level program running
 * on every computer on the planet.
 * 
 * Although this kernel is aimed to future JCU students, it's a 
 * well documented and clear example of a basic kernel. This is a 
 * logical starting spot for anyone wishing to start learning about
 * how a kernel works, or developing their own kernel.
 * 
 * POSK is maintained and authored by Paul Tagliamonte and Pat McDonnell, 
 * Copyright (c) 2010
 *
 * See http://www.jcu.edu/ for more information on John Carroll
 * univeristy.
 *  
 */

#include <posk/posk.h>

#include "slab.c"
#include "term.c"

#include "startup.c"

/*
struct frobafs {
	int x;
	int y;
	int z;
	int a;
	int b;
	int c;
	int d;
	int e;
}; // CHUNKY STRUCT
*/

/**
 * The kernel entry point. Never call this. I'm, not joking.
 * @vorsicht
 * @param mbd Bootloader ID
 * @param magic Magic Kernel ID
 */
void posk_start( void * mbd, unsigned int magic ) {
	startup();

/*
 * OK. This is _fucked_. There is something wrong with how we were using chars or
 * something. This works, but when you move all the printlines together, it freaking
 * fails again. Goddamnit, writting a kernel is hard.
 *    -- Paul 
 */

/*
	struct frobafs * alloc_test_item1 = ( struct frobafs * ) kmalloc( sizeof( struct frobafs ) );
	int addr1 = (int) alloc_test_item1;
	char * foo1 = "This is larger then the intmax";
	itoa( addr1, foo1 );
	posk_print_line(foo1);

	struct frobafs * alloc_test_item2 = ( struct frobafs * ) kmalloc( sizeof( struct frobafs ) );
	int addr2 = (int) alloc_test_item2;
	char * foo2 = "This is larger then the intmax";
	itoa( addr2, foo2 );
	posk_print_line(foo2);

	struct frobafs * alloc_test_item3 = ( struct frobafs * ) kmalloc( sizeof( struct frobafs ) );
	int addr3 = (int) alloc_test_item3;
	char * foo3 = "This is larger then the intmax";
	itoa( addr3, foo3 );
	posk_print_line(foo3);

	struct frobafs * alloc_test_item4 = ( struct frobafs * ) kmalloc( sizeof( struct frobafs ) );
	int addr4 = (int) alloc_test_item4;
	char * foo4 = "This is larger then the intmax";
	itoa( addr4, foo4 );
	posk_print_line(foo4);

*/

	posk_print_line("DONE");
	posk_print_line("DONE");
}

