#include <R328P.h>  //main library for IO AVR ports
//         ^^^ <- AtMega 328P MCU
//Arduino Style pinout table:(~ PWM)
/*
 * BASE:
 * 0 - PD0
 * 1 - PD1
 * 2 - PD2
 * 3 - PD3~
 * 4 - PD4
 * 5 - PD5~
 * 6 - PD6~
 * 7 - PD7
 * 8 - PB0
 * 9 - PB1~
 * 10 - PB2~
 * 11 - PB3~
 * 12 - PB4
 * 13 - PB5 - LED
 * ADC:
 * 14(A0) - PC0
 * 15(A1) - PC1
 * 16(A2) - PC2
 * 17(A3) - PC3
 * 18(A4) - PC4
 * 19(A5) - PC5
 */
setup{
  AdcInit();  //Declare work with ADC
  PwmInit();  //Declare work with PWM
  loop{
    PB1Value(ReadAnalog(0));  //Set ReadAnalog on PB1 Port
  }
}
