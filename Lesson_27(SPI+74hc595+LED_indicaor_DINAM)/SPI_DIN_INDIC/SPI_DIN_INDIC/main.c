/*
 * SPI_DIN_INDIC.c
 *
 * Created: 30.08.2016 20:26:01
 * Author : DANTE_L_LEVI
 */ 


#include "Main.h"

void SPI_init(void)
{
	DDRB|=(1<<PORTB2)|(1<<PORTB3)|(1<<PORTB5);
	PORTB&=~((1<<PORTB2)|(1<<PORTB3)|(1<<PORTB5));
	SPCR=((1<<SPE)|(1<<MSTR));// включаем шину , объ€вим ведущим
	
}

int main(void)
{//int i=0;
	unsigned int i=0;
	
	SPI_init();
	timer_ini();
	sei();
	
	SPDR=0b00000000;
	
	while(!(SPSR&(1<<SPIF)));//подождем пока данные передадутс€
	SPDR=0b00000000;
	
	while(!(SPSR&(1<<SPIF)));//подождем пока данные передадутс€
	//сгенерируем отрицательный фронт дл€ записи в STORAGE REGISTER
	PORTB|=(1<<PORTB2);
	PORTB&=~((1<<PORTB2));
	
	_delay_ms(500);
	// 	SPDR=0b11111111;
	// 	PORTB|=(1<<PORTB2);
	// 	PORTB&=~((1<<PORTB2));
	// 	_delay_ms(2000);
	/* Replace with your application code */
	while (1)
	{
		
		for(i=0;i<10000;i++)
		{
			ledprint(i);
			_delay_ms(500);
			
		}

		
		_delay_ms(1000);
		
	}
}
