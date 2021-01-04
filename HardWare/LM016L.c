#include <reg52.h>
#include <intrins.h>
#include "LM016L.h"
#include "main.h"

//引脚定义
sbit RS=P2^0;
sbit RW=P2^1;
sbit E=P2^2;
sbit BF=P0^7;

void delay1ms()
{
	unsigned char i,j;
	for(i=0;i<10;i++)
	for(j=0;j<33;j++);
}

/*****************************************************
函数功能：延时若干毫秒
入口参数： n
***************************************************/
void delaynms(unsigned char n)
{
	unsigned char i;
	for(i=0;i<n;i++)
	delay1ms();
}

/********************
函数功能：判断液晶模块是否忙碌
入口参数：无
返回值：result  1忙碌 0空闲
**********************/
bit BusyTest(void)
{
	bit result;
	RS=0;
	RW=1;//此时才可以读状态

	E=0;		//加上一点延时，否则在显示第二位时显示高阻态会不显示
	_nop_();
	_nop_();
	_nop_();
	_nop_();

	E=1;//此时才允许读写
	_nop_();
	_nop_();
	_nop_();
	_nop_();//四个空操作，给硬件反应时间
	result=BF;//将忙碌标值赋值给result
	E=0;
	return result;
}






/*****************************************************
函数功能：指定字符显示的实际地址
入口参数： x
***************************************************/
void WriteAddress(unsigned char x)
{
	WriteInstruction(x|0x80); // 显示位置的确定方法规定为 "80H+地址码 x"
}

/*****************************************************
函数功能：将模式设置指令或显示地址写入液晶模块
入口参数： dictate
***************************************************/
void WriteInstruction(unsigned char dictate)
{
	while(BusyTest()==1);
	RS=0;
	RW=0;
	E=0;
	_nop_();
  _nop_();
	P0=dictate;
	_nop_();
  _nop_();
  _nop_();
  _nop_(); // 空操作四个机器周期，给硬件反应时间
  E=1;
	_nop_();
  _nop_();
  _nop_();
  _nop_(); // 空操作四个机器周期，给硬件反应时间
  E=0;
}


/*****************************************************
函数功能：将数据 (字符的标准 ASCII 码) 写入液晶模块
入口参数： y( 为字符常量 )
***************************************************/
void WriteData(char y)
{
	while(BusyTest()==1);

	RS=1; //RS 为高电平， RW为低电平时，可以写入数据
	RW=0;
	E=0; //E 置低电平 ( 根据表 8-6 ，写指令时， E 为高脉冲，
	// 就是让 E 从 0 到 1 发生正跳变，所以应先置 "0"
	P0=y; // 将数据送入 P0 口，即将数据写入液晶模块
	_nop_();
	_nop_();
	_nop_();
	_nop_(); // 空操作四个机器周期，给硬件反应时间
	E=1; //E 置高电平
	_nop_();
	_nop_();
	_nop_();
	_nop_(); // 空操作四个机器周期，给硬件反应时间
	E=0; // 当 E 由高电平跳变成低电平时，液晶模块开始执行命令
}








/*****************************************************
函数功能：对 LCD的显示模式进行初始化设置
***************************************************/
void LcdInitiate(void)
{
	delaynms(100); // 延时 15ms，首次写指令时应给 LCD一段较长的反应时间
//	WriteInstruction(0x38); // 显示模式设置： 16×2 显示， 5×7 点阵， 8 位数据接口
//	delaynms(5); // 延时 5ms ，给硬件一点反应时间
	WriteInstruction(0x38);
	delaynms(5); // 延时 5ms ，给硬件一点反应时间
	WriteInstruction(0x38); // 连续三次，确保初始化成功
	delaynms(5); // 延时 5ms ，给硬件一点反应时间
	WriteInstruction(0x0c); // 显示模式设置：显示开，无光标，光标不闪烁	0x0f光标闪烁
	delaynms(5); // 延时 5ms ，给硬件一点反应时间
	WriteInstruction(0x06); // 显示模式设置：光标右移，字符不移
	delaynms(5); // 延时 5ms ，给硬件一点反应时间
	WriteInstruction(0x01); // 清屏幕指令，将以前的显示内容清除
	delaynms(5); // 延时 5ms ，给硬件一点反应时间
	CgramWrite();//向CGRAM写入自定义字符
	delaynms(5); // 延时 5ms ，给硬件一点反应时间
}


///////////////////////////////////////////////////////////////////////

// 写数据程序 //
void LCD1602_WriteData(unsigned int LCD1602_data)
{ 
   while(BusyTest()==1);
   RS = 1;
   RW = 0;
   E=0;
   P0 = LCD1602_data;
   	_nop_();
	_nop_();
	_nop_();
	_nop_();
   	E=1;
   	_nop_();
	_nop_();
	_nop_();
	_nop_();
   E = 0;
   delaynms(5);  // 修改延时，改变显示速度
}


// 自定义字符 一共可写入16个自字义字符，写入后可用其CGRAM代码直接提取显示。
unsigned int code Xword[]={
    0x18,0x18,0x07,0x08,0x08,0x08,0x07,0x00,  //℃，代码 0x00
    0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,  //一，代码 0x01
    0x00,0x00,0x00,0x0e,0x00,0xff,0x00,0x00,  //二，代码 0x02
    0x00,0x00,0xff,0x00,0x0e,0x00,0xff,0x00,  //三，代码 0x03
    0x00,0x00,0xff,0xf5,0xfb,0xf1,0xff,0x00,  //四，代码 0x04
    0x00,0xfe,0x08,0xfe,0x0a,0x0a,0xff,0x00,  //五，代码 0x05
    0x00,0x04,0x00,0xff,0x00,0x0a,0x11,0x00,  //六，代码 0x06
    0x00,0x1f,0x11,0x1f,0x11,0x11,0x1f,0x00  //日，代码 0x07
};

void CgramWrite(void)   // 装入CGRAM //
{ 
    unsigned int i;
    WriteInstruction(0x06);   // CGRAM地址自动加1
    WriteInstruction(0x40);   // CGRAM地址设为00处
//	WriteAddress(0x40);
    for(i=0;i<64;i++) 
	{
    LCD1602_WriteData(Xword[i]);// 按数组写入数据
    }
//	LCD1602_WriteData(0x00);
}

