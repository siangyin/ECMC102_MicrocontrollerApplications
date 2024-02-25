#include <xc.h>
#include "config.h"

// global variable:
unsigned int extint_pbCount = 0; // keep track of button presses

void initSysExtInt(void) {
    INTCONbits.GIE = 0; // disable global interrupt
    PIR0bits.INTF = 0; // clear external INT flag
    INTPPS = 0x09; // map external INTPPS =0x08(RB0)/ INTPPS =0x09(RB1)
    INTCONbits.INTEDG = 1; // configure for rising edge
    PIE0bits.INTE = 1; // enable external INT interrupt
    INTCONbits.GIE = 1; // enable global interrupt
}

void extint_IncrCount(void) { // function to increment count
    extint_pbCount++; // increment the count
    if (extint_pbCount > 99) { // prevent count from exceeding
        extint_pbCount = 0;
    }
}

unsigned int extint_GetCount(void) { // function for other files to get count
    return (extint_pbCount);
}