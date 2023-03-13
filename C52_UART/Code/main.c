#include<REG52.h>
#include"delay.h"
#include"LCD1602.h"
#include"key.h"
#include"uart.h"

/****************************************************************************************
*     UART Demo(Send / Receive)
****************************************************************************************/
extern unsigned char rcv_buff, rcv_flag;

void display_initial(void)
{
    LCD_Init();
    gotoxy(1,5);     // Set cursor position
    LCD_Write_String("C52 UART");
    gotoxy(2,1);     // Set cursor position
    LCD_Write_String("Send:");
    gotoxy(3,1);     // Set cursor position
    LCD_Write_String("Rcv:");;
}

void system_initial(void)
{
    UART_Init();
}

void main()
{
    unsigned char key, send_byte;
    system_initial();
    display_initial();
	
    while(1)
    {
      key = switchs();
      if(key)
      {
          send_byte = key;
          gotoxy(2,6);
          LCD_Write_DATA(send_byte+'0');
          UART_Send_Byte(send_byte);
      }
      if(rcv_flag)
      {
          rcv_flag = 0;
          gotoxy(3,5);
          LCD_Write_DATA(rcv_buff+'0');
      }
    }
}
