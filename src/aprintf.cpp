////////////////////////////////////////////////////////////////////////////////
/**
 * @file        aprintf.cpp
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

#include "aprintf.h"

#include <Arduino.h>
#if !defined( ARDUINO_ARCH_RP2040 )
    #include <SoftwareSerial.h>
#endif

/*--------------------------------------------------*/

#if defined( __AVR_ATmega640__  ) || defined( __AVR_ATmega1280__ ) || defined( __AVR_ATmega1281__ ) || defined( __AVR_ATmega2560__ ) || defined( __AVR_ATmega2561__ ) || \
    defined( __AVR_ATmega328P__ ) || defined( __AVR_ATmega168__  ) || defined( __AVR_ATmega8__    ) || \
    defined( ARDUINO_ARCH_RP2040 )
    /* Arduino UNO and MEGA. */
    static HardwareSerial * pxSerial = NULL;
#elif defined( __AVR_ATmega4809__ )
    /* Arduino NANO EVERY and UNO WIFI REV2. */
    static UartClass * pxSerial = NULL;
#endif
#if defined( __AVR_ATmega32U4__ ) || defined( __AVR_ATmega16U4__ )
    static Serial_ * pxSerial_ = NULL;
#endif
#if !defined( ARDUINO_ARCH_RP2040 )
    static SoftwareSerial * pxSerialSW = NULL;
#endif

static char * pcBuffer = NULL;
static int sBufferSize = -1;
static const char * pcErrStr = "aprintf ERROR\n";
static bool bErr = false;

/*--------------------------------------------------*/

#if defined( __AVR_ATmega640__  ) || defined( __AVR_ATmega1280__ ) || defined( __AVR_ATmega1281__ ) || defined( __AVR_ATmega2560__ ) || defined( __AVR_ATmega2561__ ) || \
    defined( __AVR_ATmega328P__ ) || defined( __AVR_ATmega168__  ) || defined( __AVR_ATmega8__    ) || \
    defined( ARDUINO_ARCH_RP2040 )

    void aprintfInit( HardwareSerial * serial, int bufferSize )
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

    void aprintfInit( UartClass * serial, int bufferSize )
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

#if !defined( ARDUINO_ARCH_RP2040 )

    void aprintfInit_SWS( SoftwareSerial * serial, int bufferSize )
    {
        pxSerialSW = serial;
        sBufferSize = bufferSize;
        pcBuffer = ( char * ) malloc( sizeof( char ) * sBufferSize );
        if( pcBuffer == NULL )
        {
            bErr = true;
        }
    }

#endif
/*--------------------------------------------------*/

#if defined( __AVR_ATmega32U4__ ) || defined( __AVR_ATmega16U4__ )

    void aprintfInit_LEO( Serial_ * serial, int bufferSize )
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

int aprintf( const char * fmt, ... )
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
#if !defined( ARDUINO_ARCH_RP2040 )
    else if( pxSerialSW != NULL )
    {
        pxSerialSW->print( pcBuffer );
    }
#endif
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
