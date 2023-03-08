#include<REG52.h>
#include"delay.h"
#include"LCD1602.h"


void main()
{
	LCD_Init();      // Initial LCD
	gotoxy(1,4);     // Set cursor position
	LCD_Write_String("-----------");
	gotoxy(2,5);     // Set cursor position
	LCD_Write_String("LCD Demo");
  
	while(1)
	{
		delay_ms(20);
	}
}
