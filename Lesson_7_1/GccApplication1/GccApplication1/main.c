/*
 * GccApplication1.c
 *
 * Created: 08.08.2016 20:52:51
 * Author : Dante_L_Levi
 */ 
#define F_CPU 8000000L
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB=0x00;
	DDRD=0xFF;
	
	PORTB=0x00;
	PORTD=0x00;
    /* Replace with your application code */
    while (1) 
    {
		PORTD |=(1<<(PORTD0));
		_delay_ms(50);
		PORTD &=~(1<<(PORTD0));
		_delay_ms(50);
		if ((PINB&0b00000001))
		{
			PORTD |=(1<<(PORTD0));
			_delay_ms(200);
			PORTD &=~(1<<(PORTD0));
			_delay_ms(200);
 		} 
		
    }
}

