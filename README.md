<<<<<<< Updated upstream
# aprintf
Wrapper library to use the Arduino serial ports like printf in C.
=======
# xprintf

## Preface

I'm a embedded systems developer and as such I write most of my C and C++ code in a more traditional and/or standard C style. In my projects I work alot with small MCUs (Micro Controler Unit) like the Arduino UNO or the Arduino Mega 2560 which have a limited amount of memory and processing capabilities. Because of this I try to avoid the usage of language specific techniques that (could) produce a lot of "invisible" background code to save space and general capacities.

## Code Style

In past and ongoing projects I worked with the RTOS (Realtime Operatin System) [FreeRTOS](https://www.freertos.org/index.html) by Richard Barry. Its coding style is very clean, easy to read and based on the [MISRA C](https://www.misra.org.uk/Activities/MISRAC/tabid/160/Default.aspx) standard. I got used to it and write most of my code based on the FreeRTOS [Coding Standard and Style Guide](https://www.freertos.org/FreeRTOS-Coding-Standard-and-Style-Guide.html).

## Tested Boards

* Arduino UNO
* Arduino Mega 2650
* Arduino Leonardo
* Arduino Pro Mini (ATmega328P, 5V, 16MHz)
* Arduino Nano Every
* Arduino Uno Wifi Rev2

# Getting Started

## Installation

Download the **.zip* file from GitHub and unzip it. Since this is a Arduino library it just has to be copied into your local Arduino sketchbook libraries folder `<YOUR SKETCHBOOK LOCATION>/libraries/`.

## Usage

To use the library in your Arduino sketches you have to include the xprintf header file, initialize the serial (Arduino) interface you want to use and the xprintfInit() function.

```C++
#incude <xprintf.h>
Serial.begin( 9600 );
xprintfInit( &Serial, 64 );
```

### Buffer

TODO

```C++
xprintfInit( &Serial, 64 );
```

### Floating Point Macros

TODO

```C++
#define _d_1f( d, f ) "%"#d"ld.%ld", ( long ) f, abs( ( long ) ( f * 10 ) % 10 )
#define _d_2f( d, f ) "%"#d"ld.%ld", ( long ) f, abs( ( long ) ( f * 100 ) % 100 )
#define _d_3f( d, f ) "%"#d"ld.%ld", ( long ) f, abs( ( long ) ( f * 1000 ) % 1000 )
#define _d_4f( d, f ) "%"#d"ld.%ld", ( long ) f, abs( ( long ) ( f * 10000 ) % 10000 )
#define _d_5f( d, f ) "%"#d"ld.%ld", ( long ) f, abs( ( long ) ( f * 100000 ) % 100000 )
#define _d_6f( d, f ) "%"#d"ld.%ld", ( long ) f, abs( ( long ) ( f * 1000000 ) % 1000000 )
```

## API

The API (Application Programming Interface) was designed to be sleak, simple and (Arduino typical) very user friendly and easy to use even for beginners.

### Functions

> `void xprintfInit( HardwareSerial * serial, int bufferSize );`
* TODO
    * `serial`     : TODO
    * `bufferSize` : TODO

> `void xprintfInit( UartClass * serial, int bufferSize );`
* TODO
    * `serial`     : TODO
    * `bufferSize` : TODO

> `void xprintfInit_SWS( SoftwareSerial * serial, int bufferSize );`
* TODO
    * `serial`     : TODO
    * `bufferSize` : TODO

> `void xprintfInit_LEO( Serial_ * serial, int bufferSize );`
* TODO
    * `serial`     : TODO
    * `bufferSize` : TODO

> `int xprintf( const char * fmt, ... );`
* TODO
    * `fmt` : TODO
    * `...` : TODO

## Usage Hints

The following points are intended to prevent incorrect usage of the library, show possible error sources and avoid frustration and general errors.

### 1. Floating Point Values

TODO
```C++
xprintf( "\nvalue = " _d_1f( 4, value ) );
```
> The first entry has the address value 0x1001 and has a object size of 3 - this covers the address values 0x1001, 0x1002 and 0x1003.
The second entry address lies in the address range of the first entry and must at least have the address value 0x1004!

# Todo

- [x] Include support for Arduino Nano Every and Arduino Uno Wifi Rev2;

# License

> MIT License
>
> Copyright (c) 2021 Martin Legleiter
>
> Permission is hereby granted, free of charge, to any person obtaining a copy
> of this software and associated documentation files (the "Software"), to deal
> in the Software without restriction, including without limitation the rights
> to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
> copies of the Software, and to permit persons to whom the Software is
> furnished to do so, subject to the following conditions:
>
> The above copyright notice and this permission notice shall be included in all
> copies or substantial portions of the Software.
>
> THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
> IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
> FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
> AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
> LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
> OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
> SOFTWARE.
>>>>>>> Stashed changes
