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

void * kmalloc( int i );


