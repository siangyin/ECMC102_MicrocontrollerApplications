#include <xc.h>
#include "config.h"
#define SW0 PORTBbits.RB0

unsigned char detSW0(void);
void seg_DispAll(unsigned int result);
unsigned int btnCount=999;

void usrTask_Disp7Seg(void) {
    if(detSW0()==1){
        btnCount++;
        if(btnCount>9999)
            btnCount=0;
    }
    
    seg_DispAll(btnCount);
}

unsigned char detSW0(void){
    unsigned char detect =0;
    
    if(SW0==0){
        __delay_ms(20);
        if(SW0==0){
            detect=1;
            while(SW0==0);
        }
    }
    return detect;
}
