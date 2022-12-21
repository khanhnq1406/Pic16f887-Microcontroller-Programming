#include <16f887.h>
#device adc=10
#fuses intrc
#use delay (clock=8M)
#include <TV_LCD.c>
#include <TV_cd.c>
unsigned int16 t,duty,encoder;
signed int8 cap=0;
void lcd()
{
   lcd_position(3,3);
   lcd_data("MSSV: 19151140");
   lcd_position(0,3);
   printf (lcd_data,"Nhiet do: %lu",t);
   lcd_data(0xdf);
   lcd_data(0x43);
   lcd_data(" ");
   lcd_position(1,3);
   printf (lcd_data,"Cap toc do: %d",cap);
   lcd_position(2,0);
   printf (lcd_data,"Toc do DC: %lu (rpm)",encoder);
}
void nhietdo()
{
   t=read_adc()/6.82;
}
void dongco()
{
   if (cap==0) //0%
   {
      duty=0;
   }
   else if (cap==1) //25%
   {
      duty=50;
   }
   else if (cap==2) //59%
   {
      duty=100;
   }
   else if (cap==3) //75%
   {
      duty=150;
   }
   else if (cap==4) //100%
   {
      duty=200;
   }
   output_high(pin_c0);
   output_low(pin_c1);
   set_pwm1_duty(duty);
   //delay_ms(10);
}
void captocdo()
{
   if (inputcd(pin_e0)==0)
   {
      cap++;
      if (cap>4)  
         cap=0;
   }
   if (inputcd(pin_e1)==0)
   {
      cap--;
      if (cap<0)  
         cap=4;
   }
}
void main()
{
   set_tris_a(1);
   set_tris_c(0);
   set_tris_d(0);
   set_tris_e(1);
   lcd_setup();
   setup_adc(adc_clock_div_32);
   setup_adc_ports(san0|vref_vref);
   set_adc_channel(0);
   delay_ms(1);
   setup_timer_2(t2_div_by_16,49,1); //T=0.4ms, PR2=49, dutymax=200
   setup_ccp1(ccp_pwm);
   
   while (true)
   {
      lcd();
      nhietdo();
      captocdo();
      dongco();
     
   }
}
