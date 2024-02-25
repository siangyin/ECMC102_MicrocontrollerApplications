#include <xc.h>
#include "config.h"


#define PB0 PORTBbits.RB0

void tone2k(void);
void blinkLEDs();
void tone1(void);
void tone2(void);

int i;

void main(void) {
  ANSELB = 0;
  ANSELA = 0;
  TRISB = 0b11110111;
  TRISA = 0b11110000;

  while (1) {
    if (PB0 == 0) {
      tone1();
      tone2();

      tone1();
      tone2();
      blinkLEDs();
      blinkLEDs();
      blinkLEDs();
      tone2k();
    }
  }
}

void tone1(void) {
  for (i = 0; i < 5000; i++) {
    PORTBbits.RB3 = 1;
    _delay(250);
    PORTBbits.RB3 = 0;
    _delay(250);
  }
}
void tone2(void) {
  for (i = 0; i < 2000; i++) {
    PORTBbits.RB3 = 1;
    _delay(600);
    PORTBbits.RB3 = 0;
    _delay(600);
  }
}

void tone2k(void) {
  for (i = 0; i < 6000; i++) {
    PORTBbits.RB3 = 1;
    _delay(250);
    PORTBbits.RB3 = 0;
    _delay(250);
  }
}

void blinkLEDs(void) {
  PORTA = 0b00001111;
  for (i = 0; i < 1000; i++)
    _delay(1000);
  PORTA = 0b00000000;
  for (i = 0; i < 1000; i++)
    _delay(1000);
}

