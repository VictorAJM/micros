/*
 * Practica 14 Serial
 *
 * Created: 21/03/2024
 * Author : Erwin Alberto Lopez Hurtado 
 */ 
#define F_CPU 1000000UL
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "../../../../../../6to semestre/Micros 2/lcd library C/lcd.h"
#include "../../../../../../6to semestre/Micros 2/lcd library C/lcd.c"

#define XTAL 1000000
#define LCD_PORT PORTC 

#define BAUD_RATE 4800
#define UBRR_VALUE ((F_CPU / (16UL * BAUD_RATE)) - 1)

void Send(uint8_t data) {
	while (!(UCSRA & (1 << UDRE)))
		;
	UDR = data;
}
int main(void)
{
	sei();
	
	ADCSRA = (1 << ADEN) | (1 << ADPS1) | (1 << ADPS0);
	ADMUX = (1<<REFS0);
	ADMUX |=2;
	
	lcd_init(LCD_DISP_ON);
	lcd_puts("Voltaje");
	
	//Puerto Serial
	UBRRH = (unsigned char)(UBRR_VALUE >> 8);
	UBRRL = (unsigned char)UBRR_VALUE;
	UCSRB = (1 << TXEN) | (1 << RXEN);
	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0) | (1 << USBS);
	DDRD=0b00000010;
	
	while (1)
	{
		while(ADCSRA & (1 << ADSC)){Send((uint8_t)((float)ADC*(float)50/(float)1023));}
		Send((uint8_t)((float)ADC*(float)50/(float)1023));
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

}
