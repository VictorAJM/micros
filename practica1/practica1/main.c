/*
 * practica1.c
 *
 * Created: 24/01/2024 10:50:51 p. m.
 * Author : victor
 */ 

#include <avr/io.h>

const uint8_t numeros[11] = {
	0b00111111, // 0
	0b00000110, // 1
	0b01011011, // 2
	0b01001111, // 3
	0b01100110, // 4
	0b01101101, // 5
	0b01111101, // 6
	0b00000111, // 7
	0b01111111, // 8
	0b01101111, // 9
	0b00000000  // 10
};


int main(void) {
	DDRA &= 0;
	DDRC |= 0xFF;
	PORTA |= 0xFF;
	PORTC = 0x00;
	while (1) {
	
		uint8_t input = PINA;
		input >>= 4;
		input = input > 9 ? 10:input;
		PORTC = numeros[input];
	}

	return 0;
}