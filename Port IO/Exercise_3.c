#include <avr/io.h>



int main(void)

{
	DDRD = 0xff; // Ustawienie wszystkich  bitow rejestru na wyjscia
    
					
    while (1) 
    {
	if ( PORTA == 0) // warunek jesli bit D0 portu A  wynoosi  "Low"
	{
	 PORTD = PORTD | 1; // Ustawienie D0 na stan wysoki High
	   for(int i = 0 ; i < 7; i ++)
	 PORTD = PORTD << 1;	// Przesuniecie bitu  w lewo
		
	}
	else
	{
		
	PORTD = PORTD >> 7;	// Przesuniecie bitu w prawo 
	}
		

    }
	
	
	
}

