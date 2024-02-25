#include <xc.h>
#include "config.h"

// global variable:
unsigned int extint_pbCount = 0; // keep track of button presses
unsigned int extint_RefreshLCDFlag = 0; // Flag: set when ext int is detected

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
    if (extint_pbCount > 9999) { // use your own limit count
        extint_pbCount = 0; // reset count to 0, as we cannot dsp 5 digits
    }

    extint_RefreshLCDFlag = 1; // set flag to 1 so main() . can redresh the lcd
}

unsigned int extint_GetCount(void) { // function for other files to return count to caller
    return (extint_pbCount);
}