#include <posk/posk.h>
#include <posk/malloc.h>
#include <posk/posk_stdout.h>
#include <sys/types.h>

int main ( int argc, char ** argv ) {
	copyright();
	pchar * foo = (pchar *)posk_malloc( sizeof(pchar) * 8 );
	foo = "Hello";
	printf( "I was able to allocate and write %s\n", foo );
	return 0;
}
