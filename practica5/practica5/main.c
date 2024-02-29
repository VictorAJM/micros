/*
 * practica5.c
 *
 * Created: 11/02/2024 05:37:30 p. m.
 * Author : victor
 */ 
#define F_CPU 1000000UL  // Frecuencia de trabajo del microcontrolador
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd.h"


volatile uint8_t morethanasecond = 0; 
volatile uint8_t letter = 'A';             
volatile uint8_t letter_count = 0;     
volatile uint8_t x_cur = 0;
volatile uint8_t cnt = 0;
void init() {
	DDRA = 0x00;
	PORTA = 0xFF;

	DDRC = 0xF0;
	lcd_init(LCD_DISP_ON);
	cnt=100;
	TCNT0= 0;
	TIMSK= 2;
	OCR0= 38;
		TCCR0= 0b00001100;
	sei();
}


int main() {
	init();

	while (1) {
		if (!!(PINA&(1<<0))) continue;
		_delay_ms(50);
		if (letter_count == 0) {
			letter = 'A';
			lcd_gotoxy(x_cur,0);
			lcd_putc(letter);
			letter_count++;
			cnt=100;
			morethanasecond = 0;


			TCNT0=0;

		} else {
		if (morethanasecond) {
			if (letter_count == 16) {
				lcd_clrscr();
				letter_count=0;
				x_cur = 0;
				letter = 0;
			} else {
				letter='A';
				x_cur++;
				lcd_gotoxy(x_cur,0);
				lcd_putc(letter);
				letter_count++;
			}
			cnt=100;
			morethanasecond = 0;


			TCNT0=0;

		} else {
			letter++;
			if (letter>'Z') letter = 'A';
			lcd_gotoxy(x_cur,0);
			lcd_putc(letter);
					cnt=100;
					morethanasecond = 0;


		TCNT0=0;

		}
			}
		while (!(PINA&(1<<0)));
		_delay_ms(50);
	}
	return 0;
}

ISR(TIMER0_COMP_vect) {
	cnt--;
	if (cnt==0) {
		morethanasecond=1;
		cnt=100;
	}
}