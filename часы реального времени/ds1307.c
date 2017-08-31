
#include "main.h"
 
unsigned char sec,min,hour,day,date,month,year;
 
int main(void)
{
    	I2C_Init();
    	USART_Init (8);
 
    	//������������� �����
    	I2C_StartCondition();
    	I2C_SendByte(0b11010000);
    	I2C_SendByte(0);//��������� �� 0x00
    	I2C_SendByte(RTC_ConvertFromBinDec(0));//�������
    	I2C_SendByte(RTC_ConvertFromBinDec(3));//������
    	I2C_SendByte(RTC_ConvertFromBinDec(13));//����
    	I2C_SendByte(RTC_ConvertFromBinDec(1));//���� ������
    	I2C_SendByte(RTC_ConvertFromBinDec(25));//����
    	I2C_SendByte(RTC_ConvertFromBinDec(1));//�����
    	I2C_SendByte(RTC_ConvertFromBinDec(16));//���
    	I2C_StopCondition();
 
    while(1)
    {
            	//������ �����
            	I2C_SendByteByADDR(0,0b11010000); //�������� ����� � ���� I2C
            	_delay_ms(300);
            	I2C_StartCondition(); //�������� ������� START
            	I2C_SendByte(0b11010001); //�������� � ���������� ��� ������
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
            	USART_Transmit(date/10+0x30);//����������� ����� � ��� �����
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
 
            	USART_Transmit(0x0d);//������� � ������ ������
            	USART_Transmit(0x0a);//������� �� ����� ������
	}
}