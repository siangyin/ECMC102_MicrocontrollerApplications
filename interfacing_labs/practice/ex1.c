#include <xc.h>
#include "config.h"
#define SW1 PORTBbits.RB0
#define SW2 PORTBbits.RB1
#define SW3 PORTBbits.RB2
#define SW4 PORTBbits.RB4


void delayInSeconds(float sec) {
    unsigned int ms = sec * 1000;  // Convert seconds to ms

    for (unsigned int i = 0; i < ms; i++) {
        _delay(1000); 
    }
}



void main(void) {
    
    ANSELA = 0;         // Configure Port A as digital I/O
    ANSELB = 0;         // Configure Port B as digital I/O
    ANSELC = 0;
    TRISA = 0b11000000; // Configure direction PortA as output
    TRISB = 0b11111111; // Configure direction of RB0-4 as input
    TRISC=0b00000000;
    
//    unsigned char count, display[] = {0b11000000, 0b11111001,
//0b10100100, 0b10110000};
    
    while (1) {
//        count=(PORTB & 0b00000011);
//        PORTA=0b11111111;
//        PORTAbits.RA5=1;
//        PORTAbits.RA4=1;
        
//        PORTC=display[count];
        PORTA=0;
        if (SW1 == 0) {// RB0 is pressed
            PORTAbits.RA0=1; 
            delayInSeconds(0.5);
            
            PORTAbits.RA0=0;
            delayInSeconds(0.5);

        } else if (SW2 == 0){// RB1 is pressed
            PORTAbits.RA1=1; 
            delayInSeconds(0.5);
            
            PORTAbits.RA1=0;
            delayInSeconds(0.5);
        }

        
    } // end of while
    
    
}
