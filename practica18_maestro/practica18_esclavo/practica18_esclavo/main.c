/*
 * practica18_esclavo.c
 *
 * Created: 10 May 2024 19:58:15
 * Author : victor
 */ 

#define F_CPU 8000000UL			/* Define CPU Frequency 8MHz */
#include <avr/io.h>			/* Include AVR std. library file */
#include <util/delay.h>			/* Include Delay header file */
#include <stdio.h>			/* Include std. i/p o/p file */
#include <string.h>			/* Include string header file */
#define MOSI 5									/* Define SPI bus pins */
#define MISO 6
#define SCK 7
#define SS 4
#define SS_Enable PORTB &= ~(1<<SS)			/* Define Slave enable */
#define SS_Disable PORTB |= (1<<SS)			/* Define Slave disable */
void SPI_Init()					/* SPI Initialize function */
{
	DDRB &= ~((1<<MOSI)|(1<<SCK)|(1<<SS));  /* Make MOSI, SCK, SS as
 						input pins */
	DDRB |= (1<<MISO);			/* Make MISO pin as 
						output pin */
	SPCR = (1<<SPE);			/* Enable SPI in slave mode */
}
char SPI_Receive()			/* SPI Receive data function */
{
	while(!(SPSR & (1<<SPIF)));	/* Wait till reception complete */
	return(SPDR);			/* Return received data */
}
int main(void)
{
	SPI_Init();
    /* Replace with your application code */
	int count=0;
	DDRC = 0xFF;
	PORTC=0;
    while (1) 
    {
		count = SPI_Receive();
		PORTC = count;
		_delay_ms(1000);
		PORTC=0;
    }
}

