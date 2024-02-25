#include <xc.h> 
#include "config.h"

// SOLUTION OPTION 1
//void main ()
//{
//	ANSELA = 0 ; // configure Port A as digital
//	TRISA = 0b11110000; // configure direction of RA0-RA3 as output
//
//	int i;
//	while(1) // repeat or run continuously
//		{ 
//			PORTA =0; 
//			for(i=0; i<1000; i++)
//				_delay(1000); // 1000ms delay
//			PORTA =0b00001000; // turn on LED4
//			for(i=0; i<1000; i++)
//				_delay(1000); // 1000ms delay
//			PORTA =0b00000100; // turn off LED3
//			for(i=0; i<1000; i++)
//				_delay(1000); // 1000ms delay
//			PORTA =0b00000010; // turn on LED2
//			for(i=0; i<1000; i++)
//				_delay(1000); // 1000ms delay
//			PORTA =0b00000001; // turn off LED1
//			for(i=0; i<1000; i++)
//				_delay(1000); // 1000ms delay
//			
//		} 
//}

// SOLUTION OPTION 2
#include <xc.h>
#include "config.h"

void waitOneSec(void) {
        _delay(1000000); // 1000ms delay
}

void main() {
    // Configure pins
    ANSELA = 0;         // Configure Port A as digital I/O
    TRISA = 0b11110000; // Configure direction of RA0-RA3 as output

    while (1) {
        PORTA = 0; // All LEDs off
        waitOneSec();

        PORTA = 0b00001000; // LED4 on
        waitOneSec();

        PORTA = 0b00000100; // LED3 off
        waitOneSec();

        PORTA = 0b00000010; // LED2 on
        waitOneSec();

        PORTA = 0b00000001; // LED1 off
        waitOneSec();
    }
}