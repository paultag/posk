#include <posk/isr.h>

isr_t interrupt_handlers[256];

void register_interrupt_handler(unsigned char n, isr_t handler) {
    interrupt_handlers[n] = handler;
}

void isr_handler(ia32_registers_t regs) {
    if (interrupt_handlers[regs.int_no] != 0) {
        isr_t handler = interrupt_handlers[regs.int_no];
        handler(regs);
    }
}

void irq_handler(ia32_registers_t regs) {
    if (regs.int_no >= 40) {
        outportb(0xA0, 0x20);
    }
    outportb(0x20, 0x20);

    if (interrupt_handlers[regs.int_no] != 0) {
        isr_t handler = interrupt_handlers[regs.int_no];
        handler(regs);
    }

}
