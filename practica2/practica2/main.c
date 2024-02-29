/*
 * practica2.c
 *
 * Created: 26/01/2024 12:04:06 p. m.
 * Author : victor
 */ 
#define F_CPU 1000000L
#include <avr/io.h>
#include <util/delay.h>
void print(uint8_t var) {
	PORTC = ((var%10)<<4) + var/10;
}
int main(void)
{
	DDRA &= 0x00;
	PORTA |= 0xFF;
	DDRC |= 0xFF;
	PORTC &= 0x00;
    /* Replace with your application code */
	uint8_t a=0;
	print(a);
    while (1) 
    {
		if (!(PINA&(1))) {
			_delay_ms(50);
			if (a<19) a++;
			print(a);
			while (!(PINA&(1)));
			_delay_ms(50);
		} else if (!(PINA&(1<<7))) {
			_delay_ms(50);
			if (a>0) a--;
			print(a);
			while (!(PINA&(1<<7)));
			_delay_ms(50);
		}
    }
}

