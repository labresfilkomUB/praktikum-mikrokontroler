#include <avr/io.h> 
#include <util/delay.h>
#include <avr/interrupt.h> 

int main(void) 
{  
    // Set Port C sebagai output 
    DDRC=0xFF; 
    
    PORTC=0x00; 

    // Set Port B sebagai input (T0 ada di PB0) 
    DDRB=0x00; 
    PORTB=0xFF; 

    // Aktifkan Timer 0 sebagai sumber interupsi dengan trigger eksternal
    TCCR0=0x06; // 0b00000110

    TCNT0=0x00; 
    OCR0=0x0A;

    // Register Output Compare Flag di Timer 0 akan di clear setelah  interupsi dilaksanakan 
    TIFR= 0x02; 

    // Mengaktifkan Output Compare Interrupt di Timer 0
    TIMSK=0x02;

    // Global enable interrupts 
    sei();

    while (1) 
    { 
            PORTC = ~TCNT0;
    } 
}

// Timer 0 Output Comparator interrupt service routine 
ISR (TIMER0_COMP_vect) { 
    // Inisialisasi kembali Nilai Counter Pembanding Timer 0 
    TCNT0 = 0x00; 
    OCR0 = 0x0A; 

    for (int i = 0; i < 3; i++) {
        PORTC = 0xFF;
        _delay_ms(500);
        PORTC = 0x0F;
        _delay_ms(500);
    }
}