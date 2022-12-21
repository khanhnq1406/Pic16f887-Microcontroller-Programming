#include <16f887.h>
#fuses intrc_io          
#use delay (clock=8M)   
#define up pin_e0 
#define down pin_e1
#define mod pin_e2
unsigned int32 led;         
signed int8 n,m,dem=0,mp,chung;    int1 mode=0,next;     
unsigned int16 ma7d[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};   
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
int1 inputcd(int16 pin)
{                                                  
   if (input(pin)==0)
   {
      delay_ms(150);          
      if (input(pin)==0)        
         return 0; 
   }
   return 1;
} 
unsigned int8 KEY4x4()
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
void updown();  
void banphim(); 
     
void choptat()                                                                
{     
   updown(); 
   banphim(); 
   led = 0xffffff;  
   updown(); 
   banphim(); 
   xuatled(led);
   updown(); 
   banphim();  
   delay_ms(500);              
   led = 0;    
   updown(); 
   banphim(); 
   xuatled(led); 
   delay_ms(500); 
   updown();    
   banphim();  
}        
void sangtatdan()
{
   for (n=24;n>=0;n--)
   {
      if (next==1) break;
      led = 0xffffff>>n;    
      xuatled(led);                                               
      delay_ms(50);
       updown();
       banphim();   
   }              
   for (n=0;n<=24;n++)
   {   
      if(next==1) break;
      led = 0xffffff>>n;    
      xuatled(led);    
      delay_ms(50);      
      updown();      
      banphim(); 
                   
   }       
}          
void sangdichpt()     
{
   for (n=0;n<=24;n++)
   {     
      
      led = 0x000001<<n;
      xuatled(led);      
      delay_ms(50);
      updown();
      banphim();
      if (next==1) break; 
   }
}
void sangdichtp()         
{
   for (n=0;n<=24;n++)
   {    
      
      led = 0x800000>>n;
      xuatled(led);     
      delay_ms(50);
       updown();
       banphim(); 
       if (next==1) break;
   }
}
void sangnt()
{
   for (n=24;n>=12;n--)      
   {  
      
      led = (0xffffff>>n)|(0xffffff<<n);  
      xuatled(led);       
      delay_ms(50);
       updown();
       banphim();  if (next==1) break;             
   }                 
} 
void tattn()
{
   for (n=12;n<=24;n++)
   {    
      
      led = (0xffffff<<n)|(0xffffff>>n);
      xuatled(led);      
      delay_ms(50);
       updown();
       banphim();   if (next==1) break; 
   }                 
} 
void sangtn()
{
         
   for (n=12;n>=0;n--)      
   {  
       
      led = (0xffffff<<n)&(0xffffff>>n);  
      xuatled(led);       
      delay_ms(50);
       updown();
       banphim();  if (next==1) break;  
   }                 
} 
void tatnt()
{                                     
   for (n=0;n<=12;n++)
   {   
      
      led = (0xffffff<<n) & (0xffffff>>n) ;
      xuatled(led);       
      delay_ms(50);
       updown();
       banphim();        if (next==1) break;
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
         xuatled(led);       
         delay_ms(50);
       updown();
       banphim();  if (next==1) break; 
      }
      if (next==1) break; 
   }     
} 
void sangdonpt()
{                                      
   for (n=24;n>=0;n--)
   {                  
      
      led = 0xffffff<<n;  
      for (m=24;m>=24-n;m--) 
      {      
         if (next==1) break;
         led = (0x800000>>m) | (0xffffff<<n);    
         xuatled(led);         
         delay_ms(50);
         updown();
         banphim(); if (next==1) break;            
      } if (next==1) break;              
   }                     
}                  
void hienthi()
{
   if (chung==0) choptat(); 
   if (chung==1) sangtatdan();   
   if (chung==2) sangdichpt(); 
   if (chung==3) sangdichtp(); 
   if (chung==4) sangnt();  
   if (chung==5) tattn();           
   if (chung==6) sangtn(); 
   if (chung==7) tatnt();  
   if (chung==8) sangdontp(); 
   if (chung==9) sangdonpt(); 
}  
void updown()       
{                
if (mode==0)
{    
   output_c(ma7d[chung]); 
   if (inputcd(up)==0)  
   {                      
      dem++;chung=dem; next=1; 
      if (dem>9)
      {  
         dem=0;
         chung=0;
          
      }
   }          
   if (inputcd(down)==0)  
   {    
      dem--; chung=dem; next=1;                
      if (dem<0) 
      {       
         dem=9;
         chung=9;  
      }
   }                            
   if (inputcd(mod)==0)     
   {              
      mode=1; chung=0;  next=1;                                                                                                                           
   }
}
}  
void banphim()        
{
   if (mode==1)
   { 
   mp=KEY4x4();
   output_c(ma7d[chung]); 
   if (mp!= 0xff)
   {  
      if (mp==15)   
      {mode=0;chung=0;next=1;} 
             
      chung=mp; next=1;   
        
   }
   }
} 
void main()           
{  
   set_tris_a(0x0f); 
   set_tris_b(0);     
   set_tris_c(0);
   set_tris_d(0); 
   set_tris_e(1); 
   output_low(pin_d3);                         
   dem=0;mode=0; 

   while(true)     
   {      
      next=0;  
      updown();
      banphim();
      hienthi();
   }

}     

   //!      choptat();           
//!      sangtatdan();    
//!      sangdichpt();            
//!      sangdichtp() ;
//!      sangnt();  
//!      tattn();   
//!      sangtn(); 
//!      tatnt();  
//!      sangdontp(); 
//!      sangdonpt();   
