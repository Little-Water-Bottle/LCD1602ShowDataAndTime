#include <reg52.h>
#include <intrins.h>
#include "Timer.h"
#include "LM016L.h"
#include "Data.h"
#include "Button.h"

//num1:���ʼֵ num2:�ֳ�ʼֵ num3:ʱ��ʼֵ
int num1=55,num2=59,num3=23;
//char num11='0',num22='0',num33='0';

//����ÿ�����ֵĸ�λ��ʮλ/
static char t_shi1,t_ge1,t_shi2,t_ge2,t_shi3,t_ge3;

static int i=0;	//���жϼ���ʹ��

char blink_flag=0;	//����ʱ����˸��־	0 ������1��˸
									  	

void TimerShow()
{
	//ʱ�䴦��
	NumDeal(num1,num2,num3);

	WriteAddress(0x40); // д Time ����ʾ��ַ , ���ڵ� 2 �е� 1 �п�ʼ��ʾ

	//ʱ��ʾ
	WriteData(t_shi3);
	WriteData(t_ge3);
	
	//��ʾ��� -
	WriteData(0x3A);

	//����ʾ
	WriteData(t_shi2);
	WriteData(t_ge2);

	//��ʾ��� -
	WriteData(0x3A);
	//����ʾ	
	WriteData(t_shi1);
	WriteData(t_ge1);

//	//��ʾ�¶ȷ���
//	WriteData(0x00);
				
//	WriteInstruction(0x01);

}

/***********************************************************
*������		��NumDeal
*����		����ֵ������Ҫ��ʾ�����ִ���ɶ�Ӧ�ַ�
*����		��num1 ��	num2 ��	  num3 ʱ
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
* �� �� ��         : BlinkDeal
* ��������		   : ��˸����
* ����			   ����
*******************************************************************************/
void BlinkDeal()
{
	switch(button_num1)
	{
		case 0: break;
		case 1:	
		if(blink_flag ==1)  //������λ��0.25��
		{
			if(button_num2 ==0)	//ʱ����˸����
			{
				t_shi3=' ';
				t_ge3=' ';
			}
			else	//������˸����
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
			if(button_num2 ==0)	//ʱ����˸����
			{
				t_shi2=' ';
				t_ge2=' ';
			}
			else	//������˸����
			{
				d_shi2=' ';
				d_ge2=' ';
			}
		} 
		break;
		case 3: 
		if(blink_flag == 1)
		{
			if(button_num2 ==0)	//ʱ����˸����
			{
				t_shi1=' ';
				t_ge1=' ';
			}
			else	//������˸����
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
* �� �� ��         : TimerInit
* ��������		   : ��ʱ��0��ʼ��
* ����			   ����
*******************************************************************************/
void TimerInit()
{
	TMOD|=0X01;	//ѡ��Ϊ��ʱ��0ģʽ��������ʽ1������TR0��������
	TH0=0X4C;	//����ʱ������ֵ����ʱ50ms 		3CB0
	TL0=0X00;	//0X3CB0��ʮ������15536 ��15536������65536����50000�� ��50000us=50ms	
	ET0=1;		//�򿪶�ʱ��0�ж�����
	EA=1;		//�����ж�
	TR0=1;		//�򿪶�ʱ��	

}

/*******************************************************************************
* �� �� ��         : Timer0()
* ��������		   : ��ʱ��0�жϺ���
* ����			   ����
*******************************************************************************/		
void Timer0() interrupt 1
{
	 TH0=0x4C;
	 TL0=0x00;
	 i++;

	//ʹ��setting_flag 0.2��ת��һ��
	if(i%10<5)
	{
		blink_flag = 0;
	}
	if(i%10>=5)
	{
		blink_flag = 1;
	}

	 if(i==20)//20��50���뼴һ��
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
				if(num2==60)//��ʱһСʱ�Զ�����
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
						//���ڴ���
						DataDeal1();
					}
				}	
			}
		}		
}