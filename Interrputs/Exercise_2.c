/*
 * GccApplication3.c
 *
 * Created: 20.04.2020 19:03:48
 * Author : Kamil
 Dane:
 TIMER 0 (8 bitowy timer 2 do 8 256
 * 10ms
 * 10000us -> 10000 taktow
 * 10000 / 256 = 39 - 1 = 38
 TIMER 1 ( 16 bitowy timer 2 do 16 65536
 * 1s
 * 1000000us  -> 1000000 taktow
 * 1000000/256 = 3906 - 1 = 3905 
 Blad wzgledny dla timera 0 -8/10000 * 100% = -0,08%
 Blad wzgledny dla timera 1  16/1000000 * 100% = 0,0046%
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define Port_Wyj PORTD
#define Czas0 38 // Czas ktory obliczylem
#define Czas1 3905 // Czas ktory obliczylem
volatile uint16_t i; //zmienna prezentujaca prace petli glownej
int main(void)
{
	// Timer0
   TCCR0 |= (1 << WGM01);					// tryb CTC
   OCR0 = Czas0;   
   TCCR0 |= (1 << CS02);  			//START 
   // Timer1   
   TCCR1B |= (1 << WGM12);					// tryb CTC
   OCR1A = Czas1;
   TCCR1B |= (1 << CS12);  //->256		    //START
   DDRD |= (1 << PD0);						// ustawienie linii 0 portu D jako wyjscie (PD0)	
   TIMSK = (1 << OCIE0) | (1 << OCIE1A);
   sei();
   Port_Wyj |= (1 << PD0);	// ustawienie P0  na High
   while (1)		// petla glowna
   {
	   i++;		//zwieksz zmienna dodatkowa
   }
}
ISR(TIMER0_COMP_vect)		//instrukcja przerwania Timer0
{
	  Port_Wyj ^= (1<<PD0);		// negacja L0
	  TCCR0 &= ~(1 << CS02);	//STOP Timer0
}
ISR(TIMER1_COMPA_vect)		//instrukcja przerwania Timer0
{
	Port_Wyj |= (1 << PD0);
	TCCR0 |= (1 << CS02);  //->256			//START	
}