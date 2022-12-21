#include <16f887.h>
#device adc=10;
#fuses hs
#use delay(clock=20M)
#include <TV_LCD.c>
unsigned int16 t1,t2,t3,n0=0,n1=0,n2=0;
unsigned int8 c0=0,c1=0,c2=0;
void lcd()
{
   lcd_position(0,0);
   printf(lcd_data,"%lu",t1); lcd_data(0xdf);lcd_data(0x43);lcd_data(" ");
   lcd_position(1,0);
   printf(lcd_data,"%lu",t2);lcd_data(0xdf);lcd_data(0x43);lcd_data(" ");
   lcd_position(2,0);
   printf(lcd_data,"%lu",t3);lcd_data(0xdf);lcd_data(0x43);lcd_data(" ");
   lcd_position(0,15);
   printf (lcd_data,"%d  ",c0);
   lcd_position(1,15);
   printf (lcd_data,"%d  ",c1);
   lcd_position(2,15);
   printf (lcd_data,"%d  ",c2);
}
void count()
{
   if (n0>=44)
   {
      n0=0;
      c0++;
      if (c0==100)
      {
         c0=0;
      }
   }
   if (n1>=10)
   {
      n1=0;
      c1++;
      if (c1==100)
      {
         c1=0;
      }
   }
   if (n2>=160)
   {
      n2=0;
      c2++;
      if (c2==100)
      {
         c2=0;
      }
   }
}
void main()
{
   set_tris_a(1);
   set_tris_c(0);
   set_tris_d(0);
   lcd_setup();
   setup_adc(adc_clock_div_32);
   setup_adc_ports(san0|san1|san2|vss_vdd);
   setup_timer_0(t0_internal|t0_div_256);
   set_timer0(34);
   setup_timer_1(t1_internal|t1_div_by_8);
   set_timer1(3036);
   setup_timer_2(t2_div_by_16,244,16);
   set_timer2(0);
   enable_interrupts(int_ad);
   enable_interrupts(int_timer0);
   enable_interrupts(int_timer1);
   enable_interrupts(int_timer2);
   enable_interrupts(global);
   while(true)
   {
      read_adc(adc_start_only);
      count();
      lcd();
   }
}
#int_ad
void ngatadc()
{
   set_adc_channel(0);
   t1=read_adc()/2.046;
   set_adc_channel(1);
   t2=read_adc()/2.046;
   set_adc_channel(2);
   t3=read_adc()/2.046;
}
#int_timer0
void ngattimer0()
{
   n0++;
   set_timer0(34);
}
#int_timer1
void ngattimer1()
{
   n1++;
   set_timer1(3036);
}
#int_timer2
void ngattimer2()
{
   n2++;
}
