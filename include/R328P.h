#ifndef R328P_H_INCLUDED
#define R328P_H_INCLUDED

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////// by R'bots company 07.10.2021 - 07.01.2022 ///////////////
///////////////////////    version for Arduino IDE   ///////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

//Lib. for arduino UNO or NANO. (AtMega328P)

//includes
#include <avr/io.h>

//defines
#define loop while(1)
#define setup int main(void)
#define end() return 0
#define end_loop() break

//defines math
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define abs(x) ((x)>0?(x):-(x))

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define EULER 2.718281828459045235360287471352

#define DegToRad(a) a * 0.017453292519943295769236907684886
#define RadToDeg(a) a * 57.295779513082320876798154814105

#define cos_deg(a) cos(a * 0.017453292519943295769236907684886)
#define sin_deg(a) sin(a * 0.017453292519943295769236907684886)
#define tan_deg(a) tan(a * 0.017453292519943295769236907684886)
#define cotan_deg(a) 1/tan(a * 0.017453292519943295769236907684886)

long double Pow(long double a, long double power){
    return power == 1 ? a : a * Pow(a, power - 1);
}

unsigned int strlen (char *str) {
    unsigned int len = 0;
    while (*str != '\0') {
        str++;
        len++;
    }
    return len;
}

void delay_loop_2(unsigned short __count){
	__asm__ volatile (
		"1: sbiw %0,1" "\n\t"
		"brne 1b"
		: "=w" (__count)
		: "0" (__count)
	);
}

void Delay(double __ms) {
    unsigned short __ticks;
    double __tmp = ((F_CPU) / 4e3) * __ms;
    if (__tmp < 1.0)
        __ticks = 1;
    else if (__tmp > 65535){
        __ticks = (unsigned short) (__ms * 10.0);
    while (__ticks){
        delay_loop_2(((F_CPU) / 4e3) / 10);
        __ticks --;
    }
        return;
    }else{
        __ticks = (unsigned short)__tmp;
    }
    delay_loop_2(__ticks);
}

void DelayMicroseconds(double __ms) {
    __ms /= 1000;
    unsigned short __ticks;
    double __tmp = ((F_CPU) / 4e3) * __ms;
    if (__tmp < 1.0)
        __ticks = 1;
    else if (__tmp > 65535){
        __ticks = (unsigned short) (__ms * 10.0);
    while (__ticks){
        _delay_loop_2(((F_CPU) / 4e3) / 10);
        __ticks --;
    }
        return;
    }else{
        __ticks = (unsigned short)__tmp;
    }
    _delay_loop_2(__ticks);
}


/** Work with Ports **/

//for another library
#define TypeB 0x05
#define TypeC 0x08
#define TypeD 0x0B

//IO port B

#define PortB1(a); (*(volatile char *)((0x05) + 0x20)) |= (1 << a);

#define PortB0(a); (*(volatile char *)((0x05) + 0x20)) &= ~(1 << a);


static void PortB(char numb, bool b){
    if(b != 0){
       (*(volatile char *)((0x05) + 0x20)) |= (1 << numb);
    }else{
       (*(volatile char *)((0x05) + 0x20)) &= ~(1 << numb);
    }
}

/*******************************************************************/

//IO port C

#define PortC1(a); (*(volatile char *)((0x08) + 0x20)) |= (1 << a);

#define PortC0(a);  (*(volatile char *)((0x08) + 0x20)) &= ~(1 << a);

static void PortC(char numb, bool b){
    if(b != 0){
        (*(volatile char *)((0x08) + 0x20)) |= (1 << numb);
    }else{
        (*(volatile char *)((0x08) + 0x20)) &= ~(1 << numb);
    }
}

/*******************************************************************/

//IO port D

#define PortD1(a);  (*(volatile char *)((0x0B) + 0x20)) |= (1 << a);

#define PortD0(a);  (*(volatile char *)((0x0B) + 0x20)) &= ~(1 << a);

static void PortD(char numb, bool b){
    if(b != 0){
        (*(volatile char *)((0x0B) + 0x20)) |= (1 << numb);
    }else{
        (*(volatile char *)((0x0B) + 0x20)) &= ~(1 << numb);
    }
}

/*******************************************************************/
/*******************************************************************/

//PORTB Ps PWM

static void PortB_8_Bit_sys(char numb, char value, unsigned int time){
    char antivalue = 255 - value;
    char prvalue = value, prantivalue = antivalue;
    //time *= 62745;   //CPU frequency : 255
    while(time){
        while(value){
            (*(volatile char *)((0x05) + 0x20)) |= (1 << numb);
            --value;
        }
        while(antivalue){
            (*(volatile char *)((0x05) + 0x20)) &= ~(1 << numb);
            --antivalue;
        }
        --time;
        value = prvalue, antivalue = prantivalue;
    }
    (*(volatile char *)((0x05) + 0x20)) &= ~(1 << numb);
}

static void PortB_10_Bit_sys(char numb, unsigned short value, unsigned int time){
    unsigned short antivalue = 1023 - value;
    unsigned short prvalue = value, prantivalue = antivalue;
    //time *= 4000000;   //CPU frequency
    while(time){
        while(value){
            (*(volatile char *)((0x05) + 0x20)) |= (1 << numb);
            --value;
        }
        while(antivalue){
            (*(volatile char *)((0x05) + 0x20)) &= ~(1 << numb);
            --antivalue;
        }
        --time;
        value = prvalue, antivalue = prantivalue;
    }
    (*(volatile char *)((0x05) + 0x20)) &= ~(1 << numb);
}

static void PortB_4_Bit_sys(char numb, char value, unsigned int time){
    unsigned short antivalue = 16 - value;
    char prvalue = value, prantivalue = antivalue;
    //time *= 4000000;   //CPU frequency
    while(time){
        while(value){
            (*(volatile char *)((0x05) + 0x20)) |= (1 << numb);
            --value;
        }
        while(antivalue){
            (*(volatile char *)((0x05) + 0x20)) &= ~(1 << numb);
            --antivalue;
        }
        --time;
        value = prvalue, antivalue = prantivalue;
    }
    (*(volatile char *)((0x05) + 0x20)) &= ~(1 << numb);
}

/*******************************************************************/

//PORTC Ps PWM

static void PortC_8_Bit_sys(char numb, char value, unsigned int time){
    char antivalue = 255 - value;
    char prvalue = value, prantivalue = antivalue;
    while(time){
        while(value){
            (*(volatile char *)((0x08) + 0x20)) |= (1 << numb);
            --value;
        }
        while(antivalue){
            (*(volatile char *)((0x08) + 0x20)) &= ~(1 << numb);
            --antivalue;
        }
        --time;
        value = prvalue, antivalue = prantivalue;
    }
    (*(volatile char *)((0x08) + 0x20)) &= ~(1 << numb);
}

static void PortC_10_Bit_sys(char numb, unsigned short value, unsigned int time){
    unsigned short antivalue = 1023 - value;
    unsigned short prvalue = value, prantivalue = antivalue;
    //time *= 4000000;   //CPU frequency
    while(time){
        while(value){
            (*(volatile char *)((0x08) + 0x20)) |= (1 << numb);
            --value;
        }
        while(antivalue){
            (*(volatile char *)((0x08) + 0x20)) &= ~(1 << numb);
            --antivalue;
        }
        --time;
        value = prvalue, antivalue = prantivalue;
    }
    (*(volatile char *)((0x08) + 0x20)) &= ~(1 << numb);
}

static void PortC_4_Bit_sys(char numb, char value, unsigned int time){
    unsigned short antivalue = 16 - value;
    char prvalue = value, prantivalue = antivalue;
    //time *= 4000000;   //CPU frequency
    while(time){
        while(value){
            (*(volatile char *)((0x08) + 0x20)) |= (1 << numb);
            --value;
        }
        while(antivalue){
            (*(volatile char *)((0x08) + 0x20)) &= ~(1 << numb);
            --antivalue;
        }
        --time;
        value = prvalue, antivalue = prantivalue;
    }
    (*(volatile char *)((0x08) + 0x20)) &= ~(1 << numb);
}

/*******************************************************************/

//PORTD Ps PWM

static void PortD_8_Bit_sys(char numb, char value, unsigned int time){
    char antivalue = 255 - value;
    char prvalue = value, prantivalue = antivalue;
    //time *= 62745;   //CPU frequency : 255
    while(time){
        while(value){
            (*(volatile char *)((0x0B) + 0x20)) |= (1 << numb);
            --value;
        }
        while(antivalue){
            (*(volatile char *)((0x0B) + 0x20)) &= ~(1 << numb);
            --antivalue;
        }
        --time;
        value = prvalue, antivalue = prantivalue;
    }
    (*(volatile char *)((0x0B) + 0x20)) &= ~(1 << numb);
}

static void PortD_10_Bit_sys(char numb, unsigned short value, unsigned int time){
    unsigned short antivalue = 1023 - value;
    unsigned short prvalue = value, prantivalue = antivalue;
    //time *= 4000000;   //CPU frequency
    while(time){
        while(value){
            (*(volatile char *)((0x0B) + 0x20)) |= (1 << numb);
            --value;
        }
        while(antivalue){
            (*(volatile char *)((0x0B) + 0x20)) &= ~(1 << numb);
            --antivalue;
        }
        --time;
        value = prvalue, antivalue = prantivalue;
    }
    (*(volatile char *)((0x0B) + 0x20)) &= ~(1 << numb);
}

static void PortD_4_Bit_sys(char numb, char value, unsigned int time){
    unsigned short antivalue = 16 - value;
    char prvalue = value, prantivalue = antivalue;
    //time *= 4000000;   //CPU frequency
    while(time){
        while(value){
            (*(volatile char *)((0x0B) + 0x20)) |= (1 << numb);
            --value;
        }
        while(antivalue){
            (*(volatile char *)((0x0B) + 0x20)) &= ~(1 << numb);
            --antivalue;
        }
        --time;
        value = prvalue, antivalue = prantivalue;
    }
    (*(volatile char *)((0x0B) + 0x20)) &= ~(1 << numb);
}

/*******************************************************************/
/*******************************************************************/

//AnalogPort Types

#define PwmInit()         (*(volatile char *)((0x04) + 0x20)) |= (1 << 1) | (1 << 2) | (1 << 3);\
                          (*(volatile char *)((0x0A) + 0x20)) |= (1 << 6) | (1 << 5) | (1 << 3);\
                          (*(volatile char *)((0x05) + 0x20)) &= ~((1 << 1) | (1 << 2) | (1 << 3));\
                          (*(volatile char *)((0x0B) + 0x20)) &= ~((1 << 6) | (1 << 5) | (1 << 3));\
                          (*(volatile char *)((0x24) + 0x20)) |= 0b10100001;\
                          (*(volatile char *)((0x25) + 0x20)) |= 0b00000100;\
                          (*(volatile char *)(0x80)) |= 0b10100001;\
                          (*(volatile char *)(0x81)) |= 0b00001101;\
                          (*(volatile char *)(0xB0)) |= 0b10100001;\
                          (*(volatile char *)(0xB1)) |= 0b00000100;


//Timer functions

static void Timer0_Fast_PWM(void){
	DDRD |= (1 << PD6) | (1 << PD5);
	PORTD &= ~((1 << PD6) | (1 << PD5));
	TCCR0A |= (1 << WGM00) | (1 << COM0B1) | (1 << COM0A1);
	TCCR0B |= (1 << CS02);
}

static void Timer1_Fast_PWM(void){
	DDRB |= (1 << PB1) | (1 << PB2);
	PORTB &= ~((1 << PB1) | (1 << PB2));
	TCCR1A |= (1 << WGM10) | (1 << COM1B1) | (1 << COM1A1);
	TCCR1B |= (1 << CS10) | (1 << CS12) | (1 << WGM12);
}

static void Timer2_Fast_PWM(void){
	DDRB |= (1 << PB3);
	PORTB &= ~(1 << PB3);
	DDRD |= (1 << PD3);
	PORTD &= ~(1 << PD3);
	TCCR2A |= (1 << WGM20) | (1 << COM2B1) | (1 << COM2A1);
	TCCR2B |= (1 << CS22);
}

/*******************************************************************/

//AVR Style

#define OC0AValue(a)    OCR0A = a

#define OC0BValue(a)    OCR0B = a

#define OC1AValue(a)    OCR1A = a

#define OC1BValue(a)    OCR1B = a

#define OC2AValue(a)    OCR2A = a

#define OC2BValue(a)    OCR2B = a

/*******************************************************************/

//Ports Style

#define PD6Value(a)    OCR0A = a

#define PD5Value(a)    OCR0B = a

#define PB1Value(a)    OCR1A = a

#define PB2Value(a)    OCR1B = a

#define PB3Value(a)    OCR2A = a

#define PD3Value(a)    OCR2B = a

/*******************************************************************/
/*******************************************************************/

//ADC Input

#define AdcInit()   (*(volatile char *)(0x7C)) |= (1 << 6);  \
                    (*(volatile char *)(0x7A)) |= (1 << 2) | (1 << 1) | (1 << 0) | (1 << 7);


unsigned short ReadAnalog(char ADCchannel) {
    (*(volatile char *)(0x7C)) = ((*(volatile char *)(0x7C)) & 0xF0) | (ADCchannel & 0x0F);
    (*(volatile char *)(0x7A)) |= (1 << 6);
    while ( (*(volatile char *)(0x7A)) & (1 << 6) );
    return ADC;
}

#define A0 0
#define A1 1
#define A2 2
#define A3 3
#define A4 4
#define A5 5

/*******************************************************************/

//Input Digital Read
#define ReadB(a) (((*(volatile char *)((0x03) + 0x20)) & 1 << a)!=0)

#define ReadC(a) (((*(volatile char *)((0x06) + 0x20)) & 1 << a)!=0)

#define ReadD(a) (((*(volatile char *)((0x09) + 0x20)) & 1 << a)!=0)

/*******************************************************************/

//IO Types
#define InputTypeB(a);  (*(volatile char *)((0x04) + 0x20)) &= ~(1 << a);

#define OutputTypeB(a); (*(volatile char *)((0x04) + 0x20)) |= (1 << a);

#define InputTypeC(a);  (*(volatile char *)((0x07) + 0x20)) &= ~(1 << a);

#define OutputTypeC(a); (*(volatile char *)((0x07) + 0x20)) |= (1 << a);

#define InputTypeD(a);  (*(volatile char *)((0x0A) + 0x20)) &= ~(1 << a);

#define OutputTypeD(a); (*(volatile char *)((0x0A) + 0x20)) |= (1 << a);

/*******************************************************************/
/*******************************************************************/

//UART

#define UartInit(b)                 (*(volatile char *)(0xC5)) = (((16000000UL / (b * 16UL))) - 1) >> 8;         \
                                    (*(volatile char *)(0xC4)) = (((16000000UL / (b * 16UL))) - 1);              \
                                    (*(volatile char *)(0xC2)) = (0 << 6) | (0 << 4) | (0 << 3) | (3 << 1);      \
                                    (*(volatile char *)(0xC1)) = (1 << 4) | (1 << 3);


#define UartOutByte(DataByte) while (((*(volatile char *)(0xC0)) & (1 << 5)) == 0) {};           \
                              (*(volatile char *)(0xC6)) = DataByte;


char UartInByte(){
	while (( (*(volatile char *)(0xC0)) & (1 << 7)) == 0){};
	return UDR0;
}

static void UartOutStr(char *str){
    for(unsigned int i = 0; i < strlen(str); ++i){
        while (( (*(volatile char *)(0xC0)) & (1 << 5)) == 0) {};
        (*(volatile char *)(0xC6)) = str[i];
    }
}

static void UartOutStrLn(char *str){
    for(unsigned int i = 0; i < strlen(str); ++i){
        while (( (*(volatile char *)(0xC0)) & (1 << 5)) == 0){};
        (*(volatile char *)(0xC6)) = str[i];
    }
    while (( (*(volatile char *)(0xC0)) & (1 << 5)) == 0){};
    (*(volatile char *)(0xC6)) = '\n';
}

/**************** EEPROM ****************/

#define EEPROM_WriteByte(address, ch)   while((*(volatile char *)((0x1F) + 0x20)) & (1 << 1)); \
                                        (*(volatile unsigned short *)((0x21) + 0x20)) = address;         \
                                        (*(volatile char *)((0x20) + 0x20)) = ch;              \
                                        (*(volatile char *)((0x1F) + 0x20)) |= (1 << 2);       \
                                        (*(volatile char *)((0x1F) + 0x20)) |= (1 << 1);

/**
    while(EECR & (1 << 1));
    EEAR = address;
    EEDR = ch;
    EECR |= (1 << 2);
    EECR |= (1 << 1);
**/

unsigned char EEPROM_ReadByte(unsigned short address){
	while((*(volatile char *)((0x1F) + 0x20)) & (1 << 1));
	(*(volatile unsigned short *)((0x21) + 0x20)) = address;
	(*(volatile char *)((0x1F) + 0x20)) |= (1 << 0);
	return (*(volatile char *)((0x20) + 0x20));
}

/**
	while(EECR & (1 << 1));
	EEAR = address;
	EECR |= (1 << 0);
	return EEDR;
**/


/**
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
**/

/********************** Arduino Style functions **********************/

#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2

static void DigitalWrite(char port, char port_type, bool b){
    if(b != 0){
        _SFR_IO8(port_type) |= (1 << port);
    }else{
        _SFR_IO8(port_type) &= ~(1 << port);
    }
}

bool DigitalRead(char port, char port_type){
    return (((*(volatile char *)((port_type-2) + 0x20)) & 1 << port)!= 0);
}

static void PinMode(char port, char port_type, char type){
    if(type != 0){
        (*(volatile char *)((port_type-1) + 0x20)) |= (1 << port);
    }else{
        (*(volatile char *)((port_type-1) + 0x20)) &= ~(1 << port);
    }
}

#endif // R328P_H_INCLUDED
