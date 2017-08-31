
#include "LCD_lib.h"
//--------------------------------------------
void sendhalfbyte(unsigned char c)

{
	
	c<<=4;
	e1;
	_delay_us(50);
	PORTD&=0b00001111;//стирание информации на входах
	PORTD|=c;
	e0;
	_delay_us(50);
	
	
	
}
//---------------------------------------------
void sendbyte(unsigned char c,unsigned char mode)

{
	if (mode==0)
	{
		rs0;
	}else

	{
		rs1;
	}
	unsigned char hc=0;
	
	hc=c>>4;
	sendhalfbyte(hc);
	sendhalfbyte(c);
	
	
}


//----------------------------------------------

void sendchar(unsigned char c)

{
	sendbyte(c,1);
}



//-------------------------------------------

void lcd_gotoxy(unsigned char x, unsigned char y)
{
	switch(y)
	{
		case 0:
		sendbyte(x|0x80,0);
		break;
		
		case 1:
		sendbyte((0x40+x)|0x80,0);
		break;
		
		case 2:
		sendbyte((0x14+x)|0x80,0);
		break;
		
		case 3:
		sendbyte((0x54+x)|0x80,0);
		break;
	}
}
//---------------------------------------
void lcd_clear()
{
	sendbyte(0b00000001,0);
	_delay_us(1500);
}


//--------------------------------------
void lcd_print(char str1[])
{
	wchar_t n;
	for (n=0;str1[n]!='\0';n++)
	{
		sendchar(str1[n]);
	}
}
//____________________________________________

void LCD_ini(void)
{
	
	_delay_ms(15);//ждем 15 милисекунд
	sendhalfbyte(0b00000011);
	_delay_ms(4);
	sendhalfbyte(0b00000011);
	_delay_us(100);
	sendhalfbyte(0b00000011);
	_delay_ms(1);
	sendhalfbyte(0b00000010);
	_delay_ms(1);
	sendbyte(0b00101000,0);//включаем 4-бытный режим,используем две линии
	_delay_ms(1);
	sendbyte(0b00001100,0);//включаем отображение на дисплее(D=1)курсоры не включены
	_delay_ms(1);
	sendbyte(0b00000110,0);//выставляем курсор двигаться слева на право
	
	
}
//--------------------------------------
void lcd_print_80(char str1[])
{
	unsigned char  n;
	
	sendbyte(0x80,0);//первая строка
	for (n=0;n<=19;n++)
	{
		sendchar(str1[n]);
	}
	
	for (n=40;n<=59;n++)//на 3ю строку перейдет автоматически
	{
		sendchar(str1[n]);
	}
	sendbyte((0xC0|0x80),0);//вторая строка
	for (n=20;n<=39;n++)
	{
		sendchar(str1[n]);
	}
	
	for (n=60;n<=79;n++)
	{
		sendchar(str1[n]);
	}
}
//____________________________________________
