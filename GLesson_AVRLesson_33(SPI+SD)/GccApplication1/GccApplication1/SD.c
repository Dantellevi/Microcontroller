/*
 * GccApplication1.c
 *
 * Created: 09.09.2016 13:32:43
 * Author : DANTE_L_LEVI
 */ 

#include "Main.h"

#define MOSI 3
#define MISO 4
#define SCK 5
#define SS 2

char buffer[512]={"The selection of RAM is set by the previous address set instruction. If the address set instruction of RAM is not performed before this instruction, the data that has been read first is invalid, as the direction of AC is not yet determined. If RAM data is read several times without RAM address instructions set before, read operation, the correct RAM data can be obtained from the second. But the first data would be incorrect, as there is no time margin to transfer RAM data. In case of DDRAM read operation..."};
char buffer2[512]={};

void Port_ini(void)
{
	DDRD=0xFF;
	PORTD=0x00;
	PORTB|=(1<<SS)|(1<<MISO)|(1<<MOSI);
	DDRB|=(1<<SS)|(1<<MOSI)|(1<<SCK);
	
}

//---------------------------
void SPI_SendByte(unsigned char byte)
{
	unsigned char i;
	for (i=0;i<8;i++)//движемся по битам байта
	{
		if ((byte&0x80)==0x00)//	проверяем левый бит
		{
			
			PORTB&=~(1<<MOSI);//если 0 , то выстовляем 0 и на шине 
			
			
		}
		else
		{
			PORTB|=(1<<MOSI);//если 1 , то выстовляем единицу и на шине
		}
		
		byte<<=1;//сдвигаем влево , в сторону старшего для проверки следующего бита
		PORTB|=(1<<SCK);//если 1 . то выставляем 1 на шине
		asm("nop");
		PORTB&=~(1<SCK);
		
		
	}
	
}

//--------------------------
unsigned char SPI_ReceiveByte(void)
{
	unsigned char i;
	unsigned char result=0;
	for (i=0;i<8;i++)
	{
		PORTB|=(1<<SCK);
		result<<=1;//ссдвигаем влево байт, чтобы записать очередной бит
		
		if ((PINB&(1<<MISO))!=0x00)
		{
			result=result|0x01;//запишем считанный с лапки порта MISOбит
			
		}
		
		PORTB&=~(1<<SCK);
		asm("nop");
		
	}
	
	return result;//вернем результат
}

//---------------------------

unsigned char SD_cmd(char dt0,char dt1,char dt2,char dt3,char dt4,char dt5)
{
	unsigned char result;
	long int cnt;
	SPI_SendByte(dt0);//индекс
	SPI_SendByte(dt1);//Аргумент
	SPI_SendByte(dt2);
	SPI_SendByte(dt3);
	SPI_SendByte(dt4);
	SPI_SendByte(dt5);//контрольная сумма
	cnt=0;
	
	do 
	{
		//ждем ответа в формате R1()
		result=SPI_ReceiveByte();
		cnt++;
	} while (((result&0x80)!=0x00)&&cnt<0xFFFF);
	return result;
}



//---------------------------

unsigned char SD_Init(void)
{
	unsigned char i,temp;
	long int cnt;
	
	for (i=0;i<10;i++)//80 импульсов не менее 74
	{
		SPI_SendByte(0xFF);
	
	}
	PORTB&=~(1<<SS);//опускаем SS
	temp=SD_cmd(0x40,0x00,0x00,0x00,0x00,0x95);
	
	if (temp!=0x00)
	{
		return 1;//выйти если ответ не 0х01
	}
	SPI_SendByte(0xFF);
	cnt=0;
	
	
	do
	{
		temp=SD_cmd(0x41,0x00,0x00,0x00,0x00,0x95);//CMD1 передаем также меняется только индекс
		
		SPI_SendByte(0xFF);
				cnt++;
				
	} while ((temp!=0x00)&&cnt<0xFFFF);
	
	if (cnt>=0xFFFF)
	{
		return 2;
	}
	
	return 0;
}

//---------------------------

unsigned char SD_Write_Block(char*bf,unsigned char dt1,unsigned char dt2,unsigned char dt3,unsigned char dt4)
{
	unsigned char result;
	long int cnt;
	result=SD_cmd(0x58,dt1,dt2,dt3,dt4,0x95);//команда 24 
	
	if (result!=0x00)
	{
		return 3;
	}
	SPI_SendByte(0xFF);
	SPI_SendByte(0xFE);
	
	
	for (cnt=0;cnt<512;cnt++)
	{
		SPI_SendByte(bf[cnt]);//данные 
		
	}
	SPI_SendByte(0xFF);
	SPI_SendByte(0xFE);
	result=SPI_ReceiveByte();
	
	
	
	if ((result&0x05)!=0x05)
	{
		return 4;
	}
	
	cnt=0;
	
	
	do
	{
		result=SPI_ReceiveByte();
		cnt++;
		
	} while ((result!=0xFF)&&cnt<0xFFFF);
	
	if(cnt>=0xFFFF) return 5;
	
	return 0;
	}

//---------------------------


//---------------------------

unsigned char SD_Read_Block(char*bf,unsigned char dt1,unsigned char dt2,unsigned char dt3,unsigned char dt4)
{
	unsigned char result;
	long int cnt;
	result=SD_cmd(0x51,dt1,dt2,dt3,dt4,0x95);//команда 17
	
	if (result!=0x00)
	{
		return 3;
	}
	SPI_SendByte(0xFF);
	cnt=0;
	
	do
	{
		result=SPI_ReceiveByte();
		cnt++;
		
	} while ((result!=0xFE)&&cnt<0xFFFF);
	
	
	for (cnt=0;cnt<512;cnt++)
	{
		bf[cnt]=SPI_ReceiveByte();//читаем данные
		
	}
	SPI_ReceiveByte();
	SPI_ReceiveByte();
	result=SPI_ReceiveByte();
	
	return 0;
}

//---------------------------





int main(void)
{
	
	//unsigned int i;
	char str[10];
	
	unsigned char result;
	
	
	Port_ini();
	LCD_ini();
	lcd_clear();
	lcd_gotoxy(0,0);
	result=SD_Init();
	sprintf(str,"%d",result);
	lcd_clear();
	lcd_gotoxy(0,0);
	lcd_print(str);
	result=SD_Write_Block(buffer,0x00,0x00,0x04,0x00);//запишем блок из буфера
	sprintf(str,"%d",result);
	
	lcd_gotoxy(0,1);
	lcd_print(str);
	
	
	result=SD_Read_Block(buffer,0x00,0x00,0x04,0x00);//читаем блок из буфера
	sprintf(str,"%d",result);
	
	lcd_gotoxy(0,2);
	lcd_print(str);
	
	
		// 	lcd_print_80(buffer);
	// 	_delay_ms(2000);
	//
	// 	lcd_print_80(buffer+20);
	// 	_delay_ms(1000);
	// 	lcd_print_80(buffer+40);
// 	for (i=0;i<=22;i++)
// 	{
// 		lcd_print_80(buffer+i*20);
// 		_delay_ms(1000);
// 	}
	/* Replace with your application code */
	while (1)
	{
		
	}
}

