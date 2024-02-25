#include <xc.h>
#include "config.h"

#define LCD_DATA PORTD 	
#define LCD_RS	PORTEbits.RE1	// RS signal for LCD
#define LCD_E	PORTEbits.RE0	// E signal for LCD

void Init_LCD(void);            // Declare function here - Initialize the LCD
void LCD_sendCW(char);          // 8-bit Control word for LCD 
void LCD_sendData(char);        // 8-bit Text Data for LCD
 
char MESS[] = "WELCOME TO TP";
unsigned char i;
 
void main() {
  ANSELD = 0;                  // Configure PORTD as digital port        
  ANSELE = 0;;                  // Configure PORTE as digital
  TRISD = 0b00001111;	          // PORTD as output 
  TRISE = 0b11111100;	          // PORTE  RE0 and RE1 as output
  Init_LCD();	                 // Init LCD 4-bit interface, multiple line
  
  while (1){
      LCD_sendCW(0b00000010);	   // Return cursor to home position 
      for (i = 0; MESS[i]!= 0; i++)
          LCD_sendData (MESS[i]);
  } // end while
  
} // end of main
 
void Init_LCD(){
    _delay(15000);
    LCD_sendCW(0b00000011);
    _delay(5000);
    LCD_sendCW(0b00000010);
    LCD_sendCW(0b00101000);    // Function Set - 8-bit, 2 lines, 5X7
    LCD_sendCW(0b00001100);    // Display on, cursor off  
    LCD_sendCW(0b00000110);	// Entry mode - inc addr, no shift 
    LCD_sendCW(0b00000001);	// Clear display and home position

}
 
 
void LCD_sendCW(char x){
    LCD_RS = 0;
    LCD_DATA=x;
    LCD_E = 1;
    _delay(1000);
    LCD_E = 0;
    _delay(1000);
    LCD_DATA=x<<4;
    LCD_E = 1;
    _delay(1000);
    LCD_E = 0;
    _delay(1000);
}
 
void LCD_sendData(char x){
    LCD_RS   = 1;
    LCD_DATA = x; 
    LCD_E    = 1; 
    _delay(1000);	
    LCD_E    = 0; 
    _delay(1000);
    LCD_DATA=x<<4;
    LCD_E = 1; 
    _delay(1000);	
    LCD_E = 0;
    _delay(1000);

}