#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile int pwmValue = 0;
void setupADC()
{
	ADMUX |= (1 << REFS0); //using ADC0 so no bits to set;
	ADCSRA |= (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	DIDR0 = (1 << ADC0D);
	startADC();
}

void startADC()
{
	ADCSRA |= (1 << ADSC); //Start Conversion
}

ISR(ADC_vect)
{
	pwmValue = ADC;
	startADC();
}

int main()
{

	OCRA0 = pwmValue; //led brightnes on pwm pin

}
