#include<REG52.h>
#include"delay.h"
#include"LCD1602.h"


void main()
{
	LCD_Init();
	gotoxy(1,6);
	LCD_Write_String("Github");
	gotoxy(2,5);
	LCD_Write_String("cangzihan");
	gotoxy(3,4);
	LCD_Write_String("-----------");
	gotoxy(4,5);
	LCD_Write_String("LCD4 Demo");
  
	while(1)
	{
		delay_ms(20);
	}
}
