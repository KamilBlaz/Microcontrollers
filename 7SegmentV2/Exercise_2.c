#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// ******* Obliczenia ******
	// 4 wyświetlacze -> 50Hz * 4 = 200 Hz
	// OCRx = (fclk / n / freq )-1
	// OCR0 = (16MHz / 1024 / 200Hz) - 1 = 77
	// ##########################

const uint8_t ArrayAnode[] = {0b00001110, 0b00001101, 0b00001011, 0b000000111};// ports binary
const uint8_t ArraySign[] = {

//hgfedcba
0b11000000, // 0
0b11111001, // 1
0b10100100, // 2
0b10110000, // 3
0b10011001, // 4
0b10010010, // 5
0b10000010,	// 6
0b11111000, // 7
0b10000000, // 8
0b10010000	// 9
};

volatile uint8_t Bufor[] = {0,0,0,0};


void Printing(int time)
{
		Bufor[0] = time % 10;	// np.: 2s % 10 = 2
		Bufor[1] = (time / 10) % 10; // np. 12s / 10 = 1 % 10 = 1 
		Bufor[2] = (time / 100) % 10; // np. 100s / 100 = 1 % 10 = 1
		Bufor[3] = (time / 1000) % 10;
}

int main(void)
{

	DDRB = (1<< PB0) | (1<< PB1) | (1<< PB2) | (1<< PB3);

	DDRC = 0xff;

	// TIMER0
	TCCR0 = (1<< WGM01); // tryb CTC
	TCCR0 = (1<< CS02) | (1<< CS00);	// preskaler = 1024
	OCR0 = 77;

	

	TIMSK = (1<< OCIE0);  // interrput on 
	sei();				
	int time = 0; 

	while(1)
	{
		_delay_ms(100);	
		time++;

		Printing(time);	 
	}
}


ISR (TIMER0_COMP_vect)
{
	static int counter;
	PORTB = ArrayAnode[counter];
	PORTC = ArraySign[Bufor[counter]];

	if(counter == 1)
	{
		PORTB = ArrayAnode[counter];
		PORTC = 0b01111111;
	}
	

	counter++;
	if(counter > 3)
	{
		counter = 0;
	}


}
