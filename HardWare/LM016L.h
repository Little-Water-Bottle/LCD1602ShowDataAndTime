#ifndef LM016L_H
#define LM016L_H

void LcdInitiate(void);
void WriteAddress(unsigned char x);
void WriteData(char y);
void WriteInstruction(unsigned char dictate);
void delaynms(unsigned char n);

bit BusyTest(void);

void LCD1602_WriteData(unsigned int LCD1602_data);
void CgramWrite(void);

#endif