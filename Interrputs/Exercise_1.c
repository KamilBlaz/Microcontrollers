/*
 * GccApplication2.c
 *
 * Created: 20.04. 20:05 20:33:17 
 * Author : Kamil
 Dane:
 
*Przebieg prostokarny 10Hz
*Linia 7 (PD7) portu D (PORTD)
*Tryb CTC
*fclk = 1MHz
 Obliczenia:
 T = 1 / f  = 0,1 s
 T/2 = 0,005 s
 0,05 = 50000 us
 50000 us / 256 = 195 - > Czas
 
 Blad wzgledny obliczenia:

 Najpierw trzeba policzyc blad bezwzgledny
 
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#define Port_Wyj PORTD
#define Czas 195  // Czas ktory wyszedl mi z obliczen

volatile uint16_t i; //zmienna prezentujaca prace petli glownej

int main(void)
{

	TCCR2 |= (1 << WGM21);					// tryb CTC
	TCCR2 |= (1 << CS22)|(1 << CS21);		// preskaler = 256
	OCR2 = Czas;							// wpisanie do rejestru porownawczego (50000/256)

    DDRD |= (1 << PD7);						// ustawienie linii 7 portu D  na wyjscie (PD7)
	Port_Wyj |= (1 << PD7);					// ustawienie stanu wysokiego na linii 7 portu D 
    
    TIMSK = (1 << OCIE2); // odblokuj maske przerwania od przepelnienia Timera2
    sei();                // odblokuj globalna maske przerwan
    
    
    while (1)		// petla glowna
    {
	    i++;		//zwieksz zmienna dodatkowa
    }
  
}

ISR(TIMER2_COMP_vect)		//instrukcja przerwania
{
	Port_Wyj ^= (1<<PD7);			// negacja linii siódmej portu wyjœciowego
}
