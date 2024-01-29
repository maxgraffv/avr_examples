#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t debounceFlag
ISR(INT0_vect)
{
	if (debounceFlag == 0)
	{
		debounceFlag = 1;
		PORTB ^= (1<<PORTB2);
	}
}

int main()
{
	DDRB |= (1 << PORTB2);

	EICRA |= (1 << ISC01);
	EIMSK |= (1 << INT0);

	sei();

	while(1)
	{
		if(debounceFlag)
		{
			_delay_ms(150);
			debounceFlag = 0;
		}
	}
}



