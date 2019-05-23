////////////////////////////////////////////////////////////////////////////////
/**
 * @file        xprintfFloat.ino
 *
 * @author      Martin Legleiter
 *
 * @brief       The xprintf library is implemented with the help of vsnprintf()
 *              which can't print floating-point values via the specifier "%f".
 *              The following example shows how you can print an float value
 *              with xprintf() by converting the decimal places to an seperate
 *              integer.
 * 
 * @copyright   2019 Martin Legleiter
 * 
 * @license     Use of this source code is governed by an MIT-style
 *              license that can be found in the LICENSE file or at
 *              @see https://opensource.org/licenses/MIT.
 */
////////////////////////////////////////////////////////////////////////////////

#include <xprintf.h>

/*-----------------------------------------------------------*/

float value = 1234.56789;

/*-----------------------------------------------------------*/

void setup( void )
{
    Serial.begin( 9600 );
    xprintfInit( &Serial );
}
/*-----------------------------------------------------------*/

void loop( void )
{
    /* One decimal ("value = 1234.5"). */
    xprintf( "value = %ld.%ld\n", ( long ) value, ( long ) ( value * 10 ) % 10 );

    /* Two decimals ("value = 1234.56"). */
    xprintf( "value = %ld.%ld\n", ( long ) value, ( long ) ( value * 100 ) % 100 );

    /* Three decimals ("value = 1234.567"). */
    xprintf( "value = %ld.%ld\n", ( long ) value, ( long ) ( value * 1000 ) % 1000 );

    delay( 2000 );
}
