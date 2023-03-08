#ifndef _LCD1602_H_
#define _LCD1602_H_

#include<REG52.h>

#define uchar unsigned char
#define uint unsigned int
    
#define LCD1602_2 0
#define LCD1602_4 1
#define LM041L 1
#define LCD12864 2

sbit RS=P2^3;                             //RS接入23
sbit RW=P2^4;                             //RW接入24
sbit EN=P2^5;                             //EN接入25

void LCD_Init(uchar lcd_type);
void LCD_Write_String(uchar *p);
void gotoxy(uchar x,uchar y);//是在x行，y列显示数据
void LCD_Write_DATA(uchar text);
void Init_LCD(void);
void disp_cn(unsigned char x,unsigned char y,unsigned char *p);
void LCD_ShowChar(unsigned char x,unsigned char y,unsigned char num,unsigned char font_size);
void LCD_ShowString(unsigned int x, unsigned int y, unsigned char font_size, unsigned char *p);





#endif