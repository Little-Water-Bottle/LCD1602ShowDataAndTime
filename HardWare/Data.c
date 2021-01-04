#include <reg52.h>
#include <intrins.h>
#include "Data.h"
#include "LM016L.h"

#include "Timer.h"
#include "temp.h"

//typedef unsigned int u16;	  //对数据类型进行声明定义
//typedef unsigned char u8;

char d_qian1,d_bai1,d_shi1,d_ge1,d_shi2,d_ge2,d_shi3,d_ge3,weekday=1;



int year1=19,year2=99,month=12,day=29;


void DataShow()
{
	//日期处理
	DataDeal2(year1,year2,month,day);

	WriteAddress(0x00); // 写 Date 的显示地址 , 将在第 1 行第 1 列开始显示

	//年显示
	WriteData(d_qian1);
	WriteData(d_bai1);
	WriteData(d_shi1);
	WriteData(d_ge1);
	
	//显示横杠 -
	WriteData(0x2D);

	//月显示
	WriteData(d_shi2);
	WriteData(d_ge2);

	//显示横杠 -
	WriteData(0x2D);

	//日显示	
	WriteData(d_shi3);
	WriteData(d_ge3);

	//星期显示
	WeekDayShow();

}

/*******************************************************************************
* 函 数 名       : DataDeal1
* 函数功能		 : 日期处理函数，计算日期的当前的日期值
* 参数			 ：无
*******************************************************************************/
void DataDeal1()
{

	if(day>=30)
	{
		month++;
		day=1;

		if(month>=13)
		{
			month = 1;
			year2++;
			if(year2>=100)
			{
				year2 = 0;
				year1++;
				if(year1>=100)
				{
					year1=0;
				}
			}
		}			
	}
}

 
/***********************************************************
*函数名		：DataDeal2
*功能		：数值处理，对要显示的数字处理成对应字符
*参数		：year 年	month 月  day 日
************************************************************/
void DataDeal2(int year1,int year2,int month,int day)
{	
	d_qian1=year1/10+'0';
	d_bai1=year1%10+'0';
	d_shi1=year2/10+'0';
	d_ge1=year2%10+'0';

	d_shi2=month/10+'0';
	d_ge2=month%10+'0';

	d_shi3=day/10+'0';
	d_ge3=day%10+'0';
	BlinkDeal();		
}

/***********************************************************
*函数名		：WeekDayShow
*功能		：对应星期显示计算
*参数		：无
************************************************************/
void WeekDayShow()
{
	WriteAddress(0x0D);
	Delay1ms(50);
	switch(weekday)
	{
		case 0: break;
		case 1: WriteData(0x01);break;
		case 2: WriteData(0x02);break;
		case 3: WriteData(0x03);break;
		case 4: WriteData(0x04);break;
		case 5: WriteData(0x05);break;
		case 6: WriteData(0x06);break;
		case 7: WriteData(0x07);break;
		
	}
}