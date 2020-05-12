#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// ******* Obliczenia ******
	// 4 wyświetlacze -> 50Hz * 4 = 200 Hz
	// OCRx = (fclk / n / freq )-1
	// OCR0 = (16MHz / 1024 / 200Hz) - 1 = 77
	// ##########################

const uint8_t ArrayAnode[] = {0b00001110, 0b00001101, 0b00001011, 0b000000111};// ports binary
const uint8_t ArraySign[] = {0b11000000, 0b11111001, 0b10100100, 0b10110000, 0b10011001, 
0b10010010, 0b100000010, 0b11111000, 0b100000000, 0b10010000}; // array sign
volatile uint8_t Bufor[] = {0,0,0,0};


void Printing(int czas)
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
	sei();				/
	int time = 0; 

	while(1)
	{
		_delay_ms(1000);	
		time++;

		Printing(time);	 
	}
}


ISR (TIMER0_COMP_vect)
{
	static int counter;
	PORTB = TabAnod[counter];
	PORTC = TabZnak[Bufor[counter]];

	counter++;
	if(counter > 3)
	{
		counter = 0;
	}


}
