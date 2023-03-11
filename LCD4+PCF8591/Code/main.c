#include<REG52.h>
#include"delay.h"
#include"LCD1602.h"
#include"I2C.h"

void main()
{
	uchar bai,shi,ge,ADdate;
	LCD_Init();
	gotoxy(1,3);     // Set cursor position ��1�е�3�п�ʼд
	LCD_Write_String("PCF8591 test");
	gotoxy(2,1);     // Set cursor position
	LCD_Write_String("Ain0:");
  
	while(1)
	{
		ISendByte(0x90,0x40); // 0x40 ��ӦAD ���� AIN0 	0x41 ��ӦAD ���� AIN1 �Դ����ơ�
		ADdate=IRcvByte(0x90);
		DACconversion(0x90,0x40, ADdate); //DAC	 �õ���ʾ

		bai=ADdate/100;
		shi=ADdate%100/10;
		ge=ADdate%10;
		
		gotoxy(2,6);     // Set cursor position
		LCD_Write_Data(bai+0x30);
		LCD_Write_Data(shi+0x30);
		LCD_Write_Data(ge+0x30);
		delay_ms(20);
	}
}
