#include <avr/io.h> 
#include <avr/interrupt.h> 

int main(void) 
{ 

    // Set Port C sebagai output 
    DDRC=0xFF; 

    PORTC=0x00; 

    // Aktifkan Timer 0 sebagai sumber interupsi 
    TCCR0=0x05; // 0b00000101

    // Timer Overflow Flag akan di clear setelah interupsi dilaksanakan 
    TIFR= 0x01; 

    // Mengaktifkan Timer Overflow di Timer 0 
    TIMSK=0x01; 

    // Global enable interrupts
    sei();

    while (1) 
    {
    } 

}

// Timer 0 overflow interrupt service routine 
ISR (TIMER0_OVF_vect) { 

    // Cek PINC 
    if (PINC == 0) 
        {PORTC=0xFF;} 
    else
        {PORTC=0x00;} 
}

