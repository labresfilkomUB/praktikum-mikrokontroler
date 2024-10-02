#include <avr/io.h> 
#include <avr/interrupt.h> 

int main(void) 
{ 
    // Set Port C sebagai output 
    DDRC=0xFF; 
    
    PORTC=0x00; 

    // Aktifkan Timer 1 sebagai sumber interupsi 
    TCCR1B=0x02; // 0b00000010

    // Nilai Counter Pembanding Timer 1B 
    TCNT1H=0x00; // TCNT1
    TCNT1L=0x0F; // = 0x000F = 15
    OCR1BH=0x0F; // OCR1B
    OCR1BL=0x00; // = 0x0F00 = 3840

    // Register Output Compare Flag di Timer 1B akan di clear setelah  interupsi dilaksanakan 
    TIFR= 0x08; 

    // Mengaktifkan Output Compare Interrupt di Timer 1B 
    TIMSK=0x08; // 0b00001000

    // Global enable interrupts 
    sei();

    while (1) 
    { 
    } 

}

// Timer 1 Output Comparator interrupt service routine 
ISR (TIMER1_COMPB_vect) { 
    // Inisialisasi kembali Nilai Counter Pembanding Timer 1B 
    TCNT1H=0x00; 
    TCNT1L=0x0F; 
    OCR1BH=0x0F; 
    OCR1BL=0x00; 

    // Cek PINC 
    if (PINC == 0) 
        {PORTC = 0xFF;} 
    else 
        {PORTC = 0x00;} 
}

