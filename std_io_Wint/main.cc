/*
 *	Basic I/O with a timer and inturrpts
 *
 *	by: Radlbeck
 *	F_CPU 1200000
 */
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/* macros for bitsetting */
#define SETBIT(ADDRESS,BIT)   (ADDRESS |= (1<<BIT))
#define CLEARBIT(ADDRESS,BIT) (ADDRESS &= ~(1<<BIT))
#define FLIPBIT(ADDRESS,BIT)  (ADDRESS ^= (1<<BIT))
#define CHECKBIT(ADDRESS,BIT) (ADDRESS & (1<<BIT))

/* pin definitions */ 
#define P_RSW   PB2
#define P_RELAY PB3

/* macros for pin setting */
#define RELAY(x) (x)? SETBIT(PORTB, P_RELAY) : CLEARBIT(PORTB, P_RELAY);
#define RSW !CHECKBIT(PINB, P_RSW)

/* flags */
bool lid_down  = false;
bool light_ran = false;

void init(void)
{
	DDRB   = (1 << P_RELAY);	// defualt input, set output
	GIMSK |= (1 << INT0);		// enable inturrupts
	MCUCR |= (1 << ISC00);		// trigger on all edges
	sei();				// start inturrupts
}

void set_flags(void)
{
	lid_down = (RSW)? true : false;
}

int main(void)
{
	init();
	set_flags();
	
	while(1){
		if(lid_down){
			RELAY(1);
		}else{
			RELAY(0);
		}
/*		if(lid_down && !light_ran){
			RELAY(1);
			for(int i = 0; i < 10; i++) _delay_ms(1000);
			light_ran = true;
		}
		RELAY(0);*/
	}
}

ISR (INT0_vect)
{
	set_flags();
/*	if(!RSW){	// saftey check
		RELAY(0);
	}	*/
	_delay_ms(1);
}
