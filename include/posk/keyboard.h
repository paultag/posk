#ifndef _KBD_H_
#define _KBD_H_ FOO

#include <posk/port.h>
#include <posk/term.h>


void KeyboardIsr() {
	char new_scan_code = inportb(0x60);
 
	/* Do something with the scancode.
	 * Remember you only get '''one''' byte of the scancode each time the ISR is invoked.
	 * (Though most of the times the scancode is only one byte.) 
	 */
 
	kprinti( new_scan_code );

	/* Acknowledge the IRQ, pretty much tells the PIC that we can accept >=priority IRQs now. */
	outportb(0x20,0x20);
}

/*
 * This breaks stuff. Leave HER ALONE
 *

#define SCROLL_LED 1
#define NUM_LED    2
#define CAPS_LED   4
 
void kbd_update_leds ( int status ) {
	// int tmp;
	while((inportb(0x64)&2)!=0){} //loop until zero
	outportb(0x60,0xED);

	while((inportb(0x64)&2)!=0){} //loop until zero
	outportb(0x60,status);
}
*/

#endif
