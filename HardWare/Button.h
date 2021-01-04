#ifndef BUTTON_H
#define BUTTON_H

//定义按键按下的次数，不同次数选择不同设置
extern char button_num1; 	//判断选则时分秒
extern char button_num2;	//判断切换时间/日期	
extern char button_flag;	//按键选择位标志，


//extern button_flag;
char KeyScan();
void button_setting();
void button_up_down();
void ButtonSwitchDT();

#endif