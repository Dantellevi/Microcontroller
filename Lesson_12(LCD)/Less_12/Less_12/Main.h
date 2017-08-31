/*
 * Main.h
 *
 * Created: 10.08.2016 20:48:09
 *  Author: Dante_L_Levi
 */ 


#ifndef MAIN_H_
#define MAIN_H_


#define F_CPU 8000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include "LCD_lib.h"
//----------------------------

#define e1 PORTD|=0b00001000;//устанавливаем линию E в единицу

#define e0 PORTD&=0b11110111;//установка e в 0

#define rs1 PORTD|=0b00000100;//

#define rs0 PORTD&=0b11111011;

//--------------------------------


#endif 