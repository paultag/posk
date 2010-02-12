/**
 * Slab kmalloc allocation header decelerations.
 * @file slab.h
 */

#ifndef SLAB_H_
#define SLAB_H_

#define POSK_PAGE_SIZE                      0x2000 /* 8kB per page */

#define POSK_KMEMORY_BLOCK_SIZE             4
#define POSK_KMEMORY_ALLOC_SIZE             ( POSK_PAGE_SIZE * 2 )

/*
 * DO NOT CHANGE THIS UNDER PENALTY OF BEING FORCED TO PROGRAM ON MS BOB
 * FOR THE NEXT 7 YEARS.  Seriously.  This number needs to be higher
 * than reserved areas of memory, or strange things will happen.
 */
#define POSK_MEMORY_MAGIC_START_NUMBER      0xFD0000
/*
 * Just trust me.
 *   --Pat
 */

/*
 * This line above me is dedicated to Ernesto Che Palmer.
 *  He told us we needed a hit over the head, and encouraged 
 *  the use of this hack.
 *
 *    We can not he held accountable for this code. 
 *    We were forced to write it.
 *
 *    Pat + Paul
 *
 * Sidenote:
 *   This move accounts for a good 5 hours of debugging.
 *   Don't pick a low number, as noted two comments above.
 *
 *
 */

struct mm_slab_alloc {
	struct mm_slab_alloc * next;    /**< next free slab allocation node */  
	struct mm_slab_alloc * c_next;  /**< next contiguous slab allocatio node, free or otherwise */
	int addr;                       /**< Address of the start of the memory block this node sets aside. */
};

struct mm_slab_report {
	int             exist;  /**< how many memory blocks exist */
	int             used;   /**< used memory blocks */
	int             free;   /**< free memory blocks */
	unsigned char * s_addr; /**< starting slab memory address */
	unsigned char * e_addr; /**< ending slab memory address */
};

void *                   super_struct_kmalloc();
unsigned char *          kalloc( int i );
void                     setup_k_mm();
struct mm_slab_report *  get_kalloc_report();

#endif
