/**
   * Kernel entry point, and main source file.
   * @file posk.c
   * @mainpage P.O.S.K.
   * This is POSK, the teaching kernel. It's written from scratch
   * in an effort to help educate future students of John Carroll
   * on the innermost workings of the lowest level program running
   * on every computer on the planet.
   * 
   * Although this kernel is aimed to future JCU students, it's a 
   * well documented and clear example of a basic kernel. This is a 
   * logical starting spot for anyone wishing to start learning about
   * how a kernel works, or developing their own kernel.
   *
   * This kernel is intended to be less then streamlined. A lot of 
   * routines have been written to be clear, and not fast. Most 
   * good kernel hackers can improve this kernel by a few orders
   * of magnitudes. Feel free to do so, it is a great exercise. 
   *
   * We love POSIX, but this kernel will never be POSIX compliant. We will
   * try our damnedest to get it working with a GNU userland, but no promises.
   * 
   * POSK is maintained and authored by Paul Tagliamonte <ptagliamonte11@jcu.edu>
   * and Pat McDonnell <pmcdonnell10@jcu.edu>, Copyright (c) 2010.
   *
   * See http://www.jcu.edu/ for more information on John Carroll
   * univeristy. Contact <dpalmer@jcu.edu> or <kirsch@jcu.edu> for
   * more information on the John Carroll Computer Science Department.
   *  
   */

#include <posk/multiboot.h>
#include <posk/common.h>
#include <posk/monitor.h>
#include <posk/gdt.h>
#include <posk/idt.h>
#include <posk/timer.h>
#include <posk/pmm.h>
#include <posk/vmm.h>
#include <posk/slab.h>
#include <posk/task.h>
#include <posk/cherrytree.h>



/**
 * Main method of the kernel, totally sweet.
 * @param mboot_ptr multiboot params
 * @return return value
 * @vorsicht
 */
int main(multiboot_t *mboot_ptr) {
  monitor_clear();
    
  debug = 0; // turn off debugging by default

  init_gdt();
  init_idt();
  init_timer(50);
  init_pmm(mboot_ptr->mem_upper);
  init_vmm();
  init_heap();

   // Find all the usable areas of memory and inform the physical memory manager about them.
  uint32_t i = mboot_ptr->mmap_addr;
  while (i < mboot_ptr->mmap_addr + mboot_ptr->mmap_length) {
    mmap_entry_t *me = (mmap_entry_t*) i;

    // Does this entry specify usable RAM?
    if (me->type == 1) {
      uint32_t j;
      // For every page in this entry, add to the free page stack.
      for (j = me->base_addr_low; j < me->base_addr_low+me->length_low; j += 0x1000) {
        pmm_free_page (j);
      }
    }

    // The multiboot specification is strange in this respect - the size member does not include "size" itself in its calculations,
    // so we must add sizeof (uint32_t).
    i += me->size + sizeof (uint32_t);
  }

    
    asm volatile("sti");
    
    init_scheduler(init_threading());
    
    #include "../cherrytree/src/kinit.posk"   
    #include "../cherrytree/src/posk-c-process-init.c"


    for(;;);
    
    return 0xDEADBEEF;
}

