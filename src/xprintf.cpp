////////////////////////////////////////////////////////////////////////////////
/**
 * @file        xprintf.cpp
 *
 * @author      Martin Legleiter
 *
 * @brief       TODO
 * 
 * @copyright   2018 Martin Legleiter
 * 
 * @license     Use of this source code is governed by an MIT-style
 *              license that can be found in the LICENSE file or at
 *              @see https://opensource.org/licenses/MIT.
 */
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdint.h>

#include "xprintf.h"

#include <Arduino.h>
#include <SoftwareSerial.h>

/*-----------------------------------------------------------*/

static HardwareSerial * pxHardwareSerial = NULL;
static SoftwareSerial * pxSoftwareSerial = NULL;
#if defined __AVR_ATmega32U4__ || defined __AVR_ATmega16U4__
static Serial_ * pxSerial_ = NULL;
#endif

static char * pcBuffer;
static int sBufferSize;

/*-----------------------------------------------------------*/

void xprintfInit( HardwareSerial * pxSerial, int sBufferSizePar )
{
    pxHardwareSerial = pxSerial;
    sBufferSize = sBufferSizePar; 
    pcBuffer = ( char * ) malloc( sizeof( char ) * sBufferSize );
}
/*-----------------------------------------------------------*/

void xprintfInit( SoftwareSerial * pxSerial, int sBufferSizePar )
{
    pxSoftwareSerial = pxSerial;
    sBufferSize = sBufferSizePar;
    pcBuffer = ( char * ) malloc( sizeof( char ) * sBufferSize );
}
/*-----------------------------------------------------------*/

#if defined __AVR_ATmega32U4__ || defined __AVR_ATmega16U4__

    void xprintfInit( Serial_ * pxSerial, int sBufferSizePar )
    {
        pxSerial_ = pxSerial;
        sBufferSize = sBufferSizePar;
        pcBuffer = ( char * ) malloc( sizeof( char ) * sBufferSize );
    }

#endif
/*-----------------------------------------------------------*/

int xprintf( const char * pcFmt, ... )
{
    int sStringLen = -1;
    va_list xArgs;

    va_start( xArgs, pcFmt );

    sStringLen = vsnprintf( pcBuffer, sBufferSize, pcFmt, xArgs );
    if( ( sStringLen > 0 ) && ( sStringLen < sBufferSize ) )
    {
        if( pxHardwareSerial != NULL )
        {
            pxHardwareSerial->print( pcBuffer );
            pxHardwareSerial->flush();
        }
        else if( pxSoftwareSerial != NULL )
        {
            pxSoftwareSerial->print( pcBuffer );
        }
#if defined( __AVR_ATmega32U4__ ) || defined( __AVR_ATmega16U4__ )
        else if( pxSerial_ != NULL )
        {
            pxSerial_->print( pcBuffer );
            pxSerial_->flush();
        }
#endif
        else
        {
            sStringLen = -1;
        }
    }
    else
    {
        sStringLen = -1;
    }

    va_end( xArgs );

    return sStringLen;
}
