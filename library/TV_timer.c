#bit t1if = 0x0c.0
unsigned int8 ss,n;
void timer()
{
   if (t1if==1) 
   {
      set_timer1(3036); //nap dua theo cong thuc 
      n++;            
      t1if=0;        
      if (n==10)  
      {            
         n=0;   
         ss++;          //tang bien can tim len 1
      }               
   }
}  
