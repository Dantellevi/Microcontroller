/*
 * _18b20_lib.h
 *
 * Created: 18.08.2016 17:17:21
 *  Author: Dante_L_Levi
 */ 


#ifndef ds18B20_LIB_H_
#define ds18B20_LIB_H_

#include "Main.h"
#define  NOID 0xCC //пропустить идентификацию 

#define T_CONVERT 0x44 //код измерения температуры

#define READ_DATA 0xBE //передача байтов ведущего

#define PORTTEMP PORTD
#define DDRTEMP DDRD
#define PINTEMP PIND
#define BITTEMP 1



int dt_check(void);
char converttemp(unsigned int tt);//преобразование температуры в единицы

#endif /* 18B20_LIB_H_ */