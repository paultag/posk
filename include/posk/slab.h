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
#define POSK_MEMORY_MAGIC_START_NUMBER      0xD0000
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
 */

/**
 * A hard-coded method for doling out linked list items. Don't call this directly under penelty of death.
 * @vorsicht
 * @return address of the block to use.
 */
void * super_struct_kmalloc();

/**
 * A first fit kalloc method to deal with kernel memory requests
 * @param size the size ( in bytes ) the kernel task would like to have.
 * @return address of the block to start using.
 */
unsigned char * kalloc( int i );

/**
 * A function to set up the kmalloc linked list items. This calls super_struct_kmalloc();
 * @vorsicht
 * @see super_struct_kmalloc();
 */
void setup_k_mm();

#endif
