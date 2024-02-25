#include <xc.h>
#include "config.h"

void initSysPins(void);
void usrTask_Disp7Seg(void);

void main(void) {
    initSysPins();
    
    while(1){
        usrTask_Disp7Seg();
    }
}

void initSysPins(void){
    ANSELA=0b00000000; // Set all PORT pins are digital
    ANSELB=0b00000000; // Set all PORT pins are digital
    ANSELC=0b00000000; // Set all PORT pins are digital
    TRISA=0b11001111; // Set RA5, RA4 as output, rest unused pins as inputs
    TRISB=0b11111111; // Set all Port B pins as inputs
    TRISC=0b00000000; // Set all Port C pins as outputs
    
}