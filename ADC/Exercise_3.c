/*OBLICZENIA 
 ########## KAMIL BLAZ ###########
 UGF = 1V + 23mV * (44172%100) = 2,6V
 2,56V / 255(8bit) = 0,01004 
 // 5,00V / 255(8bit) = 0,01960
*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>

#define  BAUD   4800
#define  UBBR	((F_CPU/16/BAUD) - 1)


int main(void)
{
	// ustawienia UART

	UBRRH = (UBBR >> 8);
	UBRRL = UBBR;
	// w31czenie odbierania
	UCSRB = (1 << RXEN) | (1<< RXCIE) | (1 << TXEN);

	// 8bit 1 bit stopu
	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);

	// ustawienie przetwornika
	ADCSRA |= (1 << ADEN) | (1 << ADATE);					
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);	//n = 128
	ADMUX = (1 << MUX1) | (1 << MUX0);		
	ADMUX |= (1 << REFS0);	//zew napiecie porównania
    

	
	char text[] ="0,00V ";
	uint8_t v = 0;
	uint8_t mv = 0;

    while (1) 
    {
		ADCSRA |= (1 << ADSC);				 
		while(!(ADCSRA & (1 << ADSC)));
		s = ADCW * 48;
		v = s/ 1000;
		mv = ADCW * 48 /100 % 100;
		// 521 * 0,048 = 2,5V
		sprintf(text,"%0u,%02uV ",v,mv);
		SendUSART(text);
		_delay_ms(1000);
    }
}

void SendUSART(char * SendUSART){			
	int i = 0;
	while (SendUSART[i] != '\0')				
	{
		while(!(UCSRA & (1 << UDRE)));			// zwolnienie rejestru
		i++;
	}
}



