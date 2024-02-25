#include <xc.h>
#include "config.h"

#define SW1 PORTBbits.RB0
unsigned char disTable[10]={0b11000000, 0b11111001,
0b10100100, 0b10110000,
0b100011001, 0b10010010,
0b10000010, 0b11111000,
0b10000000, 0b10011000};

void main(void) {
    
    ANSELB=0,ANSELC=0,ANSELA=0;
    TRISB=0b11111111,TRISC=0b00000000,TRISA=0b11001111;
    
    unsigned int count=0;
    unsigned char dig0,dig1;
    int i;
    
    while(1){
        
        if(SW1==0){
        _delay(120000);
        for(count=0;count<21;count++){
            dig1=count/10;
            dig0=count%10;
            for(i=0; i<200;i++){
                PORTAbits.RA5=0;
                PORTAbits.RA4=0;
                PORTC=disTable[dig0];
                _delay(5000);
                PORTAbits.RA5=0;
                PORTAbits.RA4=1;
                PORTC=disTable[dig1];
                 _delay(5000); 
            
            }//for loop 2 end

            
        }// for loop 1 end
       
        } // if end
        
        
        
    }//end of while loop
}// end of main
