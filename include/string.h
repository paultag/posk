/**
 * Basic string routine 
 * @file string.h
 */


/**
 * A function to reverse the string. This reverses in place.
 * @param c char array to reverse 
 * @return a reversed char array
 */
void reverse ( char s[] ) {
	int i, j;
	char c;

	for ( i = 0, j = ksize0f( s ) - 1; i < j; i++, j-- ) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

/**
 * A function to translate an integer to an ascii string
 * @param n integer to convert to a string
 * @param s char array to write to
 */
void itoa ( int n, char s[] ) {
	int i, sign;

	if ((sign = n) < 0)  /* record sign */
		n = -n;      /* make n positive */
	i = 0;
	do { /* generate digits in reverse order */
		s[i++] = n % 10 + '0';   /* get next digit */
	} while ( ( n /= 10 ) > 0 );     /* delete it */

	if ( sign < 0 ) {
		s[i++] = '-';
	}

	s[i] = '\0';
	reverse(s);
} 

