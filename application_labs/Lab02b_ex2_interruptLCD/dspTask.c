#include <xc.h>
#include "config.h"

// function declarations:
// defined in other file(s)

void LCD_sendData(char x);
void LCD_setPos(unsigned char row, unsigned char col);
unsigned int extint_GetCount(void);

// Extern Global Variable
extern unsigned int extint_RefreshLCDFlag;

void dspTask_OnLCD(void) {
    unsigned int count;
    unsigned char dig0, dig1, dig2, dig3;

    if (extint_RefreshLCDFlag == 1) {
        PORTAbits.RA0 = 1; // turn on LED

        count = extint_GetCount(); // get count

        dig0 = count % 10;
        dig1 = (count % 100) / 10;
        dig2 = (count % 1000) / 100;
        dig3 = count / 1000;


        LCD_setPos(2, 8);
        LCD_sendData(dig3 + 0x30); // add 0x30 to translate digit to ASCII
        LCD_sendData(dig2 + 0x30);
        LCD_sendData(dig1 + 0x30);
        LCD_sendData(dig0 + 0x30);

        PORTAbits.RA0 = 0; // turn off LED
        extint_RefreshLCDFlag = 0;

    }

}