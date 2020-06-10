
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
	
	UCSRB = (1 << RXEN) | (1<< RXCIE) | (1 << TXEN);

	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);

	// ustawienie przetwornika
	ADCSRA |= (1 << ADEN);					
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1);	
	ADMUX = (1 << MUX1) | (1 << MUX0);		
	ADMUX |= (1 << REFS0);	//zew napiecie porównania
    ADMUX |= (1 << ADLAR);					

	
	char text[] ="000 \0";
    while (1) 
    {
		ADCSRA |= (1 << ADSC);					//w31czenie przetwarzania czekanie na wartooci
		while(!(ADCSRA & (1 << ADSC)));			//czekaj na wykonanie pomiaru
		sprintf(text,"%3u ",ADCH);				//ADCH => rejestr przechowujacy wartosci
		SendUSART(text);
		_delay_ms(100);
    }
}



void SendUSART(char * SendUSART){			// zeby nie wysylac pojedynczego znaku to string
	int i = 0;
	while (SendUSART[i] != '\0')				
	{
		while(!(UCSRA & (1 << UDRE)));			// zwolnienie rejestru
		UDR = SendUSART[i];
		i++;
	}
}
