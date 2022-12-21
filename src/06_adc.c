#include <16f887.h>
#device adc = 10
#fuses hs
#use delay (clock=20M)
#include <TV_lcd.c>
#include <TV_cd.c>
#include <TV_7d.c>
#define up pin_e0
#define down pin_e1
#define mod pin_e2
#bit t1if = 0x0c.0
unsigned int8 n=0,t;
signed int8 sens=0;
int1 mode=0;
void timer()
{
   if (t1if==1)
   {
      set_timer1(32411);
      n++;
      t1if=0;
      if (n==100)
      {
         n=0;
         sens++;
         if (sens>3)
            sens=0;
      }
   }
}
void sensor()
{
   if (sens==0)
   {
      set_adc_channel(0); delay_ms(1);
      t=read_adc()/2.046;
   }
   if (sens==1)
   {
      set_adc_channel(1); delay_ms(1);
      t=read_adc()/2.046;
   }
   if (sens==2)
   {
      set_adc_channel(2); delay_ms(1);
      t=read_adc()/2.046;
   }
   if (sens==3)
   {
      set_adc_channel(3); delay_ms(1);
      t=read_adc()/2.046;
   }
}
void button()
{
   if (inputcd(mod)==0)
   {
      mode++;sens=0;
      if (mode>1) mode=0;
   }
   if (mode==1)
   {
      if (inputcd(up)==0)
      {
         sens++;
         if (sens>3) sens=0;
      }
      if (inputcd(down)==0)
      {
         sens--;
         if (sens<0) sens=3;
      }
      if (inputcd(mod)==0)
      {
         mode++;
      }
   }
}
void lcd()
{
   if (mode==0)
   {
      lcd_position(0,5);
      lcd_data("AUTO  ");
   }
   else
   {
      lcd_position(0,5);
      lcd_data("MANUAL");
   }
   lcd_position(1,0);
   printf(lcd_data,"KENH %d: %d  C ",sens,t);
   lcd_position(1,10);
   lcd_data(0xdf);
}
void led7d()
{
   output_b(ma7d[sens]);
}
void main()
{
   set_tris_a(1);
   set_tris_b(0);
   set_tris_c(0);
   set_tris_d(0);
   set_tris_e(1);
   setup_adc(adc_clock_div_32);
   setup_adc_ports(san0 | san1 | san2 | san3 | vss_vdd);
   lcd_setup();
   setup_timer_1(t1_internal|t1_div_by_8);
   set_timer1(32411);
   while(true)
   {
      lcd();
      if (mode==0) timer(); //mode=0: che do auto, mode=1: che do manual
      sensor();
      led7d();
      button();
   }
}
