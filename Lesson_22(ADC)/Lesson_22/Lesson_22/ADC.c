/*
 * ADC.c
 *
 * Created: 23.08.2016 20:48:10
 *  Author: DANTE_L_LEVI
 */ 

#include "ADC.h"


void init_adc()
{
	ADMUX = 0b01000000; //выбираем источник питания АЦП 5v
	ADCSRA|=(1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);// устанавливаем предделитель
	ADCSRA|=(1 << ADEN);// Включаем АЦП
}

// Функция запуска преобразования АЦП и чтения результата
unsigned int read_adc(unsigned char adc_input) {
	ADMUX|=0x07&adc_input; //определяем на какой ножке измеряем V
	_delay_us(10); // Задержка на установление опорного напряжения
	ADCSRA |= (1 << ADSC); // Запуск преобразования АЦП
	while ((ADCSRA & (1 << ADIF))==0);// Ожидание окончания преобразования
	return ADCW;
}