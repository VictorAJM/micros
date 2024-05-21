/*
 * practica 10
 *
 * Created: 05/03/2024
 * Author : Erwin
 */ 

#define F_CPU 4000000UL
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "../../../../../../6to semestre/Micros 2/lcd library C/lcd.h"
#include "../../../../../../6to semestre/Micros 2/lcd library C/lcd.c"
#include <string.h>

#define XTAL 4000000 
#define LCD_PORT PORTC
	


void write(int x){
	switch(x){
		case 0:lcd_puts("    ");break;
		case 1:lcd_puts("#   ");break;
		case 2:lcd_puts("##  ");break;
		case 3:lcd_puts("### ");break;
		case 4:lcd_puts("####");break;
		case 5:lcd_puts("####");break;
	}
	
}

int main(void)
{
	sei();
	
	ADCSRA = (1 << ADEN) | (1 << ADPS1) | (1 << ADPS2) | (1<<ADIE);
	ADMUX = (1<<REFS0);
	DDRA=0;
	
	lcd_init(LCD_DISP_ON);
	lcd_putc((char)219);
	
	ini:;
	
	ADMUX =(1<<REFS0)|0;
	ADCSRA |= (1 << ADSC);
	while (ADCSRA & (1 << ADSC))
	{}
	int val=ADC*5/1023;
	lcd_gotoxy(0,0);
	write(val);
	
	ADMUX =(1<<REFS0)|1;
	ADCSRA |= (1 << ADSC);
	while (ADCSRA & (1 << ADSC))
	{}
	val=ADC*5/1023;
	lcd_gotoxy(12,0);
	write(val);	
	
	ADMUX =(1<<REFS0)|2;
	ADCSRA |= (1 << ADSC);
	while (ADCSRA & (1 << ADSC))
	{}
	val=ADC*5/1023;
	lcd_gotoxy(0,1);
	write(val);
	
	//_delay_ms(1000);
	goto ini;

}

ISR(ADC_vect) {
		
}