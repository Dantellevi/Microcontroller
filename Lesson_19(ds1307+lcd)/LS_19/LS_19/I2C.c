/*
 * I2C.c
 *
 * Created: 13.08.2016 12:05:32
 *  Author: Dante_L_Levi
 */ 

#include "I2C.h"

void I2C_Init (void)
{
	TWBR=0x20;//�������� �������� (��� 8 ��� ���������� 100 ���, ��� � ���������� ��� ������� � ds1307)
}


void I2C_StartCondition(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));//�������� ���� ����������� TWIN
}

void I2C_StopCondition(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

void I2C_SendByte(unsigned char c)
{
	TWDR = c;//������� ���� � ������� ������
	TWCR = (1<<TWINT)|(1<<TWEN);//������� �������� �����
	while (!(TWCR & (1<<TWINT)));//�������� ���� ����������� TWIN
}

void I2C_SendByteByADDR(unsigned char c,unsigned char addr)
{
	I2C_StartCondition(); // �������� ������� START
	I2C_SendByte(addr); // �������� � ���� ����� ���������� + ��� ������-������
	I2C_SendByte(c);// �������� ���� ������
	I2C_StopCondition();// �������� ������� START
}

unsigned char I2C_ReadByte(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);//��� ������������� � �������� ��������� ��������
	//��� ��� TWEA ����� ������� ����(0<<TWEA) ����� ����� ������ ���� � �������� 
	//� ����� ��� ��������� ��������.....��� ����� ������
	while (!(TWCR & (1<<TWINT)));//�������� ��������� ���� TWIN
	return TWDR;//������ ������� ������
}

unsigned char I2C_ReadLastByte(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));//�������� ��������� ���� TWIN
	return TWDR;//������ ������� ������
}