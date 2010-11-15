/**
 * GDT ( Global Descriptor Table ) 
 * @file gdt.c
 */

#include <posk/common.h>
#include <posk/gdt.h>

// defined in gdt.s ASM
extern void gdt_flush(uint32_t);

static void gdt_set_gate (int32_t,uint32_t,uint32_t,uint8_t,uint8_t);

gdt_entry_t gdt_entries[6];
gdt_ptr_t gdt_ptr;

void init_gdt() {
	gdt_ptr.limit = sizeof(gdt_entry_t) * 6 - 1;
	gdt_ptr.base = (uint32_t) &gdt_entries;
  
	gdt_set_gate(0, 0, 0, 0, 0); // NULL segment
	gdt_set_gate(1, 0, 0xFFFFF, 0x9A, 0xCF); // kernel code
	gdt_set_gate(2, 0, 0xFFFFF, 0x92, 0xCF); // kernel data
	gdt_set_gate(3, 0, 0xFFFFF, 0xFA, 0xCF); // user code
  
	gdt_flush((uint32_t) &gdt_ptr);
}

static void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
	gdt_entries[num].base_low = (base & 0xFFFF);
	gdt_entries[num].base_middle = (base >> 16) & 0xFF;
	gdt_entries[num].base_high = (base >> 24) & 0xFF;
  
	gdt_entries[num].limit_low = (limit & 0xFFFF);
	gdt_entries[num].granularity = (limit >> 16) & 0x0F;
	gdt_entries[num].granularity |= gran & 0xF0;
	gdt_entries[num].access = access;
}

