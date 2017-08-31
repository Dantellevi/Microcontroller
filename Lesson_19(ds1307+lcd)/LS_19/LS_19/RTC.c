/*
 * RTC.c
 *
 * Created: 15.08.2016 13:25:46
 *  Author: Dante_L_Levi
 */ 

#include "RTC.h"

unsigned char RTC_ConvertFromDec(unsigned char c)
{
	unsigned char ch=((c>>4)*10+(0b00001111&c));
	
	return ch;
	
}

unsigned char RTC_ConvertFromBinDec(unsigned char c)
{
	unsigned char ch=(((c/10)<<4)|(c%10));
	
	return ch;
	
}