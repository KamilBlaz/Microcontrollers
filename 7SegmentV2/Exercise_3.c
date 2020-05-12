#include <avr/io.h>
#include <avr/interrupt.h>



// ############## KAMIl BLAZ  ###################

#define Time 256-156  // Czas ktory wyszedl mi z obliczen

//Definicje bitow dla poszczegolnych Anod
#define ANODE_0    (1<<PB3)
#define ANODE_1    (1<<PB2)
#define ANODE_2    (1<<PB1)
#define ANODE_3    (1<<PB0)


//Definicje bitow dla poszczegolnych segmentow
//volatile jest to zmienna ulotna moga zostac zmienone " z zewnatrz" 
// 0 - 9 
volatile uint8_t ArraySign[] = {

// hgfedcba
0b11000000, // 0
0b11111001, // 1
0b10100100, // 2
0b10110000, // 3
0b10011001, // 4
0b10010010, // 5
0b10000010,	// 6
0b11111000, // 7
0b10000000, // 8
0b10010000,	// 9
0b11111111, // space
0b10001000,	// A
0b10000011,	// b
0b11000110,	// C
0b10100001,	// d
0b10000110, // E
0b10000111, // t
0b11000011 // l

};
volatile uint8_t ArrayAnode[] = {ANODE_0,ANODE_1,ANODE_2,ANODE_3};
volatile uint8_t Bufor[] = {1, 10, 9, 12}; 	
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
      PORTB = ~ArrayAnode[counter]; 
	  PORTC = ArraySign[Bufor[counter]];
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
