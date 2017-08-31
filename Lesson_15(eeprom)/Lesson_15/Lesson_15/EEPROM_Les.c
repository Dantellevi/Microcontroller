/*
 * Lesson_15.c
 *
 * Created: 12.08.2016 13:06:34
 * Author : Dante_L_Levi
 */ 

#include "Main.h" 
#include <avr/eeprom.h>
/*unsigned char dtt;*/

int main(void)
{
	//EEPROM_write(1,120);
    /* Replace with your application code */
	EEPROM_write(1,120);
	
	EEPROM_write_word(1,3000);
	EEPROM_write_dword(3,0xFEDCBA98);
	EEPROM_write_string(16,"Hello World");
	USART_ini(8);
	
	//asm("nop");
	//dtt=EEPROM_read(1);
	//USART_Transmit(dtt);
    while (1) 
    {
    }
}

