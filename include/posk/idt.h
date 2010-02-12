#ifndef IDT_H_
#define IDT_H_ FOO


struct idt_entry {
    unsigned short base_lo;
    unsigned short sel;
    unsigned short always0;
    unsigned short flags;
    unsigned short base_hi;
} __attribute__((packed));

struct idt_ptr {
    unsigned short limit;
    unsigned short base;
} __attribute__((packed));

extern void idt_load();

void idt_install();
#endif