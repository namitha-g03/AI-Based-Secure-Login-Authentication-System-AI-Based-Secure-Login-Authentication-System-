#include<lpc21xx.h>
 #include"header.h"
 #define LED1 0XF
 #define LED2 0XFF
 int main()
 {
 int i,rfidcount=0,passcount=0;
 char key,password[5],pass[5]="1918";
 unsigned char rfid_og[13]="4900C8E53F5B",rfid[13];
 IODIR0|=0XFF;
 IOSET0=0XFF;
 keypad_init();
 lcd_init();
 uart0_init(9600);
 while(1)
 {

          uart0_string("\r\n SCAN RFID:");
          uart0_rx_string(rfid,12);
          uart0_string(rfid);
          IOSET0=0XFF;
          if(my_strcmp(rfid_og,rfid)==0)
          {

                  uart0_string("\r\n VALID RFID CARD");
                          lcd_cmd(0x01);
                          lcd_string("RFID VERIFIED");
                          delay_ms(100);
                          l:
                          lcd_cmd(0x01);
                          lcd_string("ENTER PASSWORD") ;
                          uart0_string("\r\n ENTER PASSWORD:");
                          for(i=0;i<4;i++)
                          {
                          key=keypad_read();
                          password[i]=key;
                          uart0_tx(key);
                          }
                          password[4]='\0' ;

                          if(my_strcmp(password,pass)==0)
                          {

                          IOCLR0=LED1;
                          uart0_string("\r\nAI STATUS : VERIFIED") ;
                          lcd_cmd(0x01);
                          lcd_string("ACCESS GRANTED");
                          return;
                          }
                          else
                          {
                                 passcount++;
                          if(passcount<=3)
                          {
                          IOCLR0=LED2;
                          uart0_string("\r\nWARNING : INVALID PASSWORD");
                          lcd_cmd(0x01);
                          lcd_string("INVALID PASSWORD");
                          goto l;
                          }
                          else
                          {
               uart0_string("\r\nACCESS DENIED");
                           return ;
                          }
                          }
         }
         else
         {
                                rfidcount++;
         if(rfidcount<=2)
         {
         uart0_string("\r\n INVALID RFID");
         lcd_cmd(0x01);
         lcd_string("INVALID RFID")      ;
         }
         else
         {
         uart0_string("\r\nINVALID USER");
         return;
         }
         }
 }
 }
