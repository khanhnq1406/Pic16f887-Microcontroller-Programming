#include <16f887.h>
#fuses hs
#use delay (clock=20M)
#use rs232(baud=4800,xmit=pin_c6,rcv=pin_c7)

unsigned int16 ac[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
unsigned int8 sp,dung;
int1 mode=1;
void demsp()
{
   sp=get_timer0();
   if (sp>24)
   {
      set_timer0(1);
   }
   putc(sp); delay_ms(100);
}
void led7d()
{
   output_b(ac[sp/10]);
   output_d(ac[sp%10]);
}
void chedodung()
{
   if (dung=='S')
   {
      mode=0;
   }
}
void main()
{
   set_tris_a(1);
   set_tris_b(0);
   set_tris_c(0x80);
   set_tris_d(0);
   setup_timer_0(t0_ext_h_to_l|t0_div_1);
   set_timer0(0);
   enable_interrupts(int_rda);
   enable_interrupts(global);
   while(true)
   {
      if (mode==1)
         demsp();
      led7d();
      chedodung();
   }
}
#int_rda
void nhandung()
{
   dung=getc();
}
