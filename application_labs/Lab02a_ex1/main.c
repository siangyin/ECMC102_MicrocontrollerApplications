#include <xc.h>
#include "config.h"

// Function Declarations:
void initSysPins(void);
void usrTask_CheckInputRB0(void);
void usrTask_CheckInputRB1(void);

void main(void) {

    initSysPins(); // initialise the port pins

    PORTA = 0b00000000; // turn off both LEDs at RA0 & RA1
    while (1) {
        usrTask_CheckInputRB0(); // call function to check RB0
        usrTask_CheckInputRB1(); // call function to check RB1
    }
}

void initSysPins(void) {
    ANSELA = 0b00000000;
    ANSELB = 0b00000000;

    TRISA = 0b11110000;
    TRISB = 0b11111111;
}