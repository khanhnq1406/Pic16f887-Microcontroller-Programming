#include <16f887.h>  
#include <codeled.c>   
#fuses intrc_io          
#use delay (clock=8M)  
#include <TV_LCD.c>  
#define up pin_e0 
#define down pin_e1
#define mod pin_e2        
void main()           
{  
   set_tris_a(0x0f);     
   set_tris_c(0);              
   set_tris_d(0);          
   set_tris_e(1);  
   output_low(pin_d3); 
   lcd_setup();
   lcd_position(0,1);                
   lcd_data(" Nguyen Quoc Khanh");   
   
   int1 mode=0;     
   signed int8 dem=0,mp;
   while(true)     
   {     
         while (mode==0)
         {  
            output_c(ma7d[dem]);   
            hienthi(dem); 
            lcd_position(1,0);                
            lcd_data(0x7e); 
            lcd_position(1,6);                
            lcd_data("BUTTON");    
            if (inputcd(up)==0)
            {
               dem++;   
               if (dem>9)
                  dem=0;    
            }
            if (inputcd(down)==0)  
            {    
               dem--;
               if (dem<0)
                  dem=9;   
            } 
            if (inputcd(mod)==0)     
            {
               mode=1;     
            }
            while (mode==1)
            {
               mp=KEY4x4();         
               if (mp!= 0xff)
               {
                  output_c(ma7d[mp]);
                  hienthi(mp);      
                  if (mp==15) mode=0;   
               }
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
}     
}
