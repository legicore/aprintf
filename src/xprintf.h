////////////////////////////////////////////////////////////////////////////////
/**
 * @file        xprintf.h
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

#ifndef __XPRINTF_H__
#define __XPRINTF_H__

#include <Arduino.h>
#include <SoftwareSerial.h>

#ifdef __cplusplus
extern "C" {
#endif

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
