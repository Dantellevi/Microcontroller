/*
 * Lesss0n_14.c
 *
 * Created: 11.08.2016 18:22:24
 * Author : Dante_L_Levi
 */ 

#include "Main.h"

void port_ini(void)
{
	PORTD=0x00;
	DDRD=0xFF;
}

// ISR(USART_RXC_vect)
// {
// 	int b;
// 	b=UDR;
// }

int main(void)
{
	 USART_ini(8);//в зависимости от числа будет меняться скорость
	 //8-115200
	 //12-76800
	 //16-57600
	 //25-38400
	 //34-28800
	 //51-19200
	 //68-14400
	 //103-9600
	 //207-4800
	 //416-2400
	USART_Transmit('O');
	USART_Transmit('K');
	USART_Transmit('!');
	USART_Transmit(0x0d);
	USART_Transmit(0x0a);
    /* Replace with your application code */
    while (1) 
    {
		USART_Transmit('O');
		USART_Transmit('K');
		USART_Transmit('!');
		USART_Transmit(0x0d);
		USART_Transmit(0x0a);
		_delay_ms(100);
    }
}

