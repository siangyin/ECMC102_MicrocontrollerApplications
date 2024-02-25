#include <xc.h> 
#include "config.h"

// SOLUTION OPTION 1
//void main ()
//{
//	ANSELA = 0 ; // configure Port A as digital
//	TRISA = 0b11110000; // configure direction of RA0-RA3 as output
//
//	while(1) // repeat or run continuously
//		{ 
//			PORTA =0b00001111; // turn on LED1-LED4
//			_delay(1000000); // 1000ms delay added 000
//			PORTA = 0b00000000; // turn off LED1-LED4 
//			// or PORTA=~PORTA
//			_delay(1000000); // 1000ms delay added 000
//		} 
//}

// SOLUTION OPTION 2
void main ()
{
	ANSELA = 0 ; // configure Port A as digital
	TRISA = 0b11110000; // configure direction of RA0-RA3 as output
	int i;
	while(1) // repeat or run continuously
		{ 
			PORTA =0b00001111; // turn on LED1-LED4
			for(i=0; i<1000; i++)
				_delay(1000); // 1000ms delay
			PORTA = 0b00000000; // turn off LED1-LED4 
			// or PORTA=~PORTA
			for(i=0; i<1000; i++)
				_delay(1000); // 1000ms delay
		} 
}