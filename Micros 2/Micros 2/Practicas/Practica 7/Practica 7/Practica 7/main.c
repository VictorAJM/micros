/*
 * Titulo: Notas Musicales
 *
 * Created: 19/02/2024
 * Author : Erwin Alberto Lopez Hurtado
 */ 

#define  F_CPU 8000000UL
#include <avr/io.h>				//Librer?a general del Microcontrolador
#include <stdint.h>				//Para poder declarar varialbes especiales
#include <util/delay.h>			//Para poder hacer delays
#include "../../../../../../6to semestre/Micros 2/lcd library C/lcd.h"
#include "../../../../../../6to semestre/Micros 2/lcd library C/lcd.c"				//lcd
#include <avr/interrupt.h>	//	 //Para poder manejar interrupciones
#include "../../../../../../6to semestre/Micros 2/Practicas/Practica 7/notes.h"


//PROTOTIPADO DE FUNCIONES PARA PODER UTILIZARLAS DESDE CUALQUIER 'LUGAR'
//*************************************************************************
uint8_t cero_en_bit(volatile uint8_t *LUGAR, uint8_t BIT);
uint8_t uno_en_bit(volatile uint8_t *LUGAR, uint8_t BIT);
uint8_t BCD(uint8_t in);
//*************************************************************************/


#define corchea 166
#define negra 2*corchea
#define blanca 2*negra
#define redonda 2*blanca
#define fhc4 (int[]){0b00011101,1351}
#define bc4 (int[]){0b00011101,1012}
#define dbc5 (int[]){0b00011101,902}
#define fhc5 (int[]){0b00011101,676}
#define bc5 (int[]){0b00011101,506}
#define dbc6 (int[]){0b00011101,451}
#define bbc5 (int[]){0b00011011,536}
#define abc5 (int[]){0b00011101,602}
#define fc5 (int[]){0b00011011,716}
#define ebc5 (int[]){0b00011011,804}
#define dc5 (int[]){0b00011011,851}
#define gc5 (int[]){0b00011101,638}
#define silencio (int[]){0,0}
#define DEFAULT_VOLUME 100
	


void frq(int* fe){
	int note=fe[1];
	if(note==0)OCR1B = 0;
	else{
		OCR1B = DEFAULT_VOLUME;
		ICR1H = (note >> 8);
		ICR1L = note;	
	}
}


int main(void)
{
while(1){
	DDRD |= (1<<DDD4); 
	TCCR1A |= (1<<COM1B1); 
	TCCR1B |= (1<<WGM13) | (1<<CS11);
	


	frq(fhc4);
	_delay_ms(corchea);
	frq(bc4);
	_delay_ms(negra);
	frq(dbc5);
	_delay_ms(negra);
	frq(fhc5);
	_delay_ms(negra);
	frq(bc5);
	_delay_ms(corchea);
	frq(dbc6);
	_delay_ms(negra);
	
	frq(fhc4);
	_delay_ms(corchea);
	frq(bc4);
	_delay_ms(corchea);
	frq(dbc5);
	_delay_ms(corchea);
	frq(fhc5);
	_delay_ms(negra);
	frq(bc5);
	_delay_ms(negra);
	frq(dbc6);
	_delay_ms(negra);
	_delay_ms(negra);
    
	frq(bc4);
	_delay_ms(negra);
	frq(dbc5);
	_delay_ms(corchea);
	frq(fhc5);
	_delay_ms(corchea);
	frq(bc5);
	_delay_ms(corchea);
	frq(dbc6);
	_delay_ms(negra);
	frq(dbc5);
	_delay_ms(corchea);
	frq(dbc5);
	_delay_ms(corchea);
	frq(silencio);
	_delay_ms(negra);
	
	frq(bbc5);
	_delay_ms(corchea);
	frq(abc5);
	_delay_ms(corchea);
	frq(fhc5);
	_delay_ms(corchea);
	frq(abc5);
	_delay_ms(corchea);
	frq(silencio);
	_delay_ms(corchea);
	frq(dbc6);
	_delay_ms(corchea);
	frq(silencio);
	_delay_ms(corchea);
	frq(abc5);
	_delay_ms(blanca);
	frq(abc5);
	_delay_ms(corchea);
	frq(fhc5);
	_delay_ms(corchea);
	
	frq(fc5);
	_delay_ms(corchea);
	frq(ebc5);
	_delay_ms(corchea);
	frq(dc5);
	_delay_ms(blanca);
	frq(abc5);
	_delay_ms(corchea);
	frq(fhc5);
	_delay_ms(corchea);
	frq(fc5);
	_delay_ms(corchea);
	frq(ebc5);
	_delay_ms(blanca);
	
	frq(ebc5);
	_delay_ms(corchea);
	frq(fc5);
	_delay_ms(corchea);
	frq(fhc5);
	_delay_ms(corchea);
	frq(abc5);
	_delay_ms(corchea);
	frq(bbc5);
	_delay_ms(corchea);
	frq(abc5);
	_delay_ms(corchea);
	frq(fhc5);
	_delay_ms(corchea);
	frq(abc5);
	_delay_ms(corchea);
	frq(silencio);
	_delay_ms(corchea);
	frq(dbc6);
	_delay_ms(corchea);
	frq(silencio);
	_delay_ms(corchea);
	
	frq(abc5);
	_delay_ms(blanca);
	frq(abc5);
	_delay_ms(corchea);
	frq(fhc5);
	_delay_ms(corchea);
	frq(fc5);
	_delay_ms(corchea);
	frq(fhc5);
	_delay_ms(corchea);
	frq(ebc5);
	_delay_ms(corchea);
	frq(fc5);
	_delay_ms(corchea);
	frq(fhc5);
	_delay_ms(corchea);
	frq(abc5);
	_delay_ms(corchea);
	
	frq(silencio);
	_delay_ms(corchea);
	frq(dbc6);
	_delay_ms(corchea);
	frq(silencio);
	_delay_ms(corchea);
	frq(bc5);
	_delay_ms(negra);
	frq(bbc5);
	_delay_ms(corchea);
	frq(abc5);
	_delay_ms(corchea);
	frq(fhc5);
	_delay_ms(corchea);
	frq(fhc5);
	_delay_ms(blanca);
	frq(silencio);
	_delay_ms(negra);
	frq(bbc5);
	_delay_ms(corchea);
	frq(abc5);
	_delay_ms(corchea);
	
	frq(fhc5);
	_delay_ms(corchea);
	frq(abc5);
	_delay_ms(corchea);
	frq(silencio);
	_delay_ms(corchea);
	frq(dbc6);
	_delay_ms(corchea);
	frq(silencio);
	_delay_ms(corchea);
	frq(abc5);
	_delay_ms(blanca);
	frq(dbc6);
	_delay_ms(blanca);
	frq(fhc5);
	_delay_ms(corchea);
	frq(abc5);
	_delay_ms(corchea);
	frq(bbc5);
	_delay_ms(corchea);
	frq(abc5);
	_delay_ms(corchea);

	frq(silencio);
	_delay_ms(corchea);
	frq(bbc5);
	_delay_ms(corchea);
	frq(dbc6);
	_delay_ms(corchea);
	frq(bc5);
	_delay_ms(negra);
	frq(bbc5);
	_delay_ms(corchea);
	frq(abc5);
	_delay_ms(corchea);
	frq(bbc5);
	_delay_ms(corchea);
	frq(fhc5);
	_delay_ms(blanca);
	
	frq(bc4);
	_delay_ms(corchea);
	frq(dbc5);
	_delay_ms(corchea);
	frq(ebc5);
	_delay_ms(corchea);
	frq(dbc5);
	_delay_ms(negra);
	frq(ebc5);
	_delay_ms(corchea);
	frq(fc5);
	_delay_ms(corchea);
	frq(ebc5);
	_delay_ms(negra);
	frq(fc5);
	_delay_ms(corchea);
	frq(fhc5);
	_delay_ms(corchea);

	frq(abc5);
	_delay_ms(negra);
	frq(fhc5);
	_delay_ms(corchea);
	frq(fc5);
	_delay_ms(corchea);
	frq(dbc5);
	_delay_ms(corchea);
	frq(abc5);
	_delay_ms(negra);
	frq(silencio);
	_delay_ms(corchea);
	frq(abc5);
	_delay_ms(corchea);
	frq(abc5);
	_delay_ms(corchea);
	frq(bbc5);
	_delay_ms(corchea);
	frq(abc5);
	_delay_ms(corchea);
	frq(abc5);
	_delay_ms(corchea);
	
	frq(silencio);
	_delay_ms(corchea);
	frq(gc5);
	_delay_ms(corchea);
	frq(silencio);
	_delay_ms(corchea);
	frq(fc5);
	_delay_ms(corchea);
	frq(silencio);
	_delay_ms(corchea);
	frq(gc5);
	_delay_ms(negra);

	frq(silencio);
	_delay_ms(redonda);
	_delay_ms(redonda);
	_delay_ms(redonda);
	
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