#define F_CPU 1000000UL
#include <avr/io.h>

#define BAUD 4800
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1)

unsigned char usart_receive()
{
    while((UCSRA & 1<<RXC) == 0);
    return UDR;
}

int main(void)
{
    unsigned char received;

    DDRB = 0xFF;
    PORTB = 0xFF;

    UBRRH = BAUDRATE>>8;
    UBRRL = BAUDRATE;
    
    UCSRB |= 1<<RXEN;
    UCSRC |= 1<<URSEL | 1<<UCSZ1 | 1<<UCSZ0;

    while (1)
    {
        received = usart_receive();

        PORTB = ~(received);
    }
}