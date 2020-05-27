#include<avr/io.h>
#include <util/delay.h>

// BAUD 4800

/* ###### Obliczenia ######
   UBRR = (F_CPU / (16 * BAUD)) - 1;
   UBRR = (16M / (16 * BAUD)) - 1 = 207
*/

void USART_Nadawaj(char data)
{
	while(!(UCSRA & ( 1<<UDRE) )); // czekaj a¿ bufor nadawczy bêdzie pusty
	UDR = data;
}

unsigned char USART_Odbieraj(void)
{
	while(!(UCSRA & ( 1<<RXC) )); // czekaj a¿ dane zostan¹ odebrane od bufora
	return UDR;
}

int main() 
{
	UBRRL = 207; // prêdkoœæ 4800 przy fclk=16MHz (zakres: 0-255)
	UCSRB = (1<<TXEN) | (1<<RXEN);
	UCSRC |= 0b10000110;
	
	while(1)
	{
		USART_Nadawaj(USART_Odbieraj());
	}
}
