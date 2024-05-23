/*
 * practica20.c
 *
 * Created: 22 May 2024 18:54:57
 * Author : victor
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <string.h>
#include "lcd.h"
#define MOSI 5								/* Define SPI bus pins */
#define MISO 6
#define SCK 7
#define SS1 4
#define SS1_Enable PORTB &= ~(1<<SS1)			/* Define Slave enable */
#define SS1_Disable PORTB |= (1<<SS1)			/* Define Slave disable */
void SPI_Init()								/* SPI Initialize function */
{
	DDRB |= (1<<MOSI)|(1<<SCK);		/* Make MOSI, SCK, 0th pin direction as output pins */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);	/* Enable SPI, Enable in master mode, with Fosc/16 SCK frequency */
	SPSR &= ~(1<<SPI2X);					/* Disable speed doubler */
	DDRB |= (1<<SS1);
	PORTB |= (1<<SS1);
}

void SPI_Write(char data)					/* SPI write data function */
{
	SPDR = data;							/* Write data to SPI data register */
	while(!(SPSR & (1<<SPIF)));				/* Wait till transmission complete */
}

char SPI_Read()								/* SPI read data function */
{
	SPDR = 0x00;
	while(!(SPSR & (1<<SPIF)));				/* Wait till reception complete */
	return(SPDR);							/* return received data */
}

char mat[4][4] = {
	{'7', '8', '9', 'A'},
	{'4', '5', '6', 'B'},
	{'1', '2', '3', 'C'},
	{'E', '0', 'F', 'D'}
};
uint8_t p_pin;
char keyboard(){
	while(1){
		for(uint8_t i = 0; i<4; i++){
			PORTA = 0b11111111 ^ (1<<(7-i));
			if(~PINA&1 && '0' <= mat[i][3] && mat[i][3]<='9') {p_pin = 1;return mat[i][3];}
			if(~PINA&2 && '0' <= mat[i][2] && mat[i][2]<='9') {p_pin = 2;return mat[i][2];}
			if(~PINA&4 && '0' <= mat[i][1] && mat[i][1]<='9') {p_pin = 4;return mat[i][1];}
			if(~PINA&8 && '0' <= mat[i][0] && mat[i][0]<='9') {p_pin = 8;return mat[i][0];}
		}
	}
}
char keyboard_1(){
	while(1){
		for(uint8_t i = 0; i<4; i++){
			PORTA = 0b11111111 ^ (1<<(7-i));
			if(~PINA&1 && '0' <= mat[i][3] && mat[i][3]<='4') {p_pin = 1;return mat[i][3];}
			if(~PINA&2 && '0' <= mat[i][2] && mat[i][2]<='4') {p_pin = 2;return mat[i][2];}
			if(~PINA&4 && '0' <= mat[i][1] && mat[i][1]<='4') {p_pin = 4;return mat[i][1];}
			if(~PINA&8 && '0' <= mat[i][0] && mat[i][0]<='4') {p_pin = 8;return mat[i][0];}
		}
	}
}
char keyboard_2(){
	while(1){
		for(uint8_t i = 0; i<4; i++){
			PORTA = 0b11111111 ^ (1<<(7-i));
			if(~PINA&1 && 'D' <= mat[i][3] && mat[i][3]<='D') {p_pin = 1;return mat[i][3];}
			if(~PINA&2 && 'D' <= mat[i][2] && mat[i][2]<='D') {p_pin = 2;return mat[i][2];}
			if(~PINA&4 && 'D' <= mat[i][1] && mat[i][1]<='D') {p_pin = 4;return mat[i][1];}
			if(~PINA&8 && 'D' <= mat[i][0] && mat[i][0]<='D') {p_pin = 8;return mat[i][0];}
		}
	}
}
void wait_btn(){
	_delay_ms(50);
	while(~PINA&p_pin);
	_delay_ms(50);
}
void mandardatos(int a) {
	a <<= 6;
	int slv = 4;
	PORTB &= ~(1<<slv);
	_delay_ms(10);
	SPDR =  (a >> 8);
	while (!(SPSR & (1 << SPIF)));
	_delay_ms(10);
	SPDR = a & 0xff;
	while (!(SPSR & (1 << SPIF)));
	PORTB |= (1<<slv);
	_delay_ms(10);
}
int main(void)
{
	SPI_Init();
	lcd_init(LCD_DISP_ON);
	DDRA = 0xF0;
	
    /* Replace with your application code */
    while (1) 
    {
		lcd_clrscr();
		lcd_puts("Ingresa voltaje");
		uint8_t num = keyboard_1();
		lcd_gotoxy(0,1);
		lcd_putc(num);
		lcd_putc('.');
		wait_btn();
		uint8_t num1 = keyboard();
		lcd_putc(num1);
		wait_btn();
		
		uint8_t num2 = keyboard();
		lcd_putc(num2);
		wait_btn();
		uint8_t num3 = keyboard_2();
		lcd_clrscr();
		lcd_puts("Listo!");
		float xd = (num-'0')*100.0;
		xd += (num1-'0')*10.0;
		xd += (num2-'0');
		xd /= 5.0;
		xd *=2.55;
		mandardatos((int)xd);
		_delay_ms(2000);
    }
}

