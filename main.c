#include <reg52.h>
#include "LM016L.h"
#include "Timer.h"
#include "Data.h"
#include "Button.h"
#include "temp.h"

/*******************************************************************************
* 函 数 名       : main
* 函数功能		 : 主函数 程序入口
* 参数			 ：无
*******************************************************************************/
void main()
{
	LcdInitiate();	//液晶屏初始化
	TimerInit();   	//定时器初始化
//	Ds18b20Init();	//温度传感器初始化	
	while(1)
	{
		 KeyScan();
		 button_setting();
		 button_up_down();
		 ButtonSwitchDT();

		 TimerShow();
		 DataShow();
		 Lcd_Tem_Display(Ds18b20ReadTemp());

//		 ShowTemperature();
//		 CgramWrite();
	}	
}

