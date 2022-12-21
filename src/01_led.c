#include <16f887.h>
#fuses hs
#use delay (clock=20M)
unsigned int32 led;  
signed int8 n,m;
void choptat()      
{
   led = 0xff;  
   output_b(led);   
   output_c(led);   
   output_d(led);    
   delay_ms(50);    
   led = 0;
   output_b(led);   
   output_c(led);   
   output_d(led); 
   delay_ms(50);
}    
void sangtatdan()
{
   for (n=24;n>=0;n--)
   {
      led = 0xffffff>>n;    
      output_b(led);   
      output_c(led>>8);   
      output_d(led>>16);
      delay_ms(2);
   }
   for (n=0;n<=24;n++)
   {
      led = 0xffffff>>n;    
      output_b(led);   
      output_c(led>>8);    
      output_d(led>>16);
      delay_ms(2);
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
      delay_ms(2);
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
      delay_ms(10);    
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
      delay_ms(10);    
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
      delay_ms(10); 
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
      delay_ms(10);    
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
      delay_ms(10);   
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
         delay_ms(2); 
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
         delay_ms(5);         
      }               
   }      
}        
void main()           
{                                
   set_tris_b(0);     
   set_tris_c(0);
   set_tris_d(0);
   while(true)
   {   
      choptat();           
      sangtatdan();    
      sangdichpt();            
      sangdichtp() ;
      sangnt(); 
      tattn();   
      sangtn(); 
      tatnt();  
      sangdontp();
      sangdonpt();
}     
}

