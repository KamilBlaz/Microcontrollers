/*
 * Gosia_timery_zad2.c
 *
 * Created: 10.04.2020 18:43:22
 * Author : Damian
 */ 


/*
 * GccApplication2.c
 *
 * Created: 10.04.2020 17:14:25
 * Author : malgo
 */ 

#include <avr/io.h>
#define High (PORTC |= (1<<PC0))		//ustawienie "1" log na PC0
#define Low (PORTC  &= ~(1<<PC0))		//ustawienie "0" log na PC0


int main(void)
{
	//  Timer pierwszy  600us
    TCCR0 |= (1 << WGM01);					// tryb CTC
    //TCCR0 |= (1 << CS01);		            // preskaler = 8
    OCR0 = 75;								// wpisz do rejestru porównawczego (600 / 8)
	
	//  Timer drugi 5ms
	TCCR1B |= (1 << WGM12);					// tryb CTC
	//TCCR1B |= (1 << CS11) | (1 << CS10);	// preskaler = 64
	OCR1A = 78;								// wpisz do rejestru porównawczego (5000 / 64)
	
	//DDRC = 0xff;							// ustawiene wszystkich linii portu C jako wyjœcia
	DDRC |= (1<<PC0);						// ustawiene konkretnie linii 0-ej portu C jako wyjœcie (PC0)

    Low;
	
	//TCNT0 = 0;								//wyzerowanie licnika TCT0  -timer0
	
    while(1)
    {
		TCCR0 |= (1 << CS01);				// Start licznia Timer0- prescaler 8
		High;								// ustawienie stanu wysokiego 
	    while(!(TIFR & (1 << OCF0)));		// czekanie -> ustawienie bitu flagi zrównania TCNT0 i OCR0
		TCCR0 &= ~(1 << CS01);				// zatrzymanie timera0 - wyzerowanie CS-ów
	    TIFR = TIFR | (1 << OCF0);		    // kasowanie bitu flagi zrównania
		//TCNT1 = 0;
		
		
		
		TCCR1B |= (1 << CS11) | (1 << CS10);	// Start licznia Timer1- prescaler 64
		Low;									// ustawienie stanu niskiego
		while(!(TIFR & (1 << OCF1A)));			// czekanie -> ustawienie bitu flagi zrównania TCNT2 i OCR2
		TCCR1B &= ~((1 << CS11) | (1 << CS10));	// zatrzymanie timera1 - wyzerowanie CS-ów
		TIFR = TIFR | (1 << OCF1A);				// kasowanie bitu flagi zrównania
		//TCNT0 = 0;
    }
}

