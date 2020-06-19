#include <avr/io.h>
#include <avr/interrupt.h>
int main(void)
{
// wypenienie 60%
    DDRB |= (1<<PB3); // linia pb3 wyjscie

	// Timer0
   TCCR0 |= (1 << WGM01);					// tryb CTC
   OCR0 = 97;
   TCCR2 |=(1 << WGM21);    // ten licznik CTC 
   OCR2 = 65;

   TCCR0 |= (1 << CS02) | (1< CS00); //Timer 0 START, n = 256
   

   TIMSK = (1 << OCIE0) | (1 << OCIE2); // w³¹czenie przerwan
   sei(); // odblkowanie maski globalnej

  
   while (1)		// petla glowna
   {
	  
   }
}
 
// Jezeli overflow to wykona sie przerwanie
ISR(TIMER0_COMP_vect)		//instrukcja przerwania Timer0
{
	  PORTB &= ~(1 << PB3);		// negacja PB3
	  TCCR0 &= ~((1 << CS02) | (1< CS00));	//STOP Timer0
      TCCR2 |= (1<<CS22) | (1<<CS21) | (1<<CS20); // TIMER2 START perskaler 1024
}
ISR(TIMER2_COMP_vect)		//instrukcja przerwania Timer2
{
	PORTB |= (1 << PB3);
    TCCR2 &= ~((1<<CS22) | (1<<CS21) | (1<<CS20));	//STOP Timer2
    TCCR0 |= (1 << CS02) | (1< CS00); //timer0 start
}
