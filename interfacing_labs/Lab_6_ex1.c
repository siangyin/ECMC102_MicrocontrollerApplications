#include <xc.h>
#include "config.h"
#include <stdio.h> // Include the necessary header for printf


#define SW1 PORTBbits.RB0

void onLED(void); // Function declaration

void main() {
    int i = 0; // Initialize i
    ANSELA = 0; // Configure Port A as digital I/O
    ANSELB = 0; // Configure Port B as digital I/O
    TRISA = 0b11111110; // Configure direction of RA0
    TRISB = 0b11111111; // Configure direction of RB0

    while (1) {
        if (SW1 == 0) { // Is SW1 closed?
            onLED();    // Turn on LED
            i += 1;
           // Print the value of i
        } 
        else {
            PORTAbits.RA0 = 0; // Turn off LED
        }
    } // end of while
} // end of main

void onLED(void) {
    PORTAbits.RA0 = 1; // Turn on LED
}
