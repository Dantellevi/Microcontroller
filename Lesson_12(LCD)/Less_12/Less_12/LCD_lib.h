


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



#endif 