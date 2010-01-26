#include <posk/term.h>

// First non C programmer to get the below line gets a cookie
// It's just fantastic looking. Bask in the glory of the next line.
// Because it is.
//
// --Paul Tagliamonte
//
int ksize0f(char*m){int i=0;for(;m[i]!='\0';++i);return i;}

void panic ( char * error_code, char * fail_point, char * message ) {
	posk_clear_screen( POSK_ORNG_BG );

	int i = 0;

	if ( MAX_WIDTH > ksize0f( message ) ) {
		int offset = ( MAX_WIDTH - ksize0f( message ) ) / 2 ;
		for ( ; i < ksize0f( message ); ++i ) {
			posk_print_char( offset + i, 5, message[i] );
		}

		i = 0;

		offset = ( MAX_WIDTH - ksize0f( error_code ) ) / 2 ;
		for ( ; i < ksize0f( error_code ); ++i ) {
			posk_print_char( offset + i, 3, error_code[i] );
		}

	} else {
		posk_clear_screen( POSK_RED_BG );
	}
}

