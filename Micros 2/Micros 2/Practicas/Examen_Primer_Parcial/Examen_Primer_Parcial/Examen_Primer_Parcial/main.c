/*
 * Titulo: Examen_Primer_Parcial
 *
 * Created: 22/02/2024
 * Author : Erwin Alberto Lopez Hurtado
 */ 

#define  F_CPU 8000000UL
#include <avr/io.h>				//Librer?a general del Microcontrolador
#include <stdint.h>				//Para poder declarar varialbes especiales
#include <util/delay.h>			//Para poder hacer delays
#include "../../../../../../6to semestre/Micros 2/lcd library C/lcd.h"
#include "../../../../../../6to semestre/Micros 2/lcd library C/lcd.c"				//lcd
#include <avr/interrupt.h>	//	 //Para poder manejar interrupciones
#include <time.h>
#include <stdlib.h>

#define LCD_PORT PORTD
#define XTAL 8000000 

//PROTOTIPADO DE FUNCIONES PARA PODER UTILIZARLAS DESDE CUALQUIER 'LUGAR'
//*************************************************************************
uint8_t cero_en_bit(volatile uint8_t *LUGAR, uint8_t BIT);
uint8_t uno_en_bit(volatile uint8_t *LUGAR, uint8_t BIT);
uint8_t BCD(uint8_t in);
//*************************************************************************/

void boton(volatile uint8_t *LUGAR, uint8_t BIT){
	_delay_ms(50);
	while(cero_en_bit(LUGAR,BIT)){}
	_delay_ms(50);	
}

int inicio=0;
uint16_t se=0;
uint16_t tpo=0;
int pasa=0;
int pre=0;
int de=0;

int main(void)
{
	sei();
	//clc();
	lcd_init(LCD_DISP_ON);
	
	ini:;
	inicio=0;
	se=0;
	tpo=0;
	pasa=1;
	pre=0;
	de=0;
	lcd_clrscr();
	GIFR=(1<<5);
	MCUCSR=(0<<6);
	GICR=(1<<5);
	PORTB=(1<<2);
	DDRB=1 | (0<<2);
	TIMSK=(1<<1);
	OCR0=124;
	
	lcd_puts("Iniciar...");
	while(!inicio){se++;}
	//_delay_ms(1000);
	srand(se);	
	lcd_clrscr();
	lcd_gotoxy(0,1);
	lcd_puts("Listo?");
	uint16_t t=rand()%9000+2000;
	pre=1;
	for(int i=0;i<t;i++){if(de)goto ini;_delay_ms(1);}
	PORTB|=1;
	pre=0;
	pasa=0;
	TCCR0=0b00001011;
	lcd_clrscr();
	while(!pasa){};	
	goto ini;	
}


uint8_t cero_en_bit(volatile uint8_t *LUGAR, uint8_t BIT)
{
	return (!(*LUGAR&(1<<BIT)));
}

uint8_t uno_en_bit(volatile uint8_t *LUGAR, uint8_t BIT)
{
	return (*LUGAR&(1<<BIT));
}

ISR (INT2_vect)
{
	boton(&PORTB,2);
	if(!inicio)inicio=1;
	else if(pre){
		lcd_clrscr();
		lcd_gotoxy(0,0);
		lcd_puts("Todavia no!!!");
		PORTB|=1;
		_delay_ms(1000);
		PORTB=0;
		_delay_ms(1000);
		PORTB|=1;
		_delay_ms(1000);
		PORTB=0;
		_delay_ms(1000);
		PORTB|=1;
		_delay_ms(1000);
		PORTB=0;
		_delay_ms(1000);
		de=1;
	}
	else if(!pasa){
		GICR=0;
		TCCR0=0;
		pasa=1;
		lcd_gotoxy(4,1);
		lcd_puts("Tpo:");
		lcd_putc(tpo/1000 +'0');
		lcd_putc('.');
		lcd_putc((tpo/100)%10 +'0');
		lcd_putc((tpo/10)%10 +'0');
		lcd_putc(tpo%10 +'0');
		lcd_puts(" s.");
		_delay_ms(2000);
	}
}

ISR (TIMER0_COMP_vect)
{
	tpo++;
	if(tpo>4000){
		GICR=0;
		TCCR0=0;
		lcd_gotoxy(3,1);
		lcd_puts("Excediste tpo");
		pasa=1;
		_delay_ms(2000);
	}
}