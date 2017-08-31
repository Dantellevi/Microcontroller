/*
 * Less_20.c
 *
 * Created: 18.08.2016 16:57:14
 * Author : Dante_L_Levi
 */ 

#include "Main.h"
unsigned char sec=0;
unsigned char min=0;
unsigned char hose=0;
unsigned char day=0;
unsigned char data=0;
unsigned char mesiac=0;
unsigned char god=0;

unsigned char tt=0;

void PoRT_ini(void)
{
	PORTD=0x00;
	DDRD=0xFF;
	
}

int main(void)
{
	PoRT_ini();
	I2C_Init();
	LCD_ini();
	lcd_print("Hello!!!");
	_delay_ms(250);
	lcd_clear();
	// 	I2C_StartCondition();
	//
	// 	I2C_SendByte(0b11010000);
	// 	I2C_SendByte(0);//��������� �� ����� ����
	// 	I2C_SendByte(RTC_ConvertFromBinDec(0));//�������
	// 	I2C_SendByte(RTC_ConvertFromBinDec(41));//������
	// 	I2C_SendByte(RTC_ConvertFromBinDec(20));//����
	// 	I2C_SendByte(RTC_ConvertFromBinDec(1));//���� ������
	// 	I2C_SendByte(RTC_ConvertFromBinDec(15));//����
	// 	I2C_SendByte(RTC_ConvertFromBinDec(8));//�����
	// 	I2C_SendByte(RTC_ConvertFromBinDec(16));//���
	// 	I2C_StopCondition();
	
	/* Replace with your application code */
	while (1)
	{
		//lcd_clear();
		
		I2C_SendByteByADDR(0,0b11010000);//��������� �� ����� 0
		_delay_ms(200);
		I2C_StartCondition();//���������� ������� ������
		I2C_SendByte(0b11010001);//���������� � ���������� ��� ������
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
		lcd_gotoxy(0,0);
		sendchar(data/10+0x30);//����������� ����� � ��� �����
		sendchar(data%10+0x30);//����������� ����� � ��� �����
		sendchar('.');
		sendchar(mesiac/10+0x30);//����������� ����� � ��� �����
		sendchar(mesiac%10+0x30);//����������� ����� � ��� �����
		sendchar('.');
		sendchar(god/10+0x30);//����������� ����� � ��� �����
		sendchar(god%10+0x30);//����������� ����� � ��� �����
		sendchar('.');
		sendchar(day+0x30);
		
		
		lcd_gotoxy(0,1);
		sendchar(hose/10+0x30);//����������� ����� � ��� �����
		sendchar(hose%10+0x30);
		sendchar(':');
		sendchar(min/10+0x30);//����������� ����� � ��� �����
		sendchar(min%10+0x30);
		sendchar(':');
		sendchar(sec/10+0x30);//����������� ����� � ��� �����
		sendchar(sec%10+0x30);
		//sendchar('0x0d');
		//sendchar('0x0a');
		sendchar(' ');
		tt=converttemp(dt_check());//�������� �����������
		
		sendchar(tt/10+0x30);
		sendchar(tt%10+0x30);
		sendchar('*');
		sendchar('C');
				
	}
}
