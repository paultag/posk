#ifndef GDT_H
#define GDT_H FOO

struct gdt_entry {
    unsigned short limit_lo;
    unsigned short base_lo;
    unsigned char base_middle;
    unsigned char access;
    unsigned char gran;
    unsigned char base_hi;
} __attribute__((packed));

struct gdt_ptr {
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

extern void gdt_flush();

void gdt_install();
#endif