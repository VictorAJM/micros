/*
 * practica4.c
 *
 * Created: 07/02/2024 10:04:41 p. m.
 * Author : victor
 */ 
#define F_CPU 1000000L
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h> // Necesario para la función rand()
#include <util/delay.h>
volatile uint8_t ran=1;
ISR(INT0_vect) {
	_delay_ms(100);
	while (!(PIND&(1<<2)));
	_delay_ms(100);
	if (ran == 1) {
		PORTB = 1;
		PORTA = 0;
	} else if (ran == 2) {
		PORTB = 0;
		PORTA = (1<<5) | (1<<2);
	} else if (ran == 3) {
		PORTB = 1;
		PORTA = (1<<0) | (1<<7);
	} else if (ran == 4) {
		PORTB = 0;
		PORTA = (1<<0) | (1<<7) | (1<<5) | (1<<2);
	} else if (ran == 5) {
		PORTB = 1;
		PORTA = (1<<0) | (1<<7) | (1<<5) | (1<<2);
	} else if (ran == 6) {
		PORTB = 0;
		PORTA = (1<<0) | (1<<7) | (1<<5) | (1<<2) | (1<<1) | (1<<6);
	}
	
}

int main(void) {
	DDRD &= ~(1 << PD2);
	DDRA = 0xFF;
	DDRB = 0XFF;
	PORTA = 0;
	PORTB = 0;
	PORTD = 0xFF;
	MCUCR = 2;
	GIFR = 0b11100000;
	GICR = 0b01000000;
	sei();
	while (1) {
		ran++;
		if (ran==7) ran=1;
	}

	return 0;
}
