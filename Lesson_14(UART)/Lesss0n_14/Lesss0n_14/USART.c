#include "USART.h"

void USART_ini(unsigned int speed)
{
	UBRRH=(unsigned char)(speed>>8);
	UBRRL=(unsigned char)speed;
	//----------------------скорость
	
	UCSRB=(1<<RXEN)|(1<<TXEN);
	//----------------------включаем прием и передачу
	
	UCSRB|=(1<<RXCIE);//разрешаем прерывания приемника
	
	UCSRA|=(1<<U2X);
	// Удвоение частоты
	
	UCSRC=(1<<URSEL)|(1<<USBS)|(1<<UCSZ1)|(1<<UCSZ0);
						//конфигурация регистра UCSRC(асинхронный режим работы UNSEL),(без контроля четности UPM1=0 и UPM0=0)
						//стоп бит (USBS=1), 8 битная посылка (UCSZ1=1 и UCSZ0=1)
						
	
	
}

void USART_Transmit(unsigned char data)
{
	while(!(UCSRA&(1<<UDRE)));

		UDR=data;//начнет передовать данные только в том случае если буфер пуст
	
	
}
