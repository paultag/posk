#include <posk/posk.h>

/**
 * A to start all pre-main loop kernel stuff. Linked lists, the screen, etc.
 * @vorsicht
 */
void startup() {
	posk_print_char_tl( 'L' );
	setup_k_mm();
	posk_clear_screen( 0x0 );
}
