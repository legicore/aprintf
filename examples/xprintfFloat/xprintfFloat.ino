////////////////////////////////////////////////////////////////////////////////
/**
 * @file        xprintfFloat.ino
 *
 * @author      Martin Legleiter
 *
 * @brief       The xprintf library is implemented with the help of vsnprintf()
 *              which can't print floating-point values via the specifier "%f".
 *              The following example shows how you can print an float value
 *              with xprintf() and the provided float specifier macros.
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

float value = 1234.56789;

/*-----------------------------------------------------------*/

void setup( void )
{
    Serial.begin( 9600 );
    xprintfInit( &Serial, 64 );
}
/*-----------------------------------------------------------*/

void loop( void )
{
    /* Outputs the same like "printf( "value = %4.1f", value );" */
    xprintf( "\nvalue = " _d_1f( 4, value ) );

    /* Two decimals ("value = 1234.56")
    Will be the same like "printf( "value = %4.2f", value );" */
    xprintf( "\nvalue = " _d_2f( 4, value ) );

    /* Three decimals ("value = 1234.567")
    Will be the same like "printf( "value = %4.3f", value );" */
    xprintf( "\nvalue = " _d_3f( 4, value ) );

    /* Three decimals ("value =  1234.567")
    Will be the same like "printf( "value = %5.3f", value );" */
    xprintf( "\nvalue = " _d_3f( 5, value ) );

    /* Three decimals ("value =   1234.567")
    Will be the same like "printf( "value = %6.3f", value );" */
    xprintf( "\nvalue = " _d_3f( 6, value ) );

    /* Three decimals ("value =  001234.567")
    Will be the same like "printf( "value = %06.3f", value );" */
    xprintf( "\nvalue = " _d_3f( 06, value ) );

    /* Three decimals ("value =  +01234.567")
    Will be the same like "printf( "value = %+06.3f", value );" */
    xprintf( "\nvalue = " _d_3f( +06, value ) );

    value *= -1;

    /* Three decimals ("value = -01234.567")
    Will be the same like "printf( "value = %+06.3f", value );" */
    xprintf( "\nvalue = " _d_3f( +06, value ) );

    value *= -1;
    xprintf( "\n" );

    delay( 2000 );
}
