#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define LED PORTC
#define LEDDir DDRC

int main(void)
{
    LEDDir = 0xFF;
    LED = 0xFF;
    DDRD = 0x00;
    PORTD = 0xFF;

    GICR = 1<<INT1; // GICR = 1<<7; atau GICR = 0b10000000;
    MCUCR = 1<<ISC11 | 1<<ISC10;
    sei();

    while (1)
    {
        LED = 0b11111110; _delay_ms(1000);
        LED = 0b11111101; _delay_ms(1000);
        LED = 0b11111011; _delay_ms(1000);
        LED = 0b11110111; _delay_ms(1000);
        LED = 0b11101111; _delay_ms(1000);
        LED = 0b11011111; _delay_ms(1000);
        LED = 0b10111111; _delay_ms(1000);
        LED = 0b01111111; _delay_ms(1000);
    }
}

ISR(INT1_vect)
{
    int i = 0;
    for (i = 0; i < 2; i++)
    {
        LED = 0xFF; _delay_ms(1000);
        LED = 0xF0; _delay_ms(1000);
    }
}