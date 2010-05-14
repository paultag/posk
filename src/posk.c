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
   * A large part of this kernel is based on the excellent resources
   * compiled by James Molloy, available from http://www.jamesmolloy.co.uk/,
   * as well as the resources available on http://osdev.org/
   *
   * Also, thanks to the OS gurus on Freenode's #osdev IRC channel.
   *  
   */

// Now that you've read all that official legal mumbo-jumbo above,
// here's the real story:

// OK, this is quite possibly the worst example of a functional
// OS ever (other than Windows ME), but it serves its purpose,
// is easily extendable, makes clever use of acronymns, has a
// nifty build system, and votes democrat.  No animals were harmed
// in the making of this kernel, though that was more a result of the intelligence
// and speed of the animals, despite attempts made by the programmers.
// Dry erase markers, on the other hand, typically being a more stationary
// target than cats, suffered great losses.

// This has only been run on real hardware once.  "Real hardware" is a bit
// of an exageration, as the only PC with a floppy drive was some old
// POS that someone left in the CS lab and forgot about.  It made scary
// screeching noises when we booted it.  It is fitting, though, that
// a POS machine was the first and only machine to run the POS kernel.

// Yes, we spent more time writing these comments than we did on any
// actual code.  Even if you consider the volumes of "code"
// we wrote that we never got to actually compile.

// Be forewarned that this kernel contains no keyboard, PC noisemaker,
// ramdisk, hard disk, network or random number routines. All of these
// features are supported, though their implementation is left as an
// exercise for future programmers.  So get to it.

// It should not be that hard. Really. 

// A word to future developers:
// Chances are, if you see a creative solution to something that is in this code
// there will be two outcomes. 
//  A. It will work better then before.
//  B. You will trash something in a monumental way that still
//     compiles. We have no idea why this happes. 
//     There is no inbetween.
//
// And, if you think you are being crafty. You're not. You're being a pain in the ass
// stop trying to impress people. You'll just get points taken off anyway. Want to be
// an Uber hacker? Go play with the ASM routines, asshole.

// "Composition! Glenn Beck! Can we push that test back?"
//  -- Steve

// "I want to take that idea, make it alive, and then kill it!"
// -- Dr. Palmer

// "You know what else you need to stick in there?"
//  -- Ben

// Whatever, its now your kernel, so all sins are forgiveable.  Unless you
// violate the One True Curly Brace Placement Style.  Then we'll have to kill
// you.  Regardless of how good your code works. 

// "Any technology distinguishable from magic is insufficiently advanced."
//    - Corollary to Clarke's Third Law

// POSK is therefore not magic. 

// Oh, and whatever you do. *DO NOT PLAY WITH THE GDT or LDT NUMBERS*
// Dr. Palmer might just say "Pick a number". Don't. That little mistake cost
// us damn near 0x2A hours of work over three weeks in room D-E223. 

// Dr. Palmer's other advice tends to be pretty good, though.  He recently asked
// us to implement a swarm-based kernel in Linden Scripting Language, and we're currently
// researching the possibility. Someone joked too loud. 

// Dr. Seiter might not have too much advice on the kernel. I have a feeling
// that she really hates the idea of writing an operating system more than
// any other programmer to have ever lived. We did use the Visitor Pattern, though.
// Ten POSK points if you can find where it is!  According to Dr. Seiter,
// the fact that this kernel does not support a keyboard is actually a
// feature, as the copy-and-paste operation is rendered completely impossible.

// Some of the numbers in the .h files are big enigmas. About 1% of them you can
// find on the internet. About 50% are numbers Dr. Kirsch came up with in his head 
// doing calculus in base-16. The other 49% are the points he took off from our
// homework assignments over the years. Seems to work.

// So, yes, even though this kernel is now near 90% comment and 10% code,
// you still won't find it to be very self-documenting.  Too bad.  It was
// hard to write the first time, its gonna be hard to read.

// "There is the easy way, then there is Paul's way"
//   -- Ben

// You can get help on our IRC channel, #windows.

// So. Godspeed, future programmer! If you have any issues, don't be afraid
// to not email us about it. We won't get back to you anyway. We're true
// Open Source developers about that sorta thing.

// Viva la vida segunda!
// -- Pat and Paul

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

  
  // This just works.  Leave it alone.
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

    init_scheduler(init_threading());
    
    asm volatile("sti"); // don't touch please
    
    #include "../cherrytree/src/kinit.posk"   
    #include "../cherrytree/src/posk-c-process-init.c"

    for(;;);
    
    return 0xDEADBEEF;
}

