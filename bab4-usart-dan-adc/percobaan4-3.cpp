#include <avr/io.h>

int adc_read_and_convert()
{
	ADCSRA |= 1<<ADSC;
	while((ADCSRA & 1<<ADSC) != 0);
	return ADC;
}

int main(void)
{
	DDRA = 0x00;
	PORTA = 0x00;

	DDRB = 0xFF;
	PORTB = 0xFF;

	ADMUX |= 1<<REFS0;
	ADMUX &= ~(1<<REFS1);
	ADCSRA |= 1<<ADEN | 1<<ADPS2 | 1<<ADPS1;
	
	while (1)
	{
		PORTB = ~adc_read_and_convert();
	}
}