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
void delayBySec(float sec);
void initLcd(void);
void sendLcdData(char data, char lcdRS);
void displayMessage(const char * line1, const char * line2);
void onLED(int position);
void toggleLEDs(char act);
void displayCount(int time);
void clearTimer(void);
void sendAlert(void);
void clearAlarm(void);
void alarmIsTriggered(void);
void startEvacuation(void);

// Display table for numeric digits
unsigned char disTable[10] = {
  0xC0, 
  0xF9,
  0xA4,
  0xB0,
  0x99,
  0x92,
  0x82,
  0xF8,
  0x80,
  0x98
};

// Global variable
unsigned char alarmStatus = 0;

void main(void) {
  configPort();

  while (alarmStatus == 0) {

    if (PB0 == 0 || PB1 == 0) {
      _delay(100000);
      alarmIsTriggered();
    }
  }

}

// Function to configure port settings
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
  // Initialize LCD and other components
  initLcd();
  clearTimer();
  toggleLEDs(0);
}

void delayBySec(float seconds) {
  unsigned int sec = seconds * 1000;

  for (unsigned int i = 0; i < sec; i++) {
    _delay(1000);
  }

}

// Function to initialize LCD
void initLcd(void) {
  _delay(15000);
  sendLcdData(0b00000011, 0); // Reset
  _delay(5000);
  sendLcdData(0b00000010, 0); // 4-bit mode
  sendLcdData(0b00101000, 0); // Function Set - 4-bit, 2 lines, 5X7
  sendLcdData(0b00001100, 0); // Display on, cursor off
  sendLcdData(0b00000110, 0); // Entry mode - inc addr, no shift
  sendLcdData(0b00000001, 0); // Clear display
}

// Function to send data to LCD
void sendLcdData(char data, char lcdRS) {
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

// Function to display a message on LCD
void displayMessage(const char * line1, const char * line2) {
  sendLcdData(0b00000001, 0); // Clear LCD display 

  sendLcdData(0b00000010, 0); // Move to the start of the first line
  for (unsigned char i = 0; line1[i] != 0; i++)
    sendLcdData(line1[i], 1);

  sendLcdData(0b11000000, 0); // Move to the start of the second line
  for (unsigned char i = 0; line2[i] != 0; i++)
    sendLcdData(line2[i], 1);

  delayBySec(1.0);
}

// Function to light up an LED
void onLED(int num) {
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

// Function to turn on/off all LEDs
void toggleLEDs(char act) {
  PORTA = act ? 0b00001111 : 0b00000000;
}

// Function to display a countdown time on 7-segments
void displayCount(int count) {
  unsigned char dig0, dig1;

  dig1 = count / 10;
  dig0 = count % 10;

  for (int i = 0; i < 1000; i++) {
    // send digit to fourth position
    PORTAbits.RA5 = 0;
    PORTAbits.RA4 = 0;
    PORTC = disTable[dig0];
    _delay(500);
    // send digit to third position
    PORTAbits.RA5 = 0;
    PORTAbits.RA4 = 1;
    PORTC = disTable[dig1];
    _delay(500);
  }
}

// Function to clear countdown time on 7-segments
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

// Function to make short alert sound on buzzer
void sendAlert(void) {

  for (int i = 0; i < 2; i++) {
    // Short beep sequence
    for (int j = 0; j < 250; j++) {
      BUZZER = 1;
      _delay(100); // Short delay for a short beep
      BUZZER = 0;
      _delay(150); // Pause between beeps
    }

    // Long beep sequence
    for (int j = 0; j < 250; j++) {
      BUZZER = 1;
      _delay(500); // Longer delay for a long beep
      BUZZER = 0;
      _delay(250); // Pause between beeps
    }
  }

}

// Function to handle false alarm, reset to default state
void clearAlarm(void) {
  toggleLEDs(0);
  displayMessage("Sorry for", "false alarm");
  delayBySec(5.0);
  initLcd();
  alarmStatus = 0;
}

// Function to activate alarm
void alarmIsTriggered(void) {
  alarmStatus = 1;
  sendAlert();
  displayMessage("Attention", "Alarm triggered");
  int count = 60;
  int position = 3;

  while (count > -1 && alarmStatus == 1) {
    if (TS2 == 1 || TS4 == 1 || count == 0) {
      sendAlert();
      clearTimer();
      TS2 == 1 ? clearAlarm() : startEvacuation();
    } else {
      onLED(position);
      displayCount(count);
      position = (position == 0) ? 3 : position - 1;
      count--;
    }
  }
}

// Function to handle emergency state
void startEvacuation(void) {
  toggleLEDs(0);
  alarmStatus = 3;
  displayMessage("Emergency", "Please evacuate");
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