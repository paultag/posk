#include <posk/slab.h>
#include <posk/kernel.h>
#include <sys/strings.h>

#define NIL                 0x0

/*
 * Don't use bochs, you twat. I know it's easier.
 * That accounts for most of our goddamn time.
 *
 */


struct mm_slab_alloc {
	struct mm_slab_alloc * next; // next unallocated node
	struct mm_slab_alloc * c_next; // next contiguous node
	int addr;
};

/*
 *  Warning Smartass CS Student:
 *    You don't know what's going on below this.
 *    We don't know what's going on below this.
 *    You think you are cool by "optmizing" this
 *
 *    You're not.
 *
 *
 *    hours_wasted_debugging = 9
 *
 */

int table_magic_number = POSK_MEMORY_MAGIC_START_NUMBER - sizeof(struct mm_slab_alloc) * (POSK_KMEMORY_ALLOC_SIZE / POSK_KMEMORY_BLOCK_SIZE);

struct mm_slab_alloc * KALLOC_HEAD = NIL;
struct mm_slab_alloc * KALLOC_END = NIL;

void * super_struct_kmalloc() {
	int ret = table_magic_number;
	table_magic_number += sizeof(struct mm_slab_alloc);
	return (void *)ret;
}

void setup_k_mm() {

	struct mm_slab_alloc * HEAD = (struct mm_slab_alloc *)super_struct_kmalloc();
	HEAD->next   = NIL;
	HEAD->c_next = NIL;
	HEAD->addr   = POSK_MEMORY_MAGIC_START_NUMBER;

	KALLOC_HEAD = HEAD;
	KALLOC_END  = HEAD;

	int i = POSK_KMEMORY_BLOCK_SIZE;

	for ( ; i <= POSK_KMEMORY_ALLOC_SIZE; i += POSK_KMEMORY_BLOCK_SIZE) {

		struct mm_slab_alloc * item = (struct mm_slab_alloc *)super_struct_kmalloc();
		
		item->addr   = i + POSK_MEMORY_MAGIC_START_NUMBER;
		item->next   = NIL;
		item->c_next = NIL;

		KALLOC_END->next   = item;
		KALLOC_END->c_next = item;
		KALLOC_END         = item;
	}

}

/* A simple first-fit method */
unsigned char * kmalloc( int size ) {
	struct mm_slab_alloc * end_node   = KALLOC_HEAD;
	struct mm_slab_alloc * first_node = KALLOC_HEAD;

	int chunk_size = 0;
	
//	posk_print_line("kmallocing");
	
	do {
		if ( end_node->next == end_node->c_next ) {
//			posk_print_line(" c1");
			end_node = end_node->next;
			chunk_size += POSK_KMEMORY_BLOCK_SIZE;
		} else {
//			posk_print_line(" c2");
			end_node = end_node->next;
			first_node = end_node;
			chunk_size = 0;
		}
	} while ( chunk_size < size && end_node->next != NIL );
	
	if ( end_node->next == NIL ) {
		return 0;
	}
	
	struct mm_slab_alloc * current_node = first_node;
	
	while ( current_node != end_node ) {
		if ( current_node == first_node ) {
			current_node->next = end_node;
		} else {
			current_node->next = NIL;
		}
		current_node = current_node->c_next;
	}
	char mychar = 'a';
	itoa( (int)first_node->addr, &mychar );

	posk_print_line( "Allocated the address: " );
	posk_print_line( &mychar );


	return (unsigned char * ) first_node->addr;
}

