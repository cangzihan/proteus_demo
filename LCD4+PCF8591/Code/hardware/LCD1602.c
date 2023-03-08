#include"LCD1602.h"
#include"delay.h"


void LCD_Write_Com(uchar com)//дָ���
{
	RS=0;
	RW=0;
	P0=com;
	EN=1;
	delay_ms(1);
	EN=0;	
}
void LCD_Write_Data(uchar text)//д���ݺ���
{
	RS=1;
	RW=0;
	P0=text;
	EN=1;
	delay_ms(1);
	EN=0;
}
/*
LM041L
Line 1: 80 - 8F
Line 2: C0 - CF
Line 3: 90 - 9F
Line 4: D0 - DF
*/
void gotoxy(uchar x,uchar y)//����x�У�y����ʾ����
{
	if(x==1)
	{
	   LCD_Write_Com(0x80+y-1);
	}
	if(x==2)
	{
		LCD_Write_Com(0xC0+y-1);
	}	
	if(x==3)
	{
		LCD_Write_Com(0x90+y-1);
	}	
	if(x==4)
	{
		LCD_Write_Com(0xD0+y-1);
	}	
}
void LCD_Write_String(uchar *p)
{
	while(*p!=0)
	{
		LCD_Write_Data(*p);	
		p++;
	}	
}

void LCD_Init(void)
{
	LCD_Write_Com(0x38);
	delay_ms(5);
	LCD_Write_Com(0x38);
	delay_ms(5);
	LCD_Write_Com(0x38);
	delay_ms(5);
	LCD_Write_Com(0x38);
	delay_ms(5);
	LCD_Write_Com(0x08);
	LCD_Write_Com(0x01);
	LCD_Write_Com(0x06);
	LCD_Write_Com(0x0c);
}