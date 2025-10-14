#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

#define BAUD 4800
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1)

void usart_transmit(char ch)
{
    while((UCSRA & 1<<UDRE) == 0);
    UDR = ch;
}

int log2n(int n)
{
    if(n <= 1) return 0;
    else return 1 + log2n(n/2);
}

int main(void)
{
    char to_transmit;

    DDRD = 0x00;
    PORTD = 0xFF;

    UBRRH = BAUDRATE>>8;
    UBRRL = BAUDRATE;

    UCSRB |= 1<<TXEN;
    UCSRC |= 1<<URSEL | 1<<UCSZ1 | 1<<UCSZ0;

    while (1)
    {
        if(PIND != 0b11111111)
        {
            to_transmit = ~PIND;
            
            usart_transmit('0' + log2n(to_transmit));
        }
        
        _delay_ms(100);
    }
}