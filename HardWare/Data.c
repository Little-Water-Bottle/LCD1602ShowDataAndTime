#include <reg52.h>
#include <intrins.h>
#include "Data.h"
#include "LM016L.h"

#include "Timer.h"
#include "temp.h"

//typedef unsigned int u16;	  //���������ͽ�����������
//typedef unsigned char u8;

char d_qian1,d_bai1,d_shi1,d_ge1,d_shi2,d_ge2,d_shi3,d_ge3,weekday=1;



int year1=19,year2=99,month=12,day=29;


void DataShow()
{
	//���ڴ���
	DataDeal2(year1,year2,month,day);

	WriteAddress(0x00); // д Date ����ʾ��ַ , ���ڵ� 1 �е� 1 �п�ʼ��ʾ

	//����ʾ
	WriteData(d_qian1);
	WriteData(d_bai1);
	WriteData(d_shi1);
	WriteData(d_ge1);
	
	//��ʾ��� -
	WriteData(0x2D);

	//����ʾ
	WriteData(d_shi2);
	WriteData(d_ge2);

	//��ʾ��� -
	WriteData(0x2D);

	//����ʾ	
	WriteData(d_shi3);
	WriteData(d_ge3);

	//������ʾ
	WeekDayShow();

}

/*******************************************************************************
* �� �� ��       : DataDeal1
* ��������		 : ���ڴ��������������ڵĵ�ǰ������ֵ
* ����			 ����
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
*������		��DataDeal2
*����		����ֵ������Ҫ��ʾ�����ִ���ɶ�Ӧ�ַ�
*����		��year ��	month ��  day ��
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
*������		��WeekDayShow
*����		����Ӧ������ʾ����
*����		����
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