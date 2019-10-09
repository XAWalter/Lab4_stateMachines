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

typedef enum States { init, seqPress, seqRelease, unlocked} States;

char LockTick(char state){
    unsigned char tmpA = PINA;
    static unsigned char tmpB = 0x00; 
    switch ( state ){ //transitions

    case init:
	if ( tmpA == 0x01 ){
	    state = seqPress;
	}
	else{
	    state = init;
	}
	break;
   
    case seqPress:
	if ( tmpA == 0x00 ){
	    state = seqRelease;
	}
	else if ( tmpA == 0x01 ){
	    state = seqPress;
	}
	else{
	    state = init;
	}
	break;
	
    case seqRelease:
	if ( tmpA == 0x00 ){
	    state = seqRelease;
	}
	else if ( tmpA == 0x02 ){
	    state = unlocked;
	}
	else{
	    state = init;
	}
	break;

    case unlocked:
	if ( ( tmpA & 0x80 ) == 0x00 ){
	    state = unlocked;
	}
	else{
	   state = init;
	}
	break;

    default:
	state = init;
	break;
    }	

    switch ( state ){

    case init:
	tmpB = ( tmpB & 0xFE );
	break;

    case seqPress:
    case seqRelease:
	break;
    
    case unlocked:
	tmpB = ( tmpB | 0x01 );
	break;

    default:
	break;
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
	state = LockTick(state);
    }
    return 1;
}
