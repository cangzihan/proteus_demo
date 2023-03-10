#include<REG52.h>
#include"delay.h"
#include"LCD1602.h"
#include"I2C.h"

void main()
{
	uchar bai,shi,ge,ADdate;
	LCD_Init();
	gotoxy(1,3);
	LCD_Write_String("PCF8591 test"); //第一行第一列开始写
	gotoxy(2,1);
	LCD_Write_String("Ain0:"); //第一行第一列开始写
  
	while(1)
	{
		ISendByte(0x90,0x40); // 0x40 对应AD 输入 AIN0 	0x41 对应AD 输入 AIN1 以此类推。
		ADdate=IRcvByte(0x90);
		DACconversion(0x90,0x40, ADdate); //DAC	 用灯显示

		bai=ADdate/100;
		shi=ADdate%100/10;
		ge=ADdate%10;
		
		gotoxy(2,6);
		LCD_Write_Data(bai+0x30);
		LCD_Write_Data(shi+0x30);
		LCD_Write_Data(ge+0x30);
		delay_ms(20);
	}
}
