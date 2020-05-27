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

	DDRA = 0xff; // ustawienie wszystkich bitów rejestru A na wyjœcia
	
	while(1)
	{
		unsigned char znak = USART_Odbieraj();
				
		if(znak >= 48 && znak <= 55)
		{
			switch(znak)
			{
				case 48: 
					PORTA = (1<<PA0);
					break;
				case 49:
					PORTA = (1<<PA1);
					break;
				case 50:
					PORTA = (1<<PA2);
					break;
				case 51:
					PORTA = (1<<PA3);
					break;
				case 52:
					PORTA = (1<<PA4);
					break;
				case 53:
					PORTA = (1<<PA5);
					break;
				case 54:
					PORTA = (1<<PA6);
					break;
				case 55:
					PORTA = (1<<PA7);
					break;
				default:
					break;

			}
		}
		else PORTA |= 0b00000000;
	}
}
