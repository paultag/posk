/**
 * memory management
 * @file mm.c
 */

#include <posk/mm.h>
#include <posk/kheap.h>
#include <posk/common.h>

page_directory_t * kernel_directory=0;
page_directory_t * current_directory=0;

u32int *frames;
u32int nframes;

#define INDEX_FROM_BIT(a) (a/32)
#define OFFSET_FROM_BIT(a) (a%32)

// Defined in kheap.c
extern u32int placement_address;

/** 
 * Static function to set a bit in the frames bitset 
 * @param frame_addr address of the frame
 */
static void set_frame(u32int frame_addr) {
    u32int frame = frame_addr/0x1000;
    u32int idx = INDEX_FROM_BIT(frame);
    u32int off = OFFSET_FROM_BIT(frame);
    frames[idx] |= (0x1 << off);
}

/** 
 * Static function to clear a bit in the frames bitset
 * @param frame_addr frame address
 */
static void clear_frame(u32int frame_addr) {
    u32int frame = frame_addr/0x1000;
    u32int idx = INDEX_FROM_BIT(frame);
    u32int off = OFFSET_FROM_BIT(frame);
    frames[idx] &= ~(0x1 << off);
}

/** 
 * Static function to test if a bit is set
 * @param frame_addr frame to test
 */
static u32int test_frame(u32int frame_addr) {
    u32int frame = frame_addr/0x1000;
    u32int idx = INDEX_FROM_BIT(frame);
    u32int off = OFFSET_FROM_BIT(frame);
    return (frames[idx] & (0x1 << off));
}

/** 
 * Static function to find the first free frame
 */
static u32int first_frame() {
    u32int i, j;
    for (i = 0; i < INDEX_FROM_BIT(nframes); i++) {
        if (frames[i] != 0xFFFFFFFF) { // nothing free, exit early.
            // at least one bit is free here.
            for (j = 0; j < 32; j++) {
                u32int toTest = 0x1 << j;
                if ( !(frames[i]&toTest) ) {
                    return i*32+j;
                }
            }
        }
    }
}

/** 
 * FUNction to allocate a frame
 * @param page the page of the frame
 * @param is_kernel if it is kernel
 * @param is_writable if it is writiable
 */
void alloc_frame(page_t *page, int is_kernel, int is_writeable) {
    if (page->frame != 0) {
        return;
    } else {
        u32int idx = first_frame();
        if (idx == (u32int)-1) {
            // PANIC! no free frames!! ToDo: Why are we not panic-ing?
        }
        set_frame(idx*0x1000);
        page->present = 1;
        page->rw = (is_writeable)?1:0;
        page->user = (is_kernel)?0:1;
        page->frame = idx;
    }
}

// Function to deallocate a frame.
/** 
 * Function to deallocate a frame
 * @param pate page to de-allocate
 */
void free_frame ( page_t *page ) {
    u32int frame;
    if (!(frame=page->frame)) {
        return;
    } else {
        clear_frame(frame);
        page->frame = 0x0;
    }
}

/** 
 * init the paging system
 */
void initialise_paging() {
    // The size of physical memory. For the moment we 
    // assume it is 16MB big.
    u32int mem_end_page = 0x1000000;
    
    nframes = mem_end_page / 0x1000;
    frames = (u32int*)kmalloc(INDEX_FROM_BIT(nframes));
    memset(frames, 0, INDEX_FROM_BIT(nframes));
    
    // Let's make a page directory.
    kernel_directory = (page_directory_t*)kmalloc_a(sizeof(page_directory_t));
    current_directory = kernel_directory;

    // We need to identity map (phys addr = virt addr) from
    // 0x0 to the end of used memory, so we can access this
    // transparently, as if paging wasn't enabled.
    // NOTE that we use a while loop here deliberately.
    // inside the loop body we actually change placement_address
    // by calling kmalloc(). A while loop causes this to be
    // computed on-the-fly rather than once at the start.
    int i = 0;
    while (i < placement_address) {
        // Kernel code is readable but not writeable from userspace.
        alloc_frame( get_page(i, 1, kernel_directory), 0, 0);
        i += 0x1000;
    }
    // Before we enable paging, we must register our page fault handler.
    register_interrupt_handler(14, page_fault);

    // Now, enable paging!
    switch_page_directory(kernel_directory);
}

/** 
 * Switch the page
 * @param dir page directory to switch to 
 */
void switch_page_directory(page_directory_t *dir) {
    current_directory = dir;
    asm volatile("mov %0, %%cr3":: "r"(&dir->tablesPhysical));
    u32int cr0;
    asm volatile("mov %%cr0, %0": "=r"(cr0));
    cr0 |= 0x80000000; // Enable paging!
    asm volatile("mov %0, %%cr0":: "r"(cr0));
}

/** 
 * Get page
 * @param address address of the page
 * @param make if we need to make it
 * @param dir the page directory
 */
page_t *get_page(u32int address, int make, page_directory_t *dir) {
    // Turn the address into an index.
    address /= 0x1000;
    // Find the page table containing this address.
    u32int table_idx = address / 1024;
    if (dir->tables[table_idx]){ // If this table is already assigned
        return &dir->tables[table_idx]->pages[address%1024];
    } else if ( make ) {
        u32int tmp;
        dir->tables[table_idx] = (page_table_t*)kmalloc_ap(sizeof(page_table_t), &tmp);
        dir->tablesPhysical[table_idx] = tmp | 0x7; // PRESENT, RW, US.
        return &dir->tables[table_idx]->pages[address%1024];
    } else {
        return 0;
    }
}

/** 
 * Page Fault callback
 * @param regs registers
 */
void page_fault(registers_t regs) {
    // A page fault has occurred.
    // The faulting address is stored in the CR2 register.
    u32int faulting_address;
    asm volatile("mov %%cr2, %0" : "=r" (faulting_address));
    
    // The error code gives us details of what happened.
    int present   = !(regs.err_code & 0x1); // Page not present
    int rw = regs.err_code & 0x2;           // Write operation?
    int us = regs.err_code & 0x4;           // Processor was in user-mode?
    int reserved = regs.err_code & 0x8;     // Overwritten CPU-reserved bits of page entry?
    int id = regs.err_code & 0x10;          // Caused by an instruction fetch?

    // Output an error message.
    //PANIC ToDo: Why does this not panic?
    ;
}
