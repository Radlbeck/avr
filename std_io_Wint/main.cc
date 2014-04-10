/*
 *	Basic I/O with a timer and inturrpts
 *
 *	by: Radlbeck
 *
 */
#include <avr/io.h>
#include <util/delay.h>

//#define F_CPU 1200000   	// define clock speed for delay reference

/* Macros For Bitsetting */
#define SETBIT(ADDRESS,BIT)   (ADDRESS |= (1<<BIT))
#define CLEARBIT(ADDRESS,BIT) (ADDRESS &= ~(1<<BIT))
#define FLIPBIT(ADDRESS,BIT)  (ADDRESS ^= (1<<BIT))
#define CHECKBIT(ADDRESS,BIT) (ADDRESS & (1<<BIT))

void init(void)
{
	DDRB = (0 << DDB2) | (1 << DDB3);		// PB2 - input; PB3 - output

//	_NOP();
}

int main(void)
{
	init();
	
	while(1){
		if(CHECKBIT(PORTB, PB2)) SETBIT(PORTB, PB3);
	}
}
