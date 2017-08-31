/*
 * Lesson_22.c
 *
 * Created: 23.08.2016 18:58:05
 * Author : DANTE_L_LEVI
 */ 
#include "Main.h"



void PORT_ini(void)
{
	DDRD=0xFF;
	PORTD=0x00;
}

int main(void)
{
	
	//unsigned int adc_value;
	
	PORT_ini();
	LCD_ini();
	init_adc();//инициализация АЦП
	lcd_clear();
	 char buf[5];
	
	
    /* Replace with your application code */
    while (1) 
    {
		
		lcd_gotoxy(0,0);
		
		unsigned int Vol=read_adc(0)*0.004883;
		 sprintf(buf,"%.1d V",(unsigned int)Vol);//конвертируем результат в масив buf
	
		lcd_print(buf);
		
	
		 
		_delay_ms(500);
		
    }
}

