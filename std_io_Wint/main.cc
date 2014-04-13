/*
 *	Basic I/O with a timer and interrupts
 *
 *	by: Andrew Radlbeck
 *	F_CPU 1200000
 */
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/* macros for bit-setting */
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
bool had_int   = false;

void init(void)
{
	DDRB   = (1 << P_RELAY);	// default input, set output
	GIMSK |= (1 << INT0);		// enable interrupts
	MCUCR |= (1 << ISC00);		// trigger on all edges
	sei();				// start interrupts
}

/* lets us know the current lid position */
void set_flags(void)
{
	lid_down = (RSW)? true : false;
}

/* this function handles when the relay is on 
 * it allows it to be interrupted at any time */
void set_light(void)
{
	if(lid_down && !light_ran){
		RELAY(1);
		for(int j = 0; j < 10; j++){		// 10 second interruptible delay
			for(int i = 0; i < 1000; i++){
				if(had_int){
					had_int = false;
				       	return;
				}
				_delay_ms(1);
			}
		}
		light_ran = true;
		had_int = false;
		RELAY(0);
	}
	return;
}

int main(void)
{
	init();
	set_flags();
	
	while(1){
		set_light();
		if(!lid_down){			// reset all flags when the lid gets lifted
			RELAY(0);
			light_ran = false;
		}
	}
}

ISR (INT0_vect)
{
	set_flags();
	had_int = true;		// residual interrupt flag
	if(!RSW) RELAY(0);	// safety check
	_delay_ms(1);
}
