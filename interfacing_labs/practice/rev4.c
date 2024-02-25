#include <xc.h>
#include "config.h"

// Define of input switches
#define PB0 PORTBbits.RB0
#define PB1 PORTBbits.RB1
#define TS2 PORTBbits.RB2
#define TS4 PORTBbits.RB4

#define LCD_DATA PORTD
#define LCD_RS PORTEbits.RE1 // RS signal for LCD 
#define LCD_E PORTEbits.RE0 // E signal for LCD

// Functions & variables
void delayInSeconds(float sec);
void displayCount(int count);
void init_LCD(void);
void LCD_send(char data, char control);
void displayTxtInLCD(const char * line1,const char * line2);

unsigned char alarmStatus = 0;
unsigned int timer = 60;

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
  ANSELB=0,ANSELC=0,ANSELA=0,ANSELD=0,ANSELE=0;
  
  TRISB = 0b11110111; // toggle-switch input: RB2, RB4, push-button switches input: RB0, RB1 , buzzer output: RA3
  TRISC = 0b00000000; // 7-Segments output
  TRISA = 0b11001111; // 7-Segments output: RA5, RA4 and LED output RA0-RA3
  TRISD = 0b00001111; // RD4-RD7 as LCD output
  TRISE = 0b11111100; // RE0, RE1 as LCD output
  
  init_LCD();
  
  alarmStatus = 0;
  LCD_send(0b00000001, 0);
  displayCount(0);
  timer = 60;
  while(1){
      
  
      if(PB0==0 || PB1==0){
          _delay(150000);
          alarmStatus=1;
          
      }
      
      while(alarmStatus==1){
          displayTxtInLCD("Attention", "Alarm triggered");
          delayInSeconds(5.0);
          displayCount(timer);
          if(TS2==1||TS4==1){
              alarmStatus=2;
              
          }
                    
      }
      
      while(alarmStatus==2){
          displayTxtInLCD("Attention", "Please evacuate asap");
          //PORTAbits.RA0=0;
          displayCount(timer);
          
      }
      
//      displayTxtInLCD("We apologized", "It's a false alarm");
  }
}

void delayInSeconds(float sec) {
  unsigned int ms = (unsigned int)(sec * 1000);

  for (unsigned int i = 0; i < ms; i++) {
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


void init_LCD() {
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