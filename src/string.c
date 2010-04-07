/**
 * String stuff
 * @file string.c
 */

#include <string.h>

  /**
   * A function to count the char values in an array
   * @param m char pointer to a char array
   * @return length of the char array
   */
  int ksize0f(char*m) {
    int i=0;
    for( ; m[i] != '\0'; ++i);
    return i;
  }
  /*
   * Hey. Paul here.
   *   Sorry to any non C programmers who have to work out what
   *   that above method does. My bad!
   *
   * Here is a description
   *   This is dedicated to you, non-c programmer.
   *
   *
   *
   * +---+---+---+---+---/--/   /--/----+
   * | H | E | L | L | O /--/   /--/ \0 |  <== C Char Array "foo"
   * +---+---+---+---+---/--/   /--/----+
   *
   *
   * foo[0] == "H"
   * foo[1] == "E"
   * foo[2] == "L"
   * foo[3] == "L"
   *  ...
   * foo[5] == "\0"
   * 
   *
   *  So, in sudo ( yes, I know it's pseudo ) code, to echo all letters out:
   *
   *
   * while [ not "\0" ]
   *   get next char
   *   echo char
   * done
   *
   *
   * -- OR --
   *
   * foreach char
   *   echo char
   * done
   *
   *  The code above ( ksize0f ) is the same as:
   *
   ****
   *
   *  int counter = 0;
   *  foreach char
   *    counter += 1
   *  done
   *  return counter
   *
   ****
   * 
   * Gotta love the C.
   *   -- Paul
   *
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
