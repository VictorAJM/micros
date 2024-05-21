/*
 * Titulo: BCD a 7 segmentos
 *
 * Created: 23/01/2024
 * Author : Erwin Alberto Lopez Hurtado
 */ 

#define  F_CPU 1000000UL
#include <avr/io.h>				//Librer?a general del Microcontrolador
#include <stdint.h>				//Para poder declarar varialbes especiales
#include <util/delay.h>			//Para poder hacer delays
//#include <avr/interrupt.h>	 //Para poder manejar interrupciones

//PROTOTIPADO DE FUNCIONES PARA PODER UTILIZARLAS DESDE CUALQUIER "LUGAR"
//*************************************************************************
uint8_t cero_en_bit(volatile uint8_t *LUGAR, uint8_t BIT);
uint8_t uno_en_bit(volatile uint8_t *LUGAR, uint8_t BIT);
void BCD(uint8_t *in, uint8_t *out);
//*************************************************************************/


int main(void)
{
	DDRA= 0b00000000;
	PORTA= 0b11110000;
	DDRC= 0b11111111;
	
    while (1) 
	{
		uint8_t in=PINA;
		uint8_t out=0;
		for(uint8_t i=0;i<4;i++)in=in>>1;
		BCD(&in,&out);
		PORTC=out;
    }
}


void BCD(uint8_t *in,uint8_t *out){
	switch(*in){
		case 0:*out=0b00111111;break;
		case 1:*out=0b00000110;break;
		case 2:*out=0b01011011;break;
		case 3:*out=0b01001111;break;
		case 4:*out=0b01100110;break;
		case 5:*out=0b01101101;break;
		case 6:*out=0b01111101;break;
		case 7:*out=0b00000111;break;
		case 8:*out=0b01111111;break;
		case 9:*out=0b01100111;break;
		case 10:*out=0b01110111;break;
		case 11:*out=0b01111100;break;
		case 12:*out=0b00111001;break;
		case 13:*out=0b01011110;break;
		case 14:*out=0b01111001;break;
		case 15:*out=0b01110001;break;
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