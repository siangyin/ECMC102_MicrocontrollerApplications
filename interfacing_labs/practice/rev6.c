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
void lightUpLED(int position);
void triggerLEDs(char act);
void displayCount(int time);
void startCountdown(void);
void displayTimeUnit(char position, char digit);
void clearTimer(void);
void init_LCD(void);
void LCD_send(char data, char lcdRS);
void displayTxtInLCD(const char * line1,
  const char * line2);

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

unsigned int timer = 60;
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

  unsigned char alarmStatus = 0;
  int position = 3;

  init_LCD();
  clearTimer();
  PORTA = 0b00000000;

  while (alarmStatus == 0) {

    if (PB0 == 0 || PB1 == 0) {
      _delay(150000);
      alarmStatus = 1;
      _delay(1000);
      displayTxtInLCD("Attention", "Alarm triggered");

      timer = 60;

    }
  }

  while (alarmStatus == 1) {

    unsigned char dig0, dig1;

    int count = 60;
    while (count > -1 && alarmStatus == 1) {

      if (TS2 == 1 || TS4 == 1) {
        if (TS2 == 1) {

          displayTxtInLCD("Sorry for", "false alarm");
          clearTimer();
          alarmStatus = 2;

        } else if (TS4 == 1) {

          displayTxtInLCD("Emergency", "Please evacuate");
          clearTimer();
          alarmStatus = 3;
        }
      } else {

        dig1 = count / 10;
        dig0 = count % 10;

        for (int i = 0; i < 1000; i++) {
          PORTAbits.RA5 = 0;
          PORTAbits.RA4 = 0;
          PORTC = disTable[dig0];
          _delay(1000); // 1-second delay for each digit

          PORTAbits.RA5 = 0;
          PORTAbits.RA4 = 1;
          PORTC = disTable[dig1];
          _delay(1000); // 1-second delay for each digit

        }

        lightUpLED(position);

        if (position == 0) {
          position = 3;
        } else {
          position--;
        }

        count--;
      }

    }

  }

  while (alarmStatus == 2) {

    triggerLEDs(0);
    delayInSeconds(5.0);
    alarmStatus = 0;
  }

  while (alarmStatus == 3) {
    triggerLEDs(1);
    delayInSeconds(0.5);
    triggerLEDs(0);
    delayInSeconds(0.5);
  }

}

void delayInSeconds(float seconds) {
  unsigned int sec = seconds * 1000;

  for (unsigned int i = 0; i < sec; i++) {
    _delay(1000);
  }

}

void init_LCD(void) {
  _delay(15000);
  LCD_send(0b00000011, 0); // Reset
  _delay(5000);
  LCD_send(0b00000010, 0); // 4-bit mode
  LCD_send(0b00101000, 0); // Function Set - 4-bit, 2 lines, 5X7
  LCD_send(0b00001100, 0); // Display on, cursor off
  LCD_send(0b00000110, 0); // Entry mode - inc addr, no shift
  LCD_send(0b00000001, 0); // Clear display
}

void LCD_send(char data, char lcdRS) {
  LCD_RS = lcdRS;
  LCD_DATA = data;
  LCD_E = 1;
  _delay(1000);
  LCD_E = 0;
  _delay(1000);
  LCD_DATA = (unsigned char)(data << 4);
  LCD_E = 1;
  _delay(1000);
  LCD_E = 0;
  _delay(1000);
}

void displayTxtInLCD(const char * line1,
  const char * line2) {
  LCD_send(0b00000001, 0); // Clear LCD display 

  LCD_send(0b00000010, 0); // Move to the start of the first line
  for (unsigned char i = 0; line1[i] != 0; i++)
    LCD_send(line1[i], 1);

  LCD_send(0b11000000, 0); // Move to the start of the second line
  for (unsigned char i = 0; line2[i] != 0; i++)
    LCD_send(line2[i], 1);

  delayInSeconds(1.0);
}

void triggerLEDs(char act) {
  if (act == 1) {
    PORTA = 0b00001111;
  } else {
    PORTA = 0b00000000;
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

void startCountdown(void) {

  unsigned char dig0, dig1;

  for (int count = 60; count > 0; count--) {
    dig1 = count / 10;
    dig0 = count % 10;

    for (int i = 0; i < 1000; i++) {
      PORTAbits.RA5 = 0;
      PORTAbits.RA4 = 0;
      PORTC = disTable[dig0];
      _delay(1000); // 1-second delay for each digit

      PORTAbits.RA5 = 0;
      PORTAbits.RA4 = 1;
      PORTC = disTable[dig1];
      _delay(1000); // 1-second delay for each digit
    }
  }

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

void lightUpLED(int num) {
  triggerLEDs(0);
  if (num == 3) {
    PORTAbits.RA3 = 1;
  } else if (num == 2) {
    PORTAbits.RA2 = 1;
  } else if (num == 1) {
    PORTAbits.RA1 = 1;
  } else {
    PORTAbits.RA0 = 1;
  }
}