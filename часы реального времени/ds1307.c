
#include "main.h"
 
unsigned char sec,min,hour,day,date,month,year;
 
int main(void)
{
    	I2C_Init();
    	USART_Init (8);
 
    	//Устанавливаем время
    	I2C_StartCondition();
    	I2C_SendByte(0b11010000);
    	I2C_SendByte(0);//переходим на 0x00
    	I2C_SendByte(RTC_ConvertFromBinDec(0));//секунды
    	I2C_SendByte(RTC_ConvertFromBinDec(3));//минуты
    	I2C_SendByte(RTC_ConvertFromBinDec(13));//часы
    	I2C_SendByte(RTC_ConvertFromBinDec(1));//день недели
    	I2C_SendByte(RTC_ConvertFromBinDec(25));//дата
    	I2C_SendByte(RTC_ConvertFromBinDec(1));//месяц
    	I2C_SendByte(RTC_ConvertFromBinDec(16));//год
    	I2C_StopCondition();
 
    while(1)
    {
            	//Читаем время
            	I2C_SendByteByADDR(0,0b11010000); //отправим адрес в шину I2C
            	_delay_ms(300);
            	I2C_StartCondition(); //Отправим условие START
            	I2C_SendByte(0b11010001); //Отправим в устройство бит чтения
            	sec = I2C_ReadByte();
            	min = I2C_ReadByte();
            	hour = I2C_ReadByte();
            	day=I2C_ReadByte();
            	date=I2C_ReadByte();
            	month=I2C_ReadByte();
            	year=I2C_ReadLastByte();
            	I2C_StopCondition();
            	sec = RTC_ConvertFromDec(sec);
            	min = RTC_ConvertFromDec(min);
            	hour = RTC_ConvertFromDec(hour);
            	day = RTC_ConvertFromDec(day);
            	year = RTC_ConvertFromDec(year);
            	month = RTC_ConvertFromDec(month);
            	date = RTC_ConvertFromDec(date);
            	USART_Transmit(date/10+0x30);//Преобразуем число в код числа
            	USART_Transmit(date%10+0x30);
            	USART_Transmit('.');
            	USART_Transmit(month/10+0x30);
            	USART_Transmit(month%10+0x30);
            	USART_Transmit('.');
            	USART_Transmit('2');
            	USART_Transmit('0');
            	USART_Transmit(year/10+0x30);
            	USART_Transmit(year%10+0x30);
            	USART_Transmit(' ');
            	USART_Transmit('-');
            	USART_Transmit(day+0x30);
            	USART_Transmit('-');
            	USART_Transmit(' ');
            	USART_Transmit(' ');
            	USART_Transmit(hour/10+0x30);
            	USART_Transmit(hour%10+0x30);
            	USART_Transmit(':');
            	USART_Transmit(min/10+0x30);
            	USART_Transmit(min%10+0x30);
            	USART_Transmit(':');
            	USART_Transmit(sec/10+0x30);
            	USART_Transmit(sec%10+0x30);
 
            	USART_Transmit(0x0d);//переход в начало строки
            	USART_Transmit(0x0a);//переход на новую строку
	}
}