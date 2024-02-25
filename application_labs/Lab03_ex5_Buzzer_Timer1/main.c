#include <xc.h>
#include "config.h"
#define SW1 PORTBbits.RB1

void initSysPins(void);
void initSysTimer1(void);
unsigned char detSW1(void);
void tmr1_StartTone(void);


void main(void) {
  initSysPins();
  initSysTimer1();
  while (1) {
    if (detSW1() == 1) {
      tmr1_StartTone();
    }
  }
}
void initSysPins(void) {
  ANSELB = 0b00000000; // Set RB1 as digital input
  TRISB = 0b00000010; // Set RB1 as input pin
}

unsigned char detSW1(void) {
  unsigned char detect = 0;

  if (SW1 == 0) {
    __delay_ms(20);
    if (SW1 == 0) {
      detect = 1;
      while (SW1 == 0);
    }
  }

  return detect;
}
