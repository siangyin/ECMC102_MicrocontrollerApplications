#include <xc.h> 
#include "config.h"

void main ()
{
	ANSELA = 0 ; // configure Port A as digital
	TRISA = 0b11110000; // configure direction of RA0-RA3 as output

	while(1) // repeat or run continuously
		{ 
			PORTA =0b00001111; // turn on LED1-LED4
			_delay(1000); // 1ms delay
			PORTA = 0b00000000; // turn off LED1-LED4 
			// or PORTA=~PORTA
			_delay(1000); // 1ms delay
		} 
}