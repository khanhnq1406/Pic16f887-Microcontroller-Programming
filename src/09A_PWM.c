#include <16f887.h>
#device adc=10
#fuses hs
#use delay (clock=20M)
#use rs232(baud=9600,xmit=pin_c6,rcv=pin_c7)
#include <TV_LCD.c>

unsigned int16 t, nhanduty[2];
int1 chieu;
unsigned int8 sobyte;
void lcd()
{
   lcd_position(0,0);
   printf (lcd_data,"NHIET DO: %lu",t);
   lcd_position(1,0);
   if (chieu==0)
   {
      lcd_data("QUAY THUAN  ");
   }
   else
   {
      lcd_data("QUAY NGHICH");
   }
   lcd_position(2,0);
   printf(lcd_data,"DUTY: %lu   ",nhanduty[0]*256+nhanduty[1]);
}
void temp()
{
   t=read_adc()/2.046;
   putc(t);
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
   enable_interrupts(int_rda);
   enable_interrupts(global);
   while (true)
   {
      temp();
      lcd();
   }
}
#int_rda
void nhan()
{
   chieu=getc();
   for (sobyte=0;sobyte<2;sobyte++)
   {
      nhanduty[sobyte]=getc();
   }
}
