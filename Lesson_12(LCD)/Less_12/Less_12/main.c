
#include "Main.h"


//--------------------------------------------
void Port_settings(void)
{
	DDRD=0xFF;
	PORTD=0x00;
}
//---------------------------------------------




int main(void)
{
	Port_settings();
	LCD_ini();
	lcd_print("Sania-Pashsa!!");
	
    /* Replace with your application code */
    while (1) 
    {
    }
}

