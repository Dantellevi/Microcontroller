

#include "Main.h"

void Settings_ports(void)
{
	PORTB=0x00;
	DDRB=0b00001000;
	
}

int main(void)
{
    /* Replace with your application code */
	unsigned char pwm_st=0;
	Settings_ports();
	init_PWM_timer();
//	OCR2=50;
    while (1) 
    {
		if (pwm_st==0)
		{
			OCR2++;
			if (OCR2>254)
			{
				pwm_st=1;
			}
		}
		if (pwm_st==1)
		{
			OCR2--;
			if (OCR2>=1)
			{
				pwm_st=1;
			}
		}
		_delay_ms(25);
    }
}

