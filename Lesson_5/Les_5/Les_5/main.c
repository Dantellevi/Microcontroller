/*
 * Les_5.c
 *
 * Created: 08.08.2016 17:01:35
 * Author : Dante_L_Levi
 */ 
#define F_CPU 8000000L

#include <avr/io.h>
#include <util/delay.h>



int main(void)
{
	DDRD=0xFF;
	PORTD=0x00;
	
    /* Replace with your application code */
    while (1) 
    {
		
		PORTD|=(1<<(PORTD0));
		_delay_ms(500);
		
		PORTD&=~(1<<(PORTD0));
		
		_delay_ms(500);
		
		
    }
}

