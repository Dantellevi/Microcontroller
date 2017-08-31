/*
 * I2C.c
 *
 * Created: 13.08.2016 12:05:32
 *  Author: Dante_L_Levi
 */ 

#include "I2C.h"

void I2C_Init(void)

{
	TWBR=0x20;//�������� �������� ��� 8��� ���������� 100���
	
	
}

void I2C_StartCondition(void)
{
	TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	
	while(!((TWCR&(1<<TWINT))));//�������� ���� ����������� TWIN
	
}
void I2C_StopCondion(void)
{
	TWCR=(1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

void I2C_SendByte(unsigned char c)
{
	TWDR=c;//������� ���� � ������� ������
	TWCR=(1<<TWINT)|(1<<TWEN);//�������� �������� ������ 
	while(!(TWCR&(1<<TWINT)));//�������� ���� ����������� TWIN
	
}