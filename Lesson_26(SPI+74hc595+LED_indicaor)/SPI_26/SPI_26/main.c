/*
 * SPI_26.c
 *
 * Created: 29.08.2016 19:27:10
 * Author : DANTE_L_LEVI
 */ 


#include "Main.h"


int main(void)
{
	
	//int i=0;
	
	DDRB|=(1<<PORTB2)|(1<<PORTB3)|(1<<PORTB5);
	PORTB&=~((1<<PORTB2)|(1<<PORTB3)|(1<<PORTB5));
	SPCR=((1<<SPE)|(1<<MSTR));// включаем шину , объ€вим ведущим
	
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
		
		// отобразим 1
		
			SPDR=0b11111001;
			while(!(SPSR&(1<<SPIF)));//подождем пока данные передадутс€
			//сгенерируем отрицательный фронт дл€ записи в STORAGE REGISTER
			PORTB|=(1<<PORTB2);
			PORTB&=~((1<<PORTB2));
			_delay_ms(1000);
		
		
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++
		
		
			//SPDR=0b11111001;
			// отобразим 2
			SPDR=0b10100100;
			while(!(SPSR&(1<<SPIF)));//подождем пока данные передадутс€
			//сгенерируем отрицательный фронт дл€ записи в STORAGE REGISTER
			PORTB|=(1<<PORTB2);
			PORTB&=~((1<<PORTB2));
			_delay_ms(1000); 
			
			// отобразим 3
			SPDR=0b10110000;
			while(!(SPSR&(1<<SPIF)));//подождем пока данные передадутс€
			//сгенерируем отрицательный фронт дл€ записи в STORAGE REGISTER
			PORTB|=(1<<PORTB2);
			PORTB&=~((1<<PORTB2));
			_delay_ms(1000);
			
			// отобразим 4
			SPDR=0b10011001;
			while(!(SPSR&(1<<SPIF)));//подождем пока данные передадутс€
			//сгенерируем отрицательный фронт дл€ записи в STORAGE REGISTER
			PORTB|=(1<<PORTB2);
			PORTB&=~((1<<PORTB2));
			_delay_ms(1000);
			
			// отобразим 5
			SPDR=0b10010010;
			while(!(SPSR&(1<<SPIF)));//подождем пока данные передадутс€
			//сгенерируем отрицательный фронт дл€ записи в STORAGE REGISTER
			PORTB|=(1<<PORTB2);
			PORTB&=~((1<<PORTB2));
			_delay_ms(1000);
			
			// отобразим 6 
			SPDR=0b10000010;
			while(!(SPSR&(1<<SPIF)));//подождем пока данные передадутс€
			//сгенерируем отрицательный фронт дл€ записи в STORAGE REGISTER
			PORTB|=(1<<PORTB2);
			PORTB&=~((1<<PORTB2));
			_delay_ms(1000);
			
			// отобразим 7
			SPDR=0b11111000;
			while(!(SPSR&(1<<SPIF)));//подождем пока данные передадутс€
			//сгенерируем отрицательный фронт дл€ записи в STORAGE REGISTER
			PORTB|=(1<<PORTB2);
			PORTB&=~((1<<PORTB2));
			_delay_ms(1000);
			
			// отобразим 8
			SPDR=0b10000000;
			while(!(SPSR&(1<<SPIF)));//подождем пока данные передадутс€
			//сгенерируем отрицательный фронт дл€ записи в STORAGE REGISTER
			PORTB|=(1<<PORTB2);
			PORTB&=~((1<<PORTB2));
			_delay_ms(1000);
			
			// отобразим 9
			SPDR=0b10010000;
			while(!(SPSR&(1<<SPIF)));//подождем пока данные передадутс€
			//сгенерируем отрицательный фронт дл€ записи в STORAGE REGISTER
			PORTB|=(1<<PORTB2);
			PORTB&=~((1<<PORTB2));
			_delay_ms(1000);
			
			// отобразим 0	
			SPDR=0b11000000;	
			while(!(SPSR&(1<<SPIF)));//подождем пока данные передадутс€
			//сгенерируем отрицательный фронт дл€ записи в STORAGE REGISTER
			PORTB|=(1<<PORTB2);
			PORTB&=~((1<<PORTB2));
			_delay_ms(1000);		

			
		
		
	}
}
