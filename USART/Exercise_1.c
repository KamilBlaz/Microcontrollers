#include<avr/io.h>
#include <util/delay.h>

// BAUD 4800

/* ###### Obliczenia ######
   UBRR = (F_CPU / (16 * BAUD)) - 1;
   UBRR = (16M / (16 * BAUD)) - 1 = 207
*/

int main() 
{
	UBRRL = 207; // prêdkoœæ 4800 przy fclk=16MHz (zakres: 0-255)
	UCSRB = (1<<TXEN); // w³¹cz wysy³anie -> TX Enable
	UCSRC |= 0b10000110;
	// 7 -> jak tu jest 1 to mo¿na dopiero konfigurowaæ 
	// 5,4 -> parzystoœæ (00 to wy³¹czona)
	// 3 -> bity stopu (0 to jeden bit stopu)
	// 2,1 -> ustawienie s³owa 8-bitowego
	// 
	//UCSRC = (1<<URSEL)|(3<<UCSZ0)

	while(1)
	{
		//while(!(UCSRA & ( 1<<UDRE) ));  -> czekanie a¿ bufor nadawaczy bêdzie pusty
		UDR = 77;
		_delay_ms(500);
	}
}
