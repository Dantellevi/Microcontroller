/*
 * Lesson_17.c
 *
 * Created: 15.08.2016 13:16:36
 * Author : Dante_L_Levi
 */ 
#include "main.h"

int sec=0;
int min=0;
int hose=0;
int day=0;
int data=0;
int mesiac=0;
int god=0;

int main(void)
{
	I2C_Init();
	USART_Init(8);
	USART_Transmit('S');
	//устанавливаем время
// 	I2C_StartCondition();
// 	
// 	I2C_SendByte(0b11010000);
// 	I2C_SendByte(0);//переходим на адрес ноль
// 	I2C_SendByte(RTC_ConvertFromBinDec(0));//секунды
// 	I2C_SendByte(RTC_ConvertFromBinDec(41));//минуты
// 	I2C_SendByte(RTC_ConvertFromBinDec(20));//часы
// 	I2C_SendByte(RTC_ConvertFromBinDec(1));//день недели
// 	I2C_SendByte(RTC_ConvertFromBinDec(15));//дата 
// 	I2C_SendByte(RTC_ConvertFromBinDec(8));//месяц
// 	I2C_SendByte(RTC_ConvertFromBinDec(16));//год
// 	I2C_StopCondition();
    /* Replace with your application code */
    while (1) 
    {
		//читаем время
		I2C_SendByte(0,0b11010000);//переходим на адрес 0
		_delay_ms(300);
		I2C_StartCondition();//отправляем условие старта
			I2C_SendByte(0b11010001);//отправляем в устройство бит чтения
			sec=I2C_ReadByte();
			min=I2C_ReadByte();
			hose=I2C_ReadByte();
			day=I2C_ReadByte();
			data=I2C_ReadByte();
			mesiac=I2C_ReadByte();
			god=I2C_ReadByte();
			I2C_StopCondition();
			sec=RTC_ConvertFromDec(sec);
			min=RTC_ConvertFromDec(min);
			hose=RTC_ConvertFromDec(hose);
			day=RTC_ConvertFromDec(day);
			data=RTC_ConvertFromDec(data);
			mesiac=RTC_ConvertFromDec(mesiac);
			god=RTC_ConvertFromDec(god);
			
			USART_Transmit(data/10+0x30);//преобразуем число в код числа
			USART_Transmit(data%10+0x30);//преобразуем число в код числа
			USART_Transmit('.');
			USART_Transmit(mesiac/10+0x30);//преобразуем число в код числа
			USART_Transmit(mesiac%10+0x30);//преобразуем число в код числа
			USART_Transmit('.');	
			USART_Transmit(god/10+0x30);//преобразуем число в код числа
			USART_Transmit(god%10+0x30);//преобразуем число в код числа
			USART_Transmit('.');
			USART_Transmit('.');
			USART_Transmit('.');
			USART_Transmit('.');
			USART_Transmit('.');
			USART_Transmit(day+0x30);
			USART_Transmit('.');
			USART_Transmit('.');
			USART_Transmit('.');
			USART_Transmit(hose/10+0x30);//преобразуем число в код числа
			USART_Transmit(hose%10+0x30);
			USART_Transmit(':');
			USART_Transmit(min/10+0x30);//преобразуем число в код числа
			USART_Transmit(min%10+0x30);
			USART_Transmit(':');
			USART_Transmit(sec/10+0x30);//преобразуем число в код числа
			USART_Transmit(sec%10+0x30);
			USART_Transmit('0x0d');
			USART_Transmit('0x0a');
    }
}

