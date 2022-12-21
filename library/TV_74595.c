void xuat1byte (unsigned int32 dl)                                             
{                         
   signed int8 n;       
   for (n=23;n>=0;n--)              
   {                      
      output_bit(pin_d0, bit_test(dl,n));
      output_low(pin_d1);output_high(pin_d1);
   }                                                     
}
void xuatled(unsigned int32 led)
{
   xuat1byte(led>>16); 
   xuat1byte(led>>8);     
   xuat1byte(led); 
   output_low(pin_d2);  output_high(pin_d2);                                    
}
//!void main()
//!{                  
//!   set_tris_a(0x0f);     
//!   output_low(pin_d3);     
//!}    
