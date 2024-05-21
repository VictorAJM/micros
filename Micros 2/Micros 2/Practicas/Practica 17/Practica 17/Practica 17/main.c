/*
 * Titulo: Practica 17
 *
 * Created: 04/04/2024
 * Author : Erwin Alberto Lopez Hurtado
 */ 

#define  F_CPU 8000000UL
#include <avr/io.h>				//Librer?a general del Microcontrolador
#include <stdint.h>				//Para poder declarar varialbes especiales
#include <util/delay.h>			//Para poder hacer delays
#include "../../../../../../6to semestre/Micros 2/lcd library C/lcd.h"
#include "../../../../../../6to semestre/Micros 2/lcd library C/lcd.c"				//lcd
#include <avr/interrupt.h>	//	 //Para poder manejar interrupciones


#define tec_ddr DDRA
#define tec_port PORTA
#define tec_pin PINA

#define BAUD_RATE 9600
#define UBRR_VALUE ((F_CPU / (16UL * BAUD_RATE)) - 1)

uint8_t cero_en_bit(volatile uint8_t *LUGAR, uint8_t BIT)
{
	return (!(*LUGAR&(1<<BIT)));
}

void Send(uint8_t data) {
	while (!(UCSRA & (1 << UDRE)));
	UDR = data;
}

uint8_t Read() {
	while (!(UCSRA & (1<<RXC)));
	return UDR;
}

void boton(volatile uint8_t *LUGAR, uint8_t BIT){
	_delay_ms(50);
	while(cero_en_bit(LUGAR,BIT)){}
	_delay_ms(50);
}

int Teclado(){
	tec_ddr=0b00001111;
	int x=-1;
	while(x==-1){
		tec_port= 0b11111110;
		if(cero_en_bit(&tec_pin,4))boton(&tec_pin,4),x=1;
		if(cero_en_bit(&tec_pin,5))boton(&tec_pin,5),x=2;
		if(cero_en_bit(&tec_pin,6))boton(&tec_pin,6),x=3;
		if(x!=-1)break;
		tec_port= 0b11111101;
		if(cero_en_bit(&tec_pin,4))boton(&tec_pin,4),x=4;
		if(cero_en_bit(&tec_pin,5))boton(&tec_pin,5),x=5;
		if(cero_en_bit(&tec_pin,6))boton(&tec_pin,6),x=6;
		if(x!=-1)break;
		tec_port= 0b11111011;
		if(cero_en_bit(&tec_pin,4))boton(&tec_pin,4),x=7;
		//if(cero_en_bit(&tec_pin,5))boton(&tec_pin,5),x=8;
		//if(cero_en_bit(&tec_pin,6))boton(&tec_pin,6),x=9;
		//if(cero_en_bit(&tec_pin,7))boton(&tec_pin,7),x=10;
		if(x!=-1)break;
	}
	return x;
}

void frq(int fe){
	OCR0=fe;
	//_delay_ms(1000);
}

int main(void)
{
	while(1){
		sei();
		//clc();
	
	
		//timer
		DDRB |= (1 << 3);
		TCCR0 = 0b00011010;
		//Puerto Serial
		UBRRH = (unsigned char)(UBRR_VALUE >> 8);
		UBRRL = (unsigned char)UBRR_VALUE;
		UCSRB = (1 << TXEN) | (1 << RXEN);
		UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0) | (1 << USBS);
		DDRD=0b00000010;
	
		DDRA=0;
		PORTA=255;
	
		//frq(238);
		
		while(Teclado()!=7);
		Send(10);
		
		ini:;
		frq(0);
		
		while(1){
			int x=Teclado();
			Send(x-1);
			int val=Read();
			if(val<255 && val>1)frq(val);
			if(val==0)goto ini;
		}	
	}
	
}
