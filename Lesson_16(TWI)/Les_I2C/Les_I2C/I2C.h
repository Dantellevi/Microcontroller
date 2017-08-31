/*
 * I2C.h
 *
 * Created: 13.08.2016 12:05:51
 *  Author: Dante_L_Levi
 */ 


#ifndef I2C_H_
#define I2C_H_

#include "Main.h"

void I2C_Init(void);
void I2C_StartCondition(void);
void I2C_StopCondion(void);
void I2C_SendByte(unsigned char c);




#endif /* I2C_H_ */