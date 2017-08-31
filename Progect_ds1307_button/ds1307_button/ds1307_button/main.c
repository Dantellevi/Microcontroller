#include "main.h"
//----------------------------------------
#define BUTTONPORT PORTC
#define BUTTONPORT1 PORTC1
#define BUTTONPORT2 PORTC2
#define BUTTONPORT3 PORTC3
#define BUTTONPIN PINC
#define BUTTONPIN1 PINC1
#define BUTTONPIN2 PINC2
#define BUTTONPIN3 PINC3
#define BUTTONDDR DDRC
#define BUTTONDDR1 DDRC1
#define BUTTONDDR2 DDRC2
#define BUTTONDDR3 DDRC3

#define CLOCKMODE0 0
#define CLOCKMODEDATE 1
#define CLOCKMODEMONTH 2
#define CLOCKMODEYEAR 3
#define CLOCKMODEDAY 4
#define CLOCKMODEHOUR 5
#define CLOCKMODEMIN 6
#define CLOCKMODESEC 7
//----------------------------------------
unsigned char sec,min,hour,day,date,month,year;
//----------------------------------------
void port_ini(void)
{
	PORTD=0x00;
	DDRD=0xFF;
	BUTTONDDR &= ~((1<<BUTTONDDR3)|(1<<BUTTONDDR2)|(1<<BUTTONDDR1));//ножки кнопок на вход
	BUTTONPORT |= (1<<BUTTONPORT3)|(1<<BUTTONPORT2)|(1<<BUTTONPORT1);//подтянем резисторы к лапкам кнопок
}
//----------------------------------------
void ModifyRTC(char index, char direction)
{
	I2C_StartCondition();
	I2C_SendByte(0b11010000);
	switch(index){
		case 1: //число даты
		I2C_SendByte(4);//Переходим на 0x04 - байт числа даты
		//вперед
		if (direction==1)
		{
			if (month==2) //февраль
			{
				if(year%4==0) //високосный год
				{
					if(date<29) I2C_SendByte(RTC_ConvertFromBinDec(date+1));
					else I2C_SendByte(RTC_ConvertFromBinDec(1));
				}
				else
				{
					if(date<28) I2C_SendByte(RTC_ConvertFromBinDec(date+1));
					else I2C_SendByte(RTC_ConvertFromBinDec(1));
				}
			}
			else if ((month==4)|(month==6)|(month==9)|(month==11))
			{
				if(date<30) I2C_SendByte(RTC_ConvertFromBinDec(date+1));
				else I2C_SendByte(RTC_ConvertFromBinDec(1));
			}
			else
			{
				if(date<31) I2C_SendByte(RTC_ConvertFromBinDec(date+1));
				else I2C_SendByte(RTC_ConvertFromBinDec(1));
			}
		}
		//назад
		if (direction==0)
		{
			if (month==2) //февраль
			{
				if(year%4==0) //високосный год
				{
					if(date>1) I2C_SendByte(RTC_ConvertFromBinDec(date-1));
					else I2C_SendByte(RTC_ConvertFromBinDec(29));
				}
				else
				{
					if(date>1) I2C_SendByte(RTC_ConvertFromBinDec(date-1));
					else I2C_SendByte(RTC_ConvertFromBinDec(28));
				}
			}
			else if ((month==4)|(month==6)|(month==9)|(month==11))
			{
				if(date>1) I2C_SendByte(RTC_ConvertFromBinDec(date-1));
				else I2C_SendByte(RTC_ConvertFromBinDec(30));
			}
			else
			{
				if(date>1) I2C_SendByte(RTC_ConvertFromBinDec(date-1));
				else I2C_SendByte(RTC_ConvertFromBinDec(31));
			}
		}
		break;
		case 2: //месяц
		I2C_SendByte(5);//Переходим на 0x05 - байт месяца
		//вперед
		if (direction==1)
		{
			if(month<12) I2C_SendByte(RTC_ConvertFromBinDec(month+1));
			else I2C_SendByte(RTC_ConvertFromBinDec(1));
		}
		//назад
		if (direction==0)
		{
			if(month>1) I2C_SendByte(RTC_ConvertFromBinDec(month-1));
			else I2C_SendByte(RTC_ConvertFromBinDec(12));
		}
		break;
		case 3: //год
		I2C_SendByte(6);//Переходим на 0x06 - байт года
		//вперед
		if (direction==1)
		{
			if(year<99) I2C_SendByte(RTC_ConvertFromBinDec(year+1));
			else I2C_SendByte(RTC_ConvertFromBinDec(1));
		}
		//назад
		if (direction==0)
		{
			if(year>1) I2C_SendByte(RTC_ConvertFromBinDec(year-1));
			else I2C_SendByte(RTC_ConvertFromBinDec(99));
		}
		break;
		case 4: //день недели
		I2C_SendByte(3);//Переходим на 0x03 - байт дня недели
		//вперед
		if (direction==1)
		{
			if(day<7) I2C_SendByte(RTC_ConvertFromBinDec(day+1));
			else I2C_SendByte(RTC_ConvertFromBinDec(1));
		}
		//назад
		if (direction==0)
		{
			if(day>1) I2C_SendByte(RTC_ConvertFromBinDec(day-1));
			else I2C_SendByte(RTC_ConvertFromBinDec(7));
		}
		break;
		case 5: //часы
		I2C_SendByte(2);//Переходим на 0x02 - байт часов
		//вперед
		if (direction==1)
		{
			if(hour<23) I2C_SendByte(RTC_ConvertFromBinDec(hour+1));
			else I2C_SendByte(RTC_ConvertFromBinDec(0));
		}
		//назад
		if (direction==0)
		{
			if(hour>0) I2C_SendByte(RTC_ConvertFromBinDec(hour-1));
			else I2C_SendByte(RTC_ConvertFromBinDec(23));
		}
		break;
		case 6: //минуты
		I2C_SendByte(1);//Переходим на 0x01 - байт минут
		//вперед
		if (direction==1)
		{
			if(min<59) I2C_SendByte(RTC_ConvertFromBinDec(min+1));
			else I2C_SendByte(RTC_ConvertFromBinDec(0));
		}
		//назад
		if (direction==0)
		{
			if(min>0) I2C_SendByte(RTC_ConvertFromBinDec(min-1));
			else I2C_SendByte(RTC_ConvertFromBinDec(59));
		}
		break;
		case 7: //секунды
		I2C_SendByte(0);//Переходим на 0x00 - байт секунд
		//сброс секунд в 0
		if (direction==1)
		{
			I2C_SendByte(RTC_ConvertFromBinDec(0));
		}
		//сброс секунд в 30
		if (direction==0)
		{
			I2C_SendByte(RTC_ConvertFromBinDec(30));
		}
		break;
	}
	I2C_StopCondition();
}
//----------------------------------------
char ButtonPress (char index)
{
	char result=0, butcount=0, butstate=0;
	
	switch(index){
		case 1:
		while (butstate==0)
		{
			if(!(BUTTONPIN&(1<<BUTTONPIN1)))//Кнопка 1 нажата
			{
				if(butcount < 5)
				{
					butcount++;
				}
				else
				{
					result = 1;
					butstate=1;
				}
			}
			else
			{
				if(butcount > 0)
				{
					butcount--;
				}
				else
				{
					butstate=1;
				}
			}
		}
		break;
		case 2:
		while (butstate==0)
		{
			if(!(BUTTONPIN&(1<<BUTTONPIN2)))//Кнопка 2 нажата
			{
				if(butcount < 5)
				{
					butcount++;
				}
				else
				{
					result = 2;
					butstate=1;
				}
			}
			else
			{
				if(butcount > 0)
				{
					butcount--;
				}
				else
				{
					butstate=1;
				}
			}
		}
		break;
		case 3:
		while (butstate==0)
		{
			if(!(BUTTONPIN&(1<<BUTTONPIN3)))//Кнопка 3 нажата
			{
				if(butcount < 5)
				{
					butcount++;
				}
				else
				{
					result = 3;
					butstate=1;
				}
			}
			else
			{
				if(butcount > 0)
				{
					butcount--;
				}
				else
				{
					butstate=1;
				}
			}
		}
		break;
	}
	return result;
}
//----------------------------------------
int main(void)
{
	unsigned int tt=0; //переменная для хранения температуры
	unsigned char button1state=0;//статус кнопки 1
	unsigned char clockmode=CLOCKMODE0;//обычный режим показаний дисплея
	char blinkstate=0;//переменная для мигания определенным показателем на дисплее
	
	//Устанавливаем время
// 	   	I2C_StartCondition();
// 	 	I2C_SendByte(0b11010000);
// 	   	I2C_SendByte(0);//Переходим на 0x00
// 	   	I2C_SendByte(RTC_ConvertFromBinDec(0)); //секунды
// 	  	I2C_SendByte(RTC_ConvertFromBinDec(14)); //минуты
// 	  	I2C_SendByte(RTC_ConvertFromBinDec(19)); //часы
// 	   	I2C_SendByte(RTC_ConvertFromBinDec(1)); //день недели
// 	   	I2C_SendByte(RTC_ConvertFromBinDec(22)); //дата
// 	   	I2C_SendByte(RTC_ConvertFromBinDec(8)); //месяц
// 	   	I2C_SendByte(RTC_ConvertFromBinDec(16)); //год
// 	   	I2C_StopCondition();
	
	
	
	port_ini(); //Инициализируем порты
	I2C_Init(); //Инициализируем шину I2C
	LCD_ini();  //Инициализируем дисплей
	lcd_clear(); //Очистим дисплей
	
	
	
	while(1)
	{
		//Читаем время
		I2C_SendByteByADDR(0,0b11010000);	//переходим на адрес 0
		_delay_ms(50);
		I2C_StartCondition(); //Отправим условие START
		I2C_SendByte(0b11010001); //отправим в устройство бит чтения
		sec = I2C_ReadByte();
		min = I2C_ReadByte();
		hour = I2C_ReadByte();
		day = I2C_ReadByte();
		date = I2C_ReadByte();
		month = I2C_ReadByte();
		year = I2C_ReadLastByte();
		I2C_StopCondition(); //Отправим условие STOP
		sec = RTC_ConvertFromDec(sec); //Преобразуем в десятичный формат
		min = RTC_ConvertFromDec(min); //Преобразуем в десятичный формат
		hour = RTC_ConvertFromDec(hour); //Преобразуем в десятичный формат
		day = RTC_ConvertFromDec(day); //Преобразуем в десятичный формат
		year = RTC_ConvertFromDec(year); //Преобразуем в десятичный формат
		month = RTC_ConvertFromDec(month); //Преобразуем в десятичный формат
		date = RTC_ConvertFromDec(date); //Преобразуем в десятичный формат
		lcd_gotoxy(0,0); //Ставим курсор на начало координат
		if(ButtonPress(1)==1)//Кнопка 1 нажата
		{
			if (clockmode==CLOCKMODE0)
			{
				clockmode=CLOCKMODEDATE;//перейдем в режим перевода даты
				blinkstate=0;//сбросим счетчик мигания
				button1state=1;//статус 1 кнопки
			}
		}
		if(clockmode!=CLOCKMODEDATE)
		{
			sendchar(date/10+0x30);//Преобразуем число в код числа
			sendchar(date%10+0x30);//Преобразуем число в код числа
		}
		else //если режим перевода даты
		{
			if (blinkstate==0)
			{
				sendchar(' ');
				sendchar(' ');
				blinkstate=1;
			}
			else
			{
				sendchar(date/10+0x30);//Преобразуем число в код числа
				sendchar(date%10+0x30);//Преобразуем число в код числа
				blinkstate=0;
			}
			if(ButtonPress(1)==1)//Кнопка 1 нажата
			{
				if(button1state==0) //опросим статус, чтобы сразу не перейти в режим перевода месяца
				{
					clockmode=CLOCKMODEMONTH; //перейдем в режим перевода месяца
					button1state=1;
				}
			}
			if (clockmode==CLOCKMODEDATE) button1state=0;//сбросим статус
			if(ButtonPress(2)==2)//Кнопка 2 нажата
			ModifyRTC(1,0);//1-дата,0-назад
			if(ButtonPress(3)==3)//Кнопка 3 нажата
			ModifyRTC(1,1);//1-дата,1-вперед
		}
		sendchar('.');
		if(clockmode!=CLOCKMODEMONTH)
		{
			sendchar(month/10+0x30);//Преобразуем число в код числа
			sendchar(month%10+0x30);//Преобразуем число в код числа
		}
		else //если режим перевода месяца
		{
			if (blinkstate==0)
			{
				sendchar(' ');
				sendchar(' ');
				blinkstate=1;
			}
			else
			{
				sendchar(month/10+0x30);//Преобразуем число в код числа
				sendchar(month%10+0x30);//Преобразуем число в код числа
				blinkstate=0;
			}
			if(ButtonPress(1)==1)//Кнопка 1 нажата
			{
				if(button1state==0) //опросим статус, чтобы сразу не перейти в режим перевода месяца
				{
					clockmode=CLOCKMODEYEAR; //перейдем в режим перевода года
					button1state=1;
				}
			}
			if (clockmode==CLOCKMODEMONTH) button1state=0;//сбросим статус
			if(ButtonPress(2)==2)//Кнопка 2 нажата
			ModifyRTC(2,0);//2-месяц,0-назад
			if(ButtonPress(3)==3)//Кнопка 3 нажата
			ModifyRTC(2,1);//2-месяц,1-вперед
		}
		sendchar('.');
		if(clockmode!=CLOCKMODEYEAR)
		{
			sendchar('2');
			sendchar('0');
			sendchar(year/10+0x30);//Преобразуем число в код числа
			sendchar(year%10+0x30);//Преобразуем число в код числа
		}
		else //если режим перевода года
		{
			if (blinkstate==0)
			{
				sendchar(' ');
				sendchar(' ');
				sendchar(' ');
				sendchar(' ');
				blinkstate=1;
			}
			else
			{
				sendchar('2');
				sendchar('0');
				sendchar(year/10+0x30);//Преобразуем число в код числа
				sendchar(year%10+0x30);//Преобразуем число в код числа
				blinkstate=0;
			}
			if(ButtonPress(1)==1)//Кнопка 1 нажата
			{
				if(button1state==0) //опросим статус, чтобы сразу не перейти в режим перевода месяца
				{
					clockmode=CLOCKMODEDAY; //перейдем в режим перевода дня недели
					button1state=1;
				}
			}
			if (clockmode==CLOCKMODEYEAR) button1state=0;//сбросим статус
			if(ButtonPress(2)==2)//Кнопка 2 нажата
			ModifyRTC(3,0);//3-год,0-назад
			if(ButtonPress(3)==3)//Кнопка 3 нажата
			ModifyRTC(3,1);//3-год,1-вперед
		}
		sendchar(' ');
		if(clockmode!=CLOCKMODEDAY)
		{
			sendchar('-');
			sendchar(day+0x30);//Преобразуем число в код числа
			sendchar('-');
		}
		else //если режим перевода года
		{
			if (blinkstate==0)
			{
				sendchar(' ');
				sendchar(' ');
				sendchar(' ');
				blinkstate=1;
			}
			else
			{
				sendchar('-');
				sendchar(day+0x30);//Преобразуем число в код числа
				sendchar('-');
				blinkstate=0;
			}
			if(ButtonPress(1)==1)//Кнопка 1 нажата
			{
				if(button1state==0)
				{
					clockmode=CLOCKMODEHOUR; //перейдем в режим перевода часов
					button1state=1;
				}
			}
			if (clockmode==CLOCKMODEDAY) button1state=0;//сбросим статус
			if(ButtonPress(2)==2)//Кнопка 2 нажата
			ModifyRTC(4,0);//4-день недели,0-назад
			if(ButtonPress(3)==3)//Кнопка 3 нажата
			ModifyRTC(4,1);//4-день недели,1-вперед
		}
		lcd_gotoxy(0,1); //Ставим курсор на начало координат
		if(clockmode!=CLOCKMODEHOUR)
		{
			sendchar(hour/10+0x30);//Преобразуем число в код числа
			sendchar(hour%10+0x30);//Преобразуем число в код числа
		}
		else //если режим перевода часов
		{
			if (blinkstate==0)
			{
				sendchar(' ');
				sendchar(' ');
				blinkstate=1;
			}
			else
			{
				sendchar(hour/10+0x30);//Преобразуем число в код числа
				sendchar(hour%10+0x30);//Преобразуем число в код числа
				blinkstate=0;
			}
			if(ButtonPress(1)==1)//Кнопка 1 нажата
			{
				if(button1state==0) //опросим статус, чтобы сразу не перейти в режим перевода месяца
				{
					clockmode=CLOCKMODEMIN; //перейдем в режим перевода минут
					button1state=1;
				}
			}
			if (clockmode==CLOCKMODEHOUR) button1state=0;//сбросим статус
			if(ButtonPress(2)==2)//Кнопка 2 нажата
			ModifyRTC(5,0);//5-часы,0-назад
			if(ButtonPress(3)==3)//Кнопка 3 нажата
			ModifyRTC(5,1);//5-часы,1-вперед
		}
		sendchar(':');
		if(clockmode!=CLOCKMODEMIN)
		{
			sendchar(min/10+0x30);//Преобразуем число в код числа
			sendchar(min%10+0x30);//Преобразуем число в код числа
		}
		else //если режим перевода минут
		{
			if (blinkstate==0)
			{
				sendchar(' ');
				sendchar(' ');
				blinkstate=1;
			}
			else
			{
				sendchar(min/10+0x30);//Преобразуем число в код числа
				sendchar(min%10+0x30);//Преобразуем число в код числа
				blinkstate=0;
			}
			if(ButtonPress(1)==1)//Кнопка 1 нажата
			{
				if(button1state==0) //опросим статус, чтобы сразу не перейти в режим перевода месяца
				{
					clockmode=CLOCKMODESEC; //перейдем в режим синхронизации секунд
					button1state=1;
				}
			}
			if (clockmode==CLOCKMODEMIN) button1state=0;//сбросим статус
			if(ButtonPress(2)==2)//Кнопка 2 нажата
			ModifyRTC(6,0);//6-минуты,0-назад
			if(ButtonPress(3)==3)//Кнопка 3 нажата
			ModifyRTC(6,1);//6-минуты,1-вперед
		}
		sendchar(':');
		if(clockmode!=CLOCKMODESEC)
		{
			sendchar(sec/10+0x30);//Преобразуем число в код числа
			sendchar(sec%10+0x30);//Преобразуем число в код числа
		}
		else //если режим синхронизации секунд
		{
			if (blinkstate==0)
			{
				sendchar(' ');
				sendchar(' ');
				blinkstate=1;
			}
			else
			{
				sendchar(sec/10+0x30);//Преобразуем число в код числа
				sendchar(sec%10+0x30);//Преобразуем число в код числа
				blinkstate=0;
			}
			if(ButtonPress(1)==1)//Кнопка 1 нажата
			{
				if(button1state==0)
				{
					clockmode=CLOCKMODE0; //перейдем в обычный режим хода
					button1state=1;
				}
			}
			if (clockmode==CLOCKMODESEC) button1state=0;//сбросим статус
			if(ButtonPress(2)==2)//Кнопка 2 нажата
			ModifyRTC(7,0);//7-минуты,0-установка 30
			if(ButtonPress(3)==3)//Кнопка 3 нажата
			ModifyRTC(7,1);//7-минуты,1-установка 0
		}
		sendchar(' ');
		tt = converttemp(dt_check()); //измеряем температуру
		sendchar(tt/10+0x30);//Преобразуем число в код числа
		sendchar(tt%10+0x30);//Преобразуем число в код числа
		sendchar('\xdf');
		sendchar('C');
	}
}
