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

/*-----------------------------------------------------------*/

#include <Arduino.h>
#include <SoftwareSerial.h>

/*-----------------------------------------------------------*/

#define xprintfDEFAULT_BUFFER_SIZE 128

/*-----------------------------------------------------------*/

void xprintfInit( HardwareSerial * pxSerial, int sBufferSizePar = xprintfDEFAULT_BUFFER_SIZE );
void xprintfInit( SoftwareSerial * pxSerial, int sBufferSizePar = xprintfDEFAULT_BUFFER_SIZE );
#if defined __AVR_ATmega32U4__ || defined __AVR_ATmega16U4__
void xprintfInit( Serial_ * pxSerial, int sBufferSizePar = xprintfDEFAULT_BUFFER_SIZE );
#endif
int xprintf( const char * pcFmt, ... );

/*-----------------------------------------------------------*/

#endif /* __XPRINTF_H__ */
