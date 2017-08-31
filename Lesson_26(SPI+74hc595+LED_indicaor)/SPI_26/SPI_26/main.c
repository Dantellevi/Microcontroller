/*
 * SPI_26.c
 *
 * Created: 29.08.2016 19:27:10
 * Author : DANTE_L_LEVI
 */ 


#include "Main.h"


int main(void)
{
	
	//int i=0;
	
	DDRB|=(1<<PORTB2)|(1<<PORTB3)|(1<<PORTB5);
	PORTB&=~((1<<PORTB2)|(1<<PORTB3)|(1<<PORTB5));
	SPCR=((1<<SPE)|(1<<MSTR));// �������� ���� , ������� �������
	
	SPDR=0b00000000;
	
	while(!(SPSR&(1<<SPIF)));//�������� ���� ������ �����������
	//����������� ������������� ����� ��� ������ � STORAGE REGISTER
	PORTB|=(1<<PORTB2);
	PORTB&=~((1<<PORTB2));
	
	_delay_ms(500);
// 	SPDR=0b11111111;
// 	PORTB|=(1<<PORTB2);
// 	PORTB&=~((1<<PORTB2));
// 	_delay_ms(2000);
	/* Replace with your application code */
	while (1)
	{
		
		// ��������� 1
		
			SPDR=0b11111001;
			while(!(SPSR&(1<<SPIF)));//�������� ���� ������ �����������
			//����������� ������������� ����� ��� ������ � STORAGE REGISTER
			PORTB|=(1<<PORTB2);
			PORTB&=~((1<<PORTB2));
			_delay_ms(1000);
		
		
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++
		
		
			//SPDR=0b11111001;
			// ��������� 2
			SPDR=0b10100100;
			while(!(SPSR&(1<<SPIF)));//�������� ���� ������ �����������
			//����������� ������������� ����� ��� ������ � STORAGE REGISTER
			PORTB|=(1<<PORTB2);
			PORTB&=~((1<<PORTB2));
			_delay_ms(1000); 
			
			// ��������� 3
			SPDR=0b10110000;
			while(!(SPSR&(1<<SPIF)));//�������� ���� ������ �����������
			//����������� ������������� ����� ��� ������ � STORAGE REGISTER
			PORTB|=(1<<PORTB2);
			PORTB&=~((1<<PORTB2));
			_delay_ms(1000);
			
			// ��������� 4
			SPDR=0b10011001;
			while(!(SPSR&(1<<SPIF)));//�������� ���� ������ �����������
			//����������� ������������� ����� ��� ������ � STORAGE REGISTER
			PORTB|=(1<<PORTB2);
			PORTB&=~((1<<PORTB2));
			_delay_ms(1000);
			
			// ��������� 5
			SPDR=0b10010010;
			while(!(SPSR&(1<<SPIF)));//�������� ���� ������ �����������
			//����������� ������������� ����� ��� ������ � STORAGE REGISTER
			PORTB|=(1<<PORTB2);
			PORTB&=~((1<<PORTB2));
			_delay_ms(1000);
			
			// ��������� 6 
			SPDR=0b10000010;
			while(!(SPSR&(1<<SPIF)));//�������� ���� ������ �����������
			//����������� ������������� ����� ��� ������ � STORAGE REGISTER
			PORTB|=(1<<PORTB2);
			PORTB&=~((1<<PORTB2));
			_delay_ms(1000);
			
			// ��������� 7
			SPDR=0b11111000;
			while(!(SPSR&(1<<SPIF)));//�������� ���� ������ �����������
			//����������� ������������� ����� ��� ������ � STORAGE REGISTER
			PORTB|=(1<<PORTB2);
			PORTB&=~((1<<PORTB2));
			_delay_ms(1000);
			
			// ��������� 8
			SPDR=0b10000000;
			while(!(SPSR&(1<<SPIF)));//�������� ���� ������ �����������
			//����������� ������������� ����� ��� ������ � STORAGE REGISTER
			PORTB|=(1<<PORTB2);
			PORTB&=~((1<<PORTB2));
			_delay_ms(1000);
			
			// ��������� 9
			SPDR=0b10010000;
			while(!(SPSR&(1<<SPIF)));//�������� ���� ������ �����������
			//����������� ������������� ����� ��� ������ � STORAGE REGISTER
			PORTB|=(1<<PORTB2);
			PORTB&=~((1<<PORTB2));
			_delay_ms(1000);
			
			// ��������� 0	
			SPDR=0b11000000;	
			while(!(SPSR&(1<<SPIF)));//�������� ���� ������ �����������
			//����������� ������������� ����� ��� ������ � STORAGE REGISTER
			PORTB|=(1<<PORTB2);
			PORTB&=~((1<<PORTB2));
			_delay_ms(1000);		

			
		
		
	}
}
