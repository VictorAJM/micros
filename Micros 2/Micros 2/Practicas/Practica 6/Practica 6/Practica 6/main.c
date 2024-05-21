/*
 * Titulo: temporizador
 *
 * Created: 13/02/2024
 * Author : Erwin Alberto Lopez Hurtado
 */ 

#define  F_CPU 4000000UL
#include <avr/io.h>				//Librer?a general del Microcontrolador
#include <stdint.h>				//Para poder declarar varialbes especiales
#include <util/delay.h>			//Para poder hacer delays
#include "../../../../../../6to semestre/Micros 2/lcd library C/lcd.h"
#include "../../../../../../6to semestre/Micros 2/lcd library C/lcd.c"				//lcd
#include <avr/interrupt.h>	//	 //Para poder manejar interrupciones

#define LCD_PORT PORTC
#define XTAL F_CPU 

//PROTOTIPADO DE FUNCIONES PARA PODER UTILIZARLAS DESDE CUALQUIER 'LUGAR'
//*************************************************************************
uint8_t cero_en_bit(volatile uint8_t *LUGAR, uint8_t BIT);
uint8_t uno_en_bit(volatile uint8_t *LUGAR, uint8_t BIT);
uint8_t BCD(uint8_t in);
//*************************************************************************/

#define tec_ddr DDRD
#define tec_port PORTD
#define tec_pin PIND

void boton(volatile uint8_t *LUGAR, uint8_t BIT){
	_delay_ms(50);
	while(cero_en_bit(LUGAR,BIT)){}
	_delay_ms(50);	
}

char Teclado(){
	tec_ddr=0b00001111;
	char x='.';
	while(x=='.'){
		tec_port= 0b11111110;
		if(cero_en_bit(&tec_pin,4))boton(&tec_pin,4),x='1';
		if(cero_en_bit(&tec_pin,5))boton(&tec_pin,5),x='2';
		if(cero_en_bit(&tec_pin,6))boton(&tec_pin,6),x='3';
		//if(cero_en_bit(&tec_pin,0))boton(&tec_pin,0,1);
		if(x!='.')break;
		tec_port= 0b11111101;
		if(cero_en_bit(&tec_pin,4))boton(&tec_pin,4),x='4';
		if(cero_en_bit(&tec_pin,5))boton(&tec_pin,5),x='5';
		if(cero_en_bit(&tec_pin,6))boton(&tec_pin,6),x='6';
		//if(cero_en_bit(&tec_pin,7))boton(&tec_pin,7),x='1';
		if(x!='.')break;
		tec_port= 0b11111011;
		if(cero_en_bit(&tec_pin,4))boton(&tec_pin,4),x='7';
		if(cero_en_bit(&tec_pin,5))boton(&tec_pin,5),x='8';
		if(cero_en_bit(&tec_pin,6))boton(&tec_pin,6),x='9';
		//if(cero_en_bit(&tec_pin,7))boton(&tec_pin,7),x='1';
		if(x!='.')break;
		tec_port= 0b11110111;
		if(cero_en_bit(&tec_pin,4))boton(&tec_pin,4),x='O';
		if(cero_en_bit(&tec_pin,5))boton(&tec_pin,5),x='0';
		//if(cero_en_bit(&tec_pin,6))boton(&tec_pin,6),x=52;
		//if(cero_en_bit(&tec_pin,7))boton(&tec_pin,7),x=49;
		if(x!='.')break;	
	}
	return x;
}

void delay_variable_ms(uint16_t milliseconds) {
	for(int i=0;i<milliseconds;i++){
		_delay_ms(1);
	}
}

int main(void)
{
	ini:;
	//sei();
	//clc();
	lcd_init(LCD_DISP_ON);
	//lcd_clrscr();
	DDRB= 0b11111111;
	DDRA= 0b11111111;
	//PORTB= 0b00000000
	TCCR0= 0b01101100;
	TCNT0= 0;
	TIMSK= 0;
	OCR0= 37;
	//8-37
	_delay_ms(1000);
	lcd_putc('0');
	lcd_putc('0');
	lcd_gotoxy(0,0);
	char x=Teclado();
	lcd_putc(x);
	char x2=Teclado();
	lcd_putc(x2);
	double t=(x-'0')*10;
	t+=x2-'0';
	t*=1000;
	t/=29;
	OCR0=8;
	delay_variable_ms(1000);
	for(int i=9;i<38;i++){
		OCR0=i;
		delay_variable_ms(t);
	}
	PORTA=1;
	PORTB=0b11100000;
	_delay_ms(2000);
	PORTA=0;
	PORTB=0;
	goto ini;
	
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