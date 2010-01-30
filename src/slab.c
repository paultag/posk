/**
 * Slab kmalloc allocation code.
 * @file slab.c
 */

#ifndef SLAB_C_
#define SLAB_C_

#include <posk/slab.h>
#include <posk/kernel.h>
#include <string.h>

#define NIL                 0x0

/*
 *  Warning Smartass CS Student:
 *    You don't know what's going on below this.
 *    We don't know what's going on below this.
 *    You think you are cool by "optmizing" this
 *
 *    You're not.
 *
 *
 *    hours_wasted_debugging = 12
 * 
 * 
 *    I'd like to add that most of the errors were
 *    not in the mysterious code. Check your own
 *    moves before some of the creepy stuff.
 *
 *    It's not the compiler(tm). Unless it is.
 *    In which case, comment below.
 *
 */

int table_magic_number =
		POSK_MEMORY_MAGIC_START_NUMBER - (
			sizeof(struct mm_slab_alloc) * (
				POSK_KMEMORY_ALLOC_SIZE / POSK_KMEMORY_BLOCK_SIZE
			)
		);

struct mm_slab_alloc * KALLOC_HEAD = NIL;
struct mm_slab_alloc * KALLOC_END = NIL;

/**
 * A hard-coded method for doling out linked list items. Don't call this directly under penelty of death.
 * @vorsicht
 * @return address of the block to use.
 * @see setup_k_mm()
 */
void * super_struct_kmalloc() {
	int ret = table_magic_number;
	table_magic_number += sizeof(struct mm_slab_alloc);
	return (unsigned char *)ret;
}

/**
 * A function to set up the kmalloc linked list items. This calls super_struct_kmalloc();
 * @vorsicht
 * @see super_struct_kmalloc()
 */
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

/**
 * a function to get the current kalloc status. This is very time consuming.
 * @return a struct of type mm_slab_report with the up-to-date info on the memory status
 *
 */
struct mm_slab_report * get_kalloc_report() {
	struct mm_slab_alloc * HEAD = KALLOC_HEAD;

	int free  = 0;
	int count = 0;

	while ( HEAD != NIL ) {
		++count;
		HEAD = HEAD->c_next;
	}

	HEAD = KALLOC_HEAD;

	while ( HEAD != NIL ) {
		++free;
		HEAD = HEAD->next;
	}

	struct mm_slab_report * ret = (struct mm_slab_report *) kalloc( sizeof(struct mm_slab_report ));
	// this could be an issue. revise, if you can.

	ret->exist = count;
	ret->free  = free;
	ret->used  = ( count - free );
	ret->s_addr = (unsigned char * )KALLOC_HEAD;
	ret->e_addr = (unsigned char * )KALLOC_END;

	return ret;
}

/**
 * A first fit kalloc method to deal with kernel memory requests
 * @param size the size ( in bytes ) the kernel task would like to have.
 * @return address of the block to start using.
 */
unsigned char * kalloc( int size ) {
	struct mm_slab_alloc * end_node   = KALLOC_HEAD;
	struct mm_slab_alloc * first_node = KALLOC_HEAD;

	int chunk_size = 0;
	
	do {
		if ( end_node->next == end_node->c_next ) {
			end_node = end_node->next;
			chunk_size += POSK_KMEMORY_BLOCK_SIZE;
		} else {
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
	void * ret = ( unsigned char * ) first_node->addr;

/*
 * Good debugging info below here.
 *    -- Paul
 *
 */

/*	char mychar = 'a';

	itoa( (int)first_node->addr, &mychar );
	posk_print_line( "Allocated the address: " );
	posk_print_line( &mychar );

	itoa( (int) ret, &mychar );
	posk_print_line( "Pointer address: " );
	posk_print_line( &mychar );
*/

	return ret;
}

#endif
