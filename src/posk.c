#include <posk/posk.h>
#include <posk/malloc.h>

int main ( int argc, char ** argv ) {
	char * foo = (char *)posk_malloc( sizeof(char) * 8 );
	foo = "Hello";
	printf( "I was able to posk allocate %s\n", foo );
}
