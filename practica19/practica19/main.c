/*
 * practica19.c
 *
 * Created: 11 May 2024 22:15:53
 * Author : victor
 */ 

#define F_CPU 8000000UL			/* Define CPU Frequency 8MHz */
#include <stdlib.h>
#include <avr/io.h>				//Librer?a general del Microcontrolador
#include <stdint.h>				//Para poder declarar varialbes especiales
#include <avr/io.h>			/* Include AVR std. library file */
#include <util/delay.h>			/* Include Delay header file */
#include <stdio.h>			/* Include Std. i/p o/p file */
#include <string.h>			/* Include String header file */
#include <avr/interrupt.h>	 //Para poder manejar interrupciones
#include "lcd.h"

#define MOSI 5								/* Define SPI bus pins */
#define MISO 6
#define SCK 7
#define SS1 6
#define SS2 7
#define SS1_Enable PORTA &= ~(1<<SS1)			/* Define Slave enable */
#define SS1_Disable PORTA |= (1<<SS1)			/* Define Slave disable */
#define SS2_Enable PORTA &= ~(1<<SS2)			/* Define Slave enable */
#define SS2_Disable PORTA |= (1<<SS2)			/* Define Slave disable */
void SPI_Init()								/* SPI Initialize function */
{
	DDRB |= (1<<MOSI)|(1<<SCK);		/* Make MOSI, SCK, 0th pin direction as output pins */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);	/* Enable SPI, Enable in master mode, with Fosc/16 SCK frequency */
	SPSR &= ~(1<<SPI2X);					/* Disable speed doubler */
	DDRA |= (1<<SS1) | (1<<SS2);
	PORTA |= (1<<SS1) | (1<<SS2);
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


int main(void)
{
	SPI_Init();
	DDRC = 0x00;
	PORTC = 0xFF;
	
	lcd_init(LCD_DISP_ON);
	
	lcd_puts("hola");
	float xd = 0.0;
	int value = 0;
    /* Replace with your application code */
	SS1_Disable;
	SS2_Disable;
    while (1) 
    {
		if (!(PINC&1)) {
			SS1_Enable;
		
			SPI_Write(0x00);
			_delay_ms(100);
			value = SPI_Read();
			_delay_ms(100);
			SS1_Disable;
			while (!(PINC&(1<<0)));
			lcd_clrscr();
			lcd_gotoxy(0,0);
			lcd_puts("Pot:1 Esclavo 6\nVolts: ");
			xd = value;
			xd*=5.0;
			xd/=255;
			lcd_putc((int)xd+'0');
			lcd_putc('.');
			xd*=10.0;
			while (xd>10.0) xd -= 10.0;
			lcd_putc((int)xd+'0');
			xd*=10.0;
			while (xd>10.0) xd -= 10.0;
			lcd_putc((int)xd+'0');
	
			// pot 1, esclavo 6
		} else if (!(PINC&(1<<2))) {
			// pot 2, esclavo 6
			SS1_Enable;
			
			SPI_Write(0x01);
			_delay_ms(100);
			value = SPI_Read();
			_delay_ms(100);
			SS1_Disable;
			while (!(PINC&(1<<2)));
			lcd_clrscr();
			lcd_gotoxy(0,0);
			lcd_puts("Pot:2 Esclavo 6\nVolts: ");
			xd = value;
			xd*=5.0;
			xd/=255;
			lcd_putc((int)xd+'0');
			lcd_putc('.');
			xd*=10.0;
			while (xd>10.0) xd -= 10.0;
			lcd_putc((int)xd+'0');
			xd*=10.0;
			while (xd>10.0) xd -= 10.0;
			lcd_putc((int)xd+'0');
		
		} else if (!(PINC&(1<<4))) {
			// pot 1 , esclavo 7
			SS2_Enable;
	
			SPI_Write(0x00);
			_delay_ms(100);
			value = SPI_Read();
			_delay_ms(100);
			SS2_Disable;
			while (!(PINC&(1<<4)));
			lcd_clrscr();
			lcd_gotoxy(0,0);
			lcd_puts("Pot:1 Esclavo 7\nVolts: ");
			xd = value;
			xd*=5.0;
			xd/=255;
			lcd_putc((int)xd+'0');
			lcd_putc('.');
			xd*=10.0;
			while (xd>10.0) xd -= 10.0;
			lcd_putc((int)xd+'0');
			xd*=10.0;
			while (xd>10.0) xd -= 10.0;
			lcd_putc((int)xd+'0');

		} else if (!(PINC&(1<<6))) {
			// pot 2, esclavo 7
			SS2_Enable;
		
			SPI_Write(0x01);
			_delay_ms(100);
			value = SPI_Read();
			_delay_ms(100);
			SS2_Disable;
			while (!(PINC&(1<<6)));
			lcd_clrscr();
			lcd_gotoxy(0,0);
			lcd_puts("Pot:2 Esclavo 7\nVolts: ");
			xd = value;
			xd*=5.0;
			xd/=255;
			lcd_putc((int)xd+'0');
			lcd_putc('.');
			xd*=10.0;
			while (xd>10.0) xd -= 10.0;
			lcd_putc((int)xd+'0');
			xd*=10.0;
			while (xd>10.0) xd -= 10.0;
			lcd_putc((int)xd+'0');
		
		} else {
				SS1_Disable;
				SS2_Disable;
		}
		
    }
}

