#include <posk/idt.h>

struct idt_entry idt[256];
struct idt_ptr idtp;

void * memset(void * dest, char val, int count) {
    char *temp = (char *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags) {
    idt[num].base_lo = (base & 0xFFFF);
    idt[num].base_hi = (base >> 16) & 0xFFFF;

    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

void idt_install() {
  idtp.limit = (sizeof(struct idt_entry) * 256) - 1;
  idtp.base  = (unsigned int)&idt;
  
  memset(&idt, 0, sizeof(struct idt_entry) * 256);
  
  idt_load();
}