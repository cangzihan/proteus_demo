#ifndef _LCD1602_H_
#define _LCD1602_H_

#include<REG52.h>

#define uchar unsigned char
#define uint unsigned int

sbit RS=P2^3;                             //RS����23
sbit RW=P2^4;                             //RW����24
sbit EN=P2^5;                             //EN����25

void LCD_Init(void);
void LCD_Write_String(uchar *p);
void gotoxy(uchar x,uchar y);//����x�У�y����ʾ����
void LCD_Write_Data(uchar text);
    
#endif