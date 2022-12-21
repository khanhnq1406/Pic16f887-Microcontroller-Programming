int1 inputcd(int16 pin)          
{                                                  
   if (input(pin)==0)
   {
		delay_ms(20);
		if (input(pin)==0) 
		{
			while (input(pin)==0);
			return 0; 
		}       	
   }
   return 1;
}         
