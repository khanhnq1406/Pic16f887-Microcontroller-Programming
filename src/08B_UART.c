#include <16f887.h>
#device adc=10
#fuses hs 
#use delay (clock = 20M)
#use rs232(baud=9600,xmit=pin_c6,rcv=pin_c7)
#include <TV_LCD.c>
unsigned int8 spnhan,n=0,ss,mm,hh;
unsigned int16 t;
void lcd()
{
   lcd_position(0,0);
   printf (lcd_data,"NHAN SP: %d  ",spnhan);
   lcd_position(1,0);
   printf (lcd_data,"GUI NHIET DO: %lu",t);
   lcd_data(0xdf);
   lcd_data(0x43);
   lcd_data(" ");
   lcd_position(2,6);
   printf(lcd_data,"%d:%d:%d    ",hh,mm,ss);
}
void nhietdo()
{
   t=read_adc()/2.046;
   putc(t);
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
   setup_adc(adc_clock_div_32);
   setup_adc_ports(san0|vss_vdd);
   set_adc_channel(0);
   delay_ms(1);
   setup_timer_1(t1_internal|t1_div_by_8);
   set_timer1(3036);
   enable_interrupts(int_rda);
   enable_interrupts(int_timer1);
   enable_interrupts(global);
   while (true)
   {
      dongho();
      nhietdo();
      lcd();
   }
}
#int_rda
void ngatnhan()
{
   spnhan=getc();
}

#int_timer1
void ngattimer1()
{
   n++;
}
