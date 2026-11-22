#include<lpc21xx.h>
#define ROW_MASK 0X000F0000
#define COL_MASK ((1<<20)|(1<<21)|(1<<22)|(1<<25))
unsigned int col_pins[4]={20,21,22,25};

char keys[4][4]={
                {'1','2','3','A'},
                                {'4','5','6','B'},
                                {'7','8','9','C'},
                                {'*','0','#','D'}
                                };
void delay_misec(unsigned int msec)
{
unsigned int i,j;
for(i=0;i<msec;i++)
 for(j=0;j<6000;j++);
}
void keypad_init(void)
{
   PINSEL1 &= ~0X000C3FFF;               //CONFIG P0.16 TO P0.23

   IODIR0=(IODIR0 & ~COL_MASK)|ROW_MASK;                                    // MAKINGF ROWS AS OUTPUT AND COLUMNS AS INPUT
   IOSET0=ROW_MASK;                                                      // INITIAL ALL ROWS HIGH
}
char keypad_read(void)
{
int r,c;

while(1)
{
     for(r=0;r<4;r++)
         {
           IOSET0=ROW_MASK;

           IOCLR0=(1<<(16+r));
           delay_misec(1);
                    for(c=0;c<4;c++)
                        {
                           if(!(IOPIN0 &(1<<col_pins[c])))
                           {
                           delay_misec(20);
                            if(!(IOPIN0 &(1<<col_pins[c])))
                                {
                                  while(!(IOPIN0 &(1<<col_pins[c])));

                                IOSET0=ROW_MASK;

                                return keys[r][c];
                           }
                        }

                 }
           }

         }
}
