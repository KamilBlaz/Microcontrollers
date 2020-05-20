/***************************************
Biblioteka obslugi modulu wyswietlacza LCD.
Biblioteka przystosowana jest do obslugi
modulu z jednego portu I/O mikrokontrolera
w trybie 4-bitowym
***************************************/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include "LCD_biblioteka.h" // TUTAJ ZMIANIA

/****************************************/
// Funkcje generowania impulsu wpisu "Enable"

void Enable_Impuls(void)
{
PortLCD |= (1 << Enable);
_delay_us(1); // czas trwania impulsu Enable (czas High)
PortLCD &= ~(1 << Enable);
_delay_us(1); // czas dla uzyskania min. czasu Low impulsu Enable

}

/****************************************/
// Funkcja wpisywania znaku do HD44780.
// Funkcja dla przypisania bitow D7-D4 portu do D7-D4 HD44780 !!!
// Wpisywanie nastepuje w dwoch taktach: 
// najpierw starszy nibble, potem mlodszy nibble

void LCD_WpiszZnak_4bit(uint8_t Znak)
{
PortLCD = Znak & 0xF0;
PortLCD |= (1 << RS);
Enable_Impuls();

PortLCD = Znak << 4;
PortLCD |= (1 << RS);
Enable_Impuls();

_delay_us(50); // czas na wykonanie operacji
}

/****************************************/
// Funkcja wpisywania rozkazu do HD44780.
// Funkcja dla przypisania bitow D7-D4 portu do D7-D4 HD44780 !!!
// Wpisywanie nastepuje w dwoch taktach: 
// najpierw starszy nibble, potem mlodszy nibble

void LCD_WpiszRozkaz_4bit(uint8_t Rozkaz)
{
PortLCD = Rozkaz & 0xF0; // kasuj 4 mlodsze bity
Enable_Impuls();    // wpisz starszy nibble

PortLCD = Rozkaz << 4;  // przesun 4 mlodsze bity na pozycje starszych
Enable_Impuls();   // wpisz mlodszy nibble

// UWAGA! dla rozkazow ClearDisplay i ReturnHome musi byæ dodatkowy czas
if((Rozkaz == HD44780_ClearDisplay) || (Rozkaz == HD44780_ReturnHome))
   _delay_ms(2);
else _delay_us(50); // czas na wykonanie operacji przez HD44780. 
}

/****************************************/
// Funkcja inicjalizacji HD44780 dla pracy 4-bitowej

void LCD_Init_4bit(void)
{
PortLCD = 0;

_delay_ms(50);

PortLCD = 0x30; // Function Set
Enable_Impuls();
_delay_ms(5);

PortLCD = 0x30; // Function Set
Enable_Impuls();
_delay_ms(5);

PortLCD = 0x30; // Function Set
Enable_Impuls();
_delay_ms(5);

//---------------------------------
PortLCD = 0x20; // Function Set, praca 4-bit
Enable_Impuls();

LCD_WpiszRozkaz_4bit(0b00101000); // function set   (0b001DNFxx)
//---------------------------------
LCD_WpiszRozkaz_4bit(0b00001111); // Display Cursor Blink On/Off (0b00001DCB)
//---------------------------------
LCD_WpiszRozkaz_4bit(0b00000001); // Clear Display
// opoznienie potrzebne dla tego rozkazu daje funkcja
//---------------------------------
LCD_WpiszRozkaz_4bit(0b00000110); // Entry Mode Set (0b000001IS)
}

/****************************************/

/****************************************/
// Funkcja ustawiania kursora na pozycje Wiersz,Kolumna.
// numerowanych od 1.
// Funkcja zaklada, ze wartosci parametrow sa prawidlowe
// dla sterowanego modulu LCD

void LCD_UstawKursor(uint8_t Wiersz, uint8_t Pozycja)
{
if(Wiersz == 1)
   {
   LCD_WpiszRozkaz_4bit((Pozycja - 1) | HD44780_DDRAMSet);
   }
if(Wiersz == 2)
   {
   LCD_WpiszRozkaz_4bit((Pozycja - 1) | (HD44780_DDRAMSet | HD44780_2_ndLineOffset));
   }
/*
// Inna wersja
LCD_WpiszRozkaz_4bit((Pozycja - 1) | (HD44780_DDRAMSet | HD44780_2_ndLineOffset * (Wiersz - 1)));
*/
}

/****************************************/
// Funkcja wyswietlania tekstu pobieranego z pamieci Flash
// Tekst zapisywany jest w pamieci z pomoca biblioteki
// <avr/pgmspace.h> 
// Przyklad:
// Definicja tekstu: const char T1[] PROGMEM = "Ala ma kota";
// Wywolanie:        WriteTextLCDFlash(&T1);


void WriteTextLCDFlash(uint8_t * String )
  {
    uint8_t Znak ;
    /*---------------------------------*/
    for ( ; ; )
    {
      Znak = pgm_read_byte (String ++) ;
      if ( ! Znak ) break ;
        
      LCD_WpiszZnak_4bit( Znak ) ;
    }
  }

/****************************************/
// Funkcja wyswietlania tekstu podanego jako parametr funkcji
// Przyklad: WriteTextLCD("Ala ma 2 koty");


void WriteTextLCD(char * String )
  {
  uint8_t i =0;

  while( String[i])
    {
	LCD_WpiszZnak_4bit(String[i++]) ;
	}
  }

/****************************************/
// Funkcja wyswietlania tekstu podanego jako parametr funkcji
// Przyklad: LCD_WriteText("Ala ma 3 koty");

void LCD_WriteText(char * String)
{
while(*String)
  LCD_WpiszZnak_4bit(*String++);
}


