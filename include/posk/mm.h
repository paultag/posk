#ifndef MM_H_
#define MM_H_

#include <posk/common.h>
#include <posk/isr.h>

u32int * frames;
u32int nframes;

typedef struct page {
    u32int present	: 1;
    u32int rw		: 1;
    u32int user		: 1;
    u32int accessed	: 1;
    u32int dirty	: 1;
    u32int unused	: 1;
    u32int frame	: 20;
} page_t;

typedef struct page_tage {
    page_t pages[1024];
} page_table_t;

typedef struct page_directory {
    page_table_t * tables[1024];
    u32int tablesPhysical[1024];
    u32int physicalAddr;
} page_directory_t;

void initialize_paging();
void switch_page_directory(page_directory_t * new);
page_t * get_page(u32int address, int make, page_directory_t * dir);
void page_fault(registers_t regs);

static void set_frame(u32int frame_addr);
static void clear_frame(u32int frame_addr);
static u32int test_frame(u32int frame_addr);
static u32int first_frame();
void alloc_frame(page_t * page, int is_kernel, int is_writeable);
void free_frame(page_t * page);
void initialize_paging();
void switch_page_directory(page_directory_t * dir);


#define INDEX_FROM_BIT(a) (a/32)
#define OFFSET_FROM_BIT(a) (a%32)

#endif 