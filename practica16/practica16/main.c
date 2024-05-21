/*
 * practica16.c
 *
 * Created: 02/04/2024 08:22:27 p. m.
 * Author : victor
 */ 

#define  F_CPU 4000000UL
#include <stdlib.h>
#include <avr/io.h>				//Librer?a general del Microcontrolador
#include <stdint.h>				//Para poder declarar varialbes especiales
#include <util/delay.h>			//Para poder hacer delays
#include <avr/interrupt.h>	 //Para poder manejar interrupciones

#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

uint8_t sensor = 0;
uint8_t wait = 0;


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
	while (! (UCSRA & (1<<UDRE)));	/* Wait for empty transmit buffer*/
	UDR = ch ;
}

int main(void){
	sei();
	DDRD = 0x00000010;
	PORTD = 0;
	DDRA = 0;
	PORTA = 0;
	DDRB = 0xff;
	DDRC = 0xff;
	PORTB=PORTC=0;
	serial_init(9600);
	
	ADMUX = 0b01000000;
	SFIOR = 0;
	ADCSRA = 0b10011011;
	
	while(1){
		sensor = serial_rxbyte();
		ADMUX = (ADMUX&(0xF0)) | (sensor-'0');
		ADCSRA |= (1 << ADSC);
	}
}

ISR(ADC_vect) {
	uint16_t val =  ADC;
	val >>= 2;
	if (sensor == '0') {
		int g = (val+1)/64;
		PORTB &= 0XF0;
		PORTB |= ((1<<(g))-1);
	}else if (sensor == '1') {
		int g = (val+1)/64;
		PORTB &= 0X0F;
		PORTB |= ((1<<(g))-1)*16;
	} else {
		int g = (val+1)/64;
		PORTC=0;
		PORTC |= ((1<<(g))-1);
	}
	serial_txbyte(val);
}