
#include <avr/io.h>


int main(void)

{
 
	DDRD = 0xff; // Ustaiwnie rejestru D na wyjscia
	
    PORTD = PORTD | 0b00000001; // ustawienie na D0 "1"
		
	while (1)
	{	
		
for(int i=0;i<7;i++) // petla for
    PORTD = PORTD << 1; //  przesuniecie bitu w lewo 
	PORTD= PORTD >> 7; // przesuniecie bitu w prawo czyli zerowanie 


	}
}

