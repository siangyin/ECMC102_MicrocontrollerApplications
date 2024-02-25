#include <xc.h>
#include "config.h"

const unsigned char segTable[]={
0b11000000, //0
0b11111001, //1
0b10100100, //2
0b10110000, //3
0b10011001, //4
0b10010010, //5
0b10000010, //6
0b11111000, //7
0b10000000, //8
0b10010000, //9
0b11111111, //blank
};

void sevseg_DspAll(unsigned int result) {
    int dig0,dig1,dig2,dig3;
    
    //dig0=result%10;
    //dig1=(result/10)%10;
    
    dig0=result%10;
    dig1=(result/10)%10;
    
    dig2=(result/100)%10;
    dig3=(result/1000)%10;
    
    
    PORTAbits.RA5=0;
    PORTAbits.RA4=0;
    
    PORTC=segTable[dig0];
    __delay_ms(5);
    PORTC=segTable[10];
    
    PORTAbits.RA5=0;
    PORTAbits.RA4=1;
    
    PORTC=segTable[dig1];
    __delay_ms(5);
    PORTC=segTable[10];
    
    PORTAbits.RA5=1;
    PORTAbits.RA4=0;
    
    PORTC=segTable[dig2];
    __delay_ms(5);
    PORTC=segTable[10];
    
    PORTAbits.RA5=1;
    PORTAbits.RA4=1;
    
    PORTC=segTable[dig3];
    __delay_ms(5);
    PORTC=segTable[10];
    
}