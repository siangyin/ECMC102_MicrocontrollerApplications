#include <xc.h>
#include "config.h"

#define S1 PORTBbits.RB2
#define S2 PORTBbits.RB4

void LUPLED1(void);
void LEDSeq(void);
void waitOneSec(void);

void main() {
    // Configure pins
    ANSELA = 0;         // Configure Port A as digital I/O
    ANSELB = 0;         // Configure Port B as digital I/O
    TRISA = 0b11110000; // Configure direction of RA0-3 as output
    TRISB = 0b11111111; // Configure direction of RB2 & RB4 as input

    while (1) {
        if(S1 == 0 && S2 == 1){
            LUPLED1();
        } else if(S1 == 1 && S2 == 0){
            LEDSeq();
        }
            
    } // end of while 
} // end of main

void waitOneSec (void){
    int i;
	for(i=0; i<1000;i++)
	  _delay(1000);
}

void LUPLED1(void){
	PORTA=0b00000001;
	waitOneSec();
	PORTA=0b00000000;
	waitOneSec();
}

void LEDSeq(void){
 PORTA=0; // all off
 PORTA=0b00001000; //on LED4
 waitOneSec();     // delay 1s
 PORTA=0b00000100; //on LED3
 waitOneSec();     // delay 1s
 PORTA=0b00000010; //on LED2
 waitOneSec();     // delay 1s
 PORTA=0b00000001; //on LED1
 waitOneSec();     // delay 1s
}
