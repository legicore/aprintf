////////////////////////////////////////////////////////////////////////////////
/**
 * @file        xprintf.h
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

#ifndef __XPRINTF_H__
#define __XPRINTF_H__

#include <stdlib.h>

#include <Arduino.h>
#include <SoftwareSerial.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------*/

#define _d_1f( d, f ) "%"#d"ld.%ld", ( long ) f, abs( ( long ) ( f * 10 ) % 10 )
#define _d_2f( d, f ) "%"#d"ld.%ld", ( long ) f, abs( ( long ) ( f * 100 ) % 100 )
#define _d_3f( d, f ) "%"#d"ld.%ld", ( long ) f, abs( ( long ) ( f * 1000 ) % 1000 )
#define _d_4f( d, f ) "%"#d"ld.%ld", ( long ) f, abs( ( long ) ( f * 10000 ) % 10000 )
#define _d_5f( d, f ) "%"#d"ld.%ld", ( long ) f, abs( ( long ) ( f * 100000 ) % 100000 )
#define _d_6f( d, f ) "%"#d"ld.%ld", ( long ) f, abs( ( long ) ( f * 1000000 ) % 1000000 )

/*--------------------------------------------------*/

#if defined( __AVR_ATmega640__  ) || defined( __AVR_ATmega1280__ ) || defined( __AVR_ATmega1281__ ) || defined( __AVR_ATmega2560__ ) || defined( __AVR_ATmega2561__ ) || \
    defined( __AVR_ATmega328P__ ) || defined( __AVR_ATmega168__  ) || defined( __AVR_ATmega8__    )
    void xprintfInit( HardwareSerial * serial, int bufferSize );
#elif defined( __AVR_ATmega4809__ )
    void xprintfInit( UartClass * serial, int bufferSize );
#endif
void xprintfInit_SWS( SoftwareSerial * serial, int bufferSize );
#if defined( __AVR_ATmega32U4__ ) || defined( __AVR_ATmega16U4__ )
    void xprintfInit_LEO( Serial_ * serial, int bufferSize );
#endif
int xprintf( const char * fmt, ... );

/*--------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __XPRINTF_H__ */
