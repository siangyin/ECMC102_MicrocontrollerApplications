#include <xc.h>
#include "config.h"

// Function Declarations:
void initSysPins(void);
void initSysExtInt(void);
void usrTask_CheckInputRB1(void);

void main(void) {
    initSysPins();
    initSysExtInt();

    PORTA = 0b00000000; // turn off both LED at RA0/RA1

    while (1) {
        usrTask_CheckInputRB1();
    }
}

void initSysPins(void) {
    ANSELA = 0b00000000;
    ANSELB = 0b00000000;

    TRISA = 0b11110000;
    TRISB = 0b11111111;
}