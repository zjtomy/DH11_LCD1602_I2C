#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>
#include "I2C_m.h"
#include "sensors.h"


void DH11_init(void)
{
  _delay_ms(2000);
  TCCR0B = 0x02;	// enable timer0 clkT2S/8
}


void DH11_read(uint8_t *bits_timing)
{
	uint8_t i,TMR_TEMP=0,DECODE_TEMP=0;int8_t j;
	DDRB = 0xFF;		// Pin0 output
	PORTB &= ~(1<<PB0);
	_delay_ms(18);
	PORTB |= (1<<PB0);
	DDRB = 0xFE;
	
	while((PINB & (1<<PINB0)));
	while(!(PINB & (1<<PINB0)));
	while((PINB & (1<<PINB0)));
	
	for (i=0;i<5;i++)
    {
		for (j=7;j>=0;j--)
		{
			while(!(PINB & (1<<PINB0)));                // wait for 0 leading bit
			TCNT0=0;
			while(PINB & (1<<PINB0));                   // high bit 0 or 1 
			TMR_TEMP = TMR0_MSK;
			if (TMR_TEMP < 35 && TMR_TEMP > 20)
				DECODE_TEMP &= ~(1<<(j));
			else
				DECODE_TEMP |= (1<<(j));
		}
		bits_timing[i] = DECODE_TEMP;
    }
}