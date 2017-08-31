#include "USART.h"

void USART_ini(unsigned int speed)
{
	UBRRH=(unsigned char)(speed>>8);
	UBRRL=(unsigned char)speed;
	//----------------------��������
	
	UCSRB=(1<<RXEN)|(1<<TXEN);
	//----------------------�������� ����� � ��������
	
	UCSRB|=(1<<RXCIE);//��������� ���������� ���������
	
	UCSRA|=(1<<U2X);
	// �������� �������
	
	UCSRC=(1<<URSEL)|(1<<USBS)|(1<<UCSZ1)|(1<<UCSZ0);
						//������������ �������� UCSRC(����������� ����� ������ UNSEL),(��� �������� �������� UPM1=0 � UPM0=0)
						//���� ��� (USBS=1), 8 ������ ������� (UCSZ1=1 � UCSZ0=1)
						
	
	
}

void USART_Transmit(unsigned char data)
{
	while(!(UCSRA&(1<<UDRE)));

		UDR=data;//������ ���������� ������ ������ � ��� ������ ���� ����� ����
	
	
}
