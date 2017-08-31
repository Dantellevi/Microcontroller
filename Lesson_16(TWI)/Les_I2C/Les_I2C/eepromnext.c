/*
 * eepromnext.c
 *
 * Created: 13.08.2016 14:13:34
 *  Author: Dante_L_Levi
 */ 

#include "eepromnext.h"

char err1=0;
int EE_WriteByte(unsigned char c)
{
	TWDR=c;//������� ���� � ������� ������
	TWCR=(1<<TWINT)|(1<<TWEN);//�������� �������� ������
	while(!(TWCR&(1<<TWINT)));//�������� ���� ����������� TWIN
	if ((TWSR&0xF8)!=TW_MT_DATA_ASK)
	{
		return 1;
	}
	return 0;
}

unsigned char EE_ReadByte(void)
{
	
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);//�������� �������� ������
	while(!(TWCR&(1<<TWINT)));//�������� ���� ����������� TWIN
	if ((TWSR&0xF8)!=TW_MT_DATA_ASK) 
	{
		err1=1;
	}
	else err1=0;
	return TWDR;
}

unsigned char EE_ReadLastByte(void)
{
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);//�������� �������� ������
	while(!(TWCR&(1<<TWINT)));//�������� ���� ����������� TWIN
	if ((TWSR&0xF8)!=TW_MT_DATA_ASK)
	{
		err1=1;
	}
	else err1=0;
	return TWDR;
}