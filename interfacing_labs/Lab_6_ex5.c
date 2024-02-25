#include <xc.h>
#include "config.h"

void waitOneSec (void);
void waitTwoSec (void);
void blinkLEDs (void);

int i;

void main() {
	unsigned char count;
  // Configure pins
  ANSELA = 0;         // Configure Port A as digital I/O
  ANSELB = 0;         // Configure Port B as digital I/O
  TRISA = 0b11110000; // Configure direction of RA0-3 as output
  TRISB = 0b11111111; // Configure direction of RB2 & RB4 as input
	
	PORTA=0;            //Task 1
    while (1) {       // Task 2 and 3
        blinkLEDs();
        waitOneSec();
            
    } // end of while 
} // end of main


void waitOneSec(void) {
    for(i=0; i<1000;i++)
        _delay(1000); 
}
void waitTwoSec(void) {
    for(i=0; i<2000;i++)
        _delay(1000); 
}


void blinkLEDs (void ){
	PORTA=0b00001111;
	waitTwoSec();
 
	PORTA=~PORTA;
	waitTwoSec();
	
}