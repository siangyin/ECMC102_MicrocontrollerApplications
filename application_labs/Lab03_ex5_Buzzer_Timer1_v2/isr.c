#include <xc.h>
#include "config.h"
#define BUZZER PORTBbits.RB3 // Buzzer is connected at RB3

extern unsigned int tmr1_TotalReqdCount;
extern unsigned int tmr1_RunCount;

void __interrupt() isr(void) {
  unsigned int preload_value;
  if (PIR4bits.TMR1IF == 1) {
    PIR4bits.TMR1IF = 0;
    if (tmr1_RunCount < tmr1_TotalReqdCount) {
      BUZZER = ~BUZZER; // Toggle the buzzer stat
      tmr1_RunCount++;
      // Reload Timer1 again
      preload_value = (MAX_COUNT_VALUE_16BIT_TIMER - HALF_PERIOD1); //
      TMR1H = (unsigned char)(preload_value >> 8);
      TMR1L = (unsigned char) preload_value;
    } else {
      // If running count has reached desired, stop the tone
      T1CONbits.TMR1ON = 0; // Stop timer
    }
  }
}