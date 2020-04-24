
#include <avr/io.h>


int main(void)

{
	DDRC = 0xff; // Ustawienie wszystkich bitow rejestru C na wyjscia
    PORTC = 0b00000001; // Ustawienie  bita portu C na "1"
					
    while (1) 
    {
		
		for( int i = 0; i < 7; i++) // petla zliczajaca od 0 do 7
		{
		
         PORTC = PORTC << 1; // Przesuniecie w lewo bitu
		 PORTC = PORTC | 1; // ustawienie logicznej "1" po przesunieciu tak aby wczesniejszy bit byl w stanie High
        }			
		 
		 PORTC = PORTC << 7; // Przesuniecie w lewo tzw zerowanie

    }
	
	
	
}

