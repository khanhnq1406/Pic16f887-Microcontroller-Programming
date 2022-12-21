#include <16f887.h>
#fuses hs
#use delay (clock=20M)
#use rs232(baud=4800,xmit=pin_c6,rcv=pin_c7)
#include <TV_lcd.c>
#include <TV_cd.c>
unsigned int8 spnhan;
void lcd()
{
   lcd_position(0,0);
   printf (lcd_data,"SP nhan: %u",spnhan);
}

void main()
{
   set_tris_c(0x80);
   set_tris_d(0);
   set_tris_e(1);
   lcd_setup();
   enable_interrupts(int_rda);
   enable_interrupts(global);
   while (true)
   {
      lcd();
      if (inputcd(pin_e0)==0)
      {
         putc('S'); delay_ms(100);
      }
   }
}
#int_rda
void ngatnhansp()
{
   spnhan = getc();
}
