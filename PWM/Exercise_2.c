#include <avr/io.h>
#include <avr/interrupt.h>
int main(void)
{
    DDRB |= (1 << PB3);		              // ustawienie PB3 na wyjscie
    TCCR0 |= (1 << WGM01) | (1 << WGM00);     // tryb fast PWM
    TCCR0 |= (1 << CS02) | (1 << CS00);       // n = 1024
    TCCR0 |= (1 << COM01);                    // czysc OC0 przy porównaniu
    OCR0 = 17;
    while(1) {}
    // ODPOWIEDZ:
    // Minimalna wartosc OCR0, przy której silnik rozpoczyna prace to 19 -> 7,5% wypelnienia
}
