////////////////////////////////////////////////////////////////////////////////
/**
 * @file        aprintfBasic.ino
 *
 * @author      Martin Legleiter
 *
 * @brief       The aprintf library is a wrapper for the standard Arduino Serial
 *              ports. After initialization it can be used like the standard C
 *              printf() (except for floating-point values and precision).
 *
 *              The used examples are taken from
 *              http://www.cplusplus.com/reference/cstdio/printf/.
 * 
 * @copyright   2024 Martin Legleiter
 * 
 * @license     Use of this source code is governed by an MIT-style
 *              license that can be found in the LICENSE file or at
 *              @see https://opensource.org/licenses/MIT.
 */
////////////////////////////////////////////////////////////////////////////////

#include <aprintf.h>

/*-----------------------------------------------------------*/

void setup( void )
{
    Serial.begin( 9600 );
    aprintfInit( &Serial );
}
/*-----------------------------------------------------------*/

void loop( void )
{
    aprintf( "Characters: %c %c \n", 'a', 65 );
    aprintf( "Decimals: %d %ld\n", 1977, 650000L );
    aprintf( "Preceding with blanks: %10d \n", 1977 );
    aprintf( "Preceding with zeros: %010d \n", 1977 );
    aprintf( "Some different radices: %d %x %o %#x %#o \n", 100, 100, 100, 100, 100 );
    // aprintf( "floats: %4.2f %+.0e %E \n", 3.1416, 3.1416, 3.1416 );
    // aprintf( "Width trick: %*d \n", 5, 10 );
    aprintf( "%s \n\n", "A string" );

    delay( 2000 );
}
