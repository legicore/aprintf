///////////////////////////////////////////////////////////////////////////////
/**
 * @file        xprintf.h
 *
 * @author      legicore
 *
 * @brief       xxx
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef __XPRINTF_H__
#define	__XPRINTF_H__

/*-----------------------------------------------------------*/

#include <Arduino.h>

#include "SoftwareSerial.h"

/*-----------------------------------------------------------*/

#define xprintfDEFAULT_BUFFER_SIZE 128

/*-----------------------------------------------------------*/

void xprintfInit( HardwareSerial * pxSerial, int sBufferSize = xprintfDEFAULT_BUFFER_SIZE );
void xprintfInit( SoftwareSerial * pxSerial, int sBufferSize = xprintfDEFAULT_BUFFER_SIZE );
#if defined( __AVR_ATmega32U4__ ) || defined( __AVR_ATmega16U4__ )
void xprintfInit( Serial_ * pxSerial, int sBufferSize = xprintfDEFAULT_BUFFER_SIZE );
#endif
int xprintf( const char * pcFmt, ... );

/*-----------------------------------------------------------*/

#endif /* __XPRINTF_H__ */
