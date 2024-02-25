#include <xc.h>
#include "config.h"
#define SW0 PORTBbits.RB0
#define SW1 PORTBbits.RB1

void usrTask_CheckInputRB0(void) {
    if (SW0 == 0) { // check SW0 for the first time
        __delay_ms(20); // delay contact bounce period
        if (SW0 == 0) { // check SW0 for the second time
            while (SW0 == 0); // wait for switch to be released
            PORTAbits.RA0 = ~PORTAbits.RA0; // toggle RA0
        }
    }
}

void usrTask_CheckInputRB1(void) {
    if (SW1 == 0) { // check SW0 for the first time
        __delay_ms(20); // delay contact bounce period
        if (SW1 == 0) { // check SW0 for the second time
            while (SW1 == 0); // wait for switch to be released
            PORTAbits.RA1 = 1; // turn on RA1 for 5s
            __delay_ms(5000); // delay for 5s
            PORTAbits.RA1 = 0; // turn off RA1
        }
    }
}
