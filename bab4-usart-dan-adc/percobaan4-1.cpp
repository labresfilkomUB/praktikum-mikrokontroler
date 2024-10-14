#include <avr/io.h>

#define F_CPU 1000000UL
#define BAUD 4800
#define VALUE_UBRR (F_CPU/(BAUD*16UL)-1)

void usart_transmit (unsigned char data)
{
	while ((UCSRA & (1<<UDRE)) == 0);
	UDR = data;
}

unsigned char usart_receive (void)
{
	while((UCSRA & (1<<RXC)) == 0);
	return UDR;
}

int main (void)
{
	UBRRH = (VALUE_UBRR >> 8);
	UBRRL = VALUE_UBRR;
	UCSRB |= (1<<TXEN) | (1<<RXEN);
	UCSRC |= (1<<URSEL) | (1<<UCSZ0) | (1<<UCSZ1);
	
	unsigned char myData;

	while(1)
	{
		if ((UCSRA & (1 << RXC)) != 0)
		{
			myData = usart_receive();
			usart_transmit(myData);
		}
	}

	return 0;
}
