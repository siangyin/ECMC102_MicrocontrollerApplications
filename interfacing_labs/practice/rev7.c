#include <xc.h>
#include "config.h"

#define PB0 PORTBbits.RB0
#define PB1 PORTBbits.RB1
#define TS2 PORTBbits.RB2
#define TS4 PORTBbits.RB4
#define LCD_DATA PORTD
#define LCD_RS PORTEbits.RE1
#define LCD_E PORTEbits.RE0
#define BUZZER PORTBbits.RB3

// Function declarations
void configPort(void);
void delayByS(float sec);
void init_LCD(void);
void LCD_send(char data, char lcdRS);
void displayMessage(const char * line1, const char * line2);
void lightUpLED(int position);
void toggleLEDs(char act);
void displayCount(int time);
void clearTimer(void);
void sendAlert(void);
void clearAlarm(void);


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
  configPort();

  unsigned char alarmStatus = 0;
  int position = 3;

  while (alarmStatus == 0) {

    if (PB0 == 0 || PB1 == 0) {
      _delay(100000);
      alarmStatus = 1;
      sendAlert();
      displayMessage("Attention", "Alarm triggered");
    }
  }

  while (alarmStatus == 1) {
    int count = 60;
    
    while (count > -1 && alarmStatus == 1) {
      if (TS2 == 1 || TS4 == 1 || count == 0) {
          clearTimer();
        if (TS2 == 1) {
          clearAlarm();
          alarmStatus = 0;
        } else {
          displayMessage("Emergency", "Please evacuate");
          alarmStatus = 3;
        }
          
      } else {
        displayCount(count);
        lightUpLED(position);
        position = (position == 0) ? 3 : position - 1;
        count--;
      }
    }
  }

  

  while (alarmStatus == 3) {

      
    toggleLEDs(1);
    for (int i = 0; i < 300; i++) {
      BUZZER = 1;
      _delay(100);
      BUZZER = 0;
      _delay(400);

    }

    toggleLEDs(0);
    for (int i = 0; i < 100; i++) {
      BUZZER = 1;
      _delay(1000);
      BUZZER = 0;
      _delay(500);

    }

  }

}

void configPort(void) {
  ANSELB = 0;
  ANSELC = 0;
  ANSELA = 0;
  ANSELD = 0;
  ANSELE = 0;
  TRISB = 0b11110111;
  TRISC = 0b00000000;
  TRISA = 0b11000000;
  TRISD = 0b00001111;
  TRISE = 0b11111100;

  init_LCD();
  clearTimer();
  toggleLEDs(0);
}

void delayByS(float seconds) {
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

void displayMessage(const char * line1, const char * line2) {
  LCD_send(0b00000001, 0); // Clear LCD display 

  LCD_send(0b00000010, 0); // Move to the start of the first line
  for (unsigned char i = 0; line1[i] != 0; i++)
    LCD_send(line1[i], 1);

  LCD_send(0b11000000, 0); // Move to the start of the second line
  for (unsigned char i = 0; line2[i] != 0; i++)
    LCD_send(line2[i], 1);

  delayByS(1.0);
}

void lightUpLED(int num) {
  toggleLEDs(0);
  switch (num) {
  case 3:
    PORTAbits.RA3 = 1;
    break;
  case 2:
    PORTAbits.RA2 = 1;
    break;
  case 1:
    PORTAbits.RA1 = 1;
    break;
  default:
    PORTAbits.RA0 = 1;
  }
}

void toggleLEDs(char act) {
  PORTA = act ? 0b00001111 : 0b00000000;

}

void displayCount(int count) {
  unsigned char dig0, dig1;

  dig1 = count / 10;
  dig0 = count % 10;
  for (int i = 0; i < 1000; i++) {
    PORTAbits.RA5 = 0;
    PORTAbits.RA4 = 0;
    PORTC = disTable[dig0];
    _delay(500);
    PORTAbits.RA5 = 0;
    PORTAbits.RA4 = 1;
    PORTC = disTable[dig1];
    _delay(500);
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

void sendAlert(void) {
// 1: sound like phone start
//  for (int i = 0; i < 2; i++) {
//    for (int i = 0; i < 300; i++) {
//      BUZZER = 1;
//      _delay(100);
//      BUZZER = 0;
//      _delay(250);
//
//    }
//
//    for (int i = 0; i < 100; i++) {
//      BUZZER = 1;
//      _delay(1000);
//      BUZZER = 0;
//      _delay(250);
//    }
//  }
// 1 : sound like phone end

// 2: sound  start
//  for (int i = 0; i < 30; i++) {
//    for (int i = 0; i < 150; i++) {
//      BUZZER = 1;
//      _delay(1200);
//      BUZZER = 0;
//      _delay(300);
//
//    }
//    
//    for (int i = 0; i < 150; i++) {
//      BUZZER = 1;
//      _delay(100);
//      BUZZER = 0;
//      _delay(100);
//    }
//  }
// 2 : sound  end
    
  

// 3 : sound  start


 for (int i = 0; i < 2; i++) {
        // Short beep sequence
        for (int j = 0; j < 250; j++) {
            BUZZER = 1;
            _delay(100);  // Short delay for a short beep
            BUZZER = 0;
            _delay(150);  // Pause between beeps
        }

        // Long beep sequence
        for (int j = 0; j < 250; j++) {
            BUZZER = 1;
            _delay(500);  // Longer delay for a long beep
            BUZZER = 0;
            _delay(250);  // Pause between beeps
        }
    }
// 3 : sound  end
}

void clearAlarm(void) {
  displayMessage("Sorry for", "false alarm");
  toggleLEDs(0);
  delayByS(5.0);
  
}
