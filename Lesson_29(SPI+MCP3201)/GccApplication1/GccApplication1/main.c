#include "main.h"

void port_ini(void)
{
	PORTD=0x00;
	DDRD=0xFF;
}
//----------------------------------------
void SPI_init(void)
{
	DDRB |= ((1<<PORTB2)|(1<<PORTB3)|(1<<PORTB5)); //ножки SPI на выход
	PORTB &= ~((1<<PORTB2)|(1<<PORTB3)|(1<<PORTB5)); //низкий уровень
	SPCR = ((1<<SPE)|(1<<MSTR)|(1<<SPR0));//включим шину, объ§вим ведущим
}

void SPI_SendByte (char byte)
{
	SPDR = byte;
	while(!(SPSR & (1<<SPIF)));//подождем пока данные передадутс€
}

unsigned char SPI_ChangeByte (char byte)
{
	SPDR = byte;
	while(!(SPSR & (1<<SPIF)));//подождем пока данные передадутс€ (обмен€ютс€)
	return SPDR;
}

unsigned int Read_3201 (void)
{
	unsigned int b1,b2;
	PORTB &= ~(1<<PORTB2); //низкий уровень
	b1=SPI_ChangeByte(0);//первый байт
	b2=SPI_ChangeByte(0);//второй байт
	b1=(b1<<8)|b2;//собираем два байта в двухбайтовую величину
	b1<<=3;//убираем ненужные биты (3 слева и 1 справа
	b1>>=4;
	PORTB |= (1<<PORTB2); //высокий уровень
	return b1;
}

float Convert_3201 (unsigned int dt)
{
	//не забываем подключить плавающую точку -Wl,-u,vfprintf -lprintf_flt -lm
	float dt1;
	dt1=((float)dt*(4.96))/4096;
	return dt1;
}

int main(void)
{
	float dt=0;
	char str[10];
	port_ini(); //»нициализируем порты
	LCD_ini();  //»нициализируем дисплей
	lcd_clear();  //ќчистим дисплей
	SPI_init(); //»нициализируем SPI
	while(1)
	{
		lcd_gotoxy(0,0);
		dt=Convert_3201(Read_3201());
		sprintf(str,"%.2fv  ",dt);
		lcd_print(str);
		_delay_ms(500);
	}
}
