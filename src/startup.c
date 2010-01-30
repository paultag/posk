/**
 * Kernel pre-loop startup code
 * @file startup.c
 */

#include <posk/posk.h>

/**
 * A to start all pre-main loop kernel stuff. Linked lists, the screen, etc.
 * @vorsicht
 * @see posk.c
 */
void startup() {
//	posk_print_char_tl( 'L' );
	setup_k_mm();
	setup_terminal();
//	posk_clear_screen( 0x0 );
}
