#include <posk/timer.h>

static void timer_callback(ia32_registers_t regs) {
    // for now, do nothing
    kprintf("tick");
}

void init_timer(unsigned int freq) {
    register_interrupt_handler(IRQ0, &timer_callback);
    unsigned int divisor = 1193180 / freq;
    outportb(0x43, 0x36);
    unsigned char l = (unsigned char)(divisor & 0xFF);
    unsigned char h = (unsigned char)( (divisor >> 8) & 0xFF);
    
    outportb(0x40, l);
    outportb(0x40, h);
}