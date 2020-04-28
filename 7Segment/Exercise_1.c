#include <avr/io.h>
#include <avr/interrupt.h>

/*
Obliczenia 
Cel:Chcialbym uzyskac 200Hz
fclk = 16Mhz
preskaler = 1024
(16 000 000 / 1024 / 200)  = 78
Moj czas to -> 78
(16 000 000 / 1024 / 78) = 200Hz 
*/



#define Time 256-78  // Czas ktory wyszedl mi z obliczen

//Definicje bitow dla poszczegolnych Anod
#define ANODE_0    (1<<PB3)
#define ANODE_1    (1<<PB2)
#define ANODE_2    (1<<PB1)
#define ANODE_3    (1<<PB0)


//Definicje bitow dla poszczegolnych segmentow
//volatile jest to zmienna ulotna moga zostac zmienone " z zewnatrz" 
// 0 - 9 
volatile uint8_t ArraySign[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
volatile uint8_t ArrayAnodes[] = {ANODE_0,ANODE_1,ANODE_2,ANODE_3};

static uint8_t counter = 0;

int main(void)
{ 

  
   
    DDRB |= ANODE_0 | ANODE_1 | ANODE_2 | ANODE_3; // ustawienie bitow rejestru B na wyjscie
    DDRC = 0xff; //ustawienie wszyskitch bitow rejestru C na wyjscie
  


  //Timer0
    TCCR0 |= (1 << WGM01);					// tryb CTC
    TCNT0 = Time;    //Licznik ktory zlicza impulsy
    TCCR0 |= (1 << CS02) | (1<<CS00) ;  //START 1024
	TIMSK = (1 << TOIE0); // odblokuj maske przerwania od przepelnienia Timera1
    sei();                // odblokuj globalna maske przerwan
    
    
    while (1)		
    {
	   
    }
	
  
}


//Oblsuga przerwania
ISR(TIMER0_OVF_vect){


  TCNT0 = Time;

  
  
   if( counter <= 3 ){
      PORTB = ~ArrayAnodes[counter]; 
	  PORTC = ArraySign[counter];
	  counter++;
   }
   else{
   
       counter=0;
	   /*
   
	   PORTB=~ArrayAnodes[counter];

	   PORTC=ArraySign[counter];
	   */
	
   }



}

