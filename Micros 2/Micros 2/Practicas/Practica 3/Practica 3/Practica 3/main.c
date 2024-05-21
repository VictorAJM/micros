/*
 * Titulo: LCD
 *
 * Created: 05/02/2024
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

#define tec_ddr DDRA
#define tec_port PORTA
#define tec_pin PINA

void boton(volatile uint8_t *LUGAR, uint8_t BIT){
	_delay_ms(50);
	while(cero_en_bit(LUGAR,BIT)){}
	_delay_ms(50);	
}

char Teclado(){
	tec_ddr=0b00001111;
	char x=47;
	while(x==47){
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
		if(x!=47)break;
		tec_port= 0b11111011;
		if(cero_en_bit(&tec_pin,4))boton(&tec_pin,4),x=48;
		if(cero_en_bit(&tec_pin,5))boton(&tec_pin,5),x=56;
		if(cero_en_bit(&tec_pin,6))boton(&tec_pin,6),x=53;
		if(cero_en_bit(&tec_pin,7))boton(&tec_pin,7),x=50;
		if(x!=47)break;
		tec_port= 0b11110111;
		if(cero_en_bit(&tec_pin,4))boton(&tec_pin,4),x=59;
		if(cero_en_bit(&tec_pin,5))boton(&tec_pin,5),x=55;
		if(cero_en_bit(&tec_pin,6))boton(&tec_pin,6),x=52;
		if(cero_en_bit(&tec_pin,7))boton(&tec_pin,7),x=49;
		if(x!=47)break;	
	}
	return x;
}


int main(void)
{
	lcd_init(LCD_DISP_ON);
	lcd_clrscr();
	uint8_t cont=0;
    while (1) 
    {
		char in=Teclado();
		if(in==59){
			lcd_clrscr();
			cont=0;
		}
		else if(in==58 && cont){
			lcd_gotoxy(cont-1,(uint8_t)0);
			lcd_putc(' ');
			lcd_gotoxy(cont-1,(uint8_t)0);
			cont--;
		}
		else if(in<58 && cont<10){
			lcd_putc(in);
			cont++;	
		}
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