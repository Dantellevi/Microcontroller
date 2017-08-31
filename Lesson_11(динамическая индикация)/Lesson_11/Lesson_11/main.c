/*
 * Lesson_11.c
 *
 * Created: 09.08.2016 19:29:43
 * Author : Dante_L_Levi
 */ 
#define F_CPU 8000000L
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//--------------------------------------
unsigned char i;
unsigned char Fl_1;
unsigned char Fl_2;
//---------------------------------------


// -------------------------------------------
void Settings(void)
{
	DDRB=0b00001111;
	DDRD=0xFF;
	PORTD=0x00;
	PORTB|=(1<<(PORTB5));
	
	//PORTB&=~(1<<(PORTB0));
	//PORTB&=~(1<<(PORTB1));
}


//-------------------------------------------
void Set(unsigned char i)
{
	switch(i)
	{
		case 0:{PORTD=0b00111111;break;}
		case 1:{PORTD=0b00000110;break;}
		case 2:{PORTD=0b01011011;break;}
		case 3:{PORTD=0b01001111;break;}
		case 4:{PORTD=0b01100110;break;}
		case 5:{PORTD=0b01101101;break;}
		case 6:{PORTD=0b01111101;break;}
		case 7:{PORTD=0b00000111;break;}
		case 8:{PORTD=0b01111111;break;}
		case 9:{PORTD=0b01101111;break;}
		
		
	}
}

//-----------------------------------------------------------------

void ledprint(unsigned char Numm)
{
	Fl_1=Numm%10;
	Fl_2=Numm/10;
	
	
	
}

//-----------------------------------------------------------------

void timer_ini(void)
{
	TCCR1B|=(1<<(WGM12));//устанавливаем режи СТС
	TIMSK|=(1<<(OCIE1A));//устанавливает бит разрешения прерывания 1-ого стчетчика по совпадению OCR1A
	OCR1AH=0b01111010;//число для сравнения
	OCR1AL=0b00010010;
	TCCR1B|=(1<<CS11);//устанавливаем делитель
	
	
	
}

//-------------------------------------------------------------------------
unsigned char N_cout;
//-----------------------------------------------------------------------

ISR(TIMER1_COMPA_vect)
{
	
	if (N_cout==0)
	{
		PORTB&=~(1<<(PORTB1));
		PORTB|=(1<<(PORTB0));
		
		Set(Fl_1);
	}
	if (N_cout==1)
	{
		
		PORTB&=~(1<<(PORTB0));
		PORTB|=(1<<(PORTB1));
		Set(Fl_2);
	}
	N_cout++;
	
	if (N_cout>1)
	{
		N_cout=0;
	}
	
	
	
	

}


//------------------------------------------------------------


int main(void)
{
	timer_ini();
	Settings();
	i=0;
	sei();
//	ledprint(72);
    /* Replace with your application code */
    while (1) 
    {
		for(i=0;i<=99;i++)
		{
			ledprint(i);
			_delay_ms(1000);
		}
    }
}

