#include <posk/ia32.h>

void memset(unsigned char * dest, unsigned char val, unsigned int len) {
    unsigned char * tmp = (unsigned char *)dest;
    for( ; len != 0; len--) *tmp++ = val;
}

extern void gdt_flush(unsigned int);
extern void idt_flush(unsigned int);

static void init_gdt();
static void gdt_set_gate(int, unsigned int, unsigned int, unsigned char, unsigned char);

static void init_idt();
static void idt_set_gate(unsigned char, unsigned int, unsigned short, unsigned char);

gdt_entry_t gdt_entries[5];
gdt_ptr_t gdt_ptr;
idt_entry_t idt_entries[256];
idt_ptr_t idt_ptr;

void init_descriptor_tables() {
    init_gdt();
    init_idt();
}

static void init_gdt() {
    gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;
    gdt_ptr.base = (unsigned int)&gdt_entries;
    
    gdt_set_gate(0, 0, 0,          0,    0); // NULL segment
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // Usermode code
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // Usermode data
    
    gdt_flush((unsigned int)&gdt_ptr);
}

static void gdt_set_gate(int num, unsigned int base, unsigned int limit, unsigned char access, unsigned char gran) {
  gdt_entries[num].base_low = (base & 0xFFFF);
  gdt_entries[num].base_middle = (base >> 16) & 0xFF;
  gdt_entries[num].base_high = (base >> 24) & 0xFF;
  
  gdt_entries[num].limit_low = (limit & 0xFFFF);
  
  gdt_entries[num].granularity = (limit >> 16) & 0x0F;
  gdt_entries[num].granularity |= gran & 0xF0;
  
  gdt_entries[num].access = access;
}

static void init_idt() {
    idt_ptr.limit = sizeof(idt_entry_t) * 256 - 1;
    idt_ptr.base = (unsigned int)&idt_entries;
    
    memset((unsigned char *)&idt_entries, 0, sizeof(idt_entry_t) * 256);
    
    idt_set_gate(0, (unsigned int)isr0, 0x08, 0x8E);
    idt_set_gate(0, (unsigned int)isr1, 0x08, 0x8E);
    idt_set_gate(0, (unsigned int)isr2, 0x08, 0x8E);
    idt_set_gate(0, (unsigned int)isr3, 0x08, 0x8E);
    idt_set_gate(0, (unsigned int)isr4, 0x08, 0x8E);
    idt_set_gate(0, (unsigned int)isr5, 0x08, 0x8E);
    idt_set_gate(0, (unsigned int)isr6, 0x08, 0x8E);
    idt_set_gate(0, (unsigned int)isr7, 0x08, 0x8E);
    idt_set_gate(0, (unsigned int)isr8, 0x08, 0x8E);
    idt_set_gate(0, (unsigned int)isr9, 0x08, 0x8E);
    idt_set_gate(0, (unsigned int)isr10, 0x08, 0x8E);
    idt_set_gate(0, (unsigned int)isr11, 0x08, 0x8E);
    idt_set_gate(0, (unsigned int)isr12, 0x08, 0x8E);
    idt_set_gate(0, (unsigned int)isr13, 0x08, 0x8E);
    idt_set_gate(0, (unsigned int)isr14, 0x08, 0x8E);
    idt_set_gate(0, (unsigned int)isr15, 0x08, 0x8E);
    idt_set_gate(0, (unsigned int)isr16, 0x08, 0x8E);
    idt_set_gate(0, (unsigned int)isr17, 0x08, 0x8E);
    idt_set_gate(0, (unsigned int)isr18, 0x08, 0x8E);
    idt_set_gate(0, (unsigned int)isr19, 0x08, 0x8E);
    idt_set_gate(0, (unsigned int)isr20, 0x08, 0x8E);
    idt_set_gate(0, (unsigned int)isr21, 0x08, 0x8E);
    idt_set_gate(0, (unsigned int)isr22, 0x08, 0x8E);
    idt_set_gate(0, (unsigned int)isr23, 0x08, 0x8E);
    idt_set_gate(0, (unsigned int)isr24, 0x08, 0x8E);
    idt_set_gate(0, (unsigned int)isr25, 0x08, 0x8E);
    idt_set_gate(0, (unsigned int)isr26, 0x08, 0x8E);
    idt_set_gate(0, (unsigned int)isr27, 0x08, 0x8E);
    idt_set_gate(0, (unsigned int)isr28, 0x08, 0x8E);
    idt_set_gate(0, (unsigned int)isr29, 0x08, 0x8E);
    idt_set_gate(0, (unsigned int)isr30, 0x08, 0x8E);
    idt_set_gate(0, (unsigned int)isr31, 0x08, 0x8E);
    
    idt_flush((unsigned int)&idt_ptr);
}

static void idt_set_gate(unsigned char num, unsigned int base, unsigned short sel, unsigned char flags) {
    idt_entries[num].base_low = base & 0xFFFF;
    idt_entries[num].base_high = (base >> 16) & 0xFFFF;
    
    idt_entries[num].sel = sel;
    idt_entries[num].always0 = 0;
    
    idt_entries[num].flags = flags | 0x60;
}