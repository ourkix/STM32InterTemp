#ifndef __STMTEMP_H
#define __STMTEMP_H
#include "stm32f10x.h"

void User_Adc_Init(void);
uint16_t Get_Temp(void);
uint16_t Get_Adc(uint8_t ch);
uint16_t Get_Adc_Average(uint8_t ch,uint8_t times);
short Get_Temprate(void);
uint8_t HexToChar(unsigned char temp);
void DecToChar(unsigned char *s,unsigned char *d,unsigned char DataCnt);
#endif
