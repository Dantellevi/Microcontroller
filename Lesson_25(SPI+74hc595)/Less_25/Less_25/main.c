/*
 * Less_25.c
 *
 * Created: 25.08.2016 21:59:48
 * Author : DANTE_L_LEVI
 */ 


#include "Main.h"

int main(void)
{
	
	int i=0;
	
	DDRB|=(1<<PORTB2)|(1<<PORTB3)|(1<<PORTB5);
	PORTB&=~((1<<PORTB2)|(1<<PORTB3)|(1<<PORTB5));
	SPCR=((1<<SPE)|(1<<MSTR));// включаем шину , объ€вим ведущим
	
	SPDR=0b00000000;
	
	while(!(SPSR&(1<<SPIF)));//подождем пока данные передадутс€
	//сгенерируем отрицательный фронт дл€ записи в STORAGE REGISTER
	PORTB|=(1<<PORTB2);
	PORTB&=~((1<<PORTB2));
	
	_delay_ms(2000);
	SPDR=0b11111111;
	PORTB|=(1<<PORTB2);
	PORTB&=~((1<<PORTB2));
	_delay_ms(2000);
    /* Replace with your application code */
    while (1) 
    {
		for(i=0;i<256;i++)
		{
			SPDR=i;
			while(!(SPSR&(1<<SPIF)));//подождем пока данные передадутс€
			//сгенерируем отрицательный фронт дл€ записи в STORAGE REGISTER
			PORTB|=(1<<PORTB2);
			PORTB&=~((1<<PORTB2));
			_delay_ms(50);
			
		}
		i=0;
		
    }
}

