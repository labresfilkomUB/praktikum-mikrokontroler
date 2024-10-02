# BAB 3 - Timer dan Counter

## Langkah-Langkah Menggunakan Timer/Counter

A. Menetapkan clk<sub>Tn</sub> dengan `TCCRn`
> Timer/Counter0 &rarr; `TCCR0`<br>
> Timer/Counter1 &rarr; `TCCR1B`<br>
> Timer/Counter2 &rarr; `TCCR2`<br>

Penetapan clock menggunakan bit [2:0]

<br>

B. Meng-enable-kan pemicuan dengan `TIMSK`
> Bit-bit pada TIMSK:<br>
> `TOIEn`&emsp;: interupsi overflow pada counter (`TCNTn`)<br>
> `OCIEn`&emsp;: interupsi compare match antara `TCNTn` dengan `OCRn`<br>
> `TICIE1`&ensp;: interupsi capture event pada pin PD6

<br>

C. Mengisi Nilai `OCRn` dan `TCNTn` jika diperlukan
* `OCRn` tidak memberikan efek untuk pemicuan overflow
* `TCNTn` bernilai awal 0 pada Timer/Counter mode normal
* Assignment nilai tertentu ke `TCNTn` berarti mengupdate nilai yang menjadi titik awal pencacahan saat ini

<br>

D. Mengaktifkan I-bit pada `SREG`

Gunakan function `sei()`

<br>

E. Mendefinisikan ISR()
> Daftar inisial vektor interupsi untuk argumen pada ISR:
> * `TIMER0_OVF_vect` untuk Timer/Counter0 pemicuan overflow
> * `TIMER0_COMP_vect` untuk Timer/Counter0 pemicuan compare match
> * `TIMER1_OVF_vect` untuk Timer/Counter1 pemicuan overflow
> * `TIMER1_COMPA_vect` untuk Timer/Counter1 pemicuan compare match A
> * `TIMER1_COMPB_vect` untuk Timer/Counter1 pemicuan compare match B
> * `TIMER2_OVF_vect` untuk Timer/Counter2 pemicuan overflow
> * `TIMER2_COMP_vect` untuk Timer/Counter2 pemicuan compare match
