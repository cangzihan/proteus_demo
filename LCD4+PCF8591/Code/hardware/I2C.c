#include"I2C.h"
#include"delay.h"

bit ack;  /*应答标志位*/

void Start_I2c()
{
  SDA=1;         /*发送起始条件的数据信号*/
  delay(1);
  SCL=1;
  delay(5);    
  SDA=0;         /*发送起始信号*/
  delay(5);     
  SCL=0;       /*钳住I2C总线，准备发送或接收数据 */
  delay(2);
}
void Stop_I2c()
{
  SDA=0;      /*发送结束条件的数据信号*/
  delay(1);       /*发送结束条件的时钟信号*/
  SCL=1;      /*结束条件建立时间大于4μs*/
  delay(5);
  SDA=1;      /*发送I2C总线结束信号*/
  delay(4);
}
void SendByte(unsigned char c)
{
 unsigned char BitCnt; 
 for(BitCnt=0;BitCnt<8;BitCnt++)  /*要传送的数据长度为8位*/
    {
     if((c<<BitCnt)&0x80)SDA=1;   /*判断发送位*/
       else SDA=0;                
     SCL=1;               /*置时钟线为高，通知被控器开始接收数据位*/
     delay(5);         
     SCL=0; 
    }   
    delay(2);
    SDA=1;                /*8位发送完后释放数据线，准备接收应答位*/
    delay(2);   
    SCL=1;
    delay(3);
    if(SDA==1)ack=0;     
       else ack=1;        /*判断是否接收到应答信号*/
    SCL=0;
    delay(2);
}
/*******************************************************************
	将需要转换成模拟量的数据传输给PCF8591             
*******************************************************************/
bit DACconversion(unsigned char sla,unsigned char c,  unsigned char Val)
{
   Start_I2c();              //启动总线
   SendByte(sla);            //发送器件地址
   if(ack==0)return(0);
   SendByte(c);              //发送控制字节
   if(ack==0)return(0);
   SendByte(Val);            //发送DAC的数值  
   if(ack==0)return(0);
   Stop_I2c();               //结束总线
   return(1);
}


void Ack_I2c(bit a)
{
  
  if(a==0)SDA=0;              /*在此发出应答或非应答信号 */
  else SDA=1;
  delay(3);      
  SCL=1;
  delay(5);  
  SCL=0;                     /*清时钟线，钳住I2C总线以便继续接收*/
  delay(2);    
}

unsigned char   RcvByte()
{
  unsigned char  retc;
  unsigned char  BitCnt;
  
  retc=0; 
  SDA=1;                       /*置数据线为输入方式*/
  for(BitCnt=0;BitCnt<8;BitCnt++)
      {
        delay(2);           
        SCL=0;                  /*置时钟线为低，准备接收数据位*/
        delay(5);
        SCL=1;                  /*置时钟线为高使数据线上数据有效*/
        delay(2);
        retc=retc<<1;
        if(SDA==1)retc=retc+1;  /*读数据位,接收的数据位放入retc中 */
        delay(2); 
      }
  SCL=0;    
  delay(2);
  return(retc);
}

bit ISendByte(unsigned char sla,unsigned char c)//发送数据或命令函数
{
   Start_I2c();              //启动总线
   SendByte(sla);            //发送器件地址
   if(ack==0)return(0);
   SendByte(c);              //发送数据
   if(ack==0)return(0);
   Stop_I2c();               //结束总线
   return(1);
}

/*******************************************************************
ADC读字节数据函数               
*******************************************************************/
unsigned char IRcvByte(unsigned char sla)
{  unsigned char c;

   Start_I2c();          //启动总线
   SendByte(sla+1);      //发送器件地址
   if(ack==0)return(0);
   c=RcvByte();          //读取数据0

   Ack_I2c(1);           //发送非就答位
   Stop_I2c();           //结束总线
   return(c);
}