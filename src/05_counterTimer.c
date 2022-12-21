#include <16f887.h>
#fuses hs       
#use delay (clock=20M) 
#include <TV_LCD.c>     
#include <TV_cd.c>     
#include <TV_7d.c>    
#define up pin_e0
#define down pin_e1 
#define mod pin_e2
#bit t1if = 0x0c.0         
unsigned int8 mode,n=0,max;    
int1 mode_c;                
signed int8 ss,mm,hh,sp; 
void dongho()                         
{                    
   if (t1if==1)     
   {                      
      set_timer1(3036);                                                                                                             
      n++;t1if=0;                  
                        
         if (n==10)                       
         {                          
            n=0;                                                                                                     
            ss++;                   
         }         
   }           
   if (ss==60)  
   {
      ss=0;
      mm++;
      if (mm==60)
      {
         mm=0;
         hh++;
         if (hh==24)
            hh=0;
      }
   }
} 
void timer()
{
   if (mode==0||mode==4||mode==5) dongho();
   if (mode_c==1)
   {
      sp=get_timer0();
      if (sp>max)
         set_timer0(1); 
   }             
   else
   {  
      if (sp<0)
         set_timer0(1);
      sp=get_timer0();
      sp=max-sp;
   }      
} 
void button()                              
{                                  
   if (mode==0) 
      if (inputcd(mod)==0) mode++;
   if (mode==1)
   {
      if (inputcd(up)==0) 
      {
         hh++;
         if (hh==24)
            hh=0;
      }
      if (inputcd(down)==0) 
      { 
         hh--;
         if (hh==-1)
            hh=23;
      }             
      if (inputcd(mod)==0) mode++;
   }
   if (mode==2)
   {
      if (inputcd(up)==0) 
      {
         mm++;
         if (mm==60)
            mm=0;
      }
      if (inputcd(down)==0) 
      { 
         mm--;
         if (mm==-1)
            mm=59;
      }             
      if (inputcd(mod)==0) mode++; 
   }
   if (mode==3)
   {
      if (inputcd(up)==0) 
      {
         ss++;
         if (ss==60)
            ss=0;
      }
      if (inputcd(down)==0) 
      { 
         ss--;
         if (ss==-1)
            ss=59;
      }             
      if (inputcd(mod)==0) mode++;  
   }
   if (mode==4)       
   {
      if (inputcd(up)==0) 
      {
         max++;
         if (max>90)
            max=10;
      }
      if (inputcd(down)==0) 
      {                
         max--;
         if (max<10)
            max=90;  
      }             
      if (inputcd(mod)==0) mode++;       
   }
   if (mode==5)
   {
   if (inputcd(up)==0)       
      {
         mode_c=1;
         set_timer0(0); 
      }
      if (inputcd(down)==0) 
      {                
         mode_c=0;
         set_timer0(0); 
      }             
      if (inputcd(mod)==0) mode=0;      
   }
     
}                         
void lcd()
{
   lcd_position(0,1);         
   lcd_data("NGUYEN QUOC KHANH");
   lcd_position(1,5);         
   printf (lcd_data,"%d : %d : %d ",hh,mm,ss);
   lcd_position(2,0);
   printf (lcd_data,"GH: %d",max); 
   lcd_position(2,13);            
   printf (lcd_data,"SP: %d ",sp);
   if (mode_c==1)
   {
      lcd_position(3,5);
      lcd_data("Dem len  ");
   }                    
   else                  
   {                      
      lcd_position(3,5);   
      lcd_data("Dem xuong");
   }
}                        
                             
void main()   
{
   set_tris_a(0x01);   
   set_tris_b(0);    
   set_tris_c(0);    
   set_tris_d(0);   
   set_tris_e(1);
   setup_timer_0(t0_ext_h_to_l|t0_div_1);
   set_timer0(0);                                 
   setup_timer_1(t1_internal|t1_div_by_8);
   set_timer1(3036);       
   lcd_setup();     
   mode=0; max=10; mode_c=1; 
   while(true)   
   {   
      lcd();
      output_b(ma7d[mode]); 
      timer(); 
      button(); 
   }                                                           
}
