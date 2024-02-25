#include <xc.h>
#include "config.h"
#define S1 PORTBbits.RB2 
#define S2 PORTBbits.RB4

void main() {
	int i;
	ANSELA=0;          // configure Port A as digital I/O
	ANSELB=0;          // configure Port B as digital I/O
	TRISA=0b11110000;  // configure direction of RA0-RA3
	TRISB=0b11111111;  // configure direction of RB2 and RB4

	while (1){
		if(S1==0&&S2==1){
			PORTA=0b00000001;
			for(i=0; i<1000;i++)
                _delay(1000);

			PORTA=0b00000000;
			for(i=0; i<1000;i++)
                _delay(1000);

		} else if(S1 == 1 && S2 == 0){
			PORTA=0;
			PORTA=0b00001000;
			for(i=0; i<1000;i++)
                _delay(1000);

			PORTA=0b00000100;
			for(i=0; i<1000;i++)
                _delay(1000);

			PORTA=0b00000010;
			for(i=0; i<1000;i++)
                _delay(1000);

			PORTA=0b00000001;
			for(i=0; i<1000;i++)
                _delay(1000);

		}
  
	} // end of while
} // end of main