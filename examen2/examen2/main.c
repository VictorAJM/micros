/*
 * examen2.c
 *
 * Created: 09/04/2024 11:07:39 a. m.
 * Author : victor
 */ 

#define  F_CPU 1000000UL
#include <stdlib.h>
#include <avr/io.h>                //Librería general del Microcontrolador
#include <stdint.h>                //Para poder declarar varialbes especiales
#include <util/delay.h>            //Para poder hacer delays
#include <avr/interrupt.h>     //Para poder manejar interrupciones
#include <avr/eeprom.h>
#include "lcd.h"

#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
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
int main(void)
{
	lcd_init(LCD_DISP_ON);
	DDRA = DDRB  = 0x00;
	PORTA = PORTB = 0xFF;
	DDRD = 0xF0;
	PORTD = 0x0F;
	char xd = eeprom_read_byte(0);
	lcd_gotoxy(0,1);
	lcd_putc(xd);
    /* Replace with your application code */
	serial_init(4800);
    while (1) 
    {
		if ((UCSRA & (1 << RXC))) {
			char c = serial_rxbyte();
			lcd_gotoxy(0,1);
			lcd_putc(c);
			serial_txbyte(c);
			eeprom_write_byte(0,c);
		}
		if (!(PINA&(1))) {
			_delay_ms(50);
			char c = 255 - PINB;
			if (c<33 || c>126) {
				while (!(PINA&(1)));
				_delay_ms(50);
			} else {
				lcd_gotoxy(0,1);
				lcd_putc(c);
				serial_txbyte(c);
				eeprom_write_byte(0,c);
				while (!(PINA&(1)));
				_delay_ms(50);
			}
		}
    }
}

