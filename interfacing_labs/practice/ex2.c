#include <xc.h>
#include "config.h"

void tone500Hz(void);
void delayInSeconds(float sec);
void runNumber(void);
void delay(int ms);
void playNote(int frequency, int duration);
void playMelody(void);

unsigned int count=0;

unsigned char dig0, dig1, num[10]={
    0b11000000, // 0
    0b11111001, // 1
    0b10100100, // 2
    0b10110000, // 3
    0b10011001, // 4
    0b10010010, // 5
    0b10000010, // 6
    0b11111000, // 7
    0b10000000, // 8
    0b10011000, // 9 
};

void main(void) {
    
    ANSELA=0;           
    ANSELB=0;
    ANSELC=0;

    TRISA=0b11000000;   
    TRISB=0b11110111;
    TRISC=0b00000000;
  
    
    while(1){
       
        if (PORTBbits.RB0 == 0 || PORTBbits.RB1 == 0 || PORTBbits.RB2 == 1 || PORTBbits.RB4 == 1) {//PORTBbits.RB0/RB1==0 is presssed
            count++;
            PORTA=0b00001111;
            //tone500Hz();
            
            //playMelody();
            delay(2000); 
            
        }else{
            PORTA=0b00000000;
            
        }
        
        //runNumber();
    } // end while
   
} // end main

void tone500Hz(void){
    int i;
    
//    for(i=0;i<2000;i++){
        PORTBbits.RB3 = 1; // Set RB3 high
        _delay(100000);     // 100ms delay
        PORTBbits.RB3 = 0;  // Set RB3 low
        _delay(100000);     // 100ms delay
//    }
} // tone500Hz



void delayInSeconds(float sec) {
    unsigned int ms = sec * 1000;  // Convert seconds to ms

    for (unsigned int i = 0; i < ms; i++) {
        _delay(1000); 
    }
}

void runNumber(void){
    
    _delay(1000);
    dig1=count/10;
    dig0=count%10;
    
    PORTAbits.RA5=1;
    PORTAbits.RA4=1;
    PORTC=num[1];
    _delay(1000);
    
    PORTAbits.RA5=1;
    PORTAbits.RA4=0;
    PORTC=num[2];
    _delay(1000);
    
    PORTAbits.RA5=0;
    PORTAbits.RA4=1;
    PORTC=num[dig1];
    _delay(1000);
    
   
    PORTAbits.RA5=0;
    PORTAbits.RA4=0;
    PORTC=num[dig0];
    _delay(1000); 
  
}

void delay(int ms) {
    for (int i = 0; i < ms; i++) {
        _delay(1);
    }
}

void playNote(int frequency, int duration) {
    int period = 1000 / frequency;
    int halfPeriod = period / 2;

    for (int i = 0; i < duration * 2; i++) {
        PORTBbits.RB3 = 1; // Set RB3 high
        delay(halfPeriod);
        PORTBbits.RB3 = 0; // Set RB3 low
        delay(halfPeriod);
    }
}

void playMelody(void) {
    int melody[] = {262, 294, 330, 349, 392, 440, 494, 523}; // Notes for "Happy Birthday"
    int duration = 500; // Duration of each note in ms

    for (int i = 0; i < 8; i++) {
        playNote(melody[i], duration);
        delay(50); // Add a short delay between notes
    }
}
