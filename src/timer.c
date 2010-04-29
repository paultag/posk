/**
 * Timer code for setting up internal tick
 * @file timer.c
 */

#include <posk/timer.h>
#include <posk/idt.h>
#include <posk/common.h>
#include <posk/monitor.h>

uint32_t tick = 0;

static void timer_callback(registers_t * regs) {
    tick++;
    #include "../cherrytree/src/tick.posk"
    schedule();
}

void init_timer(uint32_t freq) {
    // Firstly, register our timer callback.
    register_interrupt_handler(IRQ0, &timer_callback);

    // The value we send to the PIT is the value to divide it's input clock
    // (1193180 Hz) by, to get our required frequency. Important to note is
    // that the divisor must be small enough to fit into 16-bits.
    uint32_t divisor = 1193180 / freq;

    // Send the command byte.
    outb(0x43, 0x36);

    // Divisor has to be sent byte-wise, so split here into upper/lower bytes.
    uint8_t l = (uint8_t)(divisor & 0xFF);
    uint8_t h = (uint8_t)( (divisor>>8) & 0xFF );

    // Send the frequency divisor.
    outb(0x40, l);
    outb(0x40, h);
}
