#include <reg52.h>
#include "LM016L.h"
#include "Timer.h"
#include "Data.h"
#include "Button.h"
#include "temp.h"

/*******************************************************************************
* �� �� ��       : main
* ��������		 : ������ �������
* ����			 ����
*******************************************************************************/
void main()
{
	LcdInitiate();	//Һ������ʼ��
	TimerInit();   	//��ʱ����ʼ��
//	Ds18b20Init();	//�¶ȴ�������ʼ��	
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

