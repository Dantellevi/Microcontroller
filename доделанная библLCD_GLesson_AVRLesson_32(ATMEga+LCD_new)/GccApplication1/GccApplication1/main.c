/*
 * GccApplication1.c
 *
 * Created: 08.09.2016 20:45:56
 * Author : DANTE_L_LEVI
 */ 

#include "Main.h"

char buffer[512]={"The selection of RAM is set by the previous address set instruction. If the address set instruction of RAM is not performed before this instruction, the data that has been read first is invalid, as the direction of AC is not yet determined. If RAM data is read several times without RAM address instructions set before, read operation, the correct RAM data can be obtained from the second. But the first data would be incorrect, as there is no time margin to transfer RAM data. In case of DDRAM read operation..."};
	
	
void Port_ini(void)
{
	DDRD=0xFF;
	PORTD=0x00;
	
	
}


int main(void)
{
	
	unsigned int i;
	
	
	Port_ini();
	LCD_ini();
	lcd_clear();
	lcd_gotoxy(0,3);
	lcd_print("1");
	_delay_ms(250);
// 	lcd_print_80(buffer);
// 	_delay_ms(2000);
// 	
// 	lcd_print_80(buffer+20);
// 	_delay_ms(1000);
// 	lcd_print_80(buffer+40);
	for (i=0;i<=22;i++)
	{
		lcd_print_80(buffer+i*20);
		_delay_ms(1000);
	}
    /* Replace with your application code */
    while (1) 
    {
		
    }
}

