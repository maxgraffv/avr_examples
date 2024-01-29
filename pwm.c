#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile int pwmValue = 0;

ISR(TIMER2_OVF_vect)
{
	OCR2B = pwmValue;
	pwmValue += 2;
	
	if(pwmValue > 255)
		pwmValue = 0;
}

int main()
{
	DDRD |= (1 << PORTD3);

	TCCR2A |= (1 << COM2B1) | (1 << WGM20) | (1 << WGM21);
	TIMSK2 |= (1 << TOIE2);
	OCR2B = pwmValue;
	TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20); //Prescaler set 1024

	sei();

	while(1){}

}
