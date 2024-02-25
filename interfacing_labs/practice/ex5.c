#include <xc.h>
#include "config.h"

// DEFINE OF INPUT SWITCHES
#define PB0 PORTBbits.RB0
#define PB1 PORTBbits.RB1
#define TS2 PORTBbits.RB2
#define TS4 PORTBbits.RB4

// DECLARE OF FUNCTIONS
void configurePortAndState(void);
void offAllLED(void);
void blinkLEDs(void);
void lightUpLED(int position);
void delayInSeconds(float sec); 

// VARIABLES
unsigned char alarmStatus = 0;
//unsigned int timer = 6;


void main(void) {
 configurePortAndState();

  while (1) {
      

    if (PB0 == 0 || PB1 == 0) {
      alarmStatus = 1;
      PORTAbits.RA0=1;
      _delay(2000);
      //lightUpLED(0);
      //timer=6;
      
      
      while(alarmStatus == 1){ //alarmStatus>0
          //lightUpLED(1);
          PORTAbits.RA3=1;
          _delay(2000);
          if (PB0 == 0) { //alarmStatus==1 && 
              //lightUpLED(2);
              //alarmStatus = 0;
              //offAllLED();
              PORTAbits.RA0=0;
              PORTAbits.RA3=0;
              PORTA=0x00;
              _delay(5000000);
              

          } 
          
          
      } // end of while-if-while
    } // end of while-if

  } // end of of main-while
} // end of main

void configurePortAndState(void) {

  ANSELA=0, ANSELB=0, ANSELD=0, ANSELC=0;
  TRISA = 0b11110000;
  TRISB = 0b11111111; // configure direction of RA0-RA3 as output
  TRISD = 0b00001111;
  TRISE = 0b11111100; // PORTE  RE0 and RE1 as output

  //Init_LCD();
  offAllLED();
  
} // end configurePortAndState

void offAllLED(void) {
  PORTA = PORTA & 0b11110000;
}

void blinkLEDs(void) {
  //    offAllLED();
  while (1) {
    PORTA = (PORTA & 0b11110000) | 0b00001111; // Turn only LEDs in RA0-RA3
    delayInSeconds(0.25);
    PORTA = PORTA & 0b11110000;
    delayInSeconds(0.25);
  }
} // end blinkLEDs

void lightUpLED(int position) {
  if (position >= 0 && position <= 3) {
    // Ensure the position is within the valid range (0-3)
    PORTA = (PORTA & 0b11110000) | (0b00000001 << position);
  }
}