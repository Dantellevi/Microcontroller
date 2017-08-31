/*
 * Less_30.c
 *
 * Created: 05.09.2016 19:58:11
 * Author : DANTE_L_LEVI
 */ 

#include "Main.h"

void Port_ini(void)
{
	PORTD=0x00;
	DDRD=0xFF;
}

int main(void)
{
	Port_ini();
	LCD_ini();
	lcd_clear();
	lcd_gotoxy(0,0);
	lcd_print("ATTiny2313");
	lcd_gotoxy(0,1);
	lcd_print("ATMega 8A");
	
    /* Replace with your application code */
    while (1) 
    {
		
    }
}

