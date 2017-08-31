/*
 * TWI.h
 *
 * Created: 19.09.2016 16:13:33
 *  Author: DANTE_L_LEVI
 */ 


#ifndef TWI_H_
#define TWI_H_

#include "Main.h"

void I2C_Init (void); //������������� i2c
void I2C_StartCondition(void); //�������� ������� START
void I2C_StopCondition(void); //�������� ������� STOP
void I2C_SendByte(unsigned char c); //�������� ����� � ����
void I2C_SendByteByADDR(unsigned char c,unsigned char addr); //�������� ����� � ���� �� ���������� �� ������
unsigned char I2C_ReadByte(void); //������ ����
unsigned char I2C_ReadLastByte(void); //������ ��������� ����





#endif /* TWI_H_ */