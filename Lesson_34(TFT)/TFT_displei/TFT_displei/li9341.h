/*
 * li9341.h
 *
 * Created: 19.09.2016 16:14:12
 *  Author: DANTE_L_LEVI
 */ 


#ifndef LI9341_H_
#define LI9341_H_

#include <stdlib.h>
#include <stdio.h>
#include "Main.h"
#include "TWI.h"
#include "lcdTWI.h"


#define  swap(a,b) {int16_t t=a;a=b;b=t;}
#define  DATA_DDR DDRD
#define  DATA_PORT PORTD
#define DATA_PIN PIND
#define COMMAND_PORT PORTB
#define COMMAND_DDR DDRB
#define LCD_CS 2//��� ������
#define LCD_CD 1//comand/data
#define LCD_WR 3//LCD WRITE
#define LCD_RD 4 //LCD READ
#define LCD_RESET 0//RESET
#define RESET_IDLE COMMAND_PORT|=(1<<LCD_RESET)
#define CS_IDLE COMMAND_PORT|=(1<<LCD_CS)
#define WR_IDLE COMMAND_PORT|=(1<<LCD_WR)
#define RD_IDLE COMMAND_PORT|=(1<<LCD_RD)
#define RESET_ACTIVE COMMAND_PORT&=~(1<<LCD_RESET)
#define CS_ACTIVE COMMAND_PORT&=~(1<<LCD_CS)
#define WR_ACTIVE COMMAND_PORT&=~(1<<LCD_WR)
#define RD_ACTIVE COMMAND_PORT&=~(1<<LCD_RD)
#define CD_COMMAND COMMAND_PORT&=~(1<<LCD_CD)
#define CD_DATA COMMAND_PORT|=(1<<LCD_CD)

#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0x0F800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

#define setReadDir() DATA_DDR=0x00
#define setWriteDir() DATA_DDR=0xFF



#define WR_STOBE {WR_ACTIVE;WR_IDLE;}

void TFT9341_ini(void);
void TFT9341_FillScreen(unsigned int color);
void TFT9341_FillRectangle(unsigned int color,unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);
unsigned int TFT9341_RandColor(void);
void TFT9341_DrawPixel( int x, int y,unsigned int color);
void TFT9341_DrawLine(unsigned int color,unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);
void TFT9341_DrawRect(unsigned int color,unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);
void TFT9341_DrawCircle(unsigned int x0,unsigned int y0,int r,unsigned int color);
void TFT9341_Draw_char(int x,int y,unsigned int color,unsigned int phone,unsigned char charcode,unsigned char Size);
void TFT9341_String ( unsigned int x , unsigned int y , unsigned int color , unsigned int phone ,char *str , unsigned char size );



#endif /* LI9341_H_ */