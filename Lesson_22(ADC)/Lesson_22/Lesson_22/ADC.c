/*
 * ADC.c
 *
 * Created: 23.08.2016 20:48:10
 *  Author: DANTE_L_LEVI
 */ 

#include "ADC.h"


void init_adc()
{
	ADMUX = 0b01000000; //�������� �������� ������� ��� 5v
	ADCSRA|=(1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);// ������������� ������������
	ADCSRA|=(1 << ADEN);// �������� ���
}

// ������� ������� �������������� ��� � ������ ����������
unsigned int read_adc(unsigned char adc_input) {
	ADMUX|=0x07&adc_input; //���������� �� ����� ����� �������� V
	_delay_us(10); // �������� �� ������������ �������� ����������
	ADCSRA |= (1 << ADSC); // ������ �������������� ���
	while ((ADCSRA & (1 << ADIF))==0);// �������� ��������� ��������������
	return ADCW;
}