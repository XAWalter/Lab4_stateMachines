/*	Author: xwalt001
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

typedef enum States { init, releaseB0, pressB1, releaseB1, pressB0 }

char LedTick(char state){
    unsigned char tmpB = 0x00;
    unsigned char tmpA = PINA & 0x01;
    
    switch (state){
    
    case init:
	state = releaseB0;
	break;
    case releaseB0:
	state = tmpA? pressB1: releaseB0;
	break;
    case pressB1:
	state = tmpA? pressB1: releaseB1;
	break;
    case releaseB1:
	state = tmpA? pressB0: releaseB1;
	break;
    case pressB0:
	state = tmpA? pressB0: releaseB0;
	break;
    default:
	state = init;
	break;
    }

    switch(state){

    case init:
	break;
    case releaseB0:
	tmpB = 0x01;
	break;
    case pressB1:
	tmpB = 0x02;
    case releaseB1:
	tmpB = 0x02;
    case pressB0:
	tmpB = 0x01;
    default:
	tmpB = 0x00;
    }

    PORTB = tmpB;
    
    return state;

}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
    States state = init;
    while (1) {
	state = LedTick(state);
    }
    return 1;
}
