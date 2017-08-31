/*
 * Les_I2C.c
 *
 * Created: 13.08.2016 11:59:00
 * Author : Dante_L_Levi
 */ 

#include "Main.h"


unsigned char bt[32];
int main(void)
{
	int i=0;
	USART_Init(8);
	I2C_Init();
	
	
	USART_Transmit(TWSR);
	I2C_SendByte(0b10100000); //передача адреса устройства и бита записи
	USART_Transmit(TWSR);
	I2C_SendByte(0);//передача старшой части адреса ячейки памяти
	USART_Transmit(TWSR);
	I2C_SendByte(0);
	USART_Transmit(TWSR);
	I2C_StartCondition();
	USART_Transmit(TWSR);
	I2C_SendByte(0b10100001); //передача адреса устройства и бита записи(1)
	USART_Transmit(TWSR);
	
	
	I2C_StopCondion();//условия стоп
	USART_Transmit(TWSR);
	for (i=0;i<=30;i++)
	{
		bt[i]=EE_ReadByte();
	//	USART_Transmit(TWSR);
	}
	bt[31]=EE_ReadLastByte();
	for (i=0;i<=31;i++)
	{
		USART_Transmit(bt[i]);
	}
	
	
	
	//запись
	I2C_StartCondition();//отправим условие старта
//	USART_Transmit('S');

	USART_Transmit(TWSR);
	I2C_SendByte(0b10100000); //передача адреса устройства и бита записи
	USART_Transmit(TWSR);
	I2C_SendByte(0);//передача старшой части адреса ячейки памяти 
	USART_Transmit(TWSR);
	I2C_SendByte(0);
	USART_Transmit(TWSR);
	I2C_StopCondion();//условия стоп
	USART_Transmit(TWSR);
	bt[0]=0x30;bt[1]=0x31;bt[2]=0x32;bt[3]=0x33;bt[4]=0x34;
	
	for (i=0;i<=31;i++)
	{
		EE_WriteByte(bt[i]);
		USART_Transmit(TWSR);
	}
	
    /* Replace with your application code */
    while (1) 
    {
		
    }
}

