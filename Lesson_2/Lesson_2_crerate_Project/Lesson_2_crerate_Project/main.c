

#include <avr/io.h>



int main(void)
{
	
	DDRD=0xFF;
	PORTD=0b00000001;
	PORTD=0b00000010;
	
    
    while (1) 
    {
    }
}

