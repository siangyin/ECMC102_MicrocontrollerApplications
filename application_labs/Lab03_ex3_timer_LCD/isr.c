#include <xc.h>
#include "config.h"

// Function declarations:
// - Defined in this file:

// - Defined in other file(s):
void dspTask_OnTimer0Interrupt(void);

void __interrupt() isr(void) {
    if (PIR0bits.TMR0IF == 1) { // Check Timer0 interrupt flag
        PIR0bits.TMR0IF = 0; // Clear Timer0 interrupt flag
        dspTask_OnTimer0Interrupt();
        
        // reload the preload value for next interrupt
        TMR0H=0x0B;
        TMR0L=0x0c;
    }
}