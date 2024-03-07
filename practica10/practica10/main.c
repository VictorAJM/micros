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
void print(int a,int b,int c) {
	lcd_gotoxy(0,0);
	if (a&1) lcd_putc(255);		
	else lcd_putc(129);
	lcd_gotoxy(1,0);
	if (a&2) lcd_putc(255);
	else lcd_putc(129);
	lcd_gotoxy(2,0);
	if (a&4) lcd_putc(255);
	else lcd_putc(129);
	lcd_gotoxy(3,0);
	if (a&8) lcd_putc(255);
	else lcd_putc(129);
	
	lcd_gotoxy(12,0);
	if (b&1) lcd_putc(255);
	else lcd_putc(129);
	lcd_gotoxy(13,0);
	if (b&2) lcd_putc(255);
	else lcd_putc(129);
	lcd_gotoxy(14,0);
	if (b&4) lcd_putc(255);
	else lcd_putc(129);
	lcd_gotoxy(15,0);
	if (b&8) lcd_putc(255);
	else lcd_putc(129);

	lcd_gotoxy(0,1);
	if (c&1) lcd_putc(255);
	else lcd_putc(129);
	lcd_gotoxy(1,1);
	if (c&2) lcd_putc(255);
	else lcd_putc(129);
	lcd_gotoxy(2,1);
	if (c&4) lcd_putc(255);
	else lcd_putc(129);
	lcd_gotoxy(3,1);
	if (c&8) lcd_putc(255);
	else lcd_putc(129);
}
int main(void)
{
	char String[5];
		DDRA=0x0;			/* Make ADC port as input */
		ADCSRA = (1 << ADEN) | (1 << ADPS0) | (1 << ADPS2);
		ADMUX = 0x47;			/* Vref: Avcc, ADC channel: 0 */


	uint8_t puertoB = 0;
	uint8_t puertoC = 0;
	uint8_t puertoA = 0;
	int value;
	lcd_init(LCD_DISP_ON);
	lcd_clrscr();
	print(puertoB,puertoA,puertoC);
	while (1)
	{
		
		
		// Convertir a voltaje (0.0 a 5.0 V)
		value = ADC_Read(0);
		puertoB = 0;
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
		print(puertoB,puertoA,puertoC);
		_delay_ms(100);
		value = ADC_Read(1);
		puertoA = 0;
		if (value >= 205) {
			puertoA += 1;
		}
		if (value >= 410) {
			puertoA +=2;
		}
		if (value >= 615) {
			puertoA += 4;
		}
		if (value >= 820) {
			puertoA += 8;
		}
		_delay_ms(100);
		print(puertoB,puertoA,puertoC);
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
		print(puertoB,puertoA,puertoC);
		_delay_ms(100);
	}

	return 0;
}

