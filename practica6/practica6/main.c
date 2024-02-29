/*
 * practica6.c
 *
 * Created: 15/02/2024 09:05:58 a. m.
 * Author : victor
 */ 

#define F_CPU 4000000UL  // Frecuencia de trabajo del microcontrolador
#define SERVO_PIN PB3   // Pin donde está conectado el servo
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd.h"
char mat[4][4] = {
	{'1', '2', '3', 'A'},
	{'4', '5', '6', 'B'},
	{'7', '8', '9', 'C'},
	{'E', '0', 'F', 'D'}
};
uint8_t p_pin;
char letra=0;
uint8_t pos=0;
char keyboard(){
	p_pin=0;
	
		for(uint8_t i = 0; i<4; i++){
			PORTD = 0b11111111 ^ (1<<(7-i));
			if(~PIND&1) {p_pin = 1;return mat[i][3];}
			if(~PIND&2) {p_pin = 2;return mat[i][2];}
			if(~PIND&4) {p_pin = 4;return mat[i][1];}
			if(~PIND&8) {p_pin = 8;return mat[i][0];}
		}
	return 0;
}
void wait_btn(){
	_delay_ms(50);
	while(~PIND&p_pin);
	_delay_ms(50);
}
void init() {
	DDRA = 0xFF;
	PORTA = 0x00;
	DDRC = 0xF0;
	lcd_init(LCD_DISP_ON); 
	DDRD = 0xF0;
    DDRB |= (1 << SERVO_PIN);
	DDRB |= (1<<7);
    TCCR0 |= (1 << WGM00) | (1 << WGM01) | (1 << COM01) | (1<<CS02);
}
uint8_t val = 0;

int main(void)
{
	init();
	OCR0 = 0;
    /* Replace with your application code */
    while (1) 
    {
		if (pos < 2) {
			letra = keyboard();
			if (letra != 0) {
				if ('0' <= letra && letra <= '9') {
					// escribir en lcd
					lcd_gotoxy(pos++,0);
					lcd_putc(letra);
					val*=10;
					val+=letra-'0';
				}
				wait_btn();
			} else {
				wait_btn();
			}
		} else {
			uint8_t z=0;
			uint8_t cp = val;
			float x = (37.0-9.0)/val;
			for (int i=8;i<=37;i++) {
				OCR0=i;
			
				cp=val;
				for (int j=0;j<val;j++) { _delay_ms(250);
					lcd_gotoxy(0,0);
					lcd_putc(cp/10+'0');
					lcd_gotoxy(1,0);
					lcd_putc(cp%10+'0');
					cp--;
				}
				cp=val;
									lcd_gotoxy(0,0);
									lcd_putc(cp/10+'0');
									lcd_gotoxy(1,0);
									lcd_putc(cp%10+'0');
			}
			pos=0;
			lcd_clrscr();
			PORTA = 0xff;
			PORTB |= (1<<7);
			_delay_ms(2000);
			OCR0 = 0;
		
			PORTA = 0;
			PORTB &= 0b01111111;
			val=0;
		}
    }
}

