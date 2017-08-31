
#include "Main.h"
char str[10];
void Port_ini(void)
{
	PORTD=0x00;
	DDRD=0xFF;
}

void SPI_ini_SK(void)
{
	DDRB|=(1<<PORTB4);//ножки какие будут на выход!!!
	DDRB&=~((1<<PORTB2)|(1<<PORTB3)|(1<<PORTB5));//ножки SPI-на вход
	SPCR=((1<<SPE)|(1<<SPIE));//включаем шину ,включим прерывания
}
ISR(SPI_STC_vect)//прерывание SPIприем байта
{
	
	unsigned char n;
	n=SPDR;
	lcd_clear();
	lcd_gotoxy(0,0);
	itoa(n,str,10);
	lcd_print(str);
}

int main(void)
{
	
	Port_ini();
	LCD_ini();
	SPI_ini_SK();
	sei();
	lcd_clear();
	lcd_gotoxy(0,0);
// 	lcd_print("ATTiny2313");
// 	lcd_gotoxy(0,1);
// 	lcd_print("ATMega 8A");
	/* Replace with your application code */
	while (1)
	{
		
	}
}

