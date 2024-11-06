#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#define LCD_Dir DDRB
#define LCD_Port PORTB
#define RS PB0
#define EN PB1

void LCD_Command( unsigned char cmnd )
{
	LCD_Port = (LCD_Port & 0x0F) | (cmnd & 0xF0);
	LCD_Port &= ~ (1<<RS);
	LCD_Port |= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);
	_delay_us(200);
	LCD_Port = (LCD_Port & 0x0F) | (cmnd << 4);
	LCD_Port |= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);
	_delay_ms(2);
}

void LCD_Char( unsigned char data )
{
	LCD_Port = (LCD_Port & 0x0F) | (data & 0xF0);
	LCD_Port |= (1<<RS);
	LCD_Port|= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);
	_delay_us(200);
	LCD_Port = (LCD_Port & 0x0F) | (data << 4);
	LCD_Port |= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);
	_delay_ms(2);
}

void LCD_Init (void)
{
	LCD_Dir = 0xFF;
	_delay_ms(20);
	LCD_Command(0x02); //return home mengembalikan ke tampilan bagian awal
	LCD_Command(0x28); //2 baris, 5x8 Matriks, mode 4bit
	LCD_Command(0x0c); //Menyalakan display, Cursor mati
	LCD_Command(0x06); //Geser kursor ke kanan
	LCD_Command(0x01); //clrscreen (bersihin layar)
	_delay_ms(2);
}

void LCD_String (char *str)
{
	int i;
	for(i=0;str[i]!=0;i++)
	{
	LCD_Char (str[i]);
	}
}

void LCD_String_xy (char row, char pos, char *str)
{
	if (row == 0 && pos<8)
	LCD_Command((pos & 0x0F)|0x80);
	else if (row == 1 && pos<8)
	LCD_Command((pos & 0x0F)|0xC0);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
	LCD_String(str);
}

void LCD_Clear() {
	LCD_Command (0x01);
	_delay_ms(2);
	LCD_Command (0x80); //Meletakkan kursor di baris pertama 
}

int main()
{
	LCD_Init();
	LCD_String("Sismik");
	LCD_Command(0xC0); //Meletakkan kursor di baris kedua
	LCD_String("Prak");
	_delay_ms(2000);
	LCD_Clear();
	char A[8]="BAB";
	char B[8]="LCD";
	LCD_String_xy(0,1,A);
	LCD_String_xy(1,4,B);
	while(1);
}

