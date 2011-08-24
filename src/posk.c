#include <multiboot.h>
#include <types.h>
#include <asm.h>

/**
 * Main method of the kernel, totally sweet.
 * XXX: Docme
 */
int main( multiboot_t * mboot_ptr ) {
	asm volatile("sti"); // don't touch please
	for(;;);
	return 0xDEADBEEF;
}
