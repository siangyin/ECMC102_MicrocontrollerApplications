#include <xc.h>
#include "config.h"

int i,count=0;
void tone500Hz(void);

void tone500Hz(void) {
    for(i=0;i<1000;i++){
        PORTBbits.RB3 = 1; // Set RB3 high
        _delay(1000);     // 1ms delay
        PORTBbits.RB3 = 0; // Set RB3 low
        _delay(1000);        // 1ms delay
    }
    
    
}

void main() {
    // Configure pins
    ANSELB = 0;         // Configure Port B as digital I/O
    TRISB = 0b11110111; // Configure direction of RB3 as output
    
    while(1){
        if(count==0){
            tone500Hz();
            _delay(1000000); 
            count++;
        }
    }
   
}