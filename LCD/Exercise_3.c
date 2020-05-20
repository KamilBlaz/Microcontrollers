

#include <avr/io.h>
#include <avr/interrupt.h>
#include "LCD_biblioteka.h" 

const uint8_t ArraySign[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
volatile uint16_t counter = 0; // limit  255 -> 25,5 == overflow!!
//  KAMIL B£A¯
int main(void)
{
	
	DDRD = 0xff; 
	
	// Initialization
	LCD_Init_4bit();
	/*LCD_WpiszRozkaz_4bit("HD44780_ClearDisplay");*/
	
	                 // Timer 1 //
	// obliczenia: (0,1s * 16Mhz)/n = 6250
	TCCR1B |= (1 << WGM12); 	// tryb CTC
	OCR1A = 6250;
	TCCR1B |= (1 << CS12); // n = 256
	 
	TIMSK = (1 << OCIE1A);	
	sei();

	while(1)
	{
		
		LCD_WpiszZnak_4bit(ArraySign[(counter/6000) % 10]);
		
		LCD_UstawKursor(1,2);
		LCD_WpiszZnak_4bit(ArraySign[(counter/600) % 10]);

		LCD_UstawKursor(1,3);
		LCD_WriteText(" minut");

		LCD_UstawKursor(2,1);
		LCD_WpiszZnak_4bit(ArraySign[(counter/100) % 6]);
		
		LCD_UstawKursor(2,2);
		LCD_WpiszZnak_4bit(ArraySign[(counter/10) % 10]);

		LCD_UstawKursor(2,3);
		LCD_WriteText(",");

		LCD_UstawKursor(2,4);
		LCD_WpiszZnak_4bit(ArraySign[counter % 10]);

		LCD_UstawKursor(2,5);
		LCD_WriteText("sekund 44172");

	

	}

}

ISR(TIMER1_COMPA_vect)						
{
	counter++;
}

