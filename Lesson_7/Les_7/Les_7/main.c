 
#define F_CPU 8000000L
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRB=0x00;
	DDRD=0xFF;
	
    PORTD=0b00000000;
	PORTB=0b00000001;
	
	
    while (1) 
    {
		if (!(PINB&0b00000001))
		{
			_delay_ms(15);
			 PORTD=0b00000001;
		} 
		else
		{
			 PORTD=0b00000000;
		}
		
		
    }
}

