#include <16f887.h>
#fuses hs
#use delay (clock=20M)
#use rs232(baud=9600,xmit=pin_c6,rcv=pin_c7)
#include <TV_cd.c>
unsigned int8 t;
unsigned int16 duty;
int1 chieu=0;
void daochieu()
{
   if (inputcd(pin_e0)==0)
   {
      chieu=!chieu;
      putc(chieu);
   }
}
void dieukhien()
{
   if (chieu==0)
   {
      output_high(pin_c0);
      output_low(pin_c1);
      if (t<40)
      {
         duty=250;
      }
      else if (t>=40 && t<50)
      {
         duty=500;
      }
      else if (t>=50 && t<60)
      {
         duty=750;
      }
      else if (t>=40)
      {
         duty=1000;
      }
      set_pwm1_duty(duty);
      delay_ms(10);
      putc(duty>>8);
      putc(duty&0x00ff);
      delay_ms(100);
   }
   else
   {
      output_high(pin_c1);
      output_low(pin_c0);
      if (t<40)
      {
         duty=250;
      }
      else if (t>=40 && t<50)
      {
         duty=500;
      }
      else if (t>=50 && t<60)
      {
         duty=750;
      }
      else if (t>=40)
      {
         duty=1000;
      }
      set_pwm1_duty(duty);
      delay_ms(10);
      putc(duty>>8);
      putc(duty&0x00ff);
      delay_ms(100);
   }

}
void main()
{
   set_tris_e(1);
   set_tris_c(0x80);
   setup_timer_2(t2_div_by_16,249,1);
   setup_ccp1(ccp_pwm);
   enable_interrupts(int_rda);
   enable_interrupts(global);
   while (true)
   {
      daochieu(); dieukhien();
   }
}
#int_rda
void nhant()
{
   t=getc();
}
