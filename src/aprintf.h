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
#if defined( configAPF_SERIAL_SW )
    #include <SoftwareSerial.h>
#endif

/*--------------------------------------------------*/

#define _d_1f( d, f ) "%"#d"ld.%ld", ( long ) f, abs( ( long ) ( f * 10 ) % 10 )
#define _d_2f( d, f ) "%"#d"ld.%ld", ( long ) f, abs( ( long ) ( f * 100 ) % 100 )
#define _d_3f( d, f ) "%"#d"ld.%ld", ( long ) f, abs( ( long ) ( f * 1000 ) % 1000 )
#define _d_4f( d, f ) "%"#d"ld.%ld", ( long ) f, abs( ( long ) ( f * 10000 ) % 10000 )
#define _d_5f( d, f ) "%"#d"ld.%ld", ( long ) f, abs( ( long ) ( f * 100000 ) % 100000 )
#define _d_6f( d, f ) "%"#d"ld.%ld", ( long ) f, abs( ( long ) ( f * 1000000 ) % 1000000 )

/*--------------------------------------------------*/

#define configBUF_SIZE_DEFAULT 64

/*--------------------------------------------------*/

typedef configAPF_SERIAL APF_Serial_t;
#if defined( configAPF_SERIAL_HW )
    typedef configAPF_SERIAL_HW APF_HWSerial_t;
#endif
#if defined( configAPF_SERIAL_SW )
    typedef configAPF_SERIAL_SW APF_SWSerial_t;
#endif
/*--------------------------------------------------*/

int aprintfInit( APF_Serial_t * serial, int bufferSize = configBUF_SIZE_DEFAULT );
#if defined( configAPF_SERIAL_HW )
    int aprintfInit( APF_HWSerial_t * serial, int bufferSize = configBUF_SIZE_DEFAULT );
#endif
#if defined( configAPF_SERIAL_SW )
    int aprintfInit( APF_SWSerial_t * serial, int bufferSize = configBUF_SIZE_DEFAULT );
#endif
int aprintf( const char * fmt, ... );

/*--------------------------------------------------*/

#endif /* __APRINTF_H__ */
