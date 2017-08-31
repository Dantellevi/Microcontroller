/*
 * Less_28.c
 *
 * Created: 31.08.2016 19:13:55
 * Author : DANTE_L_LEVI
 */ 

#include "Main.h"

char dg=8;

void SPI_init(void)
{
	DDRB|=(1<<PORTB2)|(1<<PORTB3)|(1<<PORTB5);
	PORTB&=~((1<<PORTB2)|(1<<PORTB3)|(1<<PORTB5));
	SPCR=((1<<SPE)|(1<<MSTR)|(1<<SPR0));// включаем шину , объ€вим ведущим
	
}


void SPI_Sendbyte(char byte)
{
	SPDR=byte;
	
	while(!(SPSR&(1<<SPIF)));//подождем пока данные передадутс€
	
}


void Send_7219(char rg,char dt)
{
	PORTB&=~(1<<PORTB2);
	SPI_Sendbyte(rg);
	SPI_Sendbyte(dt);
	PORTB|=(1<<PORTB2);
}

void clear_7219(void)
{
	char i=dg;
	
	do 
	{
		Send_7219(i,0xF);//пустой символ
	} while (--i);
}

void Number_7219(volatile long n)
{
	char ng=0;//переменна€ дл€ минуса
	
	if (n<0)
	{
		ng=1;
		n*=-1;
	}
	clear_7219();
	if (n==0)
	{
		Send_7219(0x01,0);//отправл€ем ноль в первый регистр
		return;  
	}
	char i;
	do 
	{
		Send_7219(++i,n%10);
		n/=10;
	} while (n);
	if (ng)
	{
		Send_7219(i+1,0xA);//символ -
	}
}


int main(void)
{//int i=0;
	unsigned int i=0;
	
	SPI_init();
	Send_7219(0x09,0xFF);//включаем режим декодировани€
	Send_7219(0x0B,dg-1);//количество используемых элементов
	Send_7219(0x0A,0x07);//€ркость диспле€
	Send_7219(0x0C,0x01);//включаем индикатор
	clear_7219();
	
		Send_7219(1,0x1);
		Send_7219(2,0x2);
		Send_7219(3,0x3);
		Send_7219(4,0x4);
		Send_7219(5,0x5);
		Send_7219(6,0x6);
		Send_7219(7,0x7);
		Send_7219(8,0x8);
	_delay_ms(1500);
	
	_delay_ms(500);
	Number_7219(-2016);
	
	while (1)
	{
		Number_7219(i);
		i++;
		_delay_ms(250);
	}
}

