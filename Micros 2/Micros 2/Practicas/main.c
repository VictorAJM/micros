/*
 * Titulo: Main
 *
 * Created: 00/00/2024
 * Author : Erwin Alberto Lopez Hurtado
 */ 

#define  F_CPU 1000000UL
#include <avr/io.h>				//Librer?a general del Microcontrolador
#include <stdint.h>				//Para poder declarar varialbes especiales
#include <util/delay.h>			//Para poder hacer delays
#include "../../../../../../6to semestre/Micros 2/lcd library C/lcd.h"
#include "../../../../../../6to semestre/Micros 2/lcd library C/lcd.c"				//lcd
#include <avr/interrupt.h>	//	 //Para poder manejar interrupciones

#define LCD_PORT PORTD
#define XTAL 1000000 

#define BAUD_RATE 4800
#define UBRR_VALUE ((F_CPU / (16UL * BAUD_RATE)) - 1)

#define tec_ddr DDRA
#define tec_port PORTA
#define tec_pin PINA

//PROTOTIPADO DE FUNCIONES PARA PODER UTILIZARLAS DESDE CUALQUIER 'LUGAR'
//*************************************************************************
uint8_t cero_en_bit(volatile uint8_t *LUGAR, uint8_t BIT);
uint8_t uno_en_bit(volatile uint8_t *LUGAR, uint8_t BIT);
uint8_t BCD(uint8_t in);
//*************************************************************************/

void Send(uint8_t data) {
	while (!(UCSRA & (1 << UDRE)))
	;
	UDR = data;
}

uint8_t USART_Receive() {
	while (!(UCSRA & (1<<RXC)));
	
	return UDR;
}


void boton(volatile uint8_t *LUGAR, uint8_t BIT){
	_delay_ms(50);
	while(cero_en_bit(LUGAR,BIT)){}
	_delay_ms(50);	
}

char Teclado(){
	tec_ddr=0b00001111;
	char x='.';
	while(x=='.'){
		//tec_port= 0b11111110;
		//if(cero_en_bit(&tec_pin,0))boton(&tec_pin,0,1);
		//if(cero_en_bit(&tec_pin,0))boton(&tec_pin,0,1);
		//if(cero_en_bit(&tec_pin,0))boton(&tec_pin,0,1);
		//if(cero_en_bit(&tec_pin,0))boton(&tec_pin,0,1);
		tec_port= 0b11111101;
		if(cero_en_bit(&tec_pin,4))boton(&tec_pin,4),x=58;
		if(cero_en_bit(&tec_pin,5))boton(&tec_pin,5),x=57;
		if(cero_en_bit(&tec_pin,6))boton(&tec_pin,6),x=54;
		if(cero_en_bit(&tec_pin,7))boton(&tec_pin,7),x=51;
		if(x!='.')break;
		tec_port= 0b11111011;
		if(cero_en_bit(&tec_pin,4))boton(&tec_pin,4),x=48;
		if(cero_en_bit(&tec_pin,5))boton(&tec_pin,5),x=56;
		if(cero_en_bit(&tec_pin,6))boton(&tec_pin,6),x=53;
		if(cero_en_bit(&tec_pin,7))boton(&tec_pin,7),x=50;
		if(x!='.')break;
		tec_port= 0b11110111;
		if(cero_en_bit(&tec_pin,4))boton(&tec_pin,4),x=59;
		if(cero_en_bit(&tec_pin,5))boton(&tec_pin,5),x=55;
		if(cero_en_bit(&tec_pin,6))boton(&tec_pin,6),x=52;
		if(cero_en_bit(&tec_pin,7))boton(&tec_pin,7),x=49;
		if(x!='.')break;	
	}
	return x;
}


int main(void)
{
	//sei();
	//clc();
	//LCD
	lcd_init(LCD_DISP_ON);
	lcd_clrscr();
	ini:;
	
	//ADC
	ADCSRA = (1 << ADEN) | (1 << ADIF) | (1 << ADPS1) | (1 << ADPS2) | (1<<ADIE);
	ADMUX |= (1<<REFS0);
	ADMUX |=0;
	
	//timer
	//TCCR0=(0<<WGM00)|(1<<WGM01)|(0<<CS02)|(1<<CS01)|(1<<CS00);
	TCNT0=0;
	TIMSK=(1<<OCIE0);
	OCR0=124;
	
	//Interrupciones
	//MCUCR=(1<<ISC01)|(0<<ISC00);
	//GIFR=(1<<INT1)|(1<<INT0)|(1<<INT2);
	//GICR=(0<<INT1)|(1<<INT0)|(0<<INT2);
	//MCUCSR=(0<<6);
	
	//Puerto Serial
	UBRRH = (unsigned char)(UBRR_VALUE >> 8);
	UBRRL = (unsigned char)UBRR_VALUE;
	UCSRB = (1 << TXEN) | (1 << RXEN);
	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0) | (1 << USBS);
	DDRD=0b00000010;
    while (1) 
    {

	}
}

uint8_t BCD(uint8_t in){
	switch(in){
		case 0:return 0b00111111;break;
		case 1:return 0b00000110;break;
		case 2:return 0b01011011;break;
		case 3:return 0b01001111;break;
		case 4:return 0b01100110;break;
		case 5:return 0b01101101;break;
		case 6:return 0b01111101;break;
		case 7:return 0b00000111;break;
		case 8:return 0b01111111;break;
		case 9:return 0b01100111;break;
		case 10:return 0b01110111;break;
		case 11:return 0b01111100;break;
		case 12:return 0b00111001;break;
		case 13:return 0b01011110;break;
		case 14:return 0b01111001;break;
		case 15:return 0b01110001;break;
	}
	return 0;
}


uint8_t cero_en_bit(volatile uint8_t *LUGAR, uint8_t BIT)
{
	return (!(*LUGAR&(1<<BIT)));
}

uint8_t uno_en_bit(volatile uint8_t *LUGAR, uint8_t BIT)
{
	return (*LUGAR&(1<<BIT));
}

ISR(TIMER0_COMP_vect){
	
}

ISR(ADC_vect){
	
}