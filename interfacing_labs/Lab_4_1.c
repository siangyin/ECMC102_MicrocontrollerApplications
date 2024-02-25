#include <xc.h> 
#include "config.h"

void main ()
{
	ANSELAbits.ANSA0= 0; // configure Port A RA0 as digital
	TRISA = 0b11111110; // configure direction of RA0 as output

	while(1) // repeat or run continuously
		{ 
			PORTA=0b00001111; // turn on LED
		} 
}