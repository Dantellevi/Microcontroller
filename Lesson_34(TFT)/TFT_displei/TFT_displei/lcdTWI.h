/*
 * lcdTWI.h
 *
 * Created: 19.09.2016 16:13:46
 *  Author: DANTE_L_LEVI
 */ 


#ifndef LCDTWI_H_
#define LCDTWI_H_


#include "Main.h"

//----------------------------------------
void LCD_ini(void);
void setpos(unsigned char x, unsigned y);
void str_lcd (char str1[]);
void clearlcd(void);
void sendcharlcd(unsigned char c);
//----------------------------------------
#define e1   I2C_SendByteByADDR(portlcd|=0x04,0b01001110) // ��������� ����� E � 1
#define e0   I2C_SendByteByADDR(portlcd&=~0x04,0b01001110)  // ��������� ����� E � 0
#define rs1	I2C_SendByteByADDR(portlcd|=0x01,0b01001110) // ��������� ����� RS � 1
#define rs0   I2C_SendByteByADDR(portlcd&=~0x01,0b01001110)  // ��������� ����� RS � 0
#define setled()	I2C_SendByteByADDR(portlcd|=0x08,0b01001110) // ��������� ���������
#define setwrite()   I2C_SendByteByADDR(portlcd&=~0x02,0b01001110)  // ��������� ������ � ������ �������
//----------------------------------------





#endif /* LCDTWI_H_ */