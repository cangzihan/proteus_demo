#include<reg52.h>
#include"uart.h"

unsigned char rcv_buff, rcv_flag;

void UART_Init(void)
{
    SCON = 0x50;                                //UART1, Enable Receive
    TMOD= 0x20;                                 //UART1, Work Mode2
    TH1 = 0xF3;                                 //Baud 2400, Data Bit8, Stop Bit1
    TL1 = 0xF3; 
    TR1 = 1;                                    //Open Timer 1
    EA=1;                                       //Enable Interrupt
    ES=1;                                       //Enable UART Interrupt
}

void UART_Send_Byte(unsigned char send_byte)
{
    ES=0;                                //Before Send, Disable UART Interrupt
    SBUF=send_byte;                      //Send Data
    while(!TI);                          //Sent?
    TI=0;
    ES=1;                                //After Exit, Enable UART Interrupt
}


void serial() interrupt 4                         //UART Interrupt Function
{    
    rcv_buff=SBUF;                                  //Receive Data
    rcv_flag=1;                                     //Reset Flag
    RI=0;
}
