////////////////////////////////////////////////////////////////////////////////
/**
 * @file        aprintfCompat.h
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

#ifndef __APRINTF_COMPAT_H__
#define __APRINTF_COMPAT_H__

/*-----------------------------------------------------------*/

#include <Arduino.h>

/*-----------------------------------------------------------*/

/* Check if the architecture of the currently selected borad is supported. */
#if defined( ARDUINO_ARCH_AVR ) || \
    defined( ARDUINO_ARCH_MEGAAVR ) || \
    defined( ARDUINO_ARCH_SAMD ) || \
    defined( ARDUINO_ARCH_RENESAS ) || \
    defined( ARDUINO_ARCH_ESP32 )

    /* Check the type of the currently selected board and set the needed
    parameters if it is supported. */
    #if defined( ARDUINO_AVR_UNO ) || \
        defined( ARDUINO_AVR_MEGA2560 ) || \
        defined( ARDUINO_AVR_PRO )

        #define MSerial_t   HardwareSerial
        #define SSerial_t   SoftwareSerial

    #elif defined( ARDUINO_AVR_LEONARDO )

        #define MSerial_t   Serial_
        #define HSerial_t   HardwareSerial
        #define SSerial_t   SoftwareSerial

    #elif defined( ARDUINO_AVR_NANO_EVERY ) || \
          defined( ARDUINO_AVR_UNO_WIFI_REV2 )

        #define MSerial_t   UartClass
        #define SSerial_t   SoftwareSerial

    #elif defined( ARDUINO_SAMD_MKRZERO ) || \
          defined( ARDUINO_SAMD_NANO_33_IOT )

        #define MSerial_t   Serial_
        #define HSerial_t   Uart

    #elif defined( ARDUINO_MINIMA ) || \
          defined( ARDUINO_UNOWIFIR4 )

        #define MSerial_t   _SerialUSB
        #define HSerial_t   UART
        #define SSerial_t   SoftwareSerial

    #elif defined( ARDUINO_ARCH_ESP32 )

        #define MSerial_t   USBCDC
        #define HSerial_t   HardwareSerial

    #else

        #warning The selected board has not been tested with this version of aprintf.

    #endif

#else

    #warning The selected board and architecture have not been tested with this version of aprintf.

#endif

/* If none of the needed defines is set, we try to use some assumed default
values for the Arduino serial port. */

#if !defined( MSerial_t )

    #define MSerial_t HardwareSerial

#endif

/*-----------------------------------------------------------*/

#endif /* __APRINTF_COMPAT_H__ */
