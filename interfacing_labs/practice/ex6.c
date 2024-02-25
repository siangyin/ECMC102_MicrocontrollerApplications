#include <xc.h>
#include "config.h"

#define PB0 PORTBbits.RB0
#define PB1 PORTBbits.RB1
#define TS2 PORTBbits.RB2
#define TS4 PORTBbits.RB4
#define LCD_DATA PORTD
#define LCD_RS PORTEbits.RE1 // RS signal for LCD 
#define LCD_E PORTEbits.RE0 // E signal for LCD

// Functions & variables
void delayInSeconds(float sec);
void displayCount(int time);
void clearTimer(void);


unsigned char disTable[10] = {
  0b11000000,
  0b11111001,
  0b10100100,
  0b10110000,
  0b10011001,
  0b10010010,
  0b10000010,
  0b11111000,
  0b10000000,
  0b10011000
};


void main(void) {
  ANSELB = 0;
  ANSELC = 0;
  ANSELA = 0;
  ANSELD = 0;
  ANSELE = 0;
  TRISB = 0b11110111;
  TRISC = 0b00000000;
  TRISA = 0b11000000;
  TRISD = 0b00001111; // RD4-RD7 as LCD output
  TRISE = 0b11111100; // RE0, RE1 as LCD output

  unsigned char alarmStatus = 1;
  unsigned int timer = 0;
  
  unsigned int count = 0, i; 


  clearTimer();

  
  while(1){
displayCount(count);
    if (PB0 == 0) {
      _delay(120000);
      count++;
    }
  }
}

void delayInSeconds(float seconds) {
  unsigned int sec = seconds * 1000;

  for (unsigned int i = 0; i < sec; i++) {
    _delay(1000);
  }

}

void displayCount(int count) {
    unsigned char dig0, dig1;

    // Extract digits from the count
    dig1 = count / 10;
    dig0 = count % 10;

    PORTAbits.RA5 = 0;
    PORTAbits.RA4 = 0;
    PORTC = disTable[dig0];
    _delay(1000);

    PORTAbits.RA5 = 0;
    PORTAbits.RA4 = 1;
    PORTC = disTable[dig1];
    _delay(1000);
}

void clearTimer(void) {
  
    PORTAbits.RA5 = 0;
    PORTAbits.RA4 = 0;
    PORTC = 0b11111111;
    _delay(1000);

    PORTAbits.RA5 = 0;
    PORTAbits.RA4 = 1;
    PORTC = 0b11111111;
    _delay(1000);
}
