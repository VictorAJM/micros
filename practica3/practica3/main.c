/*
 * practica3.c
 *
 * Created: 05/02/2024 08:41:20 p. m.
 * Author : victor
 */ 


#define  F_CPU 1000000UL
#include <stdlib.h>
#include <avr/io.h>				//Librería general del Microcontrolador
#include <stdint.h>				//Para poder declarar varialbes especiales
#include <util/delay.h>			//Para poder hacer delays
#include "lcd.h"
//#include <avr/interrupt.h>	 //Para poder manejar interrupciones

char mat[4][4] = {
	{'1', '2', '3', 'A'},
	{'4', '5', '6', 'B'},
	{'7', '8', '9', 'C'},
	{'E', '0', 'F', 'D'}
};
uint8_t p_pin;
uint8_t x_cur = 0;
uint8_t last = 0;

char keyboard(){
	while(1){
		for(uint8_t i = 0; i<4; i++){
			PORTA = 0b11111111 ^ (1<<(7-i));
			if(~PINA&1) {p_pin = 1;return mat[i][3];}
			if(~PINA&2) {p_pin = 2;return mat[i][2];}
			if(~PINA&4) {p_pin = 4;return mat[i][1];}
			if(~PINA&8) {p_pin = 8;return mat[i][0];}
		}
	}
}

void wait_btn(){
	_delay_ms(50);
	while(~PINA&p_pin);
	_delay_ms(50);
}

void display(uint8_t val){
	if(val == 'E'){
		if(x_cur != 0){
			if (last==x_cur) last--;
			x_cur--;
			lcd_gotoxy(x_cur, 0);
			lcd_putc(' ');
			lcd_gotoxy(x_cur, 0);
		}
		return;
		}else if(val == 'F'){
		last=0;
		lcd_clrscr();
		x_cur = 0;
		return;
	}else if(x_cur == 10) return;
	lcd_putc(val);
	x_cur++;
	if (x_cur==1 && val=='1' && last==0) {
		last++;
	}
	if (x_cur==2 && val=='1' && last==1) {
		last++;
	}
	if (x_cur==3 && val=='2' && last==2) {
		last++;
	}
	if (x_cur==4 && val=='3' && last==3) {
		last++;
	}
	if (x_cur==5 && val=='5' && last==4) {
		last++;
	}
	if (x_cur==6 && val=='8' && last==5) {
		last++;
	}
	if (x_cur==7 && val=='1' && last==6) {
		last++;
	}
	if (x_cur==8 && val=='3' && last==7) {
		last++;
	}
	if (x_cur==9 && val=='2' && last==8) {
		last++;
	}
	if (x_cur==10 && val=='1' && last==9) {
		last++;
	}
	if (last==10) {
		lcd_clrscr();
		last=0;
		lcd_puts("Fibonacci");
		return;
		x_cur=0;
	}
}

int main(void){
	DDRA = 0b11110000;
	
	DDRC &=~ (1 << 2);        /* Pin PD2 input              */
	PORTC |= (1 << 2);        /* Pin PD2 pull-up enabled    */


	/* initialize display, cursor off */
	lcd_init(LCD_DISP_ON);
	
	while (1){
		display(keyboard());
		wait_btn();
	}
}

