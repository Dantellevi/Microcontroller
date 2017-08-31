/*
 * Lesson_18.c
 *
 * Created: 16.08.2016 13:24:30
 * Author : Dante_L_Levi
 */ 

#include "Main.h"


int main(void)
{
	SM_ini();
    /* Replace with your application code */
    while (1) 
    {
		for (int i=0;i<=511;i++)
		{
			SMforvard();
		}
		_delay_ms(300);
		for (int i=0;i<=511;i++)
		{
			SM_back();
			
		}_delay_ms(700);
    }
}

