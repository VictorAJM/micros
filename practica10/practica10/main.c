/*
 * practica10.c
 *
 * Created: 01/03/2024 07:09:11 p. m.
 * Author : victor
 */ 

 
#define F_CPU 4000000UL
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h" // Debes tener una librería para controlar el LCD
int ADC_Read(char channel)
{

    ADMUX =(ADMUX & 0xF8) | (channel & 7);
    
    // se inicia la conversión.
    ADCSRA |= (1 << ADSC);
    
    // espera a que termina la conversión.
    while(ADCSRA & (1 << ADSC));
    return ADC;
}
int main(void)
{
	char String[5];
		DDRA=0x0;			/* Make ADC port as input */
		ADCSRA = (1 << ADEN) | (1 << ADPS0) | (1 << ADPS2);
		ADMUX = 0x47;			/* Vref: Avcc, ADC channel: 0 */

DDRB = 0xFF;
DDRC  = 0xFF;
	uint8_t puertoB = 0;
	uint8_t puertoC = 0;
	int value;
	while (1)
	{
		
		
		// Convertir a voltaje (0.0 a 5.0 V)
		value = ADC_Read(0);
		puertoB &= 0xF0;
		if (value >= 0) {
			puertoB += 0;
		}
		if (value >= 205) {
			puertoB += 1;
		}
		if (value >= 410) {
			puertoB +=2;
		}
		if (value >= 615) {
			puertoB += 4;
		}
		if (value >= 820) {
			puertoB += 8;
		}
		PORTB = puertoB;
		_delay_ms(200);
		value = ADC_Read(1);
		puertoB &= 0x0F;
		if (value >= 205) {
			puertoB += 16;
		}
		if (value >= 410) {
			puertoB +=32;
		}
		if (value >= 615) {
			puertoB += 64;
		}
		if (value >= 820) {
			puertoB += 128;
		}
		_delay_ms(200);
		PORTB = puertoB;
		value = ADC_Read(2);
		puertoC = 0;
		if (value >= 0) {
			puertoC += 0;
		}
		if (value >= 205) {
			puertoC += 1;
		}
		if (value >= 410) {
			puertoC +=2;
		}
		if (value >= 615) {
			puertoC += 4;
		}
		if (value >= 820) {
			puertoC += 8;
		}
		PORTC = puertoC;
		_delay_ms(200);
	}

	return 0;
}

