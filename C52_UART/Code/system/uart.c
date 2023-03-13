#include<reg52.h>
#include"uart.h"

unsigned char rcv_buff, rcv_flag;

void UART_Init(void)
{
	SCON = 0x50;                                //���ڷ�ʽ1���������
  TMOD= 0x20;                                 //��ʱ��1������ʽ2
  TH1 = 0xF3;                                 //������2400������λ8��ֹͣλ1
  TL1 = 0xF3; 
  TR1 = 1;                                    //������ʱ��1
  EA=1;                                       //�����ж�
  ES=1;                                       //�����ж�
}

void UART_Send_Byte(unsigned char send_byte)
{
	ES=0;                                //���뷢������ʱ�ȹرմ����ж�
  SBUF=send_byte;                      //������ԭ������
  while(!TI);                          //�ȴ����ݷ���
  TI=0;
  ES=1;                                //�˳��ٿ������ж�
}


void serial() interrupt 4                         //�����жϺ���
{    
	rcv_buff=SBUF;                                  //��ȡ����
  rcv_flag=1;                                     //��־��λ
  RI=0;
}
