/*
 * Titulo: Practica 11
 *
 * Created: 07/03/2024
 * Author : Erwin Alberto Lopez Hurtado
 */ 

#define  F_CPU 8000000UL
#include <avr/io.h>				//Librer?a general del Microcontrolador
#include <stdint.h>				//Para poder declarar varialbes especiales
#include <util/delay.h>			//Para poder hacer delays
#include "../../../../../../6to semestre/Micros 2/lcd library C/lcd.h"
#include "../../../../../../6to semestre/Micros 2/lcd library C/lcd.c"				//lcd
#include <avr/interrupt.h>	//	 //Para poder manejar interrupciones

#define LCD_PORT PORTC
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

int contador=0;
int horas=0,minutos=0,segundos=0;
int x=0;

int main(void)
{
	sei();
	//clc();
	//LCD
	lcd_init(LCD_DISP_ON);
	lcd_clrscr();
	//ADC
	ADCSRA = (1 << ADEN) | (1 << ADIF) | (1 << ADPS1) | (1 << ADPS2) | (1<<ADIE);
	ADMUX |= (1<<REFS0);
	ADMUX |=0;
	//timer
	TCCR0=(0<<WGM00)|(1<<WGM01)|(0<<CS02)|(1<<CS01)|(1<<CS00);
	TCNT0=0;
	TIMSK=(1<<OCIE0);
	OCR0=124;
	//Interrupciones
	MCUCR=(1<<ISC01)|(0<<ISC00);
	GIFR=(1<<INT1)|(1<<INT0)|(1<<INT2);
	GICR=(0<<INT1)|(1<<INT0)|(0<<INT2);
	//MCUCSR=(0<<6);
	
	PORTD=255;
	
	lcd_gotoxy(0,0);
	lcd_putc(horas/10+'0');
	lcd_putc(horas%10+'0');
	lcd_putc(':');
	lcd_putc(minutos/10+'0');
	lcd_putc(minutos%10+'0');
	lcd_putc(':');
	lcd_putc(segundos/10+'0');
	lcd_putc(segundos%10+'0');
	

    while (1) 
    {
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

ISR(ADC_vect){
	lcd_gotoxy(0,1);
	lcd_puts("                ");
	lcd_gotoxy(0,1);
	lcd_puts("Temp. ");
	float t=(float)ADC*(float)70/(float)1023;
	t-=20;
	if(t<0)lcd_putc('-'),t*=-1;
	lcd_putc((int)t/10+'0');
	lcd_putc((int)t%10+'0');
	lcd_putc('.');
	t*=10;
	lcd_putc((int)t%10+'0');
	lcd_puts(" C");
	x=segundos;

}
ISR(INT0_vect){
	//boton(&DDRD,2);
	ADCSRA|=(1<<ADSC);
	lcd_gotoxy(0,1);
}

ISR(TIMER0_COMP_vect){
	contador++;
	if(contador==1000){
		segundos++;
		if(segundos==60){
			segundos=0;
			minutos++;
		}
		if(minutos==60){
			minutos=0;
			horas++;
		}
		lcd_gotoxy(0,0);
		lcd_putc(horas/10+'0');
		lcd_putc(horas%10+'0');
		lcd_putc(':');
		lcd_putc(minutos/10+'0');
		lcd_putc(minutos%10+'0');
		lcd_putc(':');
		lcd_putc(segundos/10+'0');
		lcd_putc(segundos%10+'0');
		contador=0;
		if(segundos-5==x){
			lcd_gotoxy(0,1);
			lcd_puts("                ");
		}
	}
}