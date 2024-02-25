#include <xc.h>
#include "config.h"

void main() {
    // Configure pins

    ANSELB = 0;         // Configure Port B as digital I/O
    TRISB = 0b11110111; // Configure direction of RA0 as output

    while (1) {
        // Generate a 500Hz tone
        PORTBbits.RB3 = 1; // Set RA0 high (half cycle)
        _delay(1000000);     // 1ms delay
        PORTBbits.RB3 = 0; // Set RA0 low (half cycle)
        _delay(1000000);     // 1ms delay
    }
}