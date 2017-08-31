#include "led.h"

// #define  MODETIMEVIEW 100
// #define  MODETEMPVIEW 101
// #define  MODEDATEVIEW 102
// #define  MODEDAYVIEW 103
// #define  MODEYEARVIEW 104
// //--------------------------------------------
// #define  MODENONEEDIT 0
// #define  MODEHOUREDIT 1
// #define  MODEMINEDIT 2
// #define  MODEDATEEDIT 3
// #define  MODEMONTHEDIT 4
// #define  MODEYEAREDIT 5
// #define  MODEDAYEDIT 6
// #define  MODEALARMHOUREDIT 7
// #define  MODEALARMMINEDIT 8




unsigned char R1=0, R2=0, R3=0, R4=0;

//extern unsigned char clockeditmode;

void segchar (unsigned char seg)
{
	switch(seg)
	{
		case 1: SPDR = 0b11111001; break;
		case 2: SPDR = 0b10100100; break;
		case 3: SPDR = 0b10110000; break;
		case 4: SPDR = 0b10011001; break;
		case 5: SPDR = 0b10010010; break;
		case 6: SPDR = 0b10000010; break;
		case 7: SPDR = 0b11111000; break;
		case 8: SPDR = 0b10000000; break;
		case 9: SPDR = 0b10010000; break;
		case 0: SPDR = 0b11000000; break;
		case 10: SPDR = 0b10111111;  break; // знак -
		case 11: SPDR = 0b11111111;  break; // пустое место
		case 12: SPDR = 0b11000110;  break; // буква — дл€ показаний температуры
	}
}
//--------------------------------------------
void timer_ini(void)
{
	TCCR1B |= (1<<WGM12); // устанавливаем режим —“— (сброс по совпадению)
	TIMSK |= (1<<OCIE1A);   //устанавливаем бит разрешени€ прерывани€ 1ого счетчика по совпадению с OCR1A(H и L)
	OCR1AH = 0b00001111; //записываем в регистр число дл€ сравнени€
	OCR1AL = 0b01000010;
	TCCR1B |= (1<<CS11);//установим делитель.
}
//--------------------------------------------
unsigned char n_count=0;
//--------------------------------------------
ISR (TIMER1_COMPA_vect)
{
	if(n_count==0)
	{
		segchar(R1);
		while(!(SPSR & (1<<SPIF)));//подождем пока данные передадутс€
		SPDR = 0b00001110;
		while(!(SPSR & (1<<SPIF)));//подождем пока данные передадутс€
		//сгенерируем отрицательный фронт дл§ записи в STORAGE REGISTER
		PORTB |= (1<<PORTB2); //высокий уровень
		PORTB &= ~(1<<PORTB2); //низкий уровень
	}
	if(n_count==1)
	{
		segchar(R2);
		while(!(SPSR & (1<<SPIF)));//подождем пока данные передадутс€
		SPDR = 0b00001101;
		while(!(SPSR & (1<<SPIF)));//подождем пока данные передадутс€
		//сгенерируем отрицательный фронт дл§ записи в STORAGE REGISTER
		PORTB |= (1<<PORTB2); //высокий уровень
		PORTB &= ~(1<<PORTB2); //низкий уровень
	}
	if(n_count==2)
	{
		segchar(R3);
		while(!(SPSR & (1<<SPIF)));//подождем пока данные передадутс€
		SPDR = 0b00001011;
		while(!(SPSR & (1<<SPIF)));//подождем пока данные передадутс€
		//сгенерируем отрицательный фронт дл§ записи в STORAGE REGISTER
		PORTB |= (1<<PORTB2); //высокий уровень
		PORTB &= ~(1<<PORTB2); //низкий уровень
	}
	if(n_count==3)
	{
		segchar(R4);
		while(!(SPSR & (1<<SPIF)));//подождем пока данные передадутс€
		SPDR = 0b00000111;
		while(!(SPSR & (1<<SPIF)));//подождем пока данные передадутс€
		//сгенерируем отрицательный фронт дл§ записи в STORAGE REGISTER
		PORTB |= (1<<PORTB2); //высокий уровень
		PORTB &= ~(1<<PORTB2); //низкий уровень
	}
	n_count++;
	if (n_count>3) n_count=0;
}
//--------------------------------------------
void ledprint(unsigned int number)
{
	R1 = number%10;
	R2 = number%100/10;
	R3 = number%1000/100;
	R4 = number/1000;
}
//--------------------------------------------
