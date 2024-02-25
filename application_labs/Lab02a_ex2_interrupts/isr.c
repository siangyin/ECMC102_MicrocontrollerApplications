#include <xc.h>
#include "config.h"

void __interrupt() isr(void){
    if(PIR0bits.INTF == 1){ // check INT flag
        PIR0bits.INTF=0; // clear INT flag
        PORTAbits.RA0=~PORTAbits.RA0; // toggle LED at RA0
    }
}