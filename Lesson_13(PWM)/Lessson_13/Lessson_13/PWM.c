#include "PWM.h"

void init_PWM_timer(void)

{
	ASSR=0x00;
	TCCR2=0b01101111;//FAST PWM  включаем,Clear OC2 в случае совпадения MATCH,тактовая частота /256
	TCNT2=0x00;//значение таймера =0
	OCR2=0;//скважность равна 0
	TIMSK|=0x00;
	
	
	
	
}
