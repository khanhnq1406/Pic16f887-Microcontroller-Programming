//!#define output_key output_port
//!#define pin_0  pin_a0
//!#define pin_1  pin_a1
//!#define pin_2  pin_a2
//!#define pin_3  pin_a3
unsigned int8 KEY_4X4()
{             
   const unsigned int8 mq[4]={0xef,0xdf, 0xbf, 0x7f};
   unsigned int8 mp= 0xff,cot;
   for (cot=0;cot<4;cot++)
   {
      output_a(mq[cot]);
      while (input(pin_a0)==0)   mp=cot*4+0; 
      while (input(pin_a1)==0)   mp=cot*4+1;  
      while (input(pin_a2)==0)   mp=cot*4+2;  
      while (input(pin_a3)==0)   mp=cot*4+3;    
   }            
   return mp; 
      
}
//!void main()
//!{
//!      unsigned int8 maphim;
//!      set_tris_b(0x0f);
//!      while(true)
//!      {
//!         maphim=quetphim();
//!         delay_ms(20);
//!         if(maphim!=0xff)
//!         {
//!            hienthi(maphim);
//!         }
//!      }
//!      
//!}
