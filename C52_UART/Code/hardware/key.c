#include<reg52.h>
#include"delay.h"
#include"key.h"

sbit Key1=P3^2;
sbit Key2=P3^3;
sbit Key3=P3^4;
sbit Key4=P3^5;

unsigned char switchs(void)
{
  if(Key1==0)
	{
		delay(10);
    if(Key1==0)
    {
			while(Key1==0);
			return 1;
    }
  }
	
  if(Key2==0)
	{
		delay(10);
    if(Key2==0)
    {
			while(Key2==0);
			return 2;
    }
  }  
	
	if(Key3==0)
	{
		delay(10);
    if(Key3==0)
    {
			while(Key3==0);
			return 3;
    }
  }  
	
	if(Key4==0)
	{
		delay(10);
    if(Key4==0)
    {
			while(Key4==0);
			return 4;
    } 
  }
	
	return 0;
}
