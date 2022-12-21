#include <16f887.h>
#fuses hs 
#use delay (clock = 20M)
#use rs232(baud=9600,xmit=pin_c6,rcv=pin_c7)
#include <TV_LCD.c>
unsigned int8 sp,tnhan,ss,mm,hh,n=0;
void lcd()
{
   lcd_position(0,0);
   printf (lcd_data,"GUI SP: %d  ",sp);
   lcd_position(1,0);
   printf (lcd_data,"NHAN NHIET DO: %u",tnhan);
   lcd_data(0xdf);
   lcd_data(0x43);
   lcd_data(" ");
   lcd_position(2,6);
   printf(lcd_data,"%d:%d:%d    ",hh,mm,ss);
}
void demsp()
{
   sp=get_timer0();
   if (sp==100)
   {
      set_timer0(0);
      sp=0;
   }
   putc(sp);
}
void dongho()
{
   if (n==10)
   {
      set_timer1(3036);
      n=0; 
      ss++;
   }
   if (ss==60)
   {
      ss=0;
      mm++;
      if (mm==60)
      {
         mm=0;
         hh++;
         if (hh==24)
            hh=0;
      }
   }
}
void main()
{
   set_tris_a(1);
   set_tris_c(0x80);
   set_tris_d(0);
   lcd_setup();
   setup_timer_0(t0_ext_h_to_l|t0_div_1);
   set_timer0(0);
   setup_timer_1(t1_internal|t1_div_by_8);
   set_timer1(3036);
   enable_interrupts(int_rda);
   enable_interrupts(int_timer1);
   enable_interrupts(global);
   while (true)
   {
      dongho();
      demsp();
      lcd();
   }
}
#int_rda
void nhant()
{
   tnhan=getc();
}
#int_timer1
void ngattimer1()
{
   n++;
}
