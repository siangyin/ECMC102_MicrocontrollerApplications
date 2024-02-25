#include <xc.h>
#include "config.h"
#define S1 PORTBbits.RB2 
#define S2 PORTBbits.RB4

// OPTION 1
//void main() {
//	int i;
//	ANSELA=0;          // configure Port A as digital I/O
//	ANSELB=0;          // configure Port B as digital I/O
//	TRISA=0b11110000;  // configure direction of RA0-RA3
//	TRISB=0b11111111;  // configure direction of RB2 and RB4
//
//	while (1){
//		if(S1==0&&S2==1){ 
////Blink all the LEDs (LED1- LED4) for 0.5 second interval
//			PORTA=0b00001111;     // ON all LEDs (LED1- LED4) 
//			for(i=0; i<500;i++)   // for 0.5 second
//	    _delay(1000);
//
//			PORTA=0b00000000;    // OFF all LEDs (LED1- LED4) 
//			for(i=0; i<500;i++)  // for 0.5 second
//	    _delay(1000);
//		} else if(S1 == 1 && S2 == 0){
////Turn on LED1 & LED3 and turn off LED2 & LED4 for 2 seconds. 
////Then turn off of all the LEDs for 2 seconds
//			PORTA=0;
//			PORTA=0b00001010;     //Turn on LED1 & LED3 
//			for(i=0; i<2000;i++)  //for 2 seconds
//	    _delay(1000);
//
//			PORTA=0b00000000;     //Turn off all LED 
//			for(i=0; i<2000;i++)  //for 2 seconds
//	    _delay(1000);
//		}
//  
//	} // end of while
//} // end of main


// OPTION 2 with delay functions

// Function to introduce a delay in seconds
void delaySeconds(float seconds) {
    // Oscillator frequency and instruction cycle time
    const unsigned int oscillatorFrequency = 4; // in MHz
    const float tcyc = 4.0 * (1.0 / oscillatorFrequency); // in microseconds

    // Calculate the number of cycles needed for the delay
    unsigned int cycles = (unsigned int)((seconds * 1000000.0) / tcyc);

    // Use a loop to introduce the delay
    for (unsigned int i = 0; i < cycles; i++) {
        _delay(1); // Delay for 1 microsecond
    }
}

void main() {
	int i;
	ANSELA=0;          // configure Port A as digital I/O
	ANSELB=0;          // configure Port B as digital I/O
	TRISA=0b11110000;  // configure direction of RA0-RA3
	TRISB=0b11111111;  // configure direction of RB2 and RB4

	while (1){
		if(S1==0&&S2==1){ 
//Blink all the LEDs (LED1- LED4) for 0.5 second interval
			PORTA=0b00001111;     // ON all LEDs (LED1- LED4) 
			delaySeconds(0.5);    // delay for 0.5 seconds

			PORTA=0b00000000;    // OFF all LEDs (LED1- LED4) 
			// OR PORTA=~PORTA   // to try
			// OR PORTA = 0;     //Turn off all LED 
			delaySeconds(0.5);   // delay for 0.5 seconds

		} else if(S1 == 1 && S2 == 0){
//Turn on LED1 & LED3 and turn off LED2 & LED4 for 2 seconds. 
//Then turn off of all the LEDs for 2 seconds
			PORTA=0;
			PORTA=0b00001010;     //Turn on LED1 & LED3 
			delaySeconds(2.0);   // delay for 2 seconds

			PORTA=0b00000000;     //Turn off all LED 
			// OR PORTA=~PORTA   // to try
			// OR PORTA = 0;     //Turn off all LED 
			delaySeconds(2.0);   // delay for 2 seconds
		}
  
	} // end of while
} // end of main