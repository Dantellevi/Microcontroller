/*
 * LEss0n_10.c
 *
 * Created: 09.08.2016 13:50:58
 * Author : Dante_L_Levi
 */ 
#define F_CPU 8000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


unsigned char i=0;

void Setting()
{
	DDRB=0xFF;
	DDRB=0b11111110;
	PORTB|=(1<<(PORTB0));
	PORTD=0x00;
}

void SET(unsigned char i)
{
	switch(i)
	{
		case 0:{PORTD=0b00111111;break;}
		case 1:{PORTD=0b00000110;break;}
		case 2:{PORTD=0b01011011;break;}
		case 3:{PORTD=0b01001111;break;}
		case 4:{PORTD=0b01100110;break;}
		case 5:{PORTD=0b01101101;break;}
		case 6:{PORTD=0b01111101;break;}
		case 7:{PORTD=0b00000111;break;}
		case 8:{PORTD=0b01111111;break;}
		case 9:{PORTD=0b01101111;break;}
		
		
	}
}

void timer_ini(void)
{
	TCCR1B|=(1<<(WGM12));//устанавливаем режи СТС
	TIMSK|=(1<<(OCIE1A));//устанавливает бит разрешения прерывания 1-ого стчетчика по совпадению OCR1A
	OCR1AH=0b01111010;//число для сравнения
	OCR1AL=0b00010010;
	TCCR1B|=(1<<CS12);//устанавливаем делитель
	
	
	
}

ISR(TIMER1_COMPA_vect)
{
	if (i>9)
	{
		i=0;
	}
SET(i);
i++;


}

int main(void)
{
	
	Setting();
	timer_ini();
	/* Replace with your application code */
	sei();
	while (1)
	{
		
		
		
		

}
}


