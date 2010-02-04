struct gdt_entry_s {
    unsigned short limit_low;
    unsigned short base_low;
    unsigned char base_middle;
    unsigned char access;
    unsigned char granularity;
    unsigned char base_high;
} __attribute__((packed));

struct gdt_ptr_s {
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

void init_descriptor_tables();