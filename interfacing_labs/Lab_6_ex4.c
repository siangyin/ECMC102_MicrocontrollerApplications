#include <xc.h>
#include "config.h"

#define SW1 PORTBbits.RB1 
#define SW2 PORTBbits.RB2 
void blinkLEDs (void );

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
        count = PORTB & 0b000000110;
        count = count >>1;
        for(i=0; i<count; i++){
          blinkLEDs();
        }
            
    } // end of while 
} // end of main


// Task 4
void blinkLEDs (void ){
	PORTA=0b00001111;
	for(i=0; i<500;i++)
		_delay(1000);
	PORTA=0b00000000;
	for(i=0; i<500;i++)
		_delay(1000);
}