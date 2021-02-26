////////////////////////////////////////////////////////////////////////////////
/**
 * @file        xprintfBasic.ino
 *
 * @author      Martin Legleiter
 *
 * @brief       The xprintf library is a wrapper for the standard Arduino Serial
 *              ports. After initialization it can be used like the standard C
 *              printf() (except for floating-point values and precision).
 *
 *              The used examples are taken from
 *              http://www.cplusplus.com/reference/cstdio/printf/.
 * 
 * @copyright   2021 Martin Legleiter
 * 
 * @license     Use of this source code is governed by an MIT-style
 *              license that can be found in the LICENSE file or at
 *              @see https://opensource.org/licenses/MIT.
 */
////////////////////////////////////////////////////////////////////////////////

#include <xprintf.h>

/*-----------------------------------------------------------*/

void setup( void )
{
    Serial.begin( 9600 );
    xprintfInit( &Serial, 64 );
}
/*-----------------------------------------------------------*/

void loop( void )
{
    xprintf( "Characters: %c %c \n", 'a', 65 );
    xprintf( "Decimals: %d %ld\n", 1977, 650000L );
    xprintf( "Preceding with blanks: %10d \n", 1977 );
    xprintf( "Preceding with zeros: %010d \n", 1977 );
    xprintf( "Some different radices: %d %x %o %#x %#o \n", 100, 100, 100, 100, 100 );
    //xprintf( "floats: %4.2f %+.0e %E \n", 3.1416, 3.1416, 3.1416 );
    //xprintf( "Width trick: %*d \n", 5, 10 );
    xprintf( "%s \n\n", "A string" );

    delay( 2000 );
}
