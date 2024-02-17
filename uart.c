#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BAUDRATE 9600
#define UBRR (F_CPU / 16 /BAUDRATE) - 1

char recv_char()
{
	while(!(UCSR0A & (1 << RXC0)));
	return UDR0;
}

void send_char(char data)
{
	while(!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

ISR(USART_RX_vect)
{
	if(recv_char() == 'p')
	{
		PORTB ^= (1 << PORTB0);
		send_char('K');
	}
}

int main(void)
{
	//LED
	DDRB |= (1 << PORTB0);
	PORTB &= ~(1 << PORTB0);

	DDRD |= (1 << PORTD1); //TX output

	

	UBRR0H = UBRR << 8;
	UBRR0L = UBRR;
	
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
	
	sei();

	while(1)
	{
		
	}

	return 0;
}



