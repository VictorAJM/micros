/*
 * Titulo: EEprom
 *
 * Created: 10/03/2024
 * Author : Erwin Alberto Lopez Hurtado
 */ 

#define  F_CPU 8000000UL
#include <avr/io.h>				//Librer?a general del Microcontrolador
#include <stdint.h>				//Para poder declarar varialbes especiales
#include <util/delay.h>			//Para poder hacer delays
#include "../../../../../../6to semestre/Micros 2/lcd library C/lcd.h"
#include "../../../../../../6to semestre/Micros 2/lcd library C/lcd.c"				//lcd
#include <avr/interrupt.h>	//	 //Para poder manejar interrupciones
#include <avr/eeprom.h>
#include <stdio.h>
#include <stdlib.h>


#define LCD_PORT PORTC
#define XTAL 8000000 

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
	char x=47;
	while(x==47){
		tec_port= 0b11111110;
		if(cero_en_bit(&tec_pin,4))boton(&tec_pin,4),x='7';
		if(cero_en_bit(&tec_pin,5))boton(&tec_pin,5),x='8';
		if(cero_en_bit(&tec_pin,6))boton(&tec_pin,6),x='9';
		if(x!=47)break;
		tec_port= 0b11111101;
		if(cero_en_bit(&tec_pin,4))boton(&tec_pin,4),x='4';
		if(cero_en_bit(&tec_pin,5))boton(&tec_pin,5),x='5';
		if(cero_en_bit(&tec_pin,6))boton(&tec_pin,6),x='6';
		if(x!=47)break;
		tec_port= 0b11111011;
		if(cero_en_bit(&tec_pin,4))boton(&tec_pin,4),x='1';
		if(cero_en_bit(&tec_pin,5))boton(&tec_pin,5),x='2';
		if(cero_en_bit(&tec_pin,6))boton(&tec_pin,6),x='3';
		if(x!=47)break;
		tec_port= 0b11110111;
		if(cero_en_bit(&tec_pin,5))boton(&tec_pin,5),x='0';
		if(x!=47)break;	
	}
	return x;
}

//EEprom
//eeprom_write_byte((uint8_t*) Direccion, valor);
//eeprom_read_byte((uint8_t*) Direccion);
/*void clear_eeprom() {
	uint8_t i;
	for (i = 0; i < E2END; i++) {
		eeprom_write_byte((uint8_t*)i, 0xFF); 
	}
}*/

int main(void)
{
	//sei();
	//clc();
	//LCD
	lcd_init(LCD_DISP_ON);
	lcd_clrscr();
	//ADC
	//ADCSRA = (1 << ADEN) | (1 << ADIF) | (1 << ADPS1) | (1 << ADPS2) | (1<<ADIE);
	//ADMUX |= (1<<REFS0);
	//ADMUX |=0;
	//timer
	//TCCR0=(0<<WGM00)|(1<<WGM01)|(0<<CS02)|(1<<CS01)|(1<<CS00);
	//TCNT0=0;
	//TIMSK=(1<<OCIE0);
	//OCR0=124;
	//Interrupciones
	//MCUCR=(1<<ISC01)|(0<<ISC00);
	//GIFR=(1<<INT1)|(1<<INT0)|(1<<INT2);
	//GICR=(0<<INT1)|(1<<INT0)|(0<<INT2);
	//MCUCSR=(0<<6);
	
	//clear_eeprom();
	uint8_t * dir=0x00;
    while (1) 
    {
		lcd_gotoxy(0,0);
		for(uint8_t* i=dir;i<=dir+3;i++)
		{
			lcd_putc(eeprom_read_byte(i)+'0');
		}
		int val=Teclado()-'0';
		for(uint8_t* i=dir+5;i>=(uint8_t *)1;i--)
		{
			eeprom_write_byte(i,eeprom_read_byte(i-1));
		}
		eeprom_write_byte(dir,val);
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