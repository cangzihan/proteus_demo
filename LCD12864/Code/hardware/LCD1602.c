#include"LCD1602.h"
#include"delay.h"
#define uchar unsigned char
#define uint unsigned int
#define u16 unsigned int
#define u8 unsigned char
#define _nop ()
#define PAGEADD 0xb8
#define TIERADD 0x40
#define DIS_STARADD 0xc0


uint key_value;
sbit DI=P2^3;
sbit CS1=P1^0;
sbit CS2=P1^1;
//e-12 rw-13


//12*12 ASCII字符集点阵
code unsigned char asc2_1206[95][12]={
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*" ",0*/
{0x00,0x00,0x00,0x00,0x3F,0x40,0x00,0x00,0x00,0x00,0x00,0x00},/*"!",1*/
{0x00,0x00,0x30,0x00,0x40,0x00,0x30,0x00,0x40,0x00,0x00,0x00},/*""",2*/
{0x09,0x00,0x0B,0xC0,0x3D,0x00,0x0B,0xC0,0x3D,0x00,0x09,0x00},/*"#",3*/
{0x18,0xC0,0x24,0x40,0x7F,0xE0,0x22,0x40,0x31,0x80,0x00,0x00},/*"$",4*/
{0x18,0x00,0x24,0xC0,0x1B,0x00,0x0D,0x80,0x32,0x40,0x01,0x80},/*"%",5*/
{0x03,0x80,0x1C,0x40,0x27,0x40,0x1C,0x80,0x07,0x40,0x00,0x40},/*"&",6*/
{0x10,0x00,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"'",7*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x80,0x20,0x40,0x40,0x20},/*"(",8*/
{0x00,0x00,0x40,0x20,0x20,0x40,0x1F,0x80,0x00,0x00,0x00,0x00},/*")",9*/
{0x09,0x00,0x06,0x00,0x1F,0x80,0x06,0x00,0x09,0x00,0x00,0x00},/*"*",10*/
{0x04,0x00,0x04,0x00,0x3F,0x80,0x04,0x00,0x04,0x00,0x00,0x00},/*"+",11*/
{0x00,0x10,0x00,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*",",12*/
{0x04,0x00,0x04,0x00,0x04,0x00,0x04,0x00,0x04,0x00,0x00,0x00},/*"-",13*/
{0x00,0x00,0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*".",14*/
{0x00,0x20,0x01,0xC0,0x06,0x00,0x38,0x00,0x40,0x00,0x00,0x00},/*"/",15*/
{0x1F,0x80,0x20,0x40,0x20,0x40,0x20,0x40,0x1F,0x80,0x00,0x00},/*"0",16*/
{0x00,0x00,0x10,0x40,0x3F,0xC0,0x00,0x40,0x00,0x00,0x00,0x00},/*"1",17*/
{0x18,0xC0,0x21,0x40,0x22,0x40,0x24,0x40,0x18,0x40,0x00,0x00},/*"2",18*/
{0x10,0x80,0x20,0x40,0x24,0x40,0x24,0x40,0x1B,0x80,0x00,0x00},/*"3",19*/
{0x02,0x00,0x0D,0x00,0x11,0x00,0x3F,0xC0,0x01,0x40,0x00,0x00},/*"4",20*/
{0x3C,0x80,0x24,0x40,0x24,0x40,0x24,0x40,0x23,0x80,0x00,0x00},/*"5",21*/
{0x1F,0x80,0x24,0x40,0x24,0x40,0x34,0x40,0x03,0x80,0x00,0x00},/*"6",22*/
{0x30,0x00,0x20,0x00,0x27,0xC0,0x38,0x00,0x20,0x00,0x00,0x00},/*"7",23*/
{0x1B,0x80,0x24,0x40,0x24,0x40,0x24,0x40,0x1B,0x80,0x00,0x00},/*"8",24*/
{0x1C,0x00,0x22,0xC0,0x22,0x40,0x22,0x40,0x1F,0x80,0x00,0x00},/*"9",25*/
{0x00,0x00,0x00,0x00,0x08,0x40,0x00,0x00,0x00,0x00,0x00,0x00},/*":",26*/
{0x00,0x00,0x00,0x00,0x04,0x60,0x00,0x00,0x00,0x00,0x00,0x00},/*";",27*/
{0x00,0x00,0x04,0x00,0x0A,0x00,0x11,0x00,0x20,0x80,0x40,0x40},/*"<",28*/
{0x09,0x00,0x09,0x00,0x09,0x00,0x09,0x00,0x09,0x00,0x00,0x00},/*"=",29*/
{0x00,0x00,0x40,0x40,0x20,0x80,0x11,0x00,0x0A,0x00,0x04,0x00},/*">",30*/
{0x18,0x00,0x20,0x00,0x23,0x40,0x24,0x00,0x18,0x00,0x00,0x00},/*"?",31*/
{0x1F,0x80,0x20,0x40,0x27,0x40,0x29,0x40,0x1F,0x40,0x00,0x00},/*"@",32*/
{0x00,0xE0,0x9C,0xF0,0x80,0x00,0x02,0x03,0x00,0x00,0x03,0x02},/*"A",33*/
{0x04,0xFC,0x24,0x24,0xD8,0x00,0x02,0x03,0x02,0x02,0x01,0x00},/*"B",34*/
{0x1F,0x80,0x20,0x40,0x20,0x40,0x20,0x40,0x30,0x80,0x00,0x00},/*"C",35*/
{0x20,0x40,0x3F,0xC0,0x20,0x40,0x20,0x40,0x1F,0x80,0x00,0x00},/*"D",36*/
{0x20,0x40,0x3F,0xC0,0x24,0x40,0x2E,0x40,0x30,0xC0,0x00,0x00},/*"E",37*/
{0x20,0x40,0x3F,0xC0,0x24,0x40,0x2E,0x00,0x30,0x00,0x00,0x00},/*"F",38*/
{0x0F,0x00,0x10,0x80,0x20,0x40,0x22,0x40,0x33,0x80,0x02,0x00},/*"G",39*/
{0x20,0x40,0x3F,0xC0,0x04,0x00,0x04,0x00,0x3F,0xC0,0x20,0x40},/*"H",40*/
{0x20,0x40,0x20,0x40,0x3F,0xC0,0x20,0x40,0x20,0x40,0x00,0x00},/*"I",41*/
{0x00,0x60,0x20,0x20,0x20,0x20,0x3F,0xC0,0x20,0x00,0x20,0x00},/*"J",42*/
{0x20,0x40,0x3F,0xC0,0x24,0x40,0x0B,0x00,0x30,0xC0,0x20,0x40},/*"K",43*/
{0x20,0x40,0x3F,0xC0,0x20,0x40,0x00,0x40,0x00,0x40,0x00,0xC0},/*"L",44*/
{0x3F,0xC0,0x3C,0x00,0x03,0xC0,0x3C,0x00,0x3F,0xC0,0x00,0x00},/*"M",45*/
{0x20,0x40,0x3F,0xC0,0x0C,0x40,0x23,0x00,0x3F,0xC0,0x20,0x00},/*"N",46*/
{0x1F,0x80,0x20,0x40,0x20,0x40,0x20,0x40,0x1F,0x80,0x00,0x00},/*"O",47*/
{0x20,0x40,0x3F,0xC0,0x24,0x40,0x24,0x00,0x18,0x00,0x00,0x00},/*"P",48*/
{0x1F,0x80,0x21,0x40,0x21,0x40,0x20,0xE0,0x1F,0xA0,0x00,0x00},/*"Q",49*/
{0x20,0x40,0x3F,0xC0,0x24,0x40,0x26,0x00,0x19,0xC0,0x00,0x40},/*"R",50*/
{0x18,0x24,0x24,0x44,0x8C,0x00,0x03,0x02,0x02,0x02,0x01,0x00},/*"S",51*/
{0x30,0x00,0x20,0x40,0x3F,0xC0,0x20,0x40,0x30,0x00,0x00,0x00},/*"T",52*/
{0x20,0x00,0x3F,0x80,0x00,0x40,0x00,0x40,0x3F,0x80,0x20,0x00},/*"U",53*/
{0x20,0x00,0x3E,0x00,0x01,0xC0,0x07,0x00,0x38,0x00,0x20,0x00},/*"V",54*/
{0x38,0x00,0x07,0xC0,0x3C,0x00,0x07,0xC0,0x38,0x00,0x00,0x00},/*"W",55*/
{0x20,0x40,0x39,0xC0,0x06,0x00,0x39,0xC0,0x20,0x40,0x00,0x00},/*"X",56*/
{0x20,0x00,0x38,0x40,0x07,0xC0,0x38,0x40,0x20,0x00,0x00,0x00},/*"Y",57*/
{0x0C,0x84,0x64,0x1C,0x04,0x00,0x02,0x03,0x02,0x02,0x03,0x00},/*"Z",58*/
{0x00,0x00,0x00,0x00,0x7F,0xE0,0x40,0x20,0x40,0x20,0x00,0x00},/*"[",59*/
{0x00,0x00,0x70,0x00,0x0C,0x00,0x03,0x80,0x00,0x40,0x00,0x00},/*"",60*/
{0x00,0x00,0x40,0x20,0x40,0x20,0x7F,0xE0,0x00,0x00,0x00,0x00},/*"]",61*/
{0x00,0x00,0x20,0x00,0x40,0x00,0x20,0x00,0x00,0x00,0x00,0x00},/*"^",62*/
{0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10},/*"_",63*/
{0x00,0x00,0x00,0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"`",64*/
{0x00,0x00,0x02,0x80,0x05,0x40,0x05,0x40,0x03,0xC0,0x00,0x40},/*"a",65*/
{0x20,0x00,0x3F,0xC0,0x04,0x40,0x04,0x40,0x03,0x80,0x00,0x00},/*"b",66*/
{0x00,0x00,0x03,0x80,0x04,0x40,0x04,0x40,0x06,0x40,0x00,0x00},/*"c",67*/
{0x00,0x00,0x03,0x80,0x04,0x40,0x24,0x40,0x3F,0xC0,0x00,0x40},/*"d",68*/
{0x00,0x00,0x03,0x80,0x05,0x40,0x05,0x40,0x03,0x40,0x00,0x00},/*"e",69*/
{0x00,0x00,0x04,0x40,0x1F,0xC0,0x24,0x40,0x24,0x40,0x20,0x00},/*"f",70*/
{0x00,0x00,0x02,0xE0,0x05,0x50,0x05,0x50,0x06,0x50,0x04,0x20},/*"g",71*/
{0x20,0x40,0x3F,0xC0,0x04,0x40,0x04,0x00,0x03,0xC0,0x00,0x40},/*"h",72*/
{0x00,0x00,0x04,0x40,0x27,0xC0,0x00,0x40,0x00,0x00,0x00,0x00},/*"i",73*/
{0x00,0x10,0x00,0x10,0x04,0x10,0x27,0xE0,0x00,0x00,0x00,0x00},/*"j",74*/
{0x20,0x40,0x3F,0xC0,0x01,0x40,0x07,0x00,0x04,0xC0,0x04,0x40},/*"k",75*/
{0x20,0x40,0x20,0x40,0x3F,0xC0,0x00,0x40,0x00,0x40,0x00,0x00},/*"l",76*/
{0x07,0xC0,0x04,0x00,0x07,0xC0,0x04,0x00,0x03,0xC0,0x00,0x00},/*"m",77*/
{0x04,0x40,0x07,0xC0,0x04,0x40,0x04,0x00,0x03,0xC0,0x00,0x40},/*"n",78*/
{0x00,0x00,0x03,0x80,0x04,0x40,0x04,0x40,0x03,0x80,0x00,0x00},/*"o",79*/
{0x04,0x10,0x07,0xF0,0x04,0x50,0x04,0x40,0x03,0x80,0x00,0x00},/*"p",80*/
{0x00,0x00,0x03,0x80,0x04,0x40,0x04,0x50,0x07,0xF0,0x00,0x10},/*"q",81*/
{0x04,0x40,0x07,0xC0,0x02,0x40,0x04,0x00,0x04,0x00,0x00,0x00},/*"r",82*/
{0x00,0x00,0x06,0x40,0x05,0x40,0x05,0x40,0x04,0xC0,0x00,0x00},/*"s",83*/
{0x00,0x00,0x04,0x00,0x1F,0x80,0x04,0x40,0x00,0x40,0x00,0x00},/*"t",84*/
{0x04,0x00,0x07,0x80,0x00,0x40,0x04,0x40,0x07,0xC0,0x00,0x40},/*"u",85*/
{0x04,0x00,0x07,0x00,0x04,0xC0,0x01,0x80,0x06,0x00,0x04,0x00},/*"v",86*/
{0x06,0x00,0x01,0xC0,0x07,0x00,0x01,0xC0,0x06,0x00,0x00,0x00},/*"w",87*/
{0x04,0x40,0x06,0xC0,0x01,0x00,0x06,0xC0,0x04,0x40,0x00,0x00},/*"x",88*/
{0x04,0x10,0x07,0x10,0x04,0xE0,0x01,0x80,0x06,0x00,0x04,0x00},/*"y",89*/
{0x00,0x00,0x04,0x40,0x05,0xC0,0x06,0x40,0x04,0x40,0x00,0x00},/*"z",90*/
{0x00,0x00,0x00,0x00,0x04,0x00,0x7B,0xE0,0x40,0x20,0x00,0x00},/*"{",91*/
{0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xF0,0x00,0x00,0x00,0x00},/*"|",92*/
{0x00,0x00,0x40,0x20,0x7B,0xE0,0x04,0x00,0x00,0x00,0x00,0x00},/*"}",93*/
{0x40,0x00,0x80,0x00,0x40,0x00,0x20,0x00,0x20,0x00,0x40,0x00}/*"~",94*/
}; 


//16*16 ASCII字符集点阵
code unsigned char asc2_1608[][16]={
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*" ",0*/
{0x00,0x00,0x00,0x00,0xFE,0x0C,0x00,0x00,0x00,0x00,0x10,0x17,0x37,0x20,0x00,0x00},/*"!",1*/
{0x00,0x00,0x1E,0x0E,0x0C,0x1E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*""",2*/
{0x00,0x20,0xF8,0x3C,0x20,0xFC,0x20,0x00,0x00,0x04,0x7F,0x04,0x7E,0x07,0x04,0x00},/*"#",3*/
{0x00,0x0C,0x38,0xE0,0xE0,0x38,0x0C,0x00,0x03,0x03,0x01,0x03,0x7F,0x01,0x01,0x01},/*"$",4*/
{0x10,0x6C,0x44,0x38,0xE0,0x38,0x0C,0x00,0x00,0x30,0x1C,0x07,0x1D,0x22,0x36,0x08},/*"%",5*/
{0x00,0x00,0x78,0xCC,0xC4,0x38,0x00,0x00,0x00,0x1C,0x37,0x21,0x3E,0x38,0x08,0x00},/*"&",6*/
{0x00,0x00,0x00,0x0C,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"'",7*/
{0x00,0x00,0xE0,0x70,0x18,0x08,0x00,0x00,0x00,0x00,0x07,0x1C,0x10,0x10,0x00,0x00},/*"(",8*/
{0x00,0x00,0x08,0x18,0x70,0xE0,0x00,0x00,0x00,0x00,0x10,0x10,0x1C,0x07,0x00,0x00},/*")",9*/
{0x80,0x80,0x00,0xF0,0x00,0x00,0x80,0x80,0x00,0x18,0x0D,0x03,0x03,0x0D,0x18,0x00},/*"*",10*/
{0x80,0x80,0x80,0xF8,0xF8,0x80,0x80,0x80,0x00,0x01,0x01,0x0F,0x1F,0x00,0x00,0x00},/*"+",11*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x70,0x00,0x00,0x00},/*",",12*/
{0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00},/*"-",13*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00},/*".",14*/
{0x00,0x00,0x00,0x80,0xE0,0x3C,0x06,0x00,0x00,0x60,0x3C,0x07,0x00,0x00,0x00,0x00},/*"/",15*/
{0x00,0xF0,0x18,0x0C,0x04,0x0C,0xF8,0x00,0x00,0x0F,0x38,0x20,0x20,0x38,0x0F,0x00},/*"0",16*/
{0x00,0x00,0x00,0xFC,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0x3F,0x00,0x00,0x00},/*"1",17*/
{0x00,0x18,0x0C,0x0C,0x8C,0xC8,0x70,0x00,0x00,0x00,0x3C,0x23,0x21,0x30,0x10,0x00},/*"2",18*/
{0x00,0x08,0x8C,0x84,0x84,0xEC,0x38,0x00,0x00,0x00,0x00,0x00,0x20,0x38,0x0F,0x00},/*"3",19*/
{0x00,0xC0,0x70,0x0C,0x80,0xFC,0x00,0x00,0x00,0x0F,0x08,0x08,0x3F,0x08,0x08,0x00},/*"4",20*/
{0x00,0xF8,0x0C,0x08,0x88,0x08,0x08,0x00,0x00,0x01,0x01,0x01,0x01,0x31,0x1F,0x00},/*"5",21*/
{0x00,0xC0,0xF0,0xD8,0xC8,0x84,0x00,0x00,0x00,0x1F,0x30,0x20,0x20,0x31,0x0F,0x00},/*"6",22*/
{0x00,0x08,0x0C,0x04,0x04,0x8C,0xF8,0x00,0x00,0x00,0x00,0x00,0x38,0x0F,0x00,0x00},/*"7",23*/
{0x00,0x78,0x88,0x84,0x84,0xC8,0x78,0x00,0x00,0x1F,0x31,0x20,0x20,0x31,0x1F,0x00},/*"8",24*/
{0x00,0xF0,0x18,0x0C,0x04,0x0C,0x78,0x00,0x00,0x03,0x06,0x04,0x04,0x3E,0x1F,0x00},/*"9",25*/
{0x00,0x00,0x00,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x31,0x31,0x00,0x00,0x00},/*":",26*/
{0x00,0x00,0x00,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x31,0x71,0x00,0x00,0x00},/*";",27*/
{0x00,0x80,0xC0,0x60,0x30,0x30,0x18,0x00,0x01,0x03,0x06,0x04,0x0C,0x08,0x18,0x10},/*"<",28*/
{0x40,0x40,0x40,0x40,0x40,0x60,0x60,0x40,0x04,0x06,0x06,0x06,0x06,0x06,0x06,0x02},/*"=",29*/
{0x00,0x18,0x30,0x30,0x60,0xC0,0x80,0x00,0x10,0x18,0x08,0x0C,0x04,0x06,0x03,0x01},/*">",30*/
{0x30,0xFC,0x06,0x02,0x06,0x04,0xFC,0x00,0x00,0x00,0x10,0x30,0x22,0x03,0x00,0x00},/*"?",31*/
{0xC0,0x70,0xC8,0x34,0x24,0xEC,0x18,0xE0,0x07,0x1C,0x33,0x24,0x26,0x37,0x16,0x01},/*"@",32*/
{0x00,0xE0,0x38,0x0C,0x0C,0x38,0xE0,0x00,0x00,0x3F,0x02,0x02,0x02,0x00,0x3F,0x00},/*"A",33*/
{0x00,0xFC,0x08,0x0C,0x84,0xC8,0x78,0x00,0x00,0x3F,0x00,0x31,0x21,0x31,0x1F,0x00},/*"B",34*/
{0x00,0xF0,0x18,0x0C,0x04,0x0C,0x18,0x00,0x00,0x1F,0x30,0x20,0x20,0x30,0x18,0x00},/*"C",35*/
{0x00,0xFC,0x08,0x0C,0x0C,0x18,0xF0,0x00,0x00,0x3F,0x00,0x30,0x20,0x30,0x1F,0x00},/*"D",36*/
{0x00,0xE4,0xBC,0x84,0x84,0x8C,0x0C,0x00,0x00,0x1F,0x30,0x20,0x20,0x30,0x10,0x00},/*"E",37*/
{0x00,0xEC,0xFC,0x04,0x04,0x0C,0x0C,0x00,0x00,0x3F,0x31,0x01,0x01,0x01,0x00,0x00},/*"F",38*/
{0x00,0xF0,0x18,0x0C,0x04,0x0C,0x18,0x00,0x00,0x1F,0x30,0x21,0x31,0x01,0x3F,0x00},/*"G",39*/
{0x00,0xF0,0x3C,0x00,0x00,0x00,0xFC,0x00,0x00,0x3F,0x21,0x01,0x01,0x00,0x3F,0x00},/*"H",40*/
{0x00,0x04,0x04,0xFC,0x1C,0x04,0x04,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x20,0x00},/*"I",41*/
{0x00,0x0C,0x0C,0x0C,0x7C,0xC4,0x04,0x08,0x00,0x30,0x20,0x20,0x30,0x1F,0x00,0x00},/*"J",42*/
{0x00,0xFC,0x8C,0xE0,0x30,0x18,0x0C,0x00,0x00,0x3F,0x23,0x06,0x0C,0x18,0x30,0x00},/*"K",43*/
{0x00,0xE0,0x7C,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x30,0x20,0x20,0x30,0x10,0x00},/*"L",44*/
{0x80,0xFC,0x30,0x60,0x60,0x30,0xF8,0x60,0x00,0x3F,0x00,0x00,0x00,0x00,0x1F,0x00},/*"M",45*/
{0x00,0xFC,0xF8,0x00,0x00,0x0C,0xFC,0x00,0x00,0x3F,0x01,0x07,0x1C,0x30,0x1F,0x00},/*"N",46*/
{0x00,0xF0,0x18,0x0C,0x0C,0x18,0xF0,0x00,0x00,0x0F,0x38,0x20,0x20,0x18,0x0F,0x00},/*"O",47*/
{0x00,0xFC,0x0C,0x0C,0x04,0x0C,0xF8,0x00,0x00,0x3F,0x00,0x04,0x04,0x06,0x03,0x00},/*"P",48*/
{0x00,0xF0,0x18,0x0C,0x0C,0x18,0xF0,0x00,0x00,0x0F,0x38,0x20,0x2C,0x18,0x3F,0x00},/*"Q",49*/
{0x00,0xFC,0x08,0x0C,0x04,0x0C,0xF8,0x00,0x00,0x3F,0x00,0x04,0x04,0x0E,0x3B,0x00},/*"R",50*/
{0x00,0x70,0xD8,0x8C,0x04,0x0C,0x08,0x00,0x00,0x18,0x30,0x21,0x21,0x33,0x1E,0x00},/*"S",51*/
{0x00,0x0C,0x0C,0xFC,0x0C,0x0C,0x0C,0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00},/*"T",52*/
{0x00,0xF0,0x1C,0x00,0x00,0x1C,0xF0,0x00,0x00,0x0F,0x38,0x20,0x20,0x18,0x0F,0x00},/*"U",53*/
{0x00,0xFC,0xC0,0x00,0x00,0xE0,0xFC,0x00,0x00,0x01,0x1F,0x30,0x38,0x0F,0x00,0x00},/*"V",54*/
{0x00,0xF8,0x0C,0x00,0x00,0x08,0xF8,0x00,0x0F,0x3F,0x20,0x30,0x30,0x20,0x3F,0x0E},/*"W",55*/
{0x00,0x0C,0x38,0xE0,0xE0,0x30,0x1C,0x08,0x20,0x3C,0x0E,0x03,0x03,0x1E,0x38,0x00},/*"X",56*/
{0x00,0xFC,0x00,0x00,0x00,0xC0,0xFC,0x00,0x00,0x01,0x07,0x3C,0x36,0x03,0x00,0x00},/*"Y",57*/
{0x00,0x08,0x0C,0x8C,0xCC,0x6C,0x18,0x00,0x00,0x1C,0x3E,0x23,0x20,0x30,0x10,0x00},/*"Z",58*/
{0x00,0x00,0xFC,0x0C,0x0C,0x0C,0x00,0x00,0x00,0x00,0x3F,0x20,0x20,0x20,0x00,0x00},/*"[",59*/
{0x00,0x06,0x3C,0xE0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x3C,0x70,0x00},/*"\",60*/
{0x00,0x00,0x0C,0x0C,0x0C,0xFC,0x00,0x00,0x00,0x00,0x20,0x20,0x20,0x3F,0x00,0x00},/*"]",61*/
{0x00,0x08,0x04,0x06,0x06,0x04,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"^",62*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80},/*"_",63*/
{0x00,0x00,0x00,0x06,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"`",64*/
{0x00,0x80,0xC0,0x20,0x20,0x20,0x40,0x00,0x00,0x1F,0x30,0x20,0x20,0x1C,0x3F,0x00},/*"a",65*/
{0x00,0xF8,0x78,0x20,0x20,0x60,0xC0,0x00,0x00,0x3F,0x00,0x30,0x20,0x30,0x1F,0x00},/*"b",66*/
{0x00,0x80,0xC0,0x20,0x20,0x20,0x60,0x00,0x00,0x1F,0x30,0x20,0x20,0x30,0x18,0x00},/*"c",67*/
{0x00,0x80,0x60,0x20,0x20,0x20,0xF8,0x00,0x00,0x1F,0x30,0x20,0x30,0x00,0x3F,0x00},/*"d",68*/
{0x00,0x80,0xE0,0x20,0x20,0x60,0xC0,0x00,0x00,0x1F,0x32,0x32,0x22,0x02,0x03,0x00},/*"e",69*/
{0x00,0x40,0x40,0xF0,0x58,0x48,0x48,0x00,0x00,0x00,0x00,0x3F,0x20,0x00,0x00,0x00},/*"f",70*/
{0x00,0xC0,0x60,0x20,0x20,0x60,0xE0,0x00,0x06,0x1F,0x30,0xB0,0x90,0x80,0x7F,0x00},/*"g",71*/
{0x00,0xF8,0xF8,0x60,0x20,0x60,0xC0,0x00,0x00,0x3F,0x00,0x00,0x00,0x38,0x1F,0x00},/*"h",72*/
{0x00,0x00,0x08,0xE8,0x08,0x10,0x00,0x00,0x00,0x00,0x00,0x0F,0x3E,0x00,0x00,0x00},/*"i",73*/
{0x00,0x00,0x08,0x08,0xE8,0x88,0x00,0x00,0x00,0x40,0xC0,0x80,0xC1,0x7F,0x38,0x00},/*"j",74*/
{0x00,0xF8,0x18,0x80,0xC0,0x60,0x20,0x00,0x00,0x3F,0x07,0x0D,0x18,0x10,0x30,0x00},/*"k",75*/
{0x00,0x00,0x00,0xF8,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0x3F,0x00,0x00,0x00},/*"l",76*/
{0xE0,0xE0,0x20,0x60,0x60,0x20,0x60,0xC0,0x0F,0x3F,0x00,0x00,0x00,0x00,0x3E,0x07},/*"m",77*/
{0x00,0xE0,0x60,0x20,0x20,0x60,0xC0,0x00,0x00,0x3F,0x20,0x00,0x00,0x38,0x1F,0x00},/*"n",78*/
{0x00,0x80,0xE0,0x20,0x20,0xE0,0x80,0x00,0x00,0x0F,0x38,0x20,0x20,0x38,0x0F,0x00},/*"o",79*/
{0x00,0xE0,0x40,0x20,0x20,0x60,0xC0,0x00,0x00,0xFF,0xC0,0x30,0x20,0x30,0x1F,0x00},/*"p",80*/
{0x00,0x80,0x40,0x60,0x20,0x60,0xE0,0x00,0x00,0x1F,0x30,0x20,0x30,0x20,0xFF,0x00},/*"q",81*/
{0x00,0xE0,0x80,0x40,0x60,0x20,0x20,0x00,0x00,0x01,0x3F,0x20,0x00,0x00,0x00,0x00},/*"r",82*/
{0x00,0xC0,0x60,0x20,0x20,0x20,0x60,0x00,0x00,0x18,0x31,0x22,0x22,0x24,0x1C,0x00},/*"s",83*/
{0x00,0x20,0xA0,0xF8,0x38,0x20,0x60,0x00,0x00,0x00,0x1F,0x31,0x20,0x30,0x10,0x00},/*"t",84*/
{0x00,0xE0,0x20,0x00,0x00,0x00,0xE0,0x00,0x00,0x1F,0x30,0x20,0x30,0x1C,0x3F,0x00},/*"u",85*/
{0x00,0xE0,0x00,0x00,0x00,0x80,0xE0,0x00,0x00,0x03,0x1F,0x30,0x38,0x0F,0x00,0x00},/*"v",86*/
{0x00,0xE0,0x20,0x00,0x00,0x20,0xE0,0x00,0x0F,0x3B,0x20,0x38,0x30,0x20,0x3F,0x0E},/*"w",87*/
{0x00,0x60,0xC0,0x80,0x80,0xC0,0x60,0x00,0x00,0x38,0x0C,0x07,0x07,0x0C,0x38,0x00},/*"x",88*/
{0x00,0xE0,0x00,0x00,0x00,0x00,0xE0,0x00,0x00,0x01,0x0F,0xB8,0xF0,0x1F,0x01,0x00},/*"y",89*/
{0x00,0x60,0x20,0x20,0x20,0xE0,0x60,0x00,0x00,0x18,0x3C,0x22,0x21,0x30,0x10,0x00},/*"z",90*/
{0x00,0x00,0x00,0xFC,0x04,0x04,0x00,0x00,0x00,0x00,0x01,0x3F,0x60,0x40,0x00,0x00},/*"{",91*/
{0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00},/*"|",92*/
{0x00,0x00,0x04,0x04,0xFC,0x00,0x00,0x00,0x00,0x00,0x40,0x60,0x3F,0x01,0x00,0x00},/*"}",93*/
{0x06,0x03,0x01,0x02,0x02,0x04,0x06,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"~",94*/
}; 


/********************************************
		DEM12864B状态检测，从EDM12864B读出数
		据检测标志位BF
********************************************/

void LCD_Busy()
{
	unsigned char busy;
	EN=0;
	DI=0;
	RW=1;
	while(1)
	{
		EN=1;
		delay(1);
		delay(1);
		busy=P0;//读状态标志寄存器
		delay(1);
		EN=0;
		if((busy&0x90)==0)//检测BF和RES位,都为0时表示可进行写入
			break;
	}
}

/************************************
	         写指令
************************************/
void WRCommand_L(unsigned char command) //########140
{
	//CS1=1;
	//CS2=0;
	LCD_Busy();
	DI=0;
	delay(1);
	RW=0;
	delay(1);
	EN=1;
	delay(1);
	P0=command;
	delay(1);
	EN=0;
	delay(1);
}


/****************************************
	  写一个字节的显示数据
****************************************/
void WRdata_L(unsigned char ucdata)
{
	//CS1=1;
	//CS2=0;
	LCD_Busy();
	DI=1;
	delay(1);
	RW=0;
	delay(1);
	EN=1;
	delay(1);
	P0=ucdata;
	delay(1);
	EN=0;
	delay(1);
}


void set_xy(unsigned char x, unsigned char y)
{
	if(y>=64) // 列地址大于等于64时右屏显示
	{
		CS1=1;
		CS2=0;
		y-=64;
	}
	else      // 列地址小于等于64时左屏显示
	{
		CS1=0;
		CS2=1;
	}

	WRCommand_L(0x40|y);  //写页地址
	delay(1);
	WRCommand_L(0xb8|x);  //写页地址
}

void disp_cn(unsigned char x,unsigned char y,unsigned char *p)   //写一个汉字16*16
{
	unsigned char i,j;
	for(i=0;i<2;i++)
	{
		for(j=0;j<16;j++)
		{
			set_xy(x+i, y+j);     //Page x and Col y.    x:0-7  y:0-128
			WRdata_L(*p);         //写数据
			p++;
		}
	}
}//##########255

void xian_shi_tu_pian(unsigned char *p)     //显示图片
{
	unsigned char i,j;
	for(i=0;i<8;i++)
	{
		for(j=0;j<128;j++)
		{
			set_xy(i,j); //设定显示位置page x和 col y     x:0-7   y:0-128
			WRdata_L(*p); //写数据
			p++;
		}
	}
}

// x,y 为坐标，num为要显示的字符
void LCD_ShowChar(unsigned char x,unsigned char y,unsigned char num,unsigned char font_size)
{
    unsigned char temp, t, t1;

	num = num - ' '; //得到偏移后的值（ASCII字库是从空格开始取模，所以-' '就是对应字符的字库）
	if(font_size==12)
	{
		for(t1=0;t1<2;t1++)
		{
			for(t=0;t<font_size/2;t++)
			{
				if(font_size==12)
					temp=asc2_1206[num][t+(font_size/2)*t1];  //调用1206字体
				else if(font_size==16)
					temp=asc2_1608[num][t+(font_size/2)*t1];  //调用1608字体
				else if(font_size==24)
					return;  
					//temp=asc_2412[num][t+(font_size/2)*t1];  //调用2412字体
				else 
					return;  
						
				set_xy(y+t1, x+t);   // 设定显示位置x页和y列   X:0-7   Y:0-128

				WRdata_L(temp); //写数据
			}
		}
	}
	else
	{
		for(t1=0;t1<font_size/8;t1++) //16
		{
			for(t=0;t<font_size/2;t++)  //16/2=8
			{	
				if(font_size==12)
					temp=asc2_1206[num][t+(font_size/2)*t1];  //调用1206字体
				else if(font_size==16)
					temp=asc2_1608[num][t+(font_size/2)*t1];  //调用1608字体         
				else if(font_size==24)
					//temp=asc_2412[num][t+(font_size/2)*t1];  //调用2412字体
					return;          
				else 
					return;                                  //没有的字库
						
				set_xy(y+t1, x+t);   // 设定显示位置x页和y列   X:0-7   Y:0-128

				WRdata_L(temp); //写数据
			}
		}
	}
} //#########360


/*************************************************************
x,y 为坐标 
size 为字的大小 12*12 16*16 24*24
x为列0-127 y为页 0-7
**************************************************************/
void LCD_ShowString(u16 x, u16 y, u8 font_size, u8 *p)
{
	while((*p<='~')&&(*p>=' '))//判断是不是非法字符
	{
		LCD_ShowChar(x,y,*p, font_size);
		x = x + font_size/2;
		p++;
	}
}

// 以下为1602屏幕API
void LCD_Write_Com(uchar com)//写指令函数
{
	RS=0;
	RW=0;
	P0=com;
	EN=1;
	delay_ms(1);
	EN=0;	
}

void LCD_Write_DATA(uchar text)//写数据函数
{
	RS=1;
	RW=0;
	P0=text;
	EN=1;
	delay_ms(1);
	EN=0;
}

/*
LM041L
Line 1: 80 - 8F
Line 2: C0 - CF
Line 3: 90 - 9F
Line 4: D0 - DF
*/
void gotoxy(uchar x,uchar y)//是在x行，y列显示数据
{
	if(x==1)
	{
	   LCD_Write_Com(0x80+y-1);
	}
	if(x==2)
	{
		LCD_Write_Com(0xC0+y-1);
	}	
	if(x==3)
	{
		LCD_Write_Com(0x90+y-1);
	}	
	if(x==4)
	{
		LCD_Write_Com(0xD0+y-1);
	}	
}

void LCD_Write_String(uchar *p)
{
	while(*p!=0)
	{
		LCD_Write_DATA(*p);	
		p++;
	}
}

// lcd_type: LCD1602_2 LCD1602_4 LCD12864
void LCD_Init(u8 lcd_type)
{
    if(lcd_type==LCD1602_2||lcd_type==LCD1602_4)
    {
        LCD_Write_Com(0x38);
        delay_ms(5);
        LCD_Write_Com(0x38);
        delay_ms(5);
        LCD_Write_Com(0x38);
        delay_ms(5);
        LCD_Write_Com(0x38);
        delay_ms(5);
        LCD_Write_Com(0x08);
        LCD_Write_Com(0x01);
        LCD_Write_Com(0x06);
        LCD_Write_Com(0x0c);
    }
    else if(lcd_type==LCD12864)
    {
        CS1=0;
        CS2=0;
        WRCommand_L(0x30);  //基本指令
        WRCommand_L(0x0c);  //开显示，关光标，不闪烁
        WRCommand_L(0x01);
        WRCommand_L(0x06);  //光标移动方向 右自动加1
    }
}
