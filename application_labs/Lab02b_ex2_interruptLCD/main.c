#include <xc.h>
#include "config.h"

// Function Declarations:
// - Defined in this file:
void initSysPins(void);

// - Defined in other file(s):
void initSysExtInt(void);
void initLCD(void);
void LCD_sendData(char x);
void LCD_setPos(char row, char col);
void dspTask_OnLCD(void);

void main(void) {
    char message1[] = "Steps Tracker";
    char message2[] = "Today:";
    unsigned int i;

    initSysPins(); // initialise the port pins
    initSysExtInt(); // initialise the external interrupt
    initLCD(); //  initialise the LCD

    LCD_setPos(1, 1);
    for (i = 0; message1[i] != 0; i++) {
        LCD_sendData(message1[i]);
    }

    LCD_setPos(2, 1);
    for (i = 0; message2[i] != 0; i++) {
        LCD_sendData(message2[i]);
    }

    PORTA = 0b00000000;
    while (1) {
        dspTask_OnLCD();
    }
}

void initSysPins(void) {
    ANSELA = 0b00000000;
    ANSELB = 0b00000000;
    ANSELD = 0b00000000;
    ANSELE = 0b00000000;
    TRISA = 0b11110000;
    TRISB = 0b11111111;
    TRISD = 0b00001111;
    TRISE = 0b11111100;
}