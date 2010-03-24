#include <posk/common.h>
#include <posk/mm.h>

extern u32int end;
u32int placement_address = (u32int)&end;

page_directory_t * kernel_directory = 0;
page_directory_t * current_directory = 0;

u32int kmalloc_int(u32int size, int align, u32int * phys) {
    if( align == 1 && (placement_address & 0xFFFFF000) ) {
      placement_address &= 0xFFFFF000;
      placement_address += 0x1000;
    }
    if( phys ) {
	*phys = placement_address;
    }
    u32int tmp = placement_address;
    placement_address += size;
    return tmp;
}

u32int kmalloc(u32int size) {
    return kmalloc_int(size, 0, 0);
}

static void set_frame(u32int frame_addr) {
    u32int frame = frame_addr / 0x1000;
    u32int index = INDEX_FROM_BIT(frame);
    u32int offset = OFFSET_FROM_BIT(frame);
    frames[index] |= (0x1 << offset);
}

static void clear_frame(u32int frame_addr) {
    u32int frame = frame_addr / 0x1000;
    u32int index = INDEX_FROM_BIT(frame);
    u32int offset = OFFSET_FROM_BIT(frame);
    frames[index] &= ~(0x1 << offset);
}

static u32int test_frame(u32int frame_addr) {
    u32int frame = frame_addr / 0x1000;
    u32int index = INDEX_FROM_BIT(frame);
    u32int offset = OFFSET_FROM_BIT(frame);
    return (frames[index] & (0x1 << offset));
}

static u32int first_free_frame() {
    u32int i, j;
    for(i = 0; i < INDEX_FROM_BIT(nframes); i++) {
	if( frames[i] != 0xFFFFFFFF ) {
	    for(j = 0; j < 32; j++) {
		u32int toTest = 0x1 << j;
		if( !(frames[i] & toTest) ) {
		    return i * 32 + j;
		}
	    }
	}
    }
}	

void alloc_frame(page_t * page, int is_kernel, int is_writeable) {
    if( page->frame != 0 ) {
       return;
    } else {
	u32int index = first_free_frame();
	if(index == (u32int)-1) {
	    // PANIC, eventually
	    for(;;);
	}
	set_frame(index * 0x1000);
	page->present = 1;
	page->rw = (is_writeable)?1:0;
	page->user = (is_kernel)?0:1;
	page->frame = index;
    }
}

void free_frame(page_t * page) {
    u32int frame;
    if( !(frame=page->frame) ) {
      return;
    } else {
      clear_frame(frame);
      page->frame = 0x0;
    }
}

void initialize_paging() {
    u32int mem_end_page = 0x1000000; // 16MB, for now...
    nframes = mem_end_page / 0x1000;
    memset(frames, 0, INDEX_FROM_BIT(nframes));
    kernel_directory = (page_directory_t *)kmalloc_int(sizeof(page_directory_t), 1, 0);
    memset(kernel_directory, 0, sizeof(page_directory_t));
    current_directory = kernel_directory;
    
    int i = 0;
    while(i < placement_address) {
	alloc_frame( get_page(i, 1, kernel_directory), 0, 0);
	i += 0x1000;
    }
    register_interrupt_handler(14, page_fault);
    switch_page_directory(kernel_directory);
}

void switch_page_directory(page_directory_t * dir) {
    current_directory = dir;
    asm volatile("mov %0, %%cr3" :: "r"(&dir->tablesPhysical));
    u32int cr0;
    asm volatile("mov %%cr0, %0" : "=r"(cr0));
    cr0 |= 0x80000000;
    asm volatile("mov %0, %%cr0" :: "r"(cr0));
}

page_t * get_page(u32int address, int make, page_directory_t * dir) {
    address /= 0x1000;
    u32int table_index = address / 1024;
    if( dir->tables[table_index] ) {
      return &dir->tables[table_index]->pages[address % 1024];
    } else if(make) {
	u32int tmp;
	dir->tables[table_index] = (page_table_t *)kmalloc_int(sizeof(page_table_t), 1, &tmp);
	memset(dir->tables[table_index], 0, 0x1000);
	dir->tablesPhysical[table_index] = tmp | 0x7;
	return &dir->tables[table_index]->pages[address % 1024];
    } else {
      return 0;
    }
}

void page_fault(registers_t regs) {
    u32int faulting_address;
    asm volatile("mov %%cr2, %0" : "=r" (faulting_address));
    int present = !(regs.err_code & 0x1);
    int rw = regs.err_code & 0x2;
    int usermode = regs.err_code & 0x4;
    int reserved = regs.err_code & 0x8;
    int id = regs.err_code & 0x10;
    
    // print debug info once we can
    for(;;);
}