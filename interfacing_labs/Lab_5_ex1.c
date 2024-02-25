#include <xc.h>
#include "config.h"

void main() {
	ANSELA=0;          // configure Port A as digital I/O
	ANSELB=0;          // configure Port B as digital I/O
	TRISA=0b11111110;  // configure direction of RA0 as o/p
	TRISB=0b11111111;  // configure direction of RB0 as i/p

	while (1){
		if (PORTBbits.RB0==0) // is SW1 closed?
			PORTAbits.RA0=1;   // turn on LED
		else
			PORTAbits.RA0=0;   // turn off LED
    } // end of while
} // end of main