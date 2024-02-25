#include <xc.h>
#include "config.h"

#define PB0 PORTBbits.RB0
#define PB1 PORTBbits.RB1
#define TS2 PORTBbits.RB2
#define TS4 PORTBbits.RB4

#define LCD_DATA PORTD
#define LCD_RS PORTEbits.RE1
#define LCD_E PORTEbits.RE0

// Function prototypes
void delayInSeconds(float sec);
void Init_LCD(void);
void LCD_send(char data, char control);
void displayTxtInLCD(const char * line1,const char * line2);

void main() {
  ANSELD = 0;
  ANSELE = 0;
  TRISD = 0b00001111;
  TRISE = 0b11111100;
  Init_LCD();

  while (1) {
    displayTxtInLCD("Attention", "Alarm triggered");
    delayInSeconds(10.0);

    displayTxtInLCD("Attention", "Please evacuate asap");
    delayInSeconds(10.0);

    displayTxtInLCD("We apologized", "It's a false alarm");
    delayInSeconds(10.0);
  }
}

void delayInSeconds(float sec) {
  unsigned int ms = (unsigned int)(sec * 1000);

  for (unsigned int i = 0; i < ms; i++) {
    _delay(1000);
  }
}

void Init_LCD() {
  _delay(15000);
  LCD_send(0b00000011, 0); // Reset
  _delay(5000);
  LCD_send(0b00000010, 0); // 4-bit mode
  LCD_send(0b00101000, 0); // Function Set - 4-bit, 2 lines, 5X7
  LCD_send(0b00001100, 0); // Display on, cursor off
  LCD_send(0b00000110, 0); // Entry mode - inc addr, no shift
  LCD_send(0b00000001, 0); // Clear display
}

void LCD_send(char data, char control) {
  LCD_RS = control;
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