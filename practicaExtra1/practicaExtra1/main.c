/*
 * practicaExtra1.c
 *
 * Created: 20/02/2024 03:03:14 p. m.
 * Author : victor
 */ 

#define  F_CPU 1000000UL
#include <stdlib.h>
#include <avr/io.h>				//Librería general del Microcontrolador
#include <stdint.h>				//Para poder declarar varialbes especiales
#include <util/delay.h>			//Para poder hacer delays
#include "lcd.h"
#include <stdlib.h> // Necesario para la función rand()
uint8_t p_pin;
char mat[4][4] = {
	{'7', '8', '9', 'A'},
	{'4', '5', '6', 'B'},
	{'1', '2', '3', 'C'},
	{'E', '0', 'F', '+'}
};
volatile uint8_t cuadritos = 0;
volatile uint8_t arrY[] = {0,1,2,3,4,5,6,7,8,9};
volatile uint8_t arrX[] = {0,1,0,1,0,1,0,1,0,1};
volatile uint8_t found[] = {0,0,0,0,0,0,0,0,0,0,0,0,0};
volatile uint8_t intentos=0;
volatile uint8_t aciertos=0;
volatile uint8_t randSeed = 1;
volatile uint8_t X;
volatile uint8_t Y;
volatile uint8_t win;
volatile uint8_t repetido=0;

char keyboard4(){
	while(1){
		randSeed++;
		if (randSeed>50) randSeed = 1;
		for(uint8_t i = 0; i<4; i++){
			PORTA = 0b11111111 ^ (1<<(7-i));
			if(~PINA&1 && '0'<=mat[i][3] && mat[i][3]<='9') {p_pin = 1;return mat[i][3];}
			if(~PINA&2 && '0'<=mat[i][2] && mat[i][2]<='9') {p_pin = 2;return mat[i][2];}
			if(~PINA&4 && '0'<=mat[i][1] && mat[i][1]<='9') {p_pin = 4;return mat[i][1];}
			if(~PINA&8 && '0'<=mat[i][0] && mat[i][0]<='9') {p_pin = 8;return mat[i][0];}
		}
	}
}
char keyboard(){
	while(1){
				
		for(uint8_t i = 0; i<4; i++){
			randSeed++;
			if (randSeed>50) randSeed = 1;
			PORTA = 0b11111111 ^ (1<<(7-i));
			if(~PINA&1 && '1'<=mat[i][3] && mat[i][3]<='9') {p_pin = 1;return mat[i][3];}
			if(~PINA&2 && '1'<=mat[i][2] && mat[i][2]<='9') {p_pin = 2;return mat[i][2];}
			if(~PINA&4 && '1'<=mat[i][1] && mat[i][1]<='9') {p_pin = 4;return mat[i][1];}
			if(~PINA&8 && '1'<=mat[i][0] && mat[i][0]<='9') {p_pin = 8;return mat[i][0];}
		}
	}
}
char keyboard2(){
	while(1){

		for(uint8_t i = 0; i<4; i++){
			PORTA = 0b11111111 ^ (1<<(7-i));
			if(~PINA&1 && mat[i][3]=='+') {p_pin = 1;return mat[i][3];}
			if(~PINA&2 && '+'==mat[i][2]) {p_pin = 2;return mat[i][2];}
			if(~PINA&4 && '+'==mat[i][1]) {p_pin = 4;return mat[i][1];}
			if(~PINA&8 && '+'==mat[i][0]) {p_pin = 8;return mat[i][0];}
		}
	}
}
void wait_btn(){
	_delay_ms(50);
	while(~PINA&p_pin);
	_delay_ms(50);
}
void preguntar() {
	lcd_puts("Cuantos Cuadros?");
	cuadritos = keyboard();	
	srand(randSeed);
	wait_btn();
}
void imprimir(uint8_t n) {
	lcd_clrscr();
	lcd_puts("Escondere ");
	lcd_gotoxy(10,0);
	lcd_putc(n);
	lcd_gotoxy(0,1);
	lcd_puts("cuadritos.");
}
void esperarMas() {
	lcd_clrscr();
	lcd_puts("Tu debes buscar");
	lcd_gotoxy(0,1);
	lcd_putc(cuadritos);
    lcd_gotoxy(3,1);
	lcd_puts("cuadritos.");
	for (int i=0;i<8;i++) _delay_ms(250);
	lcd_clrscr();
	lcd_puts("2 filas (1,2)");
	lcd_gotoxy(0,1);
	lcd_puts("10 cols (0-9)");
	for (int i=0;i<8;i++) _delay_ms(250);
	lcd_clrscr();
	lcd_puts("Presiona +");
	lcd_gotoxy(0,1);
	lcd_puts("para continuar");
	keyboard2();
	wait_btn();
}
void generar_cuadros(uint8_t n) {
	for (int i=0;i<n;i++) {
		uint8_t p = rand()%2+1;
		uint8_t q = rand()%10;
		uint8_t f = 0;
		while (!f) {
			f=1;
			p = rand()%2+1;
			q = rand()%10;
			for (int j=0;j<i;j++) if (arrX[j]==p && arrY[j]==q) f=0;
		}
		arrX[i]=p;
		arrY[i]=q;
		found[i]=0;
	}
} 
void imprimirSecret(uint8_t n) {
	lcd_clrscr();
	lcd_puts("Trata de");
	lcd_gotoxy(0,1);
	lcd_puts("memorizar...");
	for (int i=0;i<8;i++) _delay_ms(250);
	generar_cuadros(n);
	for (int i=1;i<=n;i++) {
		lcd_clrscr();
		lcd_puts("Cuadrito ");
		lcd_gotoxy(9,0);
		lcd_putc(i+'0');
		lcd_gotoxy(0,1);
		lcd_putc(arrX[i-1]+'0');
		lcd_gotoxy(1,1);
		lcd_putc(',');
		lcd_gotoxy(2,1);
		lcd_putc(arrY[i-1]+'0');
		for (int j=0;j<8;j++) _delay_ms(250);
	}
	lcd_clrscr();
	lcd_puts("tienes ");
	lcd_gotoxy(7,0);
	uint8_t m=n+n;
	lcd_putc(m/10+'0');
	lcd_gotoxy(8,0);
	lcd_putc(m%10+'0');
	lcd_gotoxy(0,1);
	lcd_puts("intentos.");
	for (int j=0;j<8;j++) _delay_ms(250);
}
void check() {
	uint8_t f = cuadritos-'0'+1;
	uint8_t g=0;
	for (int i=0;i<cuadritos-'0';i++) {
		if (!found[i] && arrX[i]==X-'0' && arrY[i]==Y-'0') f=i;
		if (arrX[i]==X-'0' && arrY[i]==Y-'0') g=1;
	}
	if (f<cuadritos-'0'+1) {
		found[f]=1;
		aciertos++;
		lcd_gotoxy(0,1);
		lcd_puts("Acierto");
	} else {
		if (g) {

			lcd_gotoxy(0,1);
			lcd_puts("Repetido");
			repetido=1;
		} else {
			if (X>'2') {
				lcd_gotoxy(0,1);
				lcd_puts("Fuera de rango");
			} else {
				lcd_gotoxy(0,1);
				lcd_puts("Error");
			}
		}
	}
				PORTB = aciertos;
	for (int i=0;i<8;i++) _delay_ms(250);
}
int main(void)
{
    /* Replace with your application code */
	DDRB = 0xFF;
	PORTB = aciertos;
	DDRA = 0b11110000;
	
	/* initialize display, cursor off */
	lcd_init(LCD_DISP_ON);
    while (1) 
    {
		PORTB = aciertos;
		preguntar();
		imprimir(cuadritos);
		for (int i=0;i<8;i++) _delay_ms(250);
		esperarMas();
		imprimirSecret(cuadritos-'0');
		intentos = 1;
		aciertos = 0;
		win=0;
		uint8_t n = cuadritos-'0';
		for (int i=1;i<=n*2;i++) {
			// hacer cosas
			lcd_clrscr();
			lcd_puts("Intento ");
			lcd_gotoxy(8,0);
			lcd_putc(i/10+'0');
			lcd_gotoxy(9,0);
			lcd_putc(i%10+'0');
			// yes, it's hardcoded
			X = keyboard4();
			wait_btn();
			lcd_gotoxy(11,0);
			lcd_putc('(');
			lcd_gotoxy(12,0);
			lcd_putc(X);
			lcd_gotoxy(13,0);
			lcd_putc(',');
			lcd_gotoxy(14,0);
			Y = keyboard4();
			wait_btn();
			lcd_putc(Y);
			lcd_gotoxy(15,0);
			lcd_putc(')');
			repetido = 0;
			check();
			if (repetido) i--;
			if (aciertos == n) {
				lcd_clrscr();
				lcd_puts("GANASTE!");
				for (int j=0;j<8;j++) _delay_ms(250);
				cuadritos = 0;
				win = 1;
				lcd_clrscr();
				n=0;
				aciertos = 0;
			}
		}
		if (!win) {
			lcd_clrscr();
			lcd_puts("PERDISTE :(");
			for (int j=0;j<8;j++) _delay_ms(250);
				cuadritos = 0;
				win = 0;
				lcd_clrscr();
				n=0;
				aciertos = 0;
		}
		
    }
}

