/*
 * practica19_esclavo.c
 *
 * Created: 11 May 2024 22:43:14
 * Author : victor
 */ 

#define F_CPU 8000000UL			/* Define CPU Frequency 8MHz */
#include <avr/io.h>			/* Include AVR std. library file */
#include <util/delay.h>			/* Include Delay header file */
#include <stdio.h>			/* Include std. i/p o/p file */
#include <string.h>			/* Include string header file */
#include <stdlib.h>
#define MOSI 5									/* Define SPI bus pins */
#define MISO 6
#define SCK 7
#define SS 4
#define SS_Enable PORTB &= ~(1<<SS)			/* Define Slave enable */
#define SS_Disable PORTB |= (1<<SS)			/* Define Slave disable */
void SPI_Init()					/* SPI Initialize function */
{
	DDRB = (1<<MISO);			/* Make MISO pin as 
						output pin */
	SPCR = (1<<SPE);		
}
int ADC_Read(char channel)
{
	int Ain,AinLow;
	
	ADMUX=ADMUX|(channel & 0x0f);	/* Set input channel to read */

	ADCSRA |= (1<<ADSC);		/* Start conversion */
	while((ADCSRA&(1<<ADIF))==0);	/* Monitor end of conversion interrupt */
	
	_delay_us(10);
	return ADC;		/* Return digital value*/
}
void SPI_Transmit(char data)					/* SPI transmit data function */
{
	SPDR = data;								/* Write data to SPI data register */
	while(!(SPSR & (1<<SPIF)));					/* Wait till transmission complete */
}

char SPI_Receive()								/* SPI Receive data function */
{
	while(!(SPSR & (1<<SPIF)));					/* Wait till reception complete */
	return(SPDR);								/* return received data */
}

void ADC_Init()
{
	DDRA=0x0;			/* Make ADC port as input */
	ADCSRA = 0x87;			/* Enable ADC, fr/128  */
	ADMUX = 0x40;			/* Vref: Avcc, ADC channel: 0 */
	
}


int main(void)
{
	SPI_Init();
	ADC_Init();
    /* Replace with your application code */
	int count=0;		
	DDRC = 0xFF;
	PORTC=0;
    while (1) 
    {
		PORTC = 0;
		count = SPI_Receive();
		_delay_ms(100);
		if (count == 1) count = 7;
		PORTC = count;
		count = ADC_Read(count);
		count/=4;
		PORTC = count;
		SPI_Transmit(count);
		_delay_ms(100);
    }
}
