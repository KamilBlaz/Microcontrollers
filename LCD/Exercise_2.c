	#include <avr/io.h>
#include "LCD_biblioteka.h" 
//KAMIL B£A¯
int main(void)
{
	DDRD = 0xff; 

	// void LCD_Init_4bit(void);
	LCD_Init_4bit();
	// void LCD_WriteText(char * String);
	LCD_WriteText("Kamil Blaz");
	// void LCD_UstawKursor(uint8_t Wiersz, uint8_t Pozycja);
	LCD_UstawKursor(2,1);

	LCD_WriteText("bk44172");
	while(1)
	{

	}

}
