#include "main.h"
//----------------------------------------
unsigned char x=0,y=0;
//----------------------------------------
void port_ini(void)
{
	PORTD=0x00;
	DDRD=0xFF;
}
//----------------------------------------
ISR(USART_RXC_vect)
{
	int b;
	b = UDR;
	setpos(x,y);
	sendchar(b);
	if(x<15) x++;
	else
	{
		x=0;
		if(y==0)	y=1;
		else if(y==1)	{y=0;clearlcd();}
	}
}
//----------------------------------------
int main(void)
{
	port_ini(); //Инициализируем порты
	LCD_ini();  //Инициализируем дисплей
	USART_Init (34); //28800
	sei();
	USART_Transmit('O');//Передаем при включении
	USART_Transmit('k');//сообщение "Ok!", что свидетельствует
	USART_Transmit('!');//о правильно работе программы
	USART_Transmit(0x0d);//переход в начало строки
	USART_Transmit(0x0a);//переход на новую строку
	clearlcd();
	while(1)
	{
	}
}