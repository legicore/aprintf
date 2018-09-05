///////////////////////////////////////////////////////////////////////////////
/**
 * @file        xprintf.cpp
 *
 * @author      legicore
 *
 * @brief       xxx
 */
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <Arduino.h>

#include "xprintf.h"

/*-----------------------------------------------------------*/

static HardwareSerial * pxHardwareSerial = NULL;
static SoftwareSerial * pxSoftwareSerial = NULL;
#if defined( __AVR_ATmega32U4__ ) || defined( __AVR_ATmega16U4__ )
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

#if defined( __AVR_ATmega32U4__ ) || defined( __AVR_ATmega16U4__ )
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
            pxSoftwareSerial->flush();
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
