/*
 * Titulo: Practica 13
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

inline uint8_t read(int addr) {
	return eeprom_read_byte((uint8_t*)addr);
}
inline void write(int addr, int val) {
	eeprom_write_byte((uint8_t*)addr, val);
}
#define pointer read(0)

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
	char x='.';
	while(x=='.'){		
		tec_port= 0b11110111;
		if(cero_en_bit(&tec_pin,4))boton(&tec_pin,4),x='<';
		if(cero_en_bit(&tec_pin,6))boton(&tec_pin,6),x='>';
		if(cero_en_bit(&tec_pin,7))boton(&tec_pin,7),x='+';
	}
	return x;
}

int contador=0;

int main(void)
{
	sei();
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
	
	contador=0;
	write(0,0x1ff);
	lcd_clrscr();
	lcd_puts("Sensando...");
	TCCR0=(0<<WGM00)|(1<<WGM01)|(0<<CS02)|(1<<CS01)|(1<<CS00);
    while(Teclado()!='+'){}
	TCCR0=0;
	write(0,pointer-1);
	lcd_clrscr();
	lcd_puts("Ultimos Val.");
	lcd_gotoxy(0,1);
	int a=1000;
	while(a!=0){
		lcd_putc((read(pointer)/a)%10+'0');
		a/=10;
	}
	lcd_puts(" Dir:");
	a=1000;
	while(a!=0){
		lcd_putc((pointer/a)%10+'0');
		a/=10;
	}
	int izq=pointer;
	while(1){
		lcd_gotoxy(0,1);
		char c=Teclado();
		int x=read(pointer);
		if(c=='+')goto ini;
		else if(c=='>' && pointer < izq){
			write(0,pointer+1);
			x=read(pointer);
		}
		else if(c=='<' && pointer > 1){
			write(0,pointer-1);
			x=read(pointer);
		}
		a=1000;
		while(a!=0){
			lcd_putc((x/a)%10+'0');
			a/=10;
		}
		lcd_puts(" Dir:");
		a=1000;
		while(a!=0){
			lcd_putc((pointer/a)%10+'0');
			a/=10;
		}
	}
}

ISR(TIMER0_COMP_vect){
	contador++;
	if(contador==250){
		ADCSRA|=(1<<ADSC);
		contador=0;
		TCCR0=0;
	}
}

ISR(ADC_vect){
	int val=ADC;
	if(pointer>=0x1ff){
		TCCR0=0;
		lcd_clrscr();
		lcd_puts("EEPROM llena");
		write(0,pointer-1);
	}
	else{
		write(pointer,val);
		write(0,pointer+1);
		TCCR0=(0<<WGM00)|(1<<WGM01)|(0<<CS02)|(1<<CS01)|(1<<CS00);
	}
}


uint8_t cero_en_bit(volatile uint8_t *LUGAR, uint8_t BIT)
{
	return (!(*LUGAR&(1<<BIT)));
}

uint8_t uno_en_bit(volatile uint8_t *LUGAR, uint8_t BIT)
{
	return (*LUGAR&(1<<BIT));
}