/*
 * practica11.c
 *
 * Created: 07/03/2024 02:59:07 p. m.
 * Author : victor
 */ 
#define F_CPU 4000000UL
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h" // Debes tener una librería para controlar el LCD
volatile int x=0;
volatile int y=0;
volatile float value;
int ADC_Read(char channel)
{

	ADMUX =(ADMUX & 0xF8) | (channel & 7);
	
	// se inicia la conversión.
	ADCSRA |= (1 << ADSC);
	
	// espera a que termina la conversión.
	while(ADCSRA & (1 << ADSC));
	return ADC;
}
ISR(INT0_vect) {
	// interrupcion
	value = ADC_Read(0);
	lcd_gotoxy(0,1);
	lcd_puts("Temp. ");
	value = value* 70.0 /1023;
	value -= 20.0;
	int xd = value;
	if (xd<0) {
		lcd_putc('-');
		xd *=-1;
		lcd_putc(xd/10+'0');
		lcd_putc(xd%10+'0');
		lcd_putc('.');
		float dx = value;
		dx += xd;
		dx*=-10.0;
		int ddx = dx;
		lcd_putc(ddx+'0');
		lcd_puts(" C");
		lcd_gotoxy(x,y);
	} else {
		lcd_putc(xd/10+'0');
		lcd_putc(xd%10+'0');
		lcd_putc('.');
		float dx = value;
		dx-=xd;
		dx*=10;
		int ddx = dx;
		lcd_putc(ddx+'0');
		lcd_puts(" C");
		lcd_gotoxy(x,y);
	}
	return;
}
int main(void)
{
	
	DDRD &= ~(1 << PD2);
			DDRA=0x0;			/* Make ADC port as input */
			ADCSRA = (1 << ADEN) | (1 << ADPS0) | (1 << ADPS2);
			ADMUX = 0x40;			/* Vref: Avcc, ADC channel: 0 */
	lcd_init(LCD_DISP_ON);
	PORTD = 0xFF;
	DDRA =0;
	PORTA = 0xFF;
    /* Replace with your application code */
		MCUCR = 2;
		GIFR = 0b11100000;
		GICR = 0b01000000;
		sei();
		int h,m,s;
		h=0; m=0; s=0;
		x=y=0;
		lcd_gotoxy(0,0);
		lcd_putc(h/10+'0');
		y++;
		lcd_putc(h%10+'0');
		y++;
		lcd_putc(':');
		y++;
		lcd_putc(m/10+'0');
		y++;
		lcd_putc(m%10+'0');
		y++;
		lcd_putc(':');
		y++;
		lcd_putc(s/10+'0');
		y++;
		lcd_putc(s%10+'0');
    while (1) 
    {
		
			_delay_ms(1000);
		s++;
		if (s==60) {
			m++;
			s=0;
			if (m==60) {
				h++;
				m=0;
			}
		}
		x=y=0;
		lcd_gotoxy(0,0);
		lcd_putc(h/10+'0');
		y++;
		lcd_putc(h%10+'0');
		y++;
		lcd_putc(':');
		y++;
		lcd_putc(m/10+'0');
		y++;
		lcd_putc(m%10+'0');
		y++;
		lcd_putc(':');
		y++;
		lcd_putc(s/10+'0');
		y++;
		lcd_putc(s%10+'0');
    }
}

