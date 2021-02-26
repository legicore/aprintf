////////////////////////////////////////////////////////////////////////////////
/**
 * @file        xprintf.cpp
 *
 * @author      Martin Legleiter
 *
 * @brief       TODO
 * 
 * @copyright   2021 Martin Legleiter
 * 
 * @license     Use of this source code is governed by an MIT-style
 *              license that can be found in the LICENSE file or at
 *              @see https://opensource.org/licenses/MIT.
 */
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>

#include "xprintf.h"

#include <Arduino.h>
#include <SoftwareSerial.h>

/*--------------------------------------------------*/

#if defined( __AVR_ATmega640__  ) || defined( __AVR_ATmega1280__ ) || defined( __AVR_ATmega1281__ ) || defined( __AVR_ATmega2560__ ) || defined( __AVR_ATmega2561__ ) || \
    defined( __AVR_ATmega328P__ ) || defined( __AVR_ATmega168__  ) || defined( __AVR_ATmega8__    )
    /* Arduino UNO and MEGA. */
    static HardwareSerial * pxSerial = NULL;
#elif defined( __AVR_ATmega4809__ )
    /* Arduino NANO EVERY and UNO WIFI REV2. */
    static UartClass * pxSerial = NULL;
#endif
#if defined( __AVR_ATmega32U4__ ) || defined( __AVR_ATmega16U4__ )
    static Serial_ * pxSerial_ = NULL;
#endif
static SoftwareSerial * pxSerialSW = NULL;

static char * pcBuffer = NULL;
static int sBufferSize = -1;
static const char * pcErrStr = "XPRINTF ERROR\n";
static bool bErr = false;

/*--------------------------------------------------*/

#if defined( __AVR_ATmega640__  ) || defined( __AVR_ATmega1280__ ) || defined( __AVR_ATmega1281__ ) || defined( __AVR_ATmega2560__ ) || defined( __AVR_ATmega2561__ ) || \
    defined( __AVR_ATmega328P__ ) || defined( __AVR_ATmega168__  ) || defined( __AVR_ATmega8__    )

    void xprintfInit( HardwareSerial * serial, int bufferSize )
    {
        pxSerial = serial;
        sBufferSize = bufferSize; 
        pcBuffer = ( char * ) malloc( sizeof( char ) * sBufferSize );
        if( pcBuffer == NULL )
        {
            bErr = true;
        }
    }

#endif
/*--------------------------------------------------*/

#if defined( __AVR_ATmega4809__ )

    void xprintfInit( UartClass * serial, int bufferSize )
    {
        pxSerial = serial;
        sBufferSize = bufferSize; 
        pcBuffer = ( char * ) malloc( sizeof( char ) * sBufferSize );
        if( pcBuffer == NULL )
        {
            bErr = true;
        }
    }

#endif
/*--------------------------------------------------*/

void xprintfInit_SWS( SoftwareSerial * serial, int bufferSize )
{
    pxSerialSW = serial;
    sBufferSize = bufferSize;
    pcBuffer = ( char * ) malloc( sizeof( char ) * sBufferSize );
    if( pcBuffer == NULL )
    {
        bErr = true;
    }
}
/*--------------------------------------------------*/

#if defined( __AVR_ATmega32U4__ ) || defined( __AVR_ATmega16U4__ )

    void xprintfInit_LEO( Serial_ * serial, int bufferSize )
    {
        pxSerial_ = serial;
        sBufferSize = bufferSize;
        pcBuffer = ( char * ) malloc( sizeof( char ) * sBufferSize );
        if( pcBuffer == NULL )
        {
            bErr = true;
        }
    }

#endif
/*--------------------------------------------------*/

int xprintf( const char * fmt, ... )
{
    int sStringLen = -1;
    va_list xArgs;

    va_start( xArgs, fmt );

    sStringLen = vsnprintf( pcBuffer, sBufferSize, fmt, xArgs );
    if( ( sStringLen < 0 ) || ( sStringLen >= sBufferSize ) )
    {
        pcBuffer = ( char * ) pcErrStr;
        sStringLen = -1;
    }

    if( pxSerial != NULL )
    {
        pxSerial->print( pcBuffer );
        pxSerial->flush();
    }
    else if( pxSerialSW != NULL )
    {
        pxSerialSW->print( pcBuffer );
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

    va_end( xArgs );

    return sStringLen;
}
