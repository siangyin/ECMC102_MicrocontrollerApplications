#include <xc.h>
#include "config.h"
#define BUZZER PORTBbits.RB3 //Buzzer is connected at RB3
#define SW0 PORTBbits.RB0

// Function declarations:

// - Defined in this file:
void initSysPins(void);
unsigned char detSW0(void);

// - Defined in other file(s):

void main(void) {
    
    unsigned int cnt;
    
    initSysPins();
    
    while(1){
        if(detSW0()==1){
            // produce 1khz tone for 1sec
            for(cnt=0;cnt<1000;cnt++){
                BUZZER=1;
                __delay_us(500);
                BUZZER=0;
                __delay_us(500);
                
            }
            
        }
    }
}

void initSysPins(void) {
    ANSELB = 0b00000000;
    TRISB = 0b00000001;
}


unsigned char detSW0(void) {
    unsigned char detect=0;
    

    
    if(SW0 == 0) {
        __delay_ms(20);
        if (SW0 == 0) {
            detect = 1;
            while (SW0 == 0);
        }

    }
    return (detect);
}