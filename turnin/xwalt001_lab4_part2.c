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

typedef enum States { init, releasedWait, pressedWait, inc, dec, reset } States;

char CountTick(char state){
    unsigned char A0 = ( PINA & 0x01 );
    unsigned char A1 = ( PINA & 0x02 );
    static unsigned char cnt = 7;   
     
    switch (state){ //transitions
    
    case init:
	state = releasedWait;
	break;
    
    case releasedWait:
	if( A0 && A1 ){
	    state = reset;	
	}
	else if ( A0 && !A1 ){
	    state = inc;
	} 
	else if ( !A0 && A1 ){
	    state = dec;
	}	
	else {
	    state = releasedWait;
	}
	break;

    case pressedWait:
	if ( !A0 && !A1 ){
	    state = releasedWait;
	}
	else if ( A0 && A1 ){
	    state = reset;
	}
	else{
	    state = pressedWait;
	}
	break;

    case inc:
	state = pressedWait; 
   	break;
    
    case dec:
	state = pressedWait;
	break;

    case reset:
	state = pressedWait;
	break;

    default:
	state = releasedWait;
	break; 
    }

    switch(state){ //actions

    case init:
	cnt = 7;
	break;
   
    case releasedWait:
	break;
 
    case pressedWait:
	break;

    case inc:
	if ( cnt < 9 ){
	    cnt++;
	}
	break;

    case dec:
	if( cnt > 0 ){
	    cnt--;
	}
	break;

    case reset:
	cnt = 0;
	break;

    default:
	break; 
    }

    PORTC = cnt;
    
    return state;

}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
    States state = init;
    while (1) {
	state = CountTick(state);
    }
    return 1;
}
