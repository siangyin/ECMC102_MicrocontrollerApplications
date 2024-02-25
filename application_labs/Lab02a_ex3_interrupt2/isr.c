#include <xc.h>
#include "config.h"

void extint_IncrCount(void);

void __interrupt() isr(void) {
    if (PIR0bits.INTF == 1) { // check INT flag
        PIR0bits.INTF = 0; // clear INT flag
        extint_IncrCount(); // increment the number of INT count
    }
}