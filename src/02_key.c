#include <16f887.h>           
#fuses intrc_io          
#use delay (clock=8M)        
#define up pin_e0         
#define dow pin_e1        
#define mod pin_e2          
unsigned int32 led;                  
signed int8 n,m,mp;                    
//void updown();                                                                     
int1 inputcd(int16 pin)  
{                                   
   if (input(pin)==0)          
   {                                      
      delay_ms(20);
      if (input(pin)==0)                               
         return 0;          
   }                         
   return 1;
}    
  
unsigned int8 KEY_4x4()  
{
   const unsigned int8 mq[4]={0xef,0xdf,0xbf,0x7f};
   unsigned int8 mp=0xff,cot;                  
   for (cot=0;cot<4;cot++)
   {                              
      output_a(mq[cot]);       
      while (input(pin_a0)==0) mp=cot*4+0;  
      while (input(pin_a1)==0) mp=cot*4+1;  
      while (input(pin_a2)==0) mp=cot*4+2;  
      while (input(pin_a3)==0) mp=cot*4+3;   
   }   
   return mp;       
}  

void choptat()      
{          
   led = 0xff;  
   output_b(led);   
   output_c(led);   
   output_d(led);   
   delay_ms(500);
   led = 0;
   output_b(led);   
   output_c(led);   
   output_d(led);      
   delay_ms(500);  
      
}   
void sangtatdan()      
{    
   for (n=24;n>=0;n--)
   {
      led = 0xffffff>>n;     
      output_b(led);   
      output_c(led>>8);   
      output_d(led>>16);
      delay_ms(50);
   }
   for (n=0;n<=24;n++)
   {
      led = 0xffffff>>n;    
      output_b(led);   
      output_c(led>>8);    
      output_d(led>>16);
      delay_ms(50);    
   }       
}          
void sangdichpt()
{
   for (n=0;n<=24;n++)
   {
      led = 0x000001<<n;                                       
      output_b(led);   
      output_c(led>>8);    
      output_d(led>>16);    
      delay_ms(50);
   }           
}
void sangdichtp() 
{
   for (n=0;n<=24;n++)
   {
      led = 0x800000>>n;
      output_b(led);   
      output_c(led>>8);    
      output_d(led>>16);    
      delay_ms(50);    
   }            
}
void sangnt()
{
   for (n=24;n>=12;n--)      
   {                                      
      led = (0xffffff>>n)|(0xffffff<<n);  
      output_b(led);
      output_c(led>>8);    
      output_d(led>>16);    
      delay_ms(50);    
   }                 
} 
void tattn()
{
   for (n=12;n<=24;n++)
   {
      led = (0xffffff<<n)|(0xffffff>>n);
      output_b(led);   
      output_c(led>>8);    
      output_d(led>>16);    
      delay_ms(50); 
   }                 
}                           
void sangtn()
{
   for (n=12;n>=0;n--)      
   {                                      
      led = (0xffffff<<n)&(0xffffff>>n);  
      output_b(led);
      output_c(led>>8);    
      output_d(led>>16);    
      delay_ms(50);    
   }                 
} 
void tatnt()
{
   for (n=0;n<=12;n++)
   {                              
      led = (0xffffff<<n) & (0xffffff>>n) ;
      output_b(led);
      output_c(led>>8);    
      output_d(led>>16);    
      delay_ms(50);   
   }  
}
void sangdontp()
{
   for (n=24;n>=0;n--)
   {                
      led = 0xffffff>>n; 
      for (m=0;m<=n-1;m++)
      {
         led = (0x800000>>m)| (0xffffff>>n) ;
         output_b(led);                                                          
         output_c(led>>8);    
         output_d(led>>16);    
         delay_ms(50); 
      }
   }     
} 
void sangdonpt()
{                                      
   for (n=24;n>=0;n--)
   {                         
      led = 0xffffff<<n;  
      for (m=24;m>=24-n;m--) 
      {                        
         led = (0x800000>>m) | (0xffffff<<n);    
         output_b(led);                                                          
         output_c(led>>8);    
         output_d(led>>16);       
         delay_ms(50);
      }               
   }        
} 
void updown(signed int8 dem)  
{ 
                        
   if (dem==0) choptat();  
   if (dem==1) sangtatdan();
   if (dem==2) sangdichpt();
   if (dem==3) sangdichtp(); 
   if (dem==4) sangnt();      
   if (dem==5) tattn();        
   if (dem==6) sangtn();
   if (dem==7) tatnt();                    
   if (dem==8) sangdontp();
   if (dem==9) sangdonpt(); 
                                  
}                      
void main()                  
{                 
   set_tris_a(0x0f);                                             
   set_tris_b(0);          
   set_tris_c(0); 
   set_tris_d(0);                     
   set_tris_e(1);    
   signed int8 dem=0;
   int1 mode=0;          
   while(true)                                                     
   {                    
           
         while(mode==0) 
         {                                  
                 updown(dem);    
                 if (inputcd(up)==0)    
                 {                       
                    dem++;                  
                    if(dem>9)                   
                        dem=0;  
                 }                       
                 if (inputcd(dow)==0)    
                 {                    
                     dem--;             
                     if(dem<0)     
                        dem=9;     
                 }
                 if (inputcd(mod)==0)    
                 {
                     mode=1;    
                 }            
               }                     
               while(mode==1)   
               {                          
                  mp= KEY_4x4();   
                  updown(mp);   
                  if (mp==15) mode=0;                                                 
                }
  
   }     
}
                                                             
//!      sangtatdan();                       
//!      sangdichpt();            
//!      sangdichtp() ;    
//!      sangnt(); 
//!      tattn();   
//!      sangtn();        
//!      tatnt();  
//!      sangdontp();
//!      sangdonpt();       
