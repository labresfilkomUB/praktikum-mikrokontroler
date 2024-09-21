#include <avr/io.h>

int main(void)
{
    DDRC = 0x00;
    PORTC = 0xFF;
    DDRB = 0xFF;
    while (1)
    {
        if (PINC == 0b11111110)
        {
            PORTB = 0b00000000;
        }
        else if (PINC == 0b11111101)
        {
            PORTB = 0b11111111;
        }
    }
}