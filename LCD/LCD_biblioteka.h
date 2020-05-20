//-------------------------------------------------------------------------------------------------
#ifndef S31_timer_h
#define S31_timer_h

#include <avr/io.h>
#include <util/delay.h>

// definicje zalezne od konfiguracji sprzetu
#define PortLCD PORTD						  // TUTAJ ZMIANA
#define Enable  3    // bit D0 portu PortLCD  // TUTAJ ZMIANA
#define RS      2    // bit D2 portu PortLCD

// definicje niezalezne od konfiguracji sprzetu
#define HD44780_ClearDisplay    0x01
#define HD44780_ReturnHome      0x02
#define HD44780_EntryModeSet    0x04
#define HD44780_DisplayOnOff    0x08
#define HD44780_DispCursorShift 0x10
#define HD44780_FunctionSet     0x20
#define HD44780_CGRAMSet        0x40
#define HD44780_DDRAMSet        0x80
#define HD44780_2_ndLineOffset  0x40

// Entry Mode Set       (0b000001IS)
#define LCD_EMS_SHIFT_CURSOR     0
#define LCD_EMS_SHIFT_DISPLAY    1
#define LCD_EMS_DECREMENT        0
#define LCD_EMS_INCREMENT        2


// Display Cursor On/Off (0b00001DCB)
#define LCD_DISPLAY_OFF          0
#define LCD_DISPLAY_ON           4
#define LCD_CURSOR_OFF           0
#define LCD_CURSOR_ON            2
#define LCD_CURSOR_BLINK_OFF     0
#define LCD_CURSOR_BLINK_ON      1

//Display Cursor Shift   (0b0001SRxx)
#define LCD_CURSOR_SHIFT         0
#define LCD_DISPLAY_SHIFT        8
#define LCD_SHIFT_LEFT           0
#define LCD_SHIFT_RIGHT          4

// Function set          (0b001DNFxx)
#define LCD_FONT_5x7             0
#define LCD_FONT_5x10            4
#define LCD_1_LINE               0
#define LCD_2_LINE               8
#define LCD_4_BIT                0
#define LCD_8_BIT               16


void Enable_Impuls(void);
void LCD_Init_4bit(void);
void LCD_WpiszZnak_4bit(uint8_t Znak);
void LCD_WpiszRozkaz_4bit(uint8_t Rozkaz);
void LCD_UstawKursor(uint8_t Wiersz, uint8_t Pozycja);
void WriteTextLCDFlash(uint8_t * String);
void WriteTextLCD(char * String);
void LCD_WriteText(char * String);


#endif
