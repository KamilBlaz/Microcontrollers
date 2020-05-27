#include<avr/io.h>
#include <util/delay.h>

// BAUD 4800

const uint8_t TabZnak[] = {

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

unsigned char USART_Odbieraj(void)
{
	while(!(UCSRA & ( 1<<RXC) )); // czekaj a¿ dane zostan¹ odebrane od bufora
	return UDR;
}

int main() 
{
	UBRRL = 207; // prêdkoœæ 4800 przy fclk=16MHz (zakres: 0-255)
	UCSRB = (1<<RXEN);
	UCSRC |= 0b10000110;

	// Piny do obs³ugi wyœwietlacza 
	DDRB = (1<< PB0) | (1<< PB1) | (1<< PB2) | (1<< PB3);
	//DDRB = 0x0f;
	DDRC = 0xFF;
	PORTC = 0xFF;
	
	while(1)
	{
		unsigned char znak = USART_Odbieraj();
		PORTB = ~(1<<PB0); // prawy skrajny segment

		if (znak >= 48 && znak <= 57)
		{
			 switch(znak)
			 {
			 	case 48:
     				PORTC = TabZnak[0]; 
					break;
				case 49:
     				PORTC = TabZnak[1]; 
					break;
				case 50:
     				PORTC = TabZnak[2];
					break;
				case 51:
     				PORTC = TabZnak[3];
					break;
				case 52:
     				PORTC = TabZnak[4];
					break;
				case 53:
     				PORTC = TabZnak[5];
					break;
				case 54:
     				PORTC = TabZnak[6];
					break;
				case 55:
     				PORTC = TabZnak[7];
					break;
				case 56:
     				PORTC = TabZnak[8];
					break;
				case 57:
     				PORTC = TabZnak[9];
					break;
				
				default:
					break;
			 }
		}
		else PORTC = 0xFF;
	}
}
