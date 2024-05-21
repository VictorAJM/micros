/*
 * practica18_maestro.c
 *
 * Created: 10 May 2024 19:57:32
 * Author : victor
 */ 

#define F_CPU 8000000UL			/* Define CPU Frequency 8MHz */
#include <avr/io.h>			/* Include AVR std. library file */
#include <util/delay.h>			/* Include Delay header file */
#include <stdio.h>			/* Include Std. i/p o/p file */
#include <string.h>			/* Include String header file */
#define MOSI 5								/* Define SPI bus pins */
#define MISO 6
#define SCK 7
#define SS 4
#define SS_Enable PORTB &= ~(1<<SS)			/* Define Slave enable */
#define SS_Disable PORTB |= (1<<SS)			/* Define Slave disable */
void SPI_Init()					/* SPI Initialize function */
{
	DDRB |= (1<<MOSI)|(1<<SCK);	/* Make MOSI, SCK, SS 
						as Output pin */
	DDRB &= ~(1<<MISO);			/* Make MISO pin 
						as input pin */
	PORTB |= (1<<SS);			/* Make high on SS pin */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);	/* Enable SPI in master mode
						with Fosc/16 */
	SPSR &= ~(1<<SPI2X);			/* Disable speed doubler */
}
void SPI_Write(char data)		/* SPI write data function */
{
	char flush_buffer;
	SPDR = data;			/* Write data to SPI data register */
	while(!(SPSR & (1<<SPIF)));	/* Wait till transmission complete */
	flush_buffer = SPDR;		/* Flush received data */
	/* Note: SPIF flag is cleared by first reading SPSR (with SPIF set) and then accessing SPDR hence flush buffer used here to access SPDR after SPSR read */
}
char SPI_Read()				/* SPI read data function */
{
	SPDR = 0xFF;
	while(!(SPSR & (1<<SPIF)));	/* Wait till reception complete */
	return(SPDR);			/* Return received data */
}
int main(void)
{
	SPI_Init();
	SS_Enable;
	DDRC = 0x00;
	PORTC = 0xFF;
	DDRA = 0xFF;
	PORTA = 0;
    /* Replace with your application code */
    while (1) 
    {
		if (!(PINC&1) > 0) {
			PORTA = 0x7F;
			SPI_Write(0xF0);
			
			PORTA = 0x8F;
			SPI_Write(0xFE);
			PORTA=0;
			while (!(PINC&(1<<0)));
		} 
		
    }
}

