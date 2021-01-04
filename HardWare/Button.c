#include <reg52.h>
#include <intrins.h>
#include "Data.h"
#include "Timer.h"
#include "Button.h"



//���尴�����µĴ�������ͬ����ѡ��ͬ����
char button_num1 = 0; 	//�ж�ѡ��ʱ����
char button_num2 = 0;	//�ж��л�ʱ��/����	
char button_flag = 0x00;	//����ѡ��λ��־��


/***********************************************************
*������		��KeyScan
*����		: ����ɨ�裬���ذ��µİ�����Ӧ��λ������ֹ����
*����ֵ		�����ذ������µ�λ��
*����		����
************************************************************/
char KeyScan() 
{
	static unsigned char klast = 0;	  //��¼��һ�εİ���ֵ
	unsigned char trg = 0,key = 0;		  //trg:�õ��ķ���ֵ������ֵ��8λֻ��һλΪ1��Ϊ1��λ�����µ�λ������λΪ��
	key = P2 & 0xF0;				  //�����µ�λת��Ϊ0 û���µ�λ��ȻΪ1
	key ^= 0xF0;					  //���֮��û���µ�λת��Ϊ1�����µ�λת��Ϊ0
	trg = key & (key ^ klast);		  //�������ؼ���һ�䣬��Ҫ�Լ����
	klast = key;

	button_flag = trg;

	return trg;	  						//���շ���ֵ�ǰ����ĸ�����������ֵ��Ӧ����1��û����Ӧ�ľ���0  eg:����button3 �򷵻�0x01 0000 0100
}



/*******************************************************************************
* �� �� ��         : button_setting
* ��������		   : ѡ��Ҫ���õ�ʱ��һλ
* ����			   ����
*******************************************************************************/
void button_setting()
{
	if((button_flag & 0xf0) == 0x10 )		//���治�����Ų��� 
	{
		button_num1++;	//ѡ�����ò�ͬλ��ʱ �� �룩
		if(button_num1 == 4)
		{
			button_num1 = 0;
		}	
	}
}

/*******************************************************************************
* �� �� ��         : button_up_down
* ��������		   : ʱ���/�� �����߼�����
* ����			   ����
*******************************************************************************/
void button_up_down()
{
	if((button_flag & 0xf0) == 0x20)	//�ϱ�����	
	{
		switch(button_num1)	//button_num1 1��ʱ/��   2����/��   3����/��
		{
			case 0:	break;
			case 1:	//��/ʱ	
			if(button_num2 == 0) 	// button_num2 0 ʱ�� 1����
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
			case 2:	//��/��

			if(button_num2 == 0)
			{
				num2++;
			} 
			else
			{
				month++;
			}
			 break; 	
			case 3:	//����
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
		if(num3 == 24) num3 = 0;	//ʱ������ڳ������㴦��			
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
//			delay_us(10); while(~button3); 	   //�ȴ������ͷ�	ʱ��һ			//����Ҫ��ôд��
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
		if(num3 == -1) num3 = 23;	//ʱ������ڼ�����ѭ����
		if(num2 == -1) num2 = 59;
		if(num1 == -1) num1 = 59;
//		if(year == -1) year = 99;
		if(month == 0 ) month = 12;
		if(day == 0) day = 30;
		if(weekday==0) weekday=7;
	}
}

/*******************************************************************************
* �� �� ��         : ButtonSwitchDT
* ��������		   : ʱ��/���� ���÷����л�
* ����			   ����
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

						           								  