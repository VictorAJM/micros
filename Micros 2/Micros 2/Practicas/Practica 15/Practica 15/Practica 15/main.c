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

#define LCD_PORT PORTC
#define XTAL 1000000 

#define BAUD_RATE 4800
#define UBRR_VALUE ((F_CPU / (16UL * BAUD_RATE)) - 1)

void Send(uint8_t data) {
	while (!(UCSRA & (1 << UDRE)))
	;
	UDR = data;
}

char Recive() {
	while (!(UCSRA & (1<<RXC)));
	
	return UDR;
}



int main(void)
{
	sei();
	//clc();
	//LCD
	lcd_init(LCD_DISP_ON);
	lcd_clrscr();
	
	//Puerto Serial
	UBRRH = (unsigned char)(UBRR_VALUE >> 8);
	UBRRL = (unsigned char)UBRR_VALUE;
	UCSRB = (1 << TXEN) | (1 << RXEN);
	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0) | (1 << USBS);
	DDRD=0b00000010;
	
	int contador=0;
	
    while (1) 
    {
		char c=Recive();
		if(c=='/'){
			if(contador!=0)contador--;
			lcd_gotoxy(contador%16,contador/16);
			lcd_putc(' ');
			lcd_gotoxy(contador%16,contador/16);
			continue;
		}
		if(contador==16){
			lcd_gotoxy(0,1);
		}
		else if(contador==32){
			contador=0;
			lcd_clrscr();
		}
		lcd_putc(c);
		_delay_ms(100);
		contador++;
	}
}

