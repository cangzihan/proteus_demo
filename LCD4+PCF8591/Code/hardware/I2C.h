#ifndef _I2C_H_
#define _I2C_H_

#include<REG52.h>

#define uchar unsigned char
#define uint unsigned int

sbit SCL=P2^1;//I2C  Ê±ÖÓ 
sbit SDA=P2^0;//I2C  Êı¾İ 

bit DACconversion(unsigned char sla,unsigned char c,  unsigned char Val);
bit ISendByte(unsigned char sla,unsigned char c);
unsigned char IRcvByte(unsigned char sla);	

#endif