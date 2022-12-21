#include <E:\dang hoc\vxl\mo phong\thu vien\TV_74595.c>    
unsigned int32 led;
signed int8 n,m;      
void choptat()
{
   led = 0xffffff;  
   xuatled(led);    
   delay_ms(500);    
   led = 0;
   xuatled(led);    
   delay_ms(500);
}    
void sangtatdan()
{
   for (n=24;n>=0;n--)
   {
      led = 0xffffff>>n;    
      xuatled(led);    
      delay_ms(50);
   }
   for (n=0;n<=24;n++)
   {
      led = 0xffffff>>n;    
      xuatled(led);    
      delay_ms(50);
   }       
}          
void sangdichpt()
{
   for (n=0;n<=24;n++)
   {
      led = 0x000001<<n;
      xuatled(led);      
      delay_ms(50);
   }           
}
void sangdichtp() 
{
   for (n=0;n<=24;n++)
   {
      led = 0x800000>>n;
      xuatled(led);     
      delay_ms(50);    
   }            
}
void sangnt()
{
   for (n=24;n>=12;n--)      
   {                                      
      led = (0xffffff>>n)|(0xffffff<<n);  
      xuatled(led);       
      delay_ms(50);    
   }                 
} 
void tattn()
{
   for (n=12;n<=24;n++)
   {
      led = (0xffffff<<n)|(0xffffff>>n);
      xuatled(led);      
      delay_ms(50); 
   }                 
} 
void sangtn()
{
   for (n=12;n>=0;n--)      
   {                                      
      led = (0xffffff<<n)&(0xffffff>>n);  
      xuatled(led);       
      delay_ms(50);    
   }                 
} 
void tatnt()
{
   for (n=0;n<=12;n++)
   {                 
      led = (0xffffff<<n) & (0xffffff>>n) ;
      xuatled(led);       
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
         xuatled(led);       
         delay_ms(20); 
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
         xuatled(led);         
         delay_ms(20);         
      }               
   }                     
}                  
