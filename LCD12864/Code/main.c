#include<REG52.h>
#include"delay.h"
#include"LCD1602.h"

code unsigned char font_base[][32]={
// Shuang
{0x00,0xA8,0xE8,0x68,0x68,0xE8,0x88,0xF8,0x1E,0xE8,0x68,0x6C,0x74,0x44,0x00,0x00,
0x00,0x0A,0x06,0x06,0x06,0x7D,0x1F,0x30,0x29,0x26,0x26,0x66,0x45,0x08,0x00,0x00}
};

void main()
{
	LCD_Init(LCD12864);                  // Initial LCD
	disp_cn(5,56,&font_base[0][0]);      // Display Database Font
	LCD_ShowString(28, 2, 16, "LCD12864");      // Display String
  
	while(1)
	{
		delay_ms(20);
	}
}