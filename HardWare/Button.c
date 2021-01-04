#include <reg52.h>
#include <intrins.h>
#include "Data.h"
#include "Timer.h"
#include "Button.h"



//定义按键按下的次数，不同次数选择不同设置
char button_num1 = 0; 	//判断选则时分秒
char button_num2 = 0;	//判断切换时间/日期	
char button_flag = 0x00;	//按键选择位标志，


/***********************************************************
*函数名		：KeyScan
*功能		: 按键扫描，返回按下的按键对应的位，并防止连按
*返回值		：返回按键按下的位置
*参数		：无
************************************************************/
char KeyScan() 
{
	static unsigned char klast = 0;	  //记录上一次的按键值
	unsigned char trg = 0,key = 0;		  //trg:得到的返回值，返回值中8位只有一位为1，为1的位代表按下的位，其余位为零
	key = P2 & 0xF0;				  //将按下的位转换为0 没按下的位依然为1
	key ^= 0xF0;					  //异或之后没按下的位转换为1，按下的位转换为0
	trg = key & (key ^ klast);		  //这句是最关键的一句，需要自己理解
	klast = key;

	button_flag = trg;

	return trg;	  						//最终返回值是按下哪个按键，返回值对应就是1，没按对应的就是0  eg:按下button3 则返回0x01 0000 0100
}



/*******************************************************************************
* 函 数 名         : button_setting
* 函数功能		   : 选择要设置的时哪一位
* 参数			   ：无
*******************************************************************************/
void button_setting()
{
	if((button_flag & 0xf0) == 0x10 )		//里面不加括号不行 
	{
		button_num1++;	//选择设置不同位（时 分 秒）
		if(button_num1 == 4)
		{
			button_num1 = 0;
		}	
	}
}

/*******************************************************************************
* 函 数 名         : button_up_down
* 函数功能		   : 时间加/减 按键逻辑处理
* 参数			   ：无
*******************************************************************************/
void button_up_down()
{
	if((button_flag & 0xf0) == 0x20)	//上被按中	
	{
		switch(button_num1)	//button_num1 1：时/年   2：分/月   3：秒/日
		{
			case 0:	break;
			case 1:	//年/时	
			if(button_num2 == 0) 	// button_num2 0 时间 1日期
			{
				num3++;
			} 
			else
			{
				year2++;
				if(year2>=100)
				{
					year2=0;
					year1++;
					if(year1>=100)
					{
						year1=0;
						year2=1;
					}

				}
			}
			 break; 		
			case 2:	//月/分

			if(button_num2 == 0)
			{
				num2++;
			} 
			else
			{
				month++;
			}
			 break; 	
			case 3:	//日秒
			 if(button_num2 == 0)
			{
				num1++;
			} 
			else
			{
				day++;
				weekday++;
			}
			 break;		
			default: break;	
		}
		if(num3 == 24) num3 = 0;	//时间和日期超出归零处理			
		if(num2 == 60) num2 = 0;
		if(num1 == 60) num1 = 0;
//		if(year == 100) year = 0;
		if(month == 13 ) month = 1;
		if(day == 31) day = 1;
		if(weekday==8) weekday=1;
		
	}

	if((button_flag & 0xf0) == 0x40)
	{
		switch(button_num1)
		{
			case 0:		break;
			case 1:
//			delay_us(10); while(~button3); 	   //等待按键释放	时加一			//不需要这么写了
			if(button_num2 == 0)
			{
				num3--;
			} 
			else
			{
				year2--;
				if(year2<=-1)
				{
				 	year2=99;
					year1--;
					if(year1<=-1)
					{
						year1=99;
					}

				}
			}
			 break; 		
			case 2:	
			if(button_num2 == 0)
			{
				num2--;
			} 
			else
			{
				month--;
			}
			 break; 	
			case 3:	
			 if(button_num2 == 0)
			{
				num1--;
			} 
			else
			{
				day--;
				weekday--;
			}
			 break;	
			default: break;
		}
		if(num3 == -1) num3 = 23;	//时间和日期减到低循环减
		if(num2 == -1) num2 = 59;
		if(num1 == -1) num1 = 59;
//		if(year == -1) year = 99;
		if(month == 0 ) month = 12;
		if(day == 0) day = 30;
		if(weekday==0) weekday=7;
	}
}

/*******************************************************************************
* 函 数 名         : ButtonSwitchDT
* 函数功能		   : 时间/日期 设置方案切换
* 参数			   ：无
*******************************************************************************/
void ButtonSwitchDT()
{
	 if((button_flag & 0xf0) == 0x80)
	{
		button_num2++;
		if(button_num2>=2)
		{
			button_num2=0;
		}
	}
}

						           								  