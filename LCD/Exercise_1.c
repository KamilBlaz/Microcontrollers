#include <avr/io.h>
#include "LCD_biblioteka.h" 



// KAMIL B£A¯ 
int main(void)
{
	
	DDRD = 0xff; 

	// void LCD_Init_4bit(void);
	LCD_Init_4bit();
	// void LCD_WpiszZnak_4bit(uint8_t Znak)
	LCD_WpiszZnak_4bit('x');

	while(1)
	{

	}

}
