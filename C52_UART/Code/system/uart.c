#include<reg52.h>
#include"uart.h"

unsigned char rcv_buff, rcv_flag;

void UART_Init(void)
{
	SCON = 0x50;                                //串口方式1，允许接收
  TMOD= 0x20;                                 //定时器1工作方式2
  TH1 = 0xF3;                                 //波特率2400、数据位8、停止位1
  TL1 = 0xF3; 
  TR1 = 1;                                    //开启定时器1
  EA=1;                                       //开总中断
  ES=1;                                       //开串中断
}

void UART_Send_Byte(unsigned char send_byte)
{
	ES=0;                                //进入发送数据时先关闭串行中断
  SBUF=send_byte;                      //将数据原样发出
  while(!TI);                          //等待数据发完
  TI=0;
  ES=1;                                //退出再开串行中断
}


void serial() interrupt 4                         //串行中断函数
{    
	rcv_buff=SBUF;                                  //收取数据
  rcv_flag=1;                                     //标志复位
  RI=0;
}
