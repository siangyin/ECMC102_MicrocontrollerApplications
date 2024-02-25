#include <xc.h>
#include "config.h"

void initSysPins(void);
void initADC(void);
void dspTask_OnSevSeg(void);

void main(void) {
    initSysPins();
    initADC();
    
    while(1){
        dspTask_OnSevSeg();
    }
}

void initSysPins(void){
    ANSELA=0b00000001;
    ANSELC=0b00000001; 
   
    TRISA=0b11000001; 
    TRISC=0b00000000; 
    
}