#include <xc.h>
#include "config.h"

#define SW1 PORTBbits.RB1

// function declarations:
// this file:
void initSysPins(void);

// other file:
void initADC(void);
unsigned int adc_GetConversion(void);

void main(void) {


    unsigned int result;
    initSysPins();
    initADC();

    while (1) {
        result = adc_GetConversion();
        if (result <= 10) {
            PORTAbits.RA1 = 0;
            PORTAbits.RA2 = 0;
            PORTAbits.RA3 = 0;
        } else if (result > 10 && result <= 100) {
            PORTAbits.RA1 = 1;
            PORTAbits.RA2 = 0;
            PORTAbits.RA3 = 0;
        } else if (result > 101 && result <= 1000) {
            PORTAbits.RA1 = 0;
            PORTAbits.RA2 = 1;
            PORTAbits.RA3 = 0;
        } else {
            PORTAbits.RA1 = 0;
            PORTAbits.RA2 = 0;
            PORTAbits.RA3 = 1;
        }

    }
}

void initSysPins(void) {
    ANSELA = 0b00000001;
    TRISA = 0b11110001;
}
