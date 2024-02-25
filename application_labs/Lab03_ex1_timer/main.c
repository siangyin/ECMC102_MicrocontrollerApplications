#include <xc.h>
#include "config.h"

// Function declarations:
// - Defined in this file:
void initSysPins(void);
// - Defined in other file(s):
void initSysTimer0(void);

void main(void) {
    initSysPins(); // Initialise the port pins
    initSysTimer0(); // Initialise Timer 0

    PORTA = 0b00000010; // Turn on LED at RA1, off LED at RA0
    while (1) {
        // Do nothing
    }
}

void initSysPins(void) {
    ANSELA = 0b00000000;
    TRISA = 0b11111100;
}