////////////////////////////////////////////////////////////////////////////////
/**
 * @file        aprintf.h
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

#ifndef __APRINTF_H__
#define __APRINTF_H__

/*--------------------------------------------------*/

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "aprintfCompat.h"

#include <Arduino.h>
#if defined( configTYPE_SSERIAL )
    #include <SoftwareSerial.h>
#endif

/*--------------------------------------------------*/

#define configBUF_SIZE_DEFAULT 64

/*--------------------------------------------------*/

#define _d_1f( d, f ) "%"#d"ld.%ld", ( long ) f, abs( ( long ) ( f * 10 ) % 10 )
#define _d_2f( d, f ) "%"#d"ld.%ld", ( long ) f, abs( ( long ) ( f * 100 ) % 100 )
#define _d_3f( d, f ) "%"#d"ld.%ld", ( long ) f, abs( ( long ) ( f * 1000 ) % 1000 )
#define _d_4f( d, f ) "%"#d"ld.%ld", ( long ) f, abs( ( long ) ( f * 10000 ) % 10000 )
#define _d_5f( d, f ) "%"#d"ld.%ld", ( long ) f, abs( ( long ) ( f * 100000 ) % 100000 )
#define _d_6f( d, f ) "%"#d"ld.%ld", ( long ) f, abs( ( long ) ( f * 1000000 ) % 1000000 )

/*--------------------------------------------------*/

typedef configTYPE_MSERIAL MSerial_t;
#if defined( configTYPE_HSERIAL )
    typedef configTYPE_HSERIAL HSerial_t;
#endif
#if defined( configTYPE_SSERIAL )
    typedef configTYPE_SSERIAL SSerial_t;
#endif
/*--------------------------------------------------*/

int aprintfInit( MSerial_t * serial, int bufferSize = configBUF_SIZE_DEFAULT );
#if defined( configTYPE_HSERIAL )
    int aprintfInit( HSerial_t * serial, int bufferSize = configBUF_SIZE_DEFAULT );
#endif
#if defined( configTYPE_SSERIAL )
    int aprintfInit( SSerial_t * serial, int bufferSize = configBUF_SIZE_DEFAULT );
#endif
int aprintf( const char * fmt, ... );

/*--------------------------------------------------*/

#endif /* __APRINTF_H__ */
