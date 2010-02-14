#ifndef IRQ_H_
#define IRQ_H_ FOO

#include <posk/isr.h>

extern void irq_install_handler(int irq, void (*handler)(struct regs *r));
extern void irq_uninstall_handler(int irq);
extern void irq_install();

#endif