#include <xc.h>
#include "config.h"

// Function declarations:

// - Defined in this file:
void initSysPins(void);

// - Defined in other file(s):
void initSysTimer0(void);
void initLCD(void);
void dspTask_TimeOnLCD(void);

void main(void) {
    initSysPins(); // Initialise the port pins
    initSysTimer0(); // Initialise Timer 0
    initLCD();
    
    while (1) {
        dspTask_TimeOnLCD();
    }
} 

void initSysPins(void) {
    ANSELD = 0b00000000;
    ANSELE = 0b00000000;
    TRISD = 0b00001111;
    TRISE = 0b11111100;
}