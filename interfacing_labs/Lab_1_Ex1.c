/*
 * File:   Ex1.c
 * Author: siangyin
 *
 * Created on 1 November, 2023, 8:40 PM
 */


#include <xc.h>

void main(void) {
    int count = 0,x;
    ANSELA = 0x00;
    TRISA = 0;
    while(1){
        for(x=0;x<5;x++)
            count =count+2;
        PORTA=0x0A;
    }
    
}
