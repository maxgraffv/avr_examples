#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile int timer0Counter = 0;

ISR(TIMER0_COMPA_vect)
{
	timer0Counter++;
	if(timer0Counter >= 100)
	{
		PORTD ^= (1 << PORTD6);
		timer0Counter = 0;
	}
}



int main()
{

	DDRD |= (1 << PORTD6);	

	TCCR0A |= (1 << WGM01); //CTC mode
	OCR0A = 78; // Compare match value
	TIMSK0 |= (1 << OCIE0A); // Enable Timer0 compare match interrupt
	TCCR0B |= (1 << CS02) | (1 << CS00); //Prescaler set 1024

	sei();

	while(1)
	{


	}

}

