#include <xc.h>
#include "config.h"

#define PB0 PORTBbits.RB0
void displayCount(int);

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

void delayInSeconds(float seconds) {
  unsigned int sec = seconds * 1000;

  for (unsigned int i = 0; i < sec; i++) {
    _delay(1000);
  }

}

void main(void) {

  ANSELB = 0, ANSELC = 0, ANSELA = 0;
  TRISB = 0b11111111, TRISC = 0b00000000, TRISA = 0b11001111;

  unsigned int count = 0;

  while (1) {
      displayCount(count);
    if (PB0 == 0) {
      _delay(120000);
      count++;
    }
  } //end of while loop
} // end of main

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