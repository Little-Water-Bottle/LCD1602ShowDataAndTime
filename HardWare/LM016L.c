#include <reg52.h>
#include <intrins.h>
#include "LM016L.h"
#include "main.h"

//���Ŷ���
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
�������ܣ���ʱ���ɺ���
��ڲ����� n
***************************************************/
void delaynms(unsigned char n)
{
	unsigned char i;
	for(i=0;i<n;i++)
	delay1ms();
}

/********************
�������ܣ��ж�Һ��ģ���Ƿ�æµ
��ڲ�������
����ֵ��result  1æµ 0����
**********************/
bit BusyTest(void)
{
	bit result;
	RS=0;
	RW=1;//��ʱ�ſ��Զ�״̬

	E=0;		//����һ����ʱ����������ʾ�ڶ�λʱ��ʾ����̬�᲻��ʾ
	_nop_();
	_nop_();
	_nop_();
	_nop_();

	E=1;//��ʱ��������д
	_nop_();
	_nop_();
	_nop_();
	_nop_();//�ĸ��ղ�������Ӳ����Ӧʱ��
	result=BF;//��æµ��ֵ��ֵ��result
	E=0;
	return result;
}






/*****************************************************
�������ܣ�ָ���ַ���ʾ��ʵ�ʵ�ַ
��ڲ����� x
***************************************************/
void WriteAddress(unsigned char x)
{
	WriteInstruction(x|0x80); // ��ʾλ�õ�ȷ�������涨Ϊ "80H+��ַ�� x"
}

/*****************************************************
�������ܣ���ģʽ����ָ�����ʾ��ַд��Һ��ģ��
��ڲ����� dictate
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
  _nop_(); // �ղ����ĸ��������ڣ���Ӳ����Ӧʱ��
  E=1;
	_nop_();
  _nop_();
  _nop_();
  _nop_(); // �ղ����ĸ��������ڣ���Ӳ����Ӧʱ��
  E=0;
}


/*****************************************************
�������ܣ������� (�ַ��ı�׼ ASCII ��) д��Һ��ģ��
��ڲ����� y( Ϊ�ַ����� )
***************************************************/
void WriteData(char y)
{
	while(BusyTest()==1);

	RS=1; //RS Ϊ�ߵ�ƽ�� RWΪ�͵�ƽʱ������д������
	RW=0;
	E=0; //E �õ͵�ƽ ( ���ݱ� 8-6 ��дָ��ʱ�� E Ϊ�����壬
	// ������ E �� 0 �� 1 ���������䣬����Ӧ���� "0"
	P0=y; // ���������� P0 �ڣ���������д��Һ��ģ��
	_nop_();
	_nop_();
	_nop_();
	_nop_(); // �ղ����ĸ��������ڣ���Ӳ����Ӧʱ��
	E=1; //E �øߵ�ƽ
	_nop_();
	_nop_();
	_nop_();
	_nop_(); // �ղ����ĸ��������ڣ���Ӳ����Ӧʱ��
	E=0; // �� E �ɸߵ�ƽ����ɵ͵�ƽʱ��Һ��ģ�鿪ʼִ������
}








/*****************************************************
�������ܣ��� LCD����ʾģʽ���г�ʼ������
***************************************************/
void LcdInitiate(void)
{
	delaynms(100); // ��ʱ 15ms���״�дָ��ʱӦ�� LCDһ�νϳ��ķ�Ӧʱ��
//	WriteInstruction(0x38); // ��ʾģʽ���ã� 16��2 ��ʾ�� 5��7 ���� 8 λ���ݽӿ�
//	delaynms(5); // ��ʱ 5ms ����Ӳ��һ�㷴Ӧʱ��
	WriteInstruction(0x38);
	delaynms(5); // ��ʱ 5ms ����Ӳ��һ�㷴Ӧʱ��
	WriteInstruction(0x38); // �������Σ�ȷ����ʼ���ɹ�
	delaynms(5); // ��ʱ 5ms ����Ӳ��һ�㷴Ӧʱ��
	WriteInstruction(0x0c); // ��ʾģʽ���ã���ʾ�����޹�꣬��겻��˸	0x0f�����˸
	delaynms(5); // ��ʱ 5ms ����Ӳ��һ�㷴Ӧʱ��
	WriteInstruction(0x06); // ��ʾģʽ���ã�������ƣ��ַ�����
	delaynms(5); // ��ʱ 5ms ����Ӳ��һ�㷴Ӧʱ��
	WriteInstruction(0x01); // ����Ļָ�����ǰ����ʾ�������
	delaynms(5); // ��ʱ 5ms ����Ӳ��һ�㷴Ӧʱ��
	CgramWrite();//��CGRAMд���Զ����ַ�
	delaynms(5); // ��ʱ 5ms ����Ӳ��һ�㷴Ӧʱ��
}


///////////////////////////////////////////////////////////////////////

// д���ݳ��� //
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
   delaynms(5);  // �޸���ʱ���ı���ʾ�ٶ�
}


// �Զ����ַ� һ����д��16���������ַ���д��������CGRAM����ֱ����ȡ��ʾ��
unsigned int code Xword[]={
    0x18,0x18,0x07,0x08,0x08,0x08,0x07,0x00,  //�棬���� 0x00
    0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,  //һ������ 0x01
    0x00,0x00,0x00,0x0e,0x00,0xff,0x00,0x00,  //�������� 0x02
    0x00,0x00,0xff,0x00,0x0e,0x00,0xff,0x00,  //�������� 0x03
    0x00,0x00,0xff,0xf5,0xfb,0xf1,0xff,0x00,  //�ģ����� 0x04
    0x00,0xfe,0x08,0xfe,0x0a,0x0a,0xff,0x00,  //�壬���� 0x05
    0x00,0x04,0x00,0xff,0x00,0x0a,0x11,0x00,  //�������� 0x06
    0x00,0x1f,0x11,0x1f,0x11,0x11,0x1f,0x00  //�գ����� 0x07
};

void CgramWrite(void)   // װ��CGRAM //
{ 
    unsigned int i;
    WriteInstruction(0x06);   // CGRAM��ַ�Զ���1
    WriteInstruction(0x40);   // CGRAM��ַ��Ϊ00��
//	WriteAddress(0x40);
    for(i=0;i<64;i++) 
	{
    LCD1602_WriteData(Xword[i]);// ������д������
    }
//	LCD1602_WriteData(0x00);
}
