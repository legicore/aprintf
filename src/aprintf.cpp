////////////////////////////////////////////////////////////////////////////////
/**
 * @file        aprintf.cpp
 *
 * @author      Martin Legleiter
 *
 * @brief       TODO
 * 
 * @copyright   2024 Martin Legleiter
 * 
 * @license     Use of this source code is governed by an MIT-style
 *              license that can be found in the LICENSE file or at
 *              @see https://opensource.org/licenses/MIT.
 */
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>

#include "aprintfCompat.h"
#include "aprintf.h"

#include <Arduino.h>
#if defined( configTYPE_SSERIAL )
    #include <SoftwareSerial.h>
#endif

/*-----------------------------------------------------------*/

MSerial_t * pxMSerial = NULL;
#if defined( configTYPE_HSERIAL )
    HSerial_t * pxHSerial = NULL;
#endif
#if defined( configTYPE_SSERIAL )
    SSerial_t * pxSSerial = NULL;
#endif

char * pcBuffer = NULL;
size_t xBufferSize = 0;

bool bInitLock = false;

/*-----------------------------------------------------------*/

static int8_t prvSetBuffer( int16_t sBufferSize );

/*-----------------------------------------------------------*/

int aprintfInit( MSerial_t * serial, int bufferSize )
{
    if( ( serial != NULL ) && ( bufferSize > 0 ) && ( bInitLock == false ) )
    {
        if( prvSetBuffer( bufferSize ) == 0 )
        {
            pxMSerial = serial;
            bInitLock = true;

            return 0;
        }
    }
    
    return -1;
}
/*-----------------------------------------------------------*/

#if defined( configTYPE_HSERIAL )

    int aprintfInit( HSerial_t * serial, int bufferSize )
    {
        if( ( serial != NULL ) && ( bufferSize > 0 ) && ( bInitLock == false ) )
        {
            if( prvSetBuffer( bufferSize ) == 0 )
            {
                pxHSerial = serial;
                bInitLock = true;

                return 0;
            }
        }
        
        return -1;
    }

#endif
/*-----------------------------------------------------------*/

#if defined( configTYPE_SSERIAL )

    int aprintfInit( SSerial_t * serial, int bufferSize )
    {
        if( ( serial != NULL ) && ( bufferSize > 0 ) && ( bInitLock == false ) )
        {
            if( prvSetBuffer( bufferSize ) == 0 )
            {
                pxSSerial = serial;
                bInitLock = true;

                return 0;
            }
        }
        
        return -1;
    }

#endif
/*-----------------------------------------------------------*/

static int8_t prvSetBuffer( int16_t sBufferSize )
{
    if( sBufferSize > 0 )
    {
        pcBuffer = ( char * ) malloc( sizeof( char ) * ( size_t ) sBufferSize );
        if( pcBuffer != NULL )
        {
            xBufferSize = ( size_t ) sBufferSize;

            return 0;
        }
    }

    return -1;
}
/*-----------------------------------------------------------*/

int aprintf( const char * fmt, ... )
{
    int sStringLen = -1;
    va_list xArgs;

    if( fmt != NULL )
    {
        va_start( xArgs, fmt );

        sStringLen = vsnprintf( pcBuffer, xBufferSize, fmt, xArgs );
        if( ( sStringLen > 0 ) && ( sStringLen < ( int ) xBufferSize ) )
        {
            if( pxMSerial != NULL )
            {
                pxMSerial->print( pcBuffer );
                pxMSerial->flush();
            }
#if defined( configTYPE_HSERIAL )
            else if( pxHSerial != NULL )
            {
                pxHSerial->print( pcBuffer );
                pxHSerial->flush();
            }
#endif
#if defined( configTYPE_SSERIAL )
            else if( pxSSerial != NULL )
            {
                pxSSerial->print( pcBuffer );
                pxSSerial->flush();
            }
#endif
            else
            {
                sStringLen = -1;
            }
        }

        va_end( xArgs );
    }

    return sStringLen;
}
