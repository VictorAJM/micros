/*
 * practica14.c
 *
 * Created: 21/03/2024 02:38:34 p. m.
 * Author : victor
 */ 

#define  F_CPU 1000000UL
#include <stdlib.h>
#include <avr/io.h>                //Librería general del Microcontrolador
#include <stdint.h>                //Para poder declarar varialbes especiales
#include <util/delay.h>            //Para poder hacer delays
#include <avr/interrupt.h>     //Para poder manejar interrupciones
#include "lcd.h"

#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

uint8_t volth  = 0, voltl = 0;
void serial_init(long USART_BAUDRATE){
	UCSRB |= (1 << RXEN) | (1 << TXEN);
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);
	UBRRL = BAUD_PRESCALE;
	UBRRH = (BAUD_PRESCALE >> 8);
}

uint8_t serial_rxbyte(){
	while ((UCSRA & (1 << RXC)) == 0);
	return(UDR);
}

void serial_txbyte(uint8_t ch){
	while (! (UCSRA & (1<<UDRE)));    /* Wait for empty transmit buffer*/
	UDR = ch ;
}

int main(void){
	lcd_init(LCD_DISP_ON);

	DDRD = 0xFF;
	PORTD = 0;
	DDRB = 0;
	PORTB = 0;

	serial_init(4800);

	sei();
	ADMUX = 0b01000000;
	SFIOR = 0;
	ADCSRA = 0b11011011;
	while(1){
		_delay_ms(20);
		serial_txbyte(volth);
		//serial_txbyte(voltl);
	}
}

ISR(ADC_vect) {
	uint16_t val =  ADCL | ADCH<<8;
	voltl = val;
	volth = (val>>2);

	lcd_gotoxy(0,0);
	lcd_putc(volth/100 +'0');
	lcd_putc((volth%100)/10 +'0');
	lcd_putc(volth%10 +'0');

	ADCSRA |= (1 << ADSC);
}