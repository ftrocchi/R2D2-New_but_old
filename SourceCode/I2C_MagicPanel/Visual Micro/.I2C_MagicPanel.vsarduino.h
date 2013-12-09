#ifndef _VSARDUINO_H_
#define _VSARDUINO_H_
//Board = Arduino Pro or Pro Mini (5V, 16 MHz) w/ ATmega328
#define __AVR_ATmega328P__
#define 
#define ARDUINO 105
#define ARDUINO_MAIN
#define __AVR__
#define F_CPU 16000000L
#define __cplusplus
#define __inline__
#define __asm__(x)
#define __extension__
#define __ATTR_PURE__
#define __ATTR_CONST__
#define __inline__
#define __asm__ 
#define __volatile__

#define __builtin_va_list
#define __builtin_va_start
#define __builtin_va_end
#define __DOXYGEN__
#define __attribute__(x)
#define NOINLINE __attribute__((noinline))
#define prog_void
#define PGM_VOID_P int
            
typedef unsigned char byte;
extern "C" void __cxa_pure_virtual() {;}

//
//
void receiveEvent(int eventCode);

#include "C:\Program Files (x86)\Arduino\hardware\arduino\variants\standard\pins_arduino.h" 
#include "C:\Program Files (x86)\Arduino\hardware\arduino\cores\arduino\arduino.h"
#include "C:\Users\Frank\Documents\Arduino\I2C_MagicPanel\I2C_MagicPanel.ino"
#include "C:\Users\Frank\Documents\Arduino\I2C_MagicPanel\I2C_Common.h"
#include "C:\Users\Frank\Documents\Arduino\I2C_MagicPanel\MagicPanel.cpp"
#include "C:\Users\Frank\Documents\Arduino\I2C_MagicPanel\MagicPanel.h"
#endif
