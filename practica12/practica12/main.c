/*
 * practica12.c
 *
 * Created: 09/03/2024 06:59:35 p. m.
 * Author : victor
 */ 
#define F_CPU 1000000UL
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <string.h>	
#include "lcd.h"
char mat[4][4] = {
	{'1', '2', '3', 'A'},
	{'4', '5', '6', 'B'},
	{'7', '8', '9', 'C'},
	{'E', '0', 'F', 'D'}
};
uint8_t p_pin;
char keyboard(){
	while(1){
		for(uint8_t i = 0; i<4; i++){
			PORTD = 0b11111111 ^ (1<<(7-i));
			if(~PIND&1 && '0' <= mat[i][3] && mat[i][3]<='9') {p_pin = 1;return mat[i][3];}
			if(~PIND&2 && '0' <= mat[i][2] && mat[i][2]<='9') {p_pin = 2;return mat[i][2];}
			if(~PIND&4 && '0' <= mat[i][1] && mat[i][1]<='9') {p_pin = 4;return mat[i][1];}
			if(~PIND&8 && '0' <= mat[i][0] && mat[i][0]<='9') {p_pin = 8;return mat[i][0];}
		}
	}
}

void wait_btn(){
	_delay_ms(50);
	while(~PIND&p_pin);
	_delay_ms(50);
}
int main(void)
{
	lcd_init(LCD_DISP_ON);
	DDRD = 0xF0;
	
    /* Replace with your application code */
	char R[4];
		lcd_clrscr();
		lcd_puts("0000");
	do {
		R[0] = eeprom_read_byte(0);
		R[1] = eeprom_read_byte(1);
		R[2] = eeprom_read_byte(2);
		R[3] = eeprom_read_byte(3);

		lcd_clrscr();
		lcd_putc(R[0]); lcd_putc(R[1]); lcd_putc(R[2]); lcd_putc(R[3]);
		uint8_t num = keyboard();
		wait_btn();
		R[3] = R[2];
		R[2] = R[1];
		R[1] = R[0];
		R[0] = num;
		eeprom_write_byte(0,R[0]);
		eeprom_write_byte(1,R[1]);
		eeprom_write_byte(2,R[2]);
		eeprom_write_byte(3,R[3]);
	}while (1);

}

