#include <reg52.h>
#include <intrins.h>
#include "Timer.h"
#include "LM016L.h"
#include "Data.h"
#include "Button.h"

//num1:秒初始值 num2:分初始值 num3:时初始值
int num1=55,num2=59,num3=23;
//char num11='0',num22='0',num33='0';

//分离每个数字的个位和十位/
static char t_shi1,t_ge1,t_shi2,t_ge2,t_shi3,t_ge3;

static int i=0;	//给中断计数使用

char blink_flag=0;	//定义时间闪烁标志	0 不闪，1闪烁
									  	

void TimerShow()
{
	//时间处理
	NumDeal(num1,num2,num3);

	WriteAddress(0x40); // 写 Time 的显示地址 , 将在第 2 行第 1 列开始显示

	//时显示
	WriteData(t_shi3);
	WriteData(t_ge3);
	
	//显示横杠 -
	WriteData(0x3A);

	//分显示
	WriteData(t_shi2);
	WriteData(t_ge2);

	//显示横杠 -
	WriteData(0x3A);
	//秒显示	
	WriteData(t_shi1);
	WriteData(t_ge1);

//	//显示温度符号
//	WriteData(0x00);
				
//	WriteInstruction(0x01);

}

/***********************************************************
*函数名		：NumDeal
*功能		：数值处理，对要显示的数字处理成对应字符
*参数		：num1 秒	num2 分	  num3 时
************************************************************/
void NumDeal(char num1,char num2,char num3)
{

	t_shi1=num1/10+'0';
	t_ge1=num1%10+'0';

	t_shi2=num2/10+'0';
	t_ge2=num2%10+'0';

	t_shi3=num3/10+'0';
	t_ge3=num3%10+'0';
	BlinkDeal();
		
}

/*******************************************************************************
* 函 数 名         : BlinkDeal
* 函数功能		   : 闪烁处理
* 参数			   ：无
*******************************************************************************/
void BlinkDeal()
{
	switch(button_num1)
	{
		case 0: break;
		case 1:	
		if(blink_flag ==1)  //被设置位灭0.25秒
		{
			if(button_num2 ==0)	//时间闪烁处理
			{
				t_shi3=' ';
				t_ge3=' ';
			}
			else	//日期闪烁处理
			{
				d_qian1=' ';
				d_bai1=' ';
				d_shi1=' ';
				d_ge1=' ';
			}
			
		} 
		break;	
		case 2:	
		if(blink_flag == 1) 
		{
			if(button_num2 ==0)	//时间闪烁处理
			{
				t_shi2=' ';
				t_ge2=' ';
			}
			else	//日期闪烁处理
			{
				d_shi2=' ';
				d_ge2=' ';
			}
		} 
		break;
		case 3: 
		if(blink_flag == 1)
		{
			if(button_num2 ==0)	//时间闪烁处理
			{
				t_shi1=' ';
				t_ge1=' ';
			}
			else	//日期闪烁处理
			{
				d_shi3=' ';
				d_ge3=' ';
			}
		} 		 
		break;
		default: break;
			
	}
}



/*******************************************************************************
* 函 数 名         : TimerInit
* 函数功能		   : 定时器0初始化
* 参数			   ：无
*******************************************************************************/
void TimerInit()
{
	TMOD|=0X01;	//选择为定时器0模式，工作方式1，仅用TR0打开启动。
	TH0=0X4C;	//给定时器赋初值，定时50ms 		3CB0
	TL0=0X00;	//0X3CB0的十进制是15536 从15536计数到65536计数50000次 即50000us=50ms	
	ET0=1;		//打开定时器0中断允许
	EA=1;		//打开总中断
	TR0=1;		//打开定时器	

}

/*******************************************************************************
* 函 数 名         : Timer0()
* 函数功能		   : 定时器0中断函数
* 参数			   ：无
*******************************************************************************/		
void Timer0() interrupt 1
{
	 TH0=0x4C;
	 TL0=0x00;
	 i++;

	//使得setting_flag 0.2秒转换一次
	if(i%10<5)
	{
		blink_flag = 0;
	}
	if(i%10>=5)
	{
		blink_flag = 1;
	}

	 if(i==20)//20个50毫秒即一秒
		{
			i=0;
		   if(button_num1==0)
		   {
		   	   num1++;
		   }
			if(num1==60)
			{
				num1=0;
				num2++;
				if(num2==60)//定时一小时自动清零
				{
					num2=0;
					num3++;
					if(num3==24)
					{
						num3=0;
						day++;
						weekday++;
						if(weekday==8)
						{
							weekday=1;
						}
						//日期处理
						DataDeal1();
					}
				}	
			}
		}		
}