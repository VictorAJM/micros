/*
 * practica13.c
 *
 * Created: 09/03/2024 07:56:21 p. m.
 * Author : victor
 */ 
#define F_CPU 1000000UL
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <string.h>
#include "lcd.h"
volatile int pos=0;
volatile int cant = 0;
volatile uint8_t mas = 0;
char mat[4][4] = {
	{'<', '+', '>', 'A'},
	{'4', '5', '6', 'B'},
	{'7', '8', '9', 'C'},
	{'E', '0', 'F', 'D'}
};
uint8_t p_pin;
char keyboard2(){
	for(uint8_t i = 0; i<=0; i++){
		PORTD = 0b11111111 ^ (1<<(7-i));
		if(~PIND&2 && mat[i][2]=='>') {p_pin = 2;return mat[i][2];}
		
		if(~PIND&4 && mat[i][1]=='+') {p_pin = 4;return mat[i][1];}
		if(~PIND&8 && mat[i][0]=='<') {p_pin = 8;return mat[i][0];}
	}
	return 0;
}
char keyboard1(){
	for(uint8_t i = 0; i<=0; i++){
		PORTD = 0b11111111 ^ (1<<(7-i));
		if(~PIND&4 && mat[i][1]=='+') {p_pin = 4;return mat[i][1];}
	}
	return 0;
}
void poner(int pos) {
	uint8_t xd;
	xd = eeprom_read_byte(pos);
	lcd_gotoxy(0,1);
	lcd_putc(xd/100+'0');
	lcd_putc((xd/10) % 10+'0');
	lcd_putc(xd%10+'0');
}
void wait_btn(){
	_delay_ms(50);
	while(~PIND&p_pin);
	_delay_ms(50);
}
uint8_t ADC_Read(char channel)
{

	ADMUX =(ADMUX & 0xF8) | (channel & 7);
	
	// se inicia la conversión.
	ADCSRA |= (1 << ADSC);
	
	// espera a que termina la conversión.
	while(ADCSRA & (1 << ADSC));
	int xd = ADC;
	xd /= 4;
	return xd;
}
ISR(TIMER0_COMP_vect) {
	// leer adc
	uint8_t val = ADC_Read(0);
	if (cant < 512) {
		eeprom_write_byte(cant,val);
		lcd_gotoxy(0,1);
		lcd_putc(cant/100+'0');
		lcd_putc((cant/10) % 10+'0');
		lcd_putc(cant%10+'0');
		cant++;
		pos = cant-1;
	
	} else {
		lcd_clrscr();
		lcd_puts("EEPROM LLENA");
		lcd_gotoxy(0,1);
		lcd_putc(cant/100+'0');
		lcd_putc((cant/10) % 10+'0');
		lcd_putc(cant%10+'0');
		cli();
		TCCR0 = 0;
		TIMSK = 0;
		OCR0 = 0;
	
	}
}
int main(void)
{
	lcd_init(LCD_DISP_ON);

    /* Replace with your application code */
	lcd_clrscr();
	lcd_puts("Sensando...");
	DDRD = 0xF0;
	TCNT0= 0;
	TIMSK= 2;
	OCR0= 50;
	TCCR0= 0b00001101;
	DDRA=0x00;
	PORTA = 0xFF;			/* Make ADC port as input */
	ADCSRA = (1 << ADEN) | (1 << ADPS0) | (1 << ADPS1);
	ADMUX = 0x40;			/* Vref: Avcc, ADC channel: 0 */
	sei();	
    while (1) 
    {
		
		if (!mas && keyboard1() != 0) {
			cli();
			TCCR0 = 0;
			TIMSK = 0;
			OCR0 = 0;
			mas=1;

			lcd_clrscr();
			lcd_puts("Ultimos val");
			lcd_gotoxy(13,0);
			lcd_putc(pos/100+'0');
			lcd_putc(pos/10 % 10+'0');
			lcd_putc(pos%10+'0');
			poner(pos);
			wait_btn();
		}
		if (mas || cant==512) {
			char let = keyboard2();
			
			if (let!=0) {
				wait_btn();
				// cosas
				if (let == '<' && pos>0) {
					pos--;
					lcd_gotoxy(13,0);
					lcd_putc(pos/100+'0');
					lcd_putc(pos/10 % 10+'0');
					lcd_putc(pos%10+'0');
					poner(pos);
				} else if (let == '>' && pos+1 < cant) {
					pos++;
					lcd_gotoxy(13,0);
					lcd_putc(pos/100+'0');
					lcd_putc(pos/10 % 10+'0');
					lcd_putc(pos%10+'0');
					poner(pos);
				} else if (let=='+') {
						lcd_clrscr();
						lcd_puts("Sensando...");
						pos = cant = mas = 0;
						DDRD = 0xF0;
						TCNT0= 0;
						TIMSK= 2;
						OCR0= 20;
						TCCR0= 0b00001101;
						DDRA=0x0;			/* Make ADC port as input */
						ADCSRA = (1 << ADEN) | (1 << ADPS0) | (1 << ADPS1);
						ADMUX = 0x40;			/* Vref: Avcc, ADC channel: 0 */
						sei();
				}
				
			} 
		}

    }
}

