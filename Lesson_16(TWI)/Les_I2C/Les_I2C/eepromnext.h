/*
 * eepromnext.h
 *
 * Created: 13.08.2016 14:13:51
 *  Author: Dante_L_Levi
 */ 


#ifndef EEPROMNEXT_H_
#define EEPROMNEXT_H_
#include "Main.h"
#define  TW_MT_DATA_ASK 0x28//������� ������� ������ � ������� ���������� �����
#define  TW_MR_DATA_ASK 0x50//������� ������ ������ � ������� �������������
#define  TW_MR_DATA_NASK 0x58//������� ������� ������ � ������� ���������� �����


int EE_WriteByte(unsigned char c);
unsigned char EE_ReadByte(void);
unsigned char EE_ReadLastByte(void);



#endif /* EEPROMNEXT_H_ */