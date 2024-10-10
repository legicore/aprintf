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

    /* Check for the known boards that are not (!) compatible with the Arduino
    SoftwareSerial library - and if none of them is selected, the compatibility
    gets activated. */
    #if !defined( ARDUINO_SAMD_MKRZERO ) && \
        !defined( ARDUINO_SAMD_NANO_33_IOT ) && \
        !defined( ARDUINO_ARCH_ESP32 )

        #define COMPAT_SOFTWARE_SERIAL

    #endif

    /* Check the type of the currently selected board and set the needed
    parameters if it is supported. */
    #if defined( ARDUINO_AVR_UNO ) || \
        defined( ARDUINO_AVR_MEGA2560 ) || \
        defined( ARDUINO_AVR_PRO )

        #define MONSerial_t     HardwareSerial

    #elif defined( ARDUINO_AVR_LEONARDO )

        #define MONSerial_t     Serial_
        #define HWSerial_t      HardwareSerial

    #elif defined( ARDUINO_AVR_NANO_EVERY ) || \
          defined( ARDUINO_AVR_UNO_WIFI_REV2 )

        #define MONSerial_t     UartClass

    #elif defined( ARDUINO_SAMD_MKRZERO ) || \
          defined( ARDUINO_SAMD_NANO_33_IOT )

        #define MONSerial_t     Serial_
        #define HWSerial_t      Uart

    #elif defined( ARDUINO_MINIMA ) || \
          defined( ARDUINO_UNOWIFIR4 )

        #define MONSerial_t     _SerialUSB
        #define HWSerial_t      UART

    #elif defined( ARDUINO_ARCH_ESP32 )

        #define MONSerial_t     USBCDC
        #define HWSerial_t      HardwareSerial

    #else

        #warning The selected board has not been tested with this version of aprintf.

        /* For unknown boards we deactivate the SoftwareSerial compatibility. */
        #if defined( COMPAT_SOFTWARE_SERIAL )
            #undef COMPAT_SOFTWARE_SERIAL
        #endif

    #endif

#else

    #warning The selected board and architecture have not been tested with this version of aprintf.

#endif

/* If none of the needed defines is set, we try to use some assumed default
values for the Arduino serial port. */

#if !defined( MONSerial_t )
    #define MONSerial_t     HardwareSerial
#endif

/*-----------------------------------------------------------*/

#endif /* __APRINTF_COMPAT_H__ */
