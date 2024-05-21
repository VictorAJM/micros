/*
	* Titulo: Timer 0
	
 * Created: 08/02/2024
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

//PROTOTIPADO DE FUNCIONES PARA PODER UTILIZARLAS DESDE CUALQUIER 'LUGAR'
//*************************************************************************
uint8_t cero_en_bit(volatile uint8_t *LUGAR, uint8_t BIT);
uint8_t uno_en_bit(volatile uint8_t *LUGAR, uint8_t BIT);
uint8_t BCD(uint8_t in);
//*************************************************************************/
//clc();

void boton(volatile uint8_t *LUGAR, uint8_t BIT){
	_delay_ms(50);
	while(cero_en_bit(LUGAR,BIT)){}
	_delay_ms(50);	
}

char x='A';
int p=-1;
int c=0;

int main(void)
{
	sei();
	DDRA= 0;
	PORTA=1;
	lcd_init(LCD_DISP_ON);
	TCNT0= 0;
	TIMSK= 2;
	OCR0= 38;
	
	
    while (1) 
    {
		if(p==16)p=-1,lcd_clrscr();
		while(uno_en_bit(&PINA,0)){}
		boton(&PINA,0);	
		if(c==0)p+=1;
		lcd_gotoxy(p,0);	
		TCCR0= 0b00001100;	
		lcd_putc(x);
		x++;
		if(x=='Z'+1)x='A';
		TCNT0= 0;
		c=0;
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
	c++;
	if(c==100){
		x='A';
		TCCR0=0;
		TCNT0=0;
		c=0;	
	}
}