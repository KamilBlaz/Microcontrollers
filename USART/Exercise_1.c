#include<avr/io.h>
#include <util/delay.h>

// BAUD 4800

/* ###### Obliczenia ######
   UBRR = (F_CPU / (16 * BAUD)) - 1;
   UBRR = (16M / (16 * BAUD)) - 1 = 207
*/

int main() 
{
	UBRRL = 207; // pr�dko�� 4800 przy fclk=16MHz (zakres: 0-255)
	UCSRB = (1<<TXEN); // w��cz wysy�anie -> TX Enable
	UCSRC |= 0b10000110;
	// 7 -> jak tu jest 1 to mo�na dopiero konfigurowa� 
	// 5,4 -> parzysto�� (00 to wy��czona)
	// 3 -> bity stopu (0 to jeden bit stopu)
	// 2,1 -> ustawienie s�owa 8-bitowego
	// 
	//UCSRC = (1<<URSEL)|(3<<UCSZ0)

	while(1)
	{
		//while(!(UCSRA & ( 1<<UDRE) ));  -> czekanie a� bufor nadawaczy b�dzie pusty
		UDR = 77;
		_delay_ms(500);
	}
}
