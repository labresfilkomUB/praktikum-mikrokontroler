#include <avr/io.h> 

int main(void) 
{
	DDRA = 0x00; 
	PORTA = 0x00; 
	DDRB = 0xFF;  
	PORTB = 0xFF; 
	
	ADMUX |= (0<<REFS1) | (1<<REFS0); 
	ADCSRA |= (1<<ADEN) | (1<<ADPS0) | (1<<ADPS1);
	
	while (1) 
	{ 
		ADCSRA |= (1<<ADSC); 
		while ((ADCSRA & (1<<ADSC)) != 0); 

		PORTB = ~ADC; 
	} 

    return 0;
}
