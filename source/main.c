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

typedef enum States { init, wait, inc, dec, reset } States;

char CountTick(char state){
    unsigned char A0 = ( PINA & 0x01 );
    unsigned char A1 = ( PINA & 0x02 );
    static unsigned char cnt;   
     
    switch (state){ //transitions
    
    case init:
	state = wait;
	break;
    
    case wait:
	if( A0 && A1 ){
	    state = reset;	
	}
	else if ( A0 && !A1 ){
	    state = inc;
	} 
	else if ( !A0 && A1 ){
	    state = dec;
	}
	else if ( !A0 && !A1 ){
     	    state = wait;
	}
	else {
	    state = wait;
	}
	break;

    case inc:
	state = wait; 
   	break;
    
    case dec:
	state = wait;
	break;

    case reset:
	state = wait;
	break; 
    }

    switch(state){ //actions

    case init:
	cnt = 7;
	break;
    
    case wait:
	break;

    case inc:
	cnt++;
	break;

    case dec:
	cnt--;
	break;

    case reset:
	cnt = 0;
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
