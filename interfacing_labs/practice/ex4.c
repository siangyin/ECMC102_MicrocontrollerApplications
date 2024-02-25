#include <xc.h>
#include "config.h"

// DEFINE OF INPUT SWITCHES
#define PB0 PORTBbits.RB0
#define PB1 PORTBbits.RB1
#define TS2 PORTBbits.RB2
#define TS4 PORTBbits.RB4

#define LCD_DATA PORTD
#define LCD_RS PORTEbits.RE1 // RS signal for LCD 
#define LCD_E PORTEbits.RE0 // E signal for LCD

// DECLARE OF FUNCTIONS
void configurePortAndState(void);
void alarmOn(void);
void alarmOff(void);
void startEvacuation(void);
void delayInSeconds(float sec);
void offAllLED(void);
void LEDSeq(void);
void blinkLEDs(void);
void lightUpLED(int position);
void LCD_sendCW(char x); // 8-bit Control word for LCD
void LCD_sendData(char x); // 8-bit Text Data for LCD
void Init_LCD(void); // Declare function here - Initialize the LCD
void displayTxtInLCD(int status);

// VARIABLES
unsigned int alarmStatus = 0;
unsigned int timer = 6;

unsigned char i;

void main(void) {
  configurePortAndState();

  while (1) {

    if (alarmStatus == 0 && (TS2 == 1 || TS4 == 1)) {
      alarmStatus = 1;
      timer=6;
      
      while(alarmStatus>0){
          if (PB0 == 0) { //alarmStatus==1 && 
              alarmStatus = 0;
              lightUpLED(3);
              //offAllLED();
              //lightUpLED(2);
          }
          
          if (PB1 == 0) { //alarmStatus==1 &&
              alarmStatus = 2;
              //offAllLED();
              blinkLEDs;
              
          } // end of while-if-while-if2
      } // end of while-if-while
    } // end of while-if

  } // of of main-while
} // end of main

void configurePortAndState(void) {

  ANSELA=0, ANSELB=0, ANSELD=0, ANSEL=0;
  TRISA = 0b11110000;
  TRISB = 0b11111111; // configure direction of RA0-RA3 as output
  TRISD = 0b00001111;
  TRISE = 0b11111100; // PORTE  RE0 and RE1 as output

  Init_LCD();
  offAllLED();
  
} // end configurePortAndState


void alarmOn(void) { 

  while (timer >= 0 && alarmStatus == 1) {
    if (PB0 == 0) { // false alarm action here
      alarmStatus = 0;
      offAllLED();
      displayTxtInLCD(1);
      LEDSeq(); // for testing purpose
      break;
    }

    if (timer == 0 || PB1 == 0) { // confirm emergency action here
      alarmStatus = 2;
      //startEvacuation();
      offAllLED();
      blinkLEDs();
      displayTxtInLCD(2);
      break;
    }

    // Within timer countdown and no response, continue countdown while loop
    if (timer > 0 && PB0 == 1 && PB1 == 1) {
      // Continue countdown
      delayInSeconds(1.0); // Delay for 1 second
      timer--;
    }

  } // end of alarmOn-while

}; // end alarmOn

void alarmOff(void) {
  offAllLED();
}

void startEvacuation(void) {
  blinkLEDs();
}

void delayInSeconds(float sec) {
  unsigned int ms = sec * 1000; // Convert seconds to ms

  for (unsigned int i = 0; i < ms; i++) {
    _delay(1000);
  }
} // end delayInSeconds

void offAllLED(void) {
  PORTA = PORTA & 0b11110000;
}

void LEDSeq() {
  offAllLED();

  while (alarmStatus == 1) {
    for (int shift = 3; shift >= 0 && alarmStatus == 1; shift--) {
      PORTA = (PORTA & 0b11110000) | (0b00000001 << shift); // Only affect positions 0 to 3
      delayInSeconds(1.0);
    }
  }
} // end LEDSeq

void blinkLEDs(void) {
  //    offAllLED();
  while (alarmStatus == 2) {
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

void Init_LCD(void) {
  _delay(15000);
  LCD_sendCW(0b00000011);
  _delay(5000);
  LCD_sendCW(0b00000010);
  LCD_sendCW(0b00101000);
  LCD_sendCW(0b00001100);
  LCD_sendCW(0b00000110);
  LCD_sendCW(0b00000001);
}

void LCD_sendCW(char x) {
  LCD_RS = 0;
  LCD_DATA = x;
  LCD_E = 1;
  _delay(1000);
  LCD_E = 0;
  _delay(1000);
  LCD_DATA = x << 4;
  LCD_E = 1;
  _delay(1000);
  LCD_E = 0;
  _delay(1000);
}

void LCD_sendData(char x) {
  LCD_RS = 1;
  LCD_DATA = x;
  LCD_E = 1;
  _delay(1000);
  LCD_E = 0;
  _delay(1000);
  LCD_DATA = x << 4;
  LCD_E = 1;
  _delay(1000);
  LCD_E = 0;
  _delay(1000);
}

void displayTxtInLCD(int status){
    // clear LCD 
    LCD_sendCW(0b00000001); 
    
    char msg1_line1[] = "Attention"; 
    char msg1_line2[] = "Alarm triggered";

    char msg2_line1[] = "Attention"; 
    char msg2_line2[] = "Please evacuate asap";
    
    char msg3_line1[] = "We apologized"; 
    char msg3_line2[] = "It's false alarm";
    
    if(status==1){
        // LCD line 1
      LCD_sendCW(0b00000010);
      for (i = 0; msg1_line1[i] != 0; i++)
        LCD_sendData(msg1_line1[i]);
      
      LCD_sendCW(0b11000000); 
      for (i = 0; msg1_line2[i] != 0; i++)
        LCD_sendData(msg1_line2[i]);
     
    }else if(status==2){
        // LCD line 1
      LCD_sendCW(0b00000010);
      for (i = 0; msg2_line1[i] != 0; i++)
        LCD_sendData(msg2_line1[i]);
      
      
      LCD_sendCW(0b11000000); 
      for (i = 0; msg2_line2[i] != 0; i++)
        LCD_sendData(msg2_line2[i]);
     
      
        
    }else{
        LCD_sendCW(0b00000010);
      for (i = 0; msg3_line1[i] != 0; i++)
        LCD_sendData(msg3_line1[i]);
      
      
      LCD_sendCW(0b11000000); 
      for (i = 0; msg3_line1[i] != 0; i++)
        LCD_sendData(msg3_line1[i]);
      
      delayInSeconds(5.0);
      LCD_sendCW(0b00000001);
    }
}