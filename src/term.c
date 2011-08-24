#include <term.h>
#include <types.h>
#include <asm.h>

/* Developer's Note
 *
 * A)
 *
 *      0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
 *    +---------------------------------------+
 *  0 | 00| 01| 02| 03| 04| 05| 06| 07| 08| 09| 
 *  1 | 10| 11| 12| 13| 14| 15| 16| 17| 18| 19|
 *  2 | 20| 21| 22| 23| 24| 25| 26| 27| 28| 29|
 *  3 | 30| 31| 32| 33| 34| 35| 36| 37| 38| 39|
 *  4 | 40| 41| 42| 43| 44| 45| 46| 47| 48| 49|
 *  5 | 50| 51| 52| 53| 54| 55| 56| 57| 58| 59|
 *  6 | 60| 61| 62| 63| 64| 65| 66| 67| 68| 69|
 *  7 | 70| 71| 72| 73| 74| 75| 76| 77| 78| 79|
 *  8 | 80| 81| 82| 83| 84| 85| 86| 87| 88| 89|
 *  9 | 90| 91| 92| 93| 94| 95| 96| 97| 98| 99|
 *    +---------------------------------------+
 *
 * B)         N       N+1
 *       +--------+--------+
 *       |   70   |   0x0  |
 *       +--------+--------+ 
 * 
 *  BEHOLD! The Graphics Card RAM! ( kinda ) ( diagram A )
 *
 *  We are using 9 x 9, and not 80 x 16.
 *
 *  One can think of this as a 2D matrix. Each "Cell" ( Diagram B )
 *  has two parts. ASCII value of the char being displayed
 *  and a color code. Color codes are defined in term.h.
 *
 * =============== 
 *
 *  Since RAM is 1D ( Ssssh. Don't tell anyone ) we have to "fake" 2D.
 * 
 *  This is a bit the Dr. Palmer taught me. Freshman year.
 *  I'm using something I learned Freshman Year in a kernel.
 *   Listen to the man.
 * 
 *  Offset = Width Y * X +
 * 
 *  Take the point "5, 5"
 * 
 *  Offset = 10 5 * 5 +
 *  Offset = 50 5 +
 *  Offset = 55
 *
 *  As you can see by the graph ( Diagram A ), this number is spot on.
 *    -- Paul
 *
 */
 
