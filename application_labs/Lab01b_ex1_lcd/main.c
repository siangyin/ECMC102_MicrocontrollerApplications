#include <xc.h>
#include "config.h"

// Function Declarations:
// - Defined in this file:
void initSysPins(void);

// - Defined in other file(s):
void initLCD(void);
void LCD_sendData(char x);
void LCD_setPos(char row, char col);

void main(void) {
    char message1[] = "Hello, World!";
    char message2[] = "I'm learning LCD";
    unsigned int i;

    initSysPins();
    initLCD();

    LCD_setPos(1, 1);
    for (i = 0; message1[i] != 0; i++) {
        LCD_sendData(message1[i]);
    }

    LCD_setPos(2, 1);
    for (i = 0; message2[i] != 0; i++) {
        LCD_sendData(message2[i]);
    }

    PORTA = 0b00001010;
    while (1) {
        PORTA ^= 0b00001111;
        __delay_ms(1000);
    }
}

void initSysPins(void) {
    ANSELA = 0b00000000;
    ANSELD = 0b00000000;
    ANSELE = 0b00000000;
    TRISA = 0b11110000;
    TRISD = 0b00001111;
    TRISE = 0b11111100;
}
