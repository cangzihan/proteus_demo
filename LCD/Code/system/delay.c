#include<reg52.h>
#include"delay.h"

void delay_ms(unsigned int time)
{
    unsigned int i,j;
	for(i=0;i<time;i++)
	   for(j=0;j<122;j++);
}


void delay(unsigned int cnt)
{
    while(--cnt);
}

