#include<lpc21xx.h>
void uart0_init(unsigned int baud)
{
unsigned int result=0,pclk;
if(VPBDIV==0)
pclk=15000000;
else if(VPBDIV==1)
pclk=60000000;
else if(VPBDIV==2)
pclk=30000000;
result=pclk/(16*baud);
PINSEL0|=0X5;
U0LCR=0X83;
U0DLL=result&0xff;
U0DLM=(result>>8)&0xff;
U0LCR=0X03;
}
#define THRE ((U0LSR>>5)&1)
void uart0_tx(unsigned char data)
{
U0THR=data;
while(THRE==0);
}
#define RDR (U0LSR&1)
unsigned char uart0_rx()
{
while(RDR==0);
return U0RBR;
}
void uart0_string(char *ptr)
{
while(*ptr!=0)
{
uart0_tx(*ptr);
ptr++;
}
}
void uart0_integer(int num)
{
int a[10],i;
if(num==0)
uart0_tx('0');
if(num<0)
{
uart0_tx('-');
num=-num;
}
i=0;
while(num>0)
{
a[i]=num%10+48;
num=num/10;
i++;
}
for(i=i-1;i>=0;i--)
uart0_tx(a[i]);
}


void uart0_rx_string(unsigned char *ptr,int len)
{
int i;
for(i=0;i<len;i++)
{
while(RDR==0);
ptr[i]=U0RBR;
if(ptr[i]=='\r')
break;
}
ptr[i]='\0';
}

int my_strcmp(char *s1,char*s2)
{
int i=0;
while(s1[i]==s2[i])
{
if(s1[i]=='\0')
return 0;

i++;
}
return s1[i]-s2[i];
}

void my_strcpy(char*src,char*dest)
{
int i=0;
for(i=0;src[i]!='\0';i++)
dest[i]=src[i];

dest[i]='\0';
}
