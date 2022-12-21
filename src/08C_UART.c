#include <16f887.h>
#device adc=10
#fuses hs 
#use delay (clock = 20M)
#use rs232(baud=9600,xmit=pin_c6,rcv=pin_c7)
#include <TV_LCD.c>
unsigned int16 t;
unsigned int8 nhan;
void nhietdo()
{
   if (nhan=='C')
   {
      t=read_adc()/2.046;
      putc(t/10+0x30);
      putc(t%10+0x30);
      printf("NHIETDO: %lu  ",t);
      delay_ms(100);
   }
   else if (nhan=='D')
      continue;
}
void main()
{
   set_tris_a(1);
   set_tris_c(0x80);
   setup_adc(adc_clock_div_32);
   setup_adc_ports(san0|vss_vdd);
   set_adc_channel(0);
   delay_ms(1);
   enable_interrupts(int_rda);
   enable_interrupts(global);
   while(true)
   {
      nhietdo();
   }
}
#int_rda
void nhanthongtin()
{
   nhan=getc();
}
