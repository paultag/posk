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
 * This kernel is intended to be less then streamlined. A lot of 
 * routines have been written to be clear, and not fast. Most 
 * good kernel hackers can improve this kernel by a few orders
 * of magnitudes. Feel free to do so, it is a great exercise. 
 *
 * We love POSIX, but this kernel will never be POSIX compliant. We will
 * try our damnedest to get it working with a GNU userland, but no promises.
 * 
 * POSK is maintained and authored by Paul Tagliamonte <ptagliamonte11@jcu.edu>
 * and Pat McDonnell <pmcdonnell10@jcu.edu>, Copyright (c) 2010.
 *
 * See http://www.jcu.edu/ for more information on John Carroll
 * univeristy. Contact <dpalmer@jcu.edu> or <kirsch@jcu.edu> for
 * more information on the John Carroll Computer Science Department.
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

	// this is a test

	kprintf( "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n" );
	kprintf( "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb\n" );
	kprintf( "cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc\n" );
	kprintf( "dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd\n" );
	kprintf( "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee\n" );
	kprintf( "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff\n" );
	kprintf( "gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg\n" );
	kprintf( "h\n" );
	kprintf( "i\n" );
	kprintf( "j\n" );
	kprintf( "k\n" );
	kprintf( "l\n" );
	kprintf( "m\n" );
	kprintf( "n\n" );
	kprintf( "o\n" );
	kprintf( "p\n" );
	kprintf( "q\n" );
	kprintf( "r\n" );
	kprintf( "s\n" );
	kprintf( "t\n" );
	kprintf( "u\n" );
	kprintf( "v\n" );
	kprintf( "w\n" );
	kprintf( "x\n" );
	kprintf( "y\n" );
	kprintf( "z\n" );
	kprintf( "a\n" );
	kprintf( "b\n" );
	kprintf( "c\n" );

	panic ( "Error POSK Main, #E1E10", "We bought the farm here. Not very fun. This is, however, planned." );

	// we will never reach here.
}

