/*
 * Titulo: contador
 *
 * Created: 30/01/2024
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
uint8_t BCD(uint8_t in);
//*************************************************************************/

uint8_t cont=0;

void boton(volatile uint8_t *LUGAR, uint8_t BIT,uint8_t x){
	_delay_ms(50);
	while(cero_en_bit(LUGAR,BIT)){}
	cont+=x;
	_delay_ms(50);	
}

int main(void)
{
	DDRA=0;
	PORTA=0b10000001;
	DDRC=255;
    while (1) 
    {
		if(cero_en_bit(&PINA,0) && cont<19)boton(&PINA,0,1);
		if(cero_en_bit(&PINA,7) && cont>0)boton(&PINA,7,-1);
		uint8_t out=cont%10;
		out=out<<4;
		out|=cont/10;
		PORTC=out;
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