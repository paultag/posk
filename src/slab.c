#include <posk/slab.h>
#include <posk/kernel.h>

#define NIL                 0x0

/* reverse:  reverse string s in place */
void reverse(char s[])
{
    int i, j;
    char c;

    for (i = 0, j = ksize0f(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

/* itoa:  convert n to characters in s */
void itoa(int n, char s[])
{
    int i, sign;

    if ((sign = n) < 0)  /* record sign */
        n = -n;          /* make n positive */
    i = 0;
    do {       /* generate digits in reverse order */
        s[i++] = n % 10 + '0';   /* get next digit */
    } while ((n /= 10) > 0);     /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
} 

struct mm_slab_alloc {
	struct mm_slab_alloc * next;
	struct mm_slab_alloc * c_next;
	int addr;
};

void setup_k_mm() {

	struct mm_slab_alloc HEAD;
	HEAD.next   = NIL;
	HEAD.c_next = NIL;
	HEAD.addr   = NIL;


	struct mm_slab_alloc * KALLOC_HEAD;
	struct mm_slab_alloc * KALLOC_END;

	KALLOC_HEAD = &HEAD;
	KALLOC_END  = &HEAD;

	int i = 0;

	char s;


	for ( ; i < POSK_KMEMORY_ALLOC_SIZE; i += POSK_KMEMORY_BLOCK_SIZE) {

		struct mm_slab_alloc item;
		item.addr   = i + POSK_MEMORY_MAGIC_START_NUMBER;
		item.next   = NIL;
		item.c_next = NIL;

		KALLOC_END->next   = &item;
		KALLOC_END->c_next = &item;
		KALLOC_END         = &item;

		itoa(item.addr, &s);

		panic("fuck", &s );
		

	}
}

void * kmalloc( int size ) {



	return 0;
}

