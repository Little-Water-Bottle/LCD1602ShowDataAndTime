#ifndef __TEMP_H_
#define __TEMP_H_

#include<reg52.h>
sbit DSPORT=P3^1;

void Delay1ms(unsigned int y);
unsigned char Ds18b20Init();
void Ds18b20WriteByte(unsigned char com);
unsigned char Ds18b20ReadByte();
void  Ds18b20ChangTemp();
void  Ds18b20ReadTempCom();
int Ds18b20ReadTemp();
void Lcd_Tem_Display(int temp);//ÎÂ¶ÈÏÔÊ¾º¯Êý


#endif
