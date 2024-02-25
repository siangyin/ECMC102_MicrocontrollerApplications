#include <xc.h>
#include "config.h"


#define SW1 PORTBbits.RB0

////SOLUTION OPTION 1
//void configurePins(void);
//void turnOnLED(void);
//void turnOffLED(void);
//
//void main() {
//    configurePins(); // Configure pins
//
//    while (1) {
//        if (SW1 == 0) // Check if SW1 is pressed
//            turnOnLED(); // Turn on LED
//        else
//            turnOffLED(); // Turn off LED
//    }
//}
//
//void configurePins(void) {
//    ANSELA = 0;         // Configure Port A as digital I/O
//    ANSELB = 0;         // Configure Port B as digital I/O
//    TRISA = 0b11111110; // Configure direction of RA0 as output
//    TRISB = 0b11111111; // Configure direction of RB0 as input
//}
//
//void turnOnLED(void) {
//    PORTAbits.RA0 = 1; // Turn on LED
//}
//
//void turnOffLED(void) {
//    PORTAbits.RA0 = 0; // Turn off LED
//}



void configurePins(void);
void controlLED(unsigned char state); // function declaration

void main() {
    configurePins(); // Configure pins

    while (1) {
        if (SW1 == 0) // is SW1 closed?
            controlLED(1); // turn off LED
        else
            controlLED(0); // turn on LED
    } // end of while
} // end of main

void configurePins(void) {
    ANSELA = 0;         // Configure Port A as digital I/O
    ANSELB = 0;         // Configure Port B as digital I/O
    TRISA = 0b11111110; // Configure direction of RA0 as output
    TRISB = 0b11111111; // Configure direction of RB0 as input
}

void controlLED(unsigned char state) {
    // state = 0 turns off the LED, state = 1 turns on the LED
    PORTAbits.RA0 = state;
}