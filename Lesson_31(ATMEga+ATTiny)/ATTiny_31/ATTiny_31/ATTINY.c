
#include "Main.h"

//__________________________________
void SPI_Init(void)
{
	DDRB|=((1<<PORTB4)|(1<<PORTB6)|(1<<PORTB7));//ножки USI на выход
	DDRB&=~((1<<PORTB5));//нока DI на вход
	PORTB&=~((1<<PORTB4)|(1<<PORTB6)|(1<<PORTB7));//ножки USI в низкий уровень
	
	
	
}


//++++++++++++++++++++++++++++++++++


char SPI_sendByte(char byte)
{
	USIDR=byte;//данные в регистр
	USISR|=(1<<USIOIF);//установим флаг начала передачи
	while(!(USISR&(1<<USIOIF)))
	{
		USICR|=((1<<USIWM0)|(1<<USICS1)|(1<<USICLK)|(1<<USITC));//постепенно передаем байт
		_delay_us(10);
		
	}
	return USIDR;

}

//+++++++++++++++++++++++

void Port_ini(void)
{
	PORTD=0x00;
	DDRD=0xFF;
}

int main(void)
{
	char str[10];
	unsigned char n=0,m=0;//переменная для случайного числа
	SPI_Init();
	Port_ini();
	LCD_ini();
	lcd_clear();
	lcd_gotoxy(0,0);
// 	lcd_print("ATTiny2313");
// 	_delay_ms(1000);
// 
// 	lcd_gotoxy(0,1);
// 	lcd_print("ATMega 8A");
// 	_delay_ms(1000);

	/* Replace with your application code */
	while (1)
	{
		lcd_clear();
		lcd_gotoxy(0,0);
		n=(unsigned char)rand()%256;
		m=SPI_sendByte(n);
		itoa(m,str,10);
		lcd_print(str);
		_delay_ms(1000);
	}
}