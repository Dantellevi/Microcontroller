


#ifndef LCD_LIB_H_
#define LCD_LIB_H_

#include "Main.h"

void LCD_ini(void);
void lcd_gotoxy(unsigned char x, unsigned char y);
void lcd_clear();
void lcd_print(char str1[]);
void sendbyte(unsigned char c,unsigned char mode);
void sendchar(unsigned char c);
void sendhalfbyte(unsigned char c);


#define e1 PORTD|=0b00001000;//������������� ����� E � �������

#define e0 PORTD&=0b11110111;//��������� e � 0

#define rs1 PORTD|=0b00000100;//

#define rs0 PORTD&=0b11111011;



#endif 