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
	BUTTONDDR &= ~((1<<BUTTONDDR3)|(1<<BUTTONDDR2)|(1<<BUTTONDDR1));//����� ������ �� ����
	BUTTONPORT |= (1<<BUTTONPORT3)|(1<<BUTTONPORT2)|(1<<BUTTONPORT1);//�������� ��������� � ������ ������
}
//----------------------------------------
void ModifyRTC(char index, char direction)
{
	I2C_StartCondition();
	I2C_SendByte(0b11010000);
	switch(index){
		case 1: //����� ����
		I2C_SendByte(4);//��������� �� 0x04 - ���� ����� ����
		//������
		if (direction==1)
		{
			if (month==2) //�������
			{
				if(year%4==0) //���������� ���
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
		//�����
		if (direction==0)
		{
			if (month==2) //�������
			{
				if(year%4==0) //���������� ���
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
		case 2: //�����
		I2C_SendByte(5);//��������� �� 0x05 - ���� ������
		//������
		if (direction==1)
		{
			if(month<12) I2C_SendByte(RTC_ConvertFromBinDec(month+1));
			else I2C_SendByte(RTC_ConvertFromBinDec(1));
		}
		//�����
		if (direction==0)
		{
			if(month>1) I2C_SendByte(RTC_ConvertFromBinDec(month-1));
			else I2C_SendByte(RTC_ConvertFromBinDec(12));
		}
		break;
		case 3: //���
		I2C_SendByte(6);//��������� �� 0x06 - ���� ����
		//������
		if (direction==1)
		{
			if(year<99) I2C_SendByte(RTC_ConvertFromBinDec(year+1));
			else I2C_SendByte(RTC_ConvertFromBinDec(1));
		}
		//�����
		if (direction==0)
		{
			if(year>1) I2C_SendByte(RTC_ConvertFromBinDec(year-1));
			else I2C_SendByte(RTC_ConvertFromBinDec(99));
		}
		break;
		case 4: //���� ������
		I2C_SendByte(3);//��������� �� 0x03 - ���� ��� ������
		//������
		if (direction==1)
		{
			if(day<7) I2C_SendByte(RTC_ConvertFromBinDec(day+1));
			else I2C_SendByte(RTC_ConvertFromBinDec(1));
		}
		//�����
		if (direction==0)
		{
			if(day>1) I2C_SendByte(RTC_ConvertFromBinDec(day-1));
			else I2C_SendByte(RTC_ConvertFromBinDec(7));
		}
		break;
		case 5: //����
		I2C_SendByte(2);//��������� �� 0x02 - ���� �����
		//������
		if (direction==1)
		{
			if(hour<23) I2C_SendByte(RTC_ConvertFromBinDec(hour+1));
			else I2C_SendByte(RTC_ConvertFromBinDec(0));
		}
		//�����
		if (direction==0)
		{
			if(hour>0) I2C_SendByte(RTC_ConvertFromBinDec(hour-1));
			else I2C_SendByte(RTC_ConvertFromBinDec(23));
		}
		break;
		case 6: //������
		I2C_SendByte(1);//��������� �� 0x01 - ���� �����
		//������
		if (direction==1)
		{
			if(min<59) I2C_SendByte(RTC_ConvertFromBinDec(min+1));
			else I2C_SendByte(RTC_ConvertFromBinDec(0));
		}
		//�����
		if (direction==0)
		{
			if(min>0) I2C_SendByte(RTC_ConvertFromBinDec(min-1));
			else I2C_SendByte(RTC_ConvertFromBinDec(59));
		}
		break;
		case 7: //�������
		I2C_SendByte(0);//��������� �� 0x00 - ���� ������
		//����� ������ � 0
		if (direction==1)
		{
			I2C_SendByte(RTC_ConvertFromBinDec(0));
		}
		//����� ������ � 30
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
			if(!(BUTTONPIN&(1<<BUTTONPIN1)))//������ 1 ������
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
			if(!(BUTTONPIN&(1<<BUTTONPIN2)))//������ 2 ������
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
			if(!(BUTTONPIN&(1<<BUTTONPIN3)))//������ 3 ������
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
	unsigned int tt=0; //���������� ��� �������� �����������
	unsigned char button1state=0;//������ ������ 1
	unsigned char clockmode=CLOCKMODE0;//������� ����� ��������� �������
	char blinkstate=0;//���������� ��� ������� ������������ ����������� �� �������
	
	//������������� �����
// 	   	I2C_StartCondition();
// 	 	I2C_SendByte(0b11010000);
// 	   	I2C_SendByte(0);//��������� �� 0x00
// 	   	I2C_SendByte(RTC_ConvertFromBinDec(0)); //�������
// 	  	I2C_SendByte(RTC_ConvertFromBinDec(14)); //������
// 	  	I2C_SendByte(RTC_ConvertFromBinDec(19)); //����
// 	   	I2C_SendByte(RTC_ConvertFromBinDec(1)); //���� ������
// 	   	I2C_SendByte(RTC_ConvertFromBinDec(22)); //����
// 	   	I2C_SendByte(RTC_ConvertFromBinDec(8)); //�����
// 	   	I2C_SendByte(RTC_ConvertFromBinDec(16)); //���
// 	   	I2C_StopCondition();
	
	
	
	port_ini(); //�������������� �����
	I2C_Init(); //�������������� ���� I2C
	LCD_ini();  //�������������� �������
	lcd_clear(); //������� �������
	
	
	
	while(1)
	{
		//������ �����
		I2C_SendByteByADDR(0,0b11010000);	//��������� �� ����� 0
		_delay_ms(50);
		I2C_StartCondition(); //�������� ������� START
		I2C_SendByte(0b11010001); //�������� � ���������� ��� ������
		sec = I2C_ReadByte();
		min = I2C_ReadByte();
		hour = I2C_ReadByte();
		day = I2C_ReadByte();
		date = I2C_ReadByte();
		month = I2C_ReadByte();
		year = I2C_ReadLastByte();
		I2C_StopCondition(); //�������� ������� STOP
		sec = RTC_ConvertFromDec(sec); //����������� � ���������� ������
		min = RTC_ConvertFromDec(min); //����������� � ���������� ������
		hour = RTC_ConvertFromDec(hour); //����������� � ���������� ������
		day = RTC_ConvertFromDec(day); //����������� � ���������� ������
		year = RTC_ConvertFromDec(year); //����������� � ���������� ������
		month = RTC_ConvertFromDec(month); //����������� � ���������� ������
		date = RTC_ConvertFromDec(date); //����������� � ���������� ������
		lcd_gotoxy(0,0); //������ ������ �� ������ ���������
		if(ButtonPress(1)==1)//������ 1 ������
		{
			if (clockmode==CLOCKMODE0)
			{
				clockmode=CLOCKMODEDATE;//�������� � ����� �������� ����
				blinkstate=0;//������� ������� �������
				button1state=1;//������ 1 ������
			}
		}
		if(clockmode!=CLOCKMODEDATE)
		{
			sendchar(date/10+0x30);//����������� ����� � ��� �����
			sendchar(date%10+0x30);//����������� ����� � ��� �����
		}
		else //���� ����� �������� ����
		{
			if (blinkstate==0)
			{
				sendchar(' ');
				sendchar(' ');
				blinkstate=1;
			}
			else
			{
				sendchar(date/10+0x30);//����������� ����� � ��� �����
				sendchar(date%10+0x30);//����������� ����� � ��� �����
				blinkstate=0;
			}
			if(ButtonPress(1)==1)//������ 1 ������
			{
				if(button1state==0) //������� ������, ����� ����� �� ������� � ����� �������� ������
				{
					clockmode=CLOCKMODEMONTH; //�������� � ����� �������� ������
					button1state=1;
				}
			}
			if (clockmode==CLOCKMODEDATE) button1state=0;//������� ������
			if(ButtonPress(2)==2)//������ 2 ������
			ModifyRTC(1,0);//1-����,0-�����
			if(ButtonPress(3)==3)//������ 3 ������
			ModifyRTC(1,1);//1-����,1-������
		}
		sendchar('.');
		if(clockmode!=CLOCKMODEMONTH)
		{
			sendchar(month/10+0x30);//����������� ����� � ��� �����
			sendchar(month%10+0x30);//����������� ����� � ��� �����
		}
		else //���� ����� �������� ������
		{
			if (blinkstate==0)
			{
				sendchar(' ');
				sendchar(' ');
				blinkstate=1;
			}
			else
			{
				sendchar(month/10+0x30);//����������� ����� � ��� �����
				sendchar(month%10+0x30);//����������� ����� � ��� �����
				blinkstate=0;
			}
			if(ButtonPress(1)==1)//������ 1 ������
			{
				if(button1state==0) //������� ������, ����� ����� �� ������� � ����� �������� ������
				{
					clockmode=CLOCKMODEYEAR; //�������� � ����� �������� ����
					button1state=1;
				}
			}
			if (clockmode==CLOCKMODEMONTH) button1state=0;//������� ������
			if(ButtonPress(2)==2)//������ 2 ������
			ModifyRTC(2,0);//2-�����,0-�����
			if(ButtonPress(3)==3)//������ 3 ������
			ModifyRTC(2,1);//2-�����,1-������
		}
		sendchar('.');
		if(clockmode!=CLOCKMODEYEAR)
		{
			sendchar('2');
			sendchar('0');
			sendchar(year/10+0x30);//����������� ����� � ��� �����
			sendchar(year%10+0x30);//����������� ����� � ��� �����
		}
		else //���� ����� �������� ����
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
				sendchar(year/10+0x30);//����������� ����� � ��� �����
				sendchar(year%10+0x30);//����������� ����� � ��� �����
				blinkstate=0;
			}
			if(ButtonPress(1)==1)//������ 1 ������
			{
				if(button1state==0) //������� ������, ����� ����� �� ������� � ����� �������� ������
				{
					clockmode=CLOCKMODEDAY; //�������� � ����� �������� ��� ������
					button1state=1;
				}
			}
			if (clockmode==CLOCKMODEYEAR) button1state=0;//������� ������
			if(ButtonPress(2)==2)//������ 2 ������
			ModifyRTC(3,0);//3-���,0-�����
			if(ButtonPress(3)==3)//������ 3 ������
			ModifyRTC(3,1);//3-���,1-������
		}
		sendchar(' ');
		if(clockmode!=CLOCKMODEDAY)
		{
			sendchar('-');
			sendchar(day+0x30);//����������� ����� � ��� �����
			sendchar('-');
		}
		else //���� ����� �������� ����
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
				sendchar(day+0x30);//����������� ����� � ��� �����
				sendchar('-');
				blinkstate=0;
			}
			if(ButtonPress(1)==1)//������ 1 ������
			{
				if(button1state==0)
				{
					clockmode=CLOCKMODEHOUR; //�������� � ����� �������� �����
					button1state=1;
				}
			}
			if (clockmode==CLOCKMODEDAY) button1state=0;//������� ������
			if(ButtonPress(2)==2)//������ 2 ������
			ModifyRTC(4,0);//4-���� ������,0-�����
			if(ButtonPress(3)==3)//������ 3 ������
			ModifyRTC(4,1);//4-���� ������,1-������
		}
		lcd_gotoxy(0,1); //������ ������ �� ������ ���������
		if(clockmode!=CLOCKMODEHOUR)
		{
			sendchar(hour/10+0x30);//����������� ����� � ��� �����
			sendchar(hour%10+0x30);//����������� ����� � ��� �����
		}
		else //���� ����� �������� �����
		{
			if (blinkstate==0)
			{
				sendchar(' ');
				sendchar(' ');
				blinkstate=1;
			}
			else
			{
				sendchar(hour/10+0x30);//����������� ����� � ��� �����
				sendchar(hour%10+0x30);//����������� ����� � ��� �����
				blinkstate=0;
			}
			if(ButtonPress(1)==1)//������ 1 ������
			{
				if(button1state==0) //������� ������, ����� ����� �� ������� � ����� �������� ������
				{
					clockmode=CLOCKMODEMIN; //�������� � ����� �������� �����
					button1state=1;
				}
			}
			if (clockmode==CLOCKMODEHOUR) button1state=0;//������� ������
			if(ButtonPress(2)==2)//������ 2 ������
			ModifyRTC(5,0);//5-����,0-�����
			if(ButtonPress(3)==3)//������ 3 ������
			ModifyRTC(5,1);//5-����,1-������
		}
		sendchar(':');
		if(clockmode!=CLOCKMODEMIN)
		{
			sendchar(min/10+0x30);//����������� ����� � ��� �����
			sendchar(min%10+0x30);//����������� ����� � ��� �����
		}
		else //���� ����� �������� �����
		{
			if (blinkstate==0)
			{
				sendchar(' ');
				sendchar(' ');
				blinkstate=1;
			}
			else
			{
				sendchar(min/10+0x30);//����������� ����� � ��� �����
				sendchar(min%10+0x30);//����������� ����� � ��� �����
				blinkstate=0;
			}
			if(ButtonPress(1)==1)//������ 1 ������
			{
				if(button1state==0) //������� ������, ����� ����� �� ������� � ����� �������� ������
				{
					clockmode=CLOCKMODESEC; //�������� � ����� ������������� ������
					button1state=1;
				}
			}
			if (clockmode==CLOCKMODEMIN) button1state=0;//������� ������
			if(ButtonPress(2)==2)//������ 2 ������
			ModifyRTC(6,0);//6-������,0-�����
			if(ButtonPress(3)==3)//������ 3 ������
			ModifyRTC(6,1);//6-������,1-������
		}
		sendchar(':');
		if(clockmode!=CLOCKMODESEC)
		{
			sendchar(sec/10+0x30);//����������� ����� � ��� �����
			sendchar(sec%10+0x30);//����������� ����� � ��� �����
		}
		else //���� ����� ������������� ������
		{
			if (blinkstate==0)
			{
				sendchar(' ');
				sendchar(' ');
				blinkstate=1;
			}
			else
			{
				sendchar(sec/10+0x30);//����������� ����� � ��� �����
				sendchar(sec%10+0x30);//����������� ����� � ��� �����
				blinkstate=0;
			}
			if(ButtonPress(1)==1)//������ 1 ������
			{
				if(button1state==0)
				{
					clockmode=CLOCKMODE0; //�������� � ������� ����� ����
					button1state=1;
				}
			}
			if (clockmode==CLOCKMODESEC) button1state=0;//������� ������
			if(ButtonPress(2)==2)//������ 2 ������
			ModifyRTC(7,0);//7-������,0-��������� 30
			if(ButtonPress(3)==3)//������ 3 ������
			ModifyRTC(7,1);//7-������,1-��������� 0
		}
		sendchar(' ');
		tt = converttemp(dt_check()); //�������� �����������
		sendchar(tt/10+0x30);//����������� ����� � ��� �����
		sendchar(tt%10+0x30);//����������� ����� � ��� �����
		sendchar('\xdf');
		sendchar('C');
	}
}
