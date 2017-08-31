
#define F_CPU 8000000L
#include <avr/io.h>
#include <util/delay.h>

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

int main(void)
{
	
	Setting();
	
    /* Replace with your application code */
    while (1) 
    {
		if (i>9)
		{
			i=0;
		}
		
		
		
		if (!(PINB&0b00000001))
		{
			i++;
			_delay_ms(25);
			
			
		}
		SET(i);
		_delay_ms(250);
		
    }
}

