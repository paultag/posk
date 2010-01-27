#define POSK_PAGE_SIZE                      0x2000 /* 8kB per page */

#define POSK_KMEMORY_BLOCK_SIZE             4
#define POSK_KMEMORY_ALLOC_SIZE             ( POSK_PAGE_SIZE * 2 )

#define POSK_MEMORY_MAGIC_START_NUMBER      0x0B0000
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


