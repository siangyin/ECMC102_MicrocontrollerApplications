#include <xc.h>
#include "config.h"

// function declarations:
// defined in other file(s)

void LCD_sendData(char x);
void LCD_setPos(unsigned char row, unsigned char col);


// Extern Global Variable
unsigned char updateTime=0; // flag
unsigned char hour=0,min=0,sec=0; 

// This function is called by ISR whenever there is 1-second interrupt:
void dspTask_OnTimer0Interrupt(void){
    sec++;
    if(sec>59){
        sec=0;
        min++;
        if(min>59){
            min=0;
            hour++;
            if(hour>23){
                hour=0;
            }
        }
    }
    updateTime=1;
}


void dspTask_TimeOnLCD(void) {
    unsigned char dig0, dig1;

    if (updateTime == 1) {
        LCD_setPos(1,1);

        // Display the hour. make use of the % and / operators
        dig0 = hour % 10;
        dig1 = hour / 10;
        LCD_sendData(dig1 + 0x30); // add 0x30 to translate digit to ASCII
        LCD_sendData(dig0 + 0x30); // add 0x30 to translate digit to ASCII
        LCD_sendData(':'); // Send colon character

        // display min
        dig0 = min % 10;
        dig1 = min / 10;
        LCD_sendData(dig1 + 0x30); // add 0x30 to translate digit to ASCII
        LCD_sendData(dig0 + 0x30); // add 0x30 to translate digit to ASCII
        LCD_sendData(':'); // Send colon character

        // display min
        dig0 = sec % 10;
        dig1 = sec / 10;
        LCD_sendData(dig1 + 0x30); // add 0x30 to translate digit to ASCII
        LCD_sendData(dig0 + 0x30); // add 0x30 to translate digit to ASCII
        
        updateTime=0; // reset flag to zero so it refresh on LCD
        // is only done once every second
        
        

    }

}