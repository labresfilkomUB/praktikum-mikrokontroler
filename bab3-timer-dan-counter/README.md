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

## Contoh Pengaturan Timer

### 1. Mencari durasi untuk 1 tick

$$
\begin{aligned}
f_{clk_{I/O}}&=\text{1 MHz} = 1.000.000 \text{ tick/detik}\\
\text{Periode (durasi 1 tick)}&= 0,000001 \text{ detik}\\
\end{aligned}
$$

Durasi tentunya **sangat ditentukan oleh prescaler** yang dipilih.

Misalkan prescaler terpilih adalah $clk_{I/O}/64$. Counter akan melakukan 1 tick *count* setiap $clk_{I/O}$ melakukan tick sebanyak 64 kali, maka:

$$
\begin{aligned}
\text{Durasi pertick}&= 64 \times 0,000001\\
&= 0,000064 \text{ detik}
\end{aligned}
$$

### 2. Memeriksa batas durasi maksimal (langkah opsional)
Batas maksimal yang dimaksud adalah durasi Timer/Counter dalam melakukan *count* dari BOTTOM hingga MAX (sehingga kemudian kembali mencacah dari BOTTOM).

Jika Timer/Counter berukuran 8 bit (seperti Timer/Counter0 dan Timer/Counter2), total tick dari BOTTOM hingga MAX hingga kemudian kembali lagi dari BOTTOM adalah $2^8=256$.

$$
\begin{aligned}
\text{Durasi maksimal}&=256 \times 0,000064\\
&\approx 0,0164 \text{ detik}\\
\text{(overflow sekitar 60}&\text{ kali dalam 1 detik)}
\end{aligned}
$$

Jika Timer/Counter berukuran 16 bit (seperti Timer/Counter1), total tick dari BOTTOM hingga MAX hingga kemudian kembali lagi dari BOTTOM adalah $2^{16}=65.536$.

$$
\begin{aligned}
\text{Durasi maksimal}&=65536 \times 0,000064\\
&\approx 4,194 \text{ detik}
\end{aligned}
$$

### 3. Mencari Jumlah Tick yang Diperlukan
Contoh: Mengatur timer untuk memicu dalam durasi 3 detik

$$
\begin{aligned}
\text{Jumlah tick diperlukan}&= \frac{3}{0,000064}\\
&= 46.875 \text{ tick}
\end{aligned}
$$

Jumlah tick sebanyak 46.875 dapat digunakan langsung pada Timer/Counter1 karena memiliki pencacahan maksimal sebanyak 65.536. Sedangkan pada Timer/Counter0 dan Timer/Counter2 tidak.

### 4. Menentukan Nilai Inisialisasi `TCNTn` dan `OCRn`
#### A. Menggunakan pemicuan Overflow
Pemicuan overflow hanya bergantung pada *count* yang dilakukan oleh `TCNTn`. Yaitu saat `TCNTn` mengalami overflow (menembus nilai MAX), hasil dari komparator akan mengatur flag interupsi untuk bernilai `1`.

Karena itu, yang dapat diatur adalah inisialisasi nilai `TCNTn` saja.

Nilai MAX pada Timer/Counter1 adalah 65.535.

$$
\begin{aligned}
\text{Nilai awal pencacahan }&= 65.535 + 1 - 46.875\\
&= 18.661
\end{aligned}
$$

Contoh kode untuk inisialisasi nilai awal pencacahan:

`TCNT1 = 18661;`<br>atau<br>
`TCNT1 = 0b0100100011100101;`<br>atau<br>
`TCNT1 = 0x48E5;`
<br>atau
```cpp
TCNT1H = 0x48;  // 0b01001000
TCNT1L = 0xE5;  // 0b11100101
```
Catatan: Untuk membuat timer memicu selama 3 detik secara terus menerus, pastikan perncacahan dimulai kembali dari 18.661. Lakukan assignment nilai 18.661 lagi pada `TCNTn` di dalam kode program interupsi, atau di dalam `main()` seperti berikut.
```cpp
if(TCNT1 == 0)
    TCNT1 = 18661;
```
Pemilihan cara assignment kembali nilai `TCNTn` disesuaikan dengan kebutuhan.

#### B. Menggunakan Pemicuan Compare Match

Pemicuan compare match didasari oleh kecocokan antara nilai `TCNTn` (yang terus-menerus melakukan *count*) saat ini dengan nilai `OCRn`. Karena itu, pengaturan dapat dilakukan pada `TCNTn` dan juga `OCRn` dengan cara membuat selisih antara keduanya adalah 18.661.

Skenario 1: Tidak mengatur nilai awal pencacahan

Nilai awal `TCNTn` secara default adalah 0. Oleh karena itu, nilai `OCRn` yang sesuai adalah 46.875 itu sendiri (46.875 - 0).

Skenario 2: Ingin mengatur nilai awal pencacahan

Misal nilai awal pencacahan menjadi 10000. Maka nilai `OCRn` adalah

$$
\begin{aligned}
46.875 &= OCRn - \text{nilai-awal-pencacahan}\\
OCRn &= 46.875 + 10.000\\
&= 56.875
\end{aligned}
$$

Contoh kode untuk inisialisasi (menggunakan compare match A):
```cpp
TCNT1 = 10000;
OCR1A = 56875;
```
atau
```cpp
TCNT1H = 0x27;
TCNT1L = 0x10;
OCR1AH = 0xDE;
OCR1AL = 0x2B;
```


#### **Catatan**
Pada penggunaan pemicuan compare match skenario 2 dan skenario 3, pastikan untuk mengatur kembali nilai awal pencacahan di dalam program interupsi ataupun di dalam `main()` seperti pada penggunaan pemicuan overflow.
