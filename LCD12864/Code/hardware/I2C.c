#include"I2C.h"
#include"delay.h"

bit ack;  /*Ӧ���־λ*/

void Start_I2c()
{
  SDA=1;         /*������ʼ�����������ź�*/
  delay(1);
  SCL=1;
  delay(5);    
  SDA=0;         /*������ʼ�ź�*/
  delay(5);     
  SCL=0;       /*ǯסI2C���ߣ�׼�����ͻ�������� */
  delay(2);
}
void Stop_I2c()
{
  SDA=0;      /*���ͽ��������������ź�*/
  delay(1);       /*���ͽ���������ʱ���ź�*/
  SCL=1;      /*������������ʱ�����4��s*/
  delay(5);
  SDA=1;      /*����I2C���߽����ź�*/
  delay(4);
}
void SendByte(unsigned char c)
{
 unsigned char BitCnt; 
 for(BitCnt=0;BitCnt<8;BitCnt++)  /*Ҫ���͵����ݳ���Ϊ8λ*/
    {
     if((c<<BitCnt)&0x80)SDA=1;   /*�жϷ���λ*/
       else SDA=0;                
     SCL=1;               /*��ʱ����Ϊ�ߣ�֪ͨ��������ʼ��������λ*/
     delay(5);         
     SCL=0; 
    }   
    delay(2);
    SDA=1;                /*8λ��������ͷ������ߣ�׼������Ӧ��λ*/
    delay(2);   
    SCL=1;
    delay(3);
    if(SDA==1)ack=0;     
       else ack=1;        /*�ж��Ƿ���յ�Ӧ���ź�*/
    SCL=0;
    delay(2);
}
/*******************************************************************
	����Ҫת����ģ���������ݴ����PCF8591             
*******************************************************************/
bit DACconversion(unsigned char sla,unsigned char c,  unsigned char Val)
{
   Start_I2c();              //��������
   SendByte(sla);            //����������ַ
   if(ack==0)return(0);
   SendByte(c);              //���Ϳ����ֽ�
   if(ack==0)return(0);
   SendByte(Val);            //����DAC����ֵ  
   if(ack==0)return(0);
   Stop_I2c();               //��������
   return(1);
}