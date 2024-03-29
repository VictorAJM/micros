/*
 * practica11.c
 *
 * Created: 07/03/2024 02:59:07 p. m.
 * Author : victor
 */ 
#define F_CPU 1000000UL
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h" // Debes tener una librer�a para controlar el LCD
volatile int x=0;
volatile int y=0;
volatile float value;
volatile int cnt=10;
volatile int morethanasecond=0;
volatile int s=0;
volatile int h=0;
volatile int m=0;
volatile int last=0;
volatile int gg=0;
int ADC_Read(char channel)
{

	ADMUX =(ADMUX & 0xF8) | (channel & 7);
	
	// se inicia la conversi�n.
	ADCSRA |= (1 << ADSC);
	
	// espera a que termina la conversi�n.
	while(ADCSRA & (1 << ADSC));
	return ADC;
}

ISR(TIMER0_COMP_vect) {

	cnt--;
	if (cnt==0) {
			DDRB = 0xFF;
			PORTB = 0xFF;
			s++;
			gg++;
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
			if (last+5 == gg) {
				lcd_gotoxy(0,1);
				lcd_puts("               ");
			}
		cnt=10;
	}
}
ISR(INT0_vect) {
	// interrupcion
	value = ADC_Read(0);
	last = gg;
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
		lcd_puts(" C ");
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
		lcd_puts(" C ");
		lcd_gotoxy(x,y);
	}
	return;
}
int main(void)
{
		TCNT0= 0;
		TIMSK= 2;
		OCR0= 97;
		TCCR0= 0b00001101;
	DDRD &= ~(1 << PD2);
			DDRA=0x0;			/* Make ADC port as input */
			ADCSRA = (1 << ADEN) | (1 << ADPS0) | (1 << ADPS1);
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
		
    }
}

