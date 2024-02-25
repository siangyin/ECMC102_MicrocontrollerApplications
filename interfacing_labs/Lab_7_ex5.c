#include <xc.h>
#include "config.h"

void generateTone(unsigned int frequency, unsigned int duration) {
    unsigned int i, j;

    for (i = 0; i < duration; i++) {
        PORTAbits.RA0 = 1;
        _delay(frequency);

        PORTAbits.RA0 = 0;
        _delay(frequency);
    }
}

void playTwinkleTwinkle() {
    generateTone(523, 500);  // C
    generateTone(523, 500);  // C
    generateTone(659, 500);  // E
    generateTone(659, 500);  // E
    generateTone(698, 500);  // F
    generateTone(698, 500);  // F
    generateTone(659, 500);  // E

    _delay(500);  // Pause between phrases

    generateTone(587, 500);  // D
    generateTone(587, 500);  // D
    generateTone(523, 500);  // C
    generateTone(523, 500);  // C
    generateTone(659, 500);  // E
    generateTone(659, 500);  // E
    generateTone(587, 500);  // D

    _delay(500);  // Pause between phrases

    generateTone(523, 500);  // C
    generateTone(523, 500);  // C
    generateTone(659, 500);  // E
    generateTone(659, 500);  // E
    generateTone(698, 500);  // F
    generateTone(698, 500);  // F
    generateTone(659, 500);  // E

    _delay(500);  // Pause between phrases

    generateTone(587, 500);  // D
    generateTone(587, 500);  // D
    generateTone(523, 500);  // C
    generateTone(523, 500);  // C
}

void main() {
    // Configure pins
    ANSELA = 0;         // Configure Port A as digital I/O
    TRISA = 0b11111110; // Configure direction of RA0 as output

    // Play "Twinkle, Twinkle, Little Star" melody
    playTwinkleTwinkle();

    // Infinite loop
    while (1) {
        // Additional tasks can be added here
    }
}