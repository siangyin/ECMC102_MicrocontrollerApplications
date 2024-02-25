#include <xc.h>
#include "config.h"

void delayInSeconds(float sec);

unsigned char dig0, dig1, num[10]={
    0b11000000, // 0
    0b11111001, // 1
    0b10100100, // 2
    0b10110000, // 3
    0b10011001, // 4
    0b10010010, // 5
    0b10000010, // 6
    0b11111000, // 7
    0b10000000, // 8
    0b10011000, // 9 
};

void main(void) {
    
    ANSELA=0;           
    ANSELB=0;
//    ANSELC=0;

    TRISA=0b11000000;   
    TRISB=0b11110111;
//    TRISC=0b00000000;
  
    
    while(1){
        
//        PORTA=0b000011111;      // on LED1-4
//        delayInSeconds(1.0);    // delay 1sec
//        PORTA=0b00000000;       // off LED1-4 // or PORTA=~PORTA; or PORTA=0; 
//        delayInSeconds(1.0);    // delay 1sec
        
        // Turn on LED1 for 1 second
//        PORTA = 0b00000000;
//        delayInSeconds(1.0);
//
//        if(PORTBbits.RB0==0){ // PORTBbits.RB0==0 RB0 pressed
//            // Shift to the next LED for 1 second
//        for (int i = 0; i < 3; i++) {
//            PORTA = PORTA << 1;
//            delayInSeconds(1.0);
//        }
//        } else {
//            // Turn off all LEDs for 1 second
//            PORTA = 0;
//            delayInSeconds(1.0);
//        }
        
        
        
    } // end while
   
} // end main

void delayInSeconds(float sec) {
    unsigned int ms = sec * 1000;  // Convert seconds to ms

    for (unsigned int i = 0; i < ms; i++) {
        _delay(1000); 
    }
}