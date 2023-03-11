#include"LCD1602.h"
#include"delay.h"


void LCD_Write_Com(uchar com)//写指令函数(write command function)
{
	RS=0;
	RW=0;
	P0=com;
	EN=1;
	delay_ms(1);
	EN=0;	
}
void LCD_Write_DATA(uchar text)//写数据函数(write data function)
{
	RS=1;
	RW=0;
	P0=text;
	EN=1;
	delay_ms(1);
	EN=0;
}
void gotoxy(uchar x,uchar y)//是在x行，y列显示数据(set cursor position function)
{
	if(x==1)
	{
	   LCD_Write_Com(0x80+y-1);
	}
	if(x==2)
	{
		LCD_Write_Com(0xC0+y-1);
	}	
}
void LCD_Write_String(uchar *p) // write string function
{
	while(*p!=0)
	{
		LCD_Write_DATA(*p);	
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
	LCD_Write_Com(0x08);  // turn off display
	LCD_Write_Com(0x01);  // clear screen
	LCD_Write_Com(0x06);  // set cursor moving direction to right
	LCD_Write_Com(0x0c);  // turn on display, turn off cursor
}