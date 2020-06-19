#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
int main(void)
{   
    //KAMIL B£A¯

	//Skokowa zmiana
    
   int RGB[4][3] = { {255,0,4},
   							{0,255,0},
							{0,0,255},
							{50,70,25} };

    
    uint8_t  i = 0;
    DDRD = (1 << PD4) | (1 << PD5) | (1 << PD7);	  // ustawienie konkretnych linii na wyjscia
    
    TCCR1A |= (1 << WGM10);                    // fast PWM 8bit  
    TCCR1B |= (1 << WGM12);                    
    TCCR1B |= (1 << CS12) | (1 << CS10);       // preskaler = 1024
    TCCR1A |= (1 << COM1A1) | (1 << COM1B1);   // czysc OC1A/OC1B podczas porównania
    
    TCCR2 |= (1 << WGM21) | (1 << WGM20);                   // tryb fast PWM
    TCCR2 |= (1 << CS22) | (1 << CS21) | (1 << CS20);       // preskaler = 1024
    TCCR2 |= (1 << COM21);                                  // czyszczenie 
   
    while(1) 
    {
        for(i = 0; i < 4; i++)
        {
             
			     OCR1A = RGB[i][0];       
                  OCR1B =   RGB[i][1];       
                  OCR2 = RGB[i][2];        
				  _delay_ms(500);
        }
    }
}
