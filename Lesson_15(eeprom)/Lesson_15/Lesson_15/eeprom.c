/*
 * eeprom.c
 *
 * Created: 12.08.2016 13:13:31
 *  Author: Dante_L_Levi
 */ 

#include "eeprom.h"

void EEPROM_write(unsigned int uiAddress,unsigned char ucData)
{
	while(EECR&(1<<(EEWE)));
	
	EEAR=uiAddress;
	EEDR=ucData;
	
	EECR|=(1<<EEMWE);
	EECR|=(1<<EEWE);
}

unsigned char EEPROM_read(unsigned int uiAddress)
{
	while(EECR&(1<<EEWE));
	
	EEAR=uiAddress;
	
	EECR|=(1<<EERE);
	
	return EEDR;
	
	
}

void EEPROM_write_word(unsigned int uiAddress, uint16_t ucData)

{
	
EEPROM_write(uiAddress,(unsigned char)ucData);
unsigned char dt=ucData>>8;
EEPROM_write(uiAddress+1,dt);

}

uint16_t EEPROM_read_word(unsigned int uiAddress)

{
	uint16_t dt=EEPROM_read(uiAddress+1)*256;
	asm("nop");
	dt+=EEPROM_read(uiAddress+1)*256;
	return dt;
}

void EEPROM_write_dword(unsigned int uiAddress, uint32_t ucData)

{
	
	EEPROM_write_word(uiAddress,(uint16_t)ucData);
	unsigned char dt=ucData>>16;
	EEPROM_write_word(uiAddress+2,dt);

}
uint32_t EEPROM_read_dword(unsigned int uiAdress)
{
	uint32_t dt=EEPROM_read_word(uiAdress)*65536;
	asm("nop");
	dt+=EEPROM_read_word(uiAdress);
	return dt;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



void EEPROM_write_string(unsigned int uiAddress, char str1[])

{
	wchar_t n;
	for (n=0;str1[n]!='\0';n++)
	{
		EEPROM_write(uiAddress+n,str1[n]);
	}
	
	
	
	

}
const char* EEPROM_read_string(unsigned int uiAdress,unsigned int sz)
{
	unsigned int i;
	char *str1;
	str1=(char*)realloc(NULL,sz);
	for (i=0;i<sz;i++)
	{
		str1[i]=EEPROM_read(uiAdress+i);
		
	}
	
	
	asm("nop");
	str1[i]+=EEPROM_read_word(uiAdress);
	return str1;
}