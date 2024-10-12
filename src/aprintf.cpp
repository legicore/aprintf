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
#if defined( configAPF_SERIAL_SW )
    #include <SoftwareSerial.h>
#endif

/*-----------------------------------------------------------*/

APF_Serial_t * pxSerial = NULL;
#if defined( configAPF_SERIAL_HW )
    APF_HWSerial_t * pxHWSerial = NULL;
#endif
#if defined( configAPF_SERIAL_SW )
    APF_SWSerial_t * pxSWSerial = NULL;
#endif

char * pcBuffer = NULL;
size_t xBufferSize = 0;

bool bInitLock = false;

/*-----------------------------------------------------------*/

static int8_t prvSetBuffer( int16_t sBufferSize );

/*-----------------------------------------------------------*/

int aprintfInit( APF_Serial_t * serial, int bufferSize )
{
    if( ( serial != NULL ) && ( bufferSize > 0 ) && ( bInitLock == false ) )
    {
        if( prvSetBuffer( bufferSize ) == 0 )
        {
            pxSerial = serial;
            bInitLock = true;

            return 0;
        }
    }
    
    return -1;
}
/*-----------------------------------------------------------*/

#if defined( configAPF_SERIAL_HW )

    int aprintfInit( APF_HWSerial_t * serial, int bufferSize )
    {
        if( ( serial != NULL ) && ( bufferSize > 0 ) && ( bInitLock == false ) )
        {
            if( prvSetBuffer( bufferSize ) == 0 )
            {
                pxHWSerial = serial;
                bInitLock = true;

                return 0;
            }
        }
        
        return -1;
    }

#endif
/*-----------------------------------------------------------*/

#if defined( configAPF_SERIAL_SW )

    int aprintfInit( APF_SWSerial_t * serial, int bufferSize )
    {
        if( ( serial != NULL ) && ( bufferSize > 0 ) && ( bInitLock == false ) )
        {
            if( prvSetBuffer( bufferSize ) == 0 )
            {
                pxSWSerial = serial;
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
            if( pxSerial != NULL )
            {
                pxSerial->print( pcBuffer );
                pxSerial->flush();
            }
#if defined( configAPF_SERIAL_HW )
            else if( pxHWSerial != NULL )
            {
                pxHWSerial->print( pcBuffer );
                pxHWSerial->flush();
            }
#endif
#if defined( configAPF_SERIAL_SW )
            else if( pxSWSerial != NULL )
            {
                pxSWSerial->print( pcBuffer );
                pxSWSerial->flush();
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
