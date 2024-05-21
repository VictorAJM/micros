/*
 * practica9.c
 *
 * Created: 28/02/2024 09:15:04 a. m.
 * Author : victor
 */ 
#define F_CPU 8000000UL
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "../../../../../../6to semestre/Micros 2/lcd library C/lcd.h"
#include "../../../../../../6to semestre/Micros 2/lcd library C/lcd.c"

int main(void)
{
	sei();
	
	ADCSRA = (1 << ADEN) | (1 << ADPS1) | (1 << ADPS2) | (1<<ADIE);
	ADMUX = (1<<REFS0);
	ADMUX |=7;
	
	lcd_init(LCD_DISP_ON);
	lcd_puts("Voltaje");
	ADCSRA |= (1 << ADSC);
	
	while (1)
	{
	}

}

ISR(ADC_vect) {
	lcd_gotoxy(0,1);
	lcd_puts("                ");
	lcd_gotoxy(0,1);
	float value=(float)ADC*5.0/1023.0;
	lcd_putc((int)value%10 +'0');
	value*=10.0;
	lcd_putc('.');
	lcd_putc((int)value%10 +'0');
	value*=10.0;
	lcd_putc((int)value%10 +'0');
	value*=10.0;
	lcd_putc((int)value%10 +'0');
	_delay_ms(100);
	ADCSRA |= (1<<ADSC);
}