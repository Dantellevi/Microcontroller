#include "PWM.h"

void init_PWM_timer(void)

{
	ASSR=0x00;
	TCCR2=0b01101111;//FAST PWM  ��������,Clear OC2 � ������ ���������� MATCH,�������� ������� /256
	TCNT2=0x00;//�������� ������� =0
	OCR2=0;//���������� ����� 0
	TIMSK|=0x00;
	
	
	
	
}
