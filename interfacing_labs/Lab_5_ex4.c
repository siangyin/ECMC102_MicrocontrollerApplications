#include <xc.h>
#include "config.h"

void main() {
	int i;
	ANSELA=0;          // configure Port RA0-RA3 as digital I/O
	ANSELB=0;          // configure Port B as digital I/O
	TRISA=0b11110000;  // configure direction of RA0-RA3
	TRISB=0b11111111;  // configure direction of input
	PORTA = 0;
    
	unsigned char count;

	while (1){
		count = PORTB & 0b000000110;
		count = count >>1;
		for(i=0; i<count; i++){
			PORTA=0b00001111;
			for(i=0; i<500;i++)  // for 0.5 second
	    _delay(1000);

			PORTA=0b00000000;
			for(i=0; i<500;i++)  // for 0.5 second
	    _delay(1000);
		}

  
	} // end of while
} // end of main