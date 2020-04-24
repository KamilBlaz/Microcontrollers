/*
 * GccApplication1.c
 *
 * Created: 10.04.2020 15:42:10
 * Author : Kamil Blaz


Obliczenia: 2,5ms = 25000us 
            preskaler = 64
            25000 / 64 = 39,0625  w zaokragleniu 39
 */ 

#include <avr/io.h>

int main(void)
{
	TCCR1B |= (1 << WGM12);				// Ustawienie trybu CTC
	TCCR1B |= (1 << CS11) | (1 << CS10);		// preskaler = 64
	OCR1A = 39;					// Wpisanie do rejestru porównawczego (2500 / 64)
	
	while(1) 
	{  
		while(!(TIFR & (1 << OCF1A)));		// czekanie -> ustawienie bitu flagi zrównania TCNT0 i OCR0  
		TIFR = TIFR | (1 << OCF1A);		// kasowanie bitu flagi zrównania 
	}

}