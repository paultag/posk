/**
 * Main POSK kernel loop routines.
 * @file posk.h
 */


#ifndef POSK_H_
#define POSK_H_ FOO

#include <posk/term.h>
#include <posk/slab.h>
#include <string.h>

#include <posk/keyboard.h>


void fpanic() {
	int foreground = POSK_RED;
	int background = POSK_BLACK;
	unsigned short attrib = (background << 4) | (foreground & 0x0F); // C-ism!
	posk_clear_screen( attrib );

	place_cursor( MAX_WIDTH, MAX_HEIGHT );
	
	for(;;);
}

/**
 * A function to lock up the machine, if we reach an unsafe state
 * @param error_code a char array of the error code.
 * @param message the fatal error's description
 * @return nothing. This will always lock up and block.
 */
void panic ( char * error_code, char * message ) {

	int foreground = POSK_BLACK;
	int background = POSK_GREEN;
	unsigned short attrib = (background << 4) | (foreground & 0x0F); // C-ism!

	posk_clear_screen( attrib );

	int i = 0;

	if ( MAX_WIDTH > ksize0f( message ) ) {

		int offset = ( MAX_WIDTH - ksize0f( message ) ) / 2 ;
		for ( ; i < ksize0f( message ); ++i ) {
			posk_print_char(
				message[i],
				foreground,
				background,
				offset + i,
				13
			);
		}

		i = 0;

		offset = ( MAX_WIDTH - ksize0f( error_code ) ) / 2 ;
		for ( ; i < ksize0f( error_code ); ++i ) {
			posk_print_char(
				error_code[i],
				foreground,
				background,
				offset + i,
				10
			);
		}

	} else {
		background = POSK_RED;
		attrib = (background << 4) | (foreground & 0x0F); // C-ism!
		posk_clear_screen( attrib );
	}

	place_cursor( 0, 0 );
	struct mm_slab_report * mem = get_kalloc_report();

	kprintf( "Free kalloc Blocks:  " );
	kprinti( mem->free );
	kprintf( "\n" );

	kprintf( "Total kalloc Blocks: " );
	kprinti( mem->exist );
	kprintf( "\n" );

	float f = (float)((float)mem->used / (float)mem->exist);

	int f1 = f * 100;

	kprintf( "Used Kernel Memory:  " );
	kprinti( f1 );
	kprintf( "%\n" );

	place_cursor( MAX_HEIGHT - 2, 0 );

	kprintf( "kalloc alloc starts: " );
	kprinti( (int)mem->s_addr );
	kprintf( "\n" );

	kprintf( "kalloc alloc ends:   " );
	kprinti( (int)mem->e_addr );
	kprintf( "\n" );

	for(;;); // FFFFFFFUUUUUUUUUUUUUUU
}

#endif
