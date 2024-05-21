/*
 * Titulo: RA1000
 *
 * Created: 31/03/2024
 * Author : Erwin Alberto Lopez Hurtado
 */ 

#define  F_CPU 2000000UL
#include <stdlib.h>
#include <avr/io.h>				//Librer?a general del Microcontrolador
#include <stdint.h>				//Para poder declarar varialbes especiales
#include <util/delay.h>			//Para poder hacer delays
#include "../../../../../../6to semestre/Micros 2/lcd library C/lcd.h"
#include "../../../../../../6to semestre/Micros 2/lcd library C/lcd.c"				//lcd
#include <avr/interrupt.h>	//	 //Para poder manejar interrupciones


#define BAUD_RATE 9600
#define UBRR_VALUE ((F_CPU / (16UL * BAUD_RATE)) - 1)


void Send(uint8_t data) {
	while (!(UCSRA & (1 << UDRE)));
	UDR = data;
}

uint8_t Read() {
	while (!(UCSRA & (1<<RXC)));
	return  UDR;
}

int ReadA(uint8_t i){
	ADMUX = i | (1<<REFS0);
	ADCSRA |= (1 << ADSC);
	while (ADCSRA & (1 << ADSC));
	return ADC;	
}

int main(void)
{
	sei();
	//clc();
	//ADC
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS0);
	ADMUX |= (1<<REFS0);
	
	//Puerto Serial
	UBRRH = (unsigned char)(UBRR_VALUE >> 8);
	UBRRL = (unsigned char)UBRR_VALUE;
	UCSRB = (1 << TXEN) | (1 << RXEN);
	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0) | (1 << USBS);
	DDRD=0b00000010;
	
    while (1) 
    {
		Read();
		Send(0);
		int pos=(float)ReadA(0)/1023.0*500;
		int neg=(float)ReadA(1)/1023.0*500;
		Send(pos);
		Send(neg);
	}
}
