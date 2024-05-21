/*
 * Titulo: 3 decimas
 *
 * Created: 20/02/2024
 * Author : Erwin Alberto Lopez Hurtado
 */ 

#define  F_CPU 1000000UL
#include <avr/io.h>				//Librer?a general del Microcontrolador
#include <stdint.h>				//Para poder declarar varialbes especiales
#include <util/delay.h>			//Para poder hacer delays
#include "../../../../../../6to semestre/Micros 2/lcd library C/lcd.h"
#include "../../../../../../6to semestre/Micros 2/lcd library C/lcd.c"				//lcd
#include <avr/interrupt.h>	//	 //Para poder manejar interrupciones
#include <time.h>
#include <stdlib.h>
#define LCD_PORT PORTC
#define XTAL 1000000 

//PROTOTIPADO DE FUNCIONES PARA PODER UTILIZARLAS DESDE CUALQUIER 'LUGAR'
//*************************************************************************
uint8_t cero_en_bit(volatile uint8_t *LUGAR, uint8_t BIT);
uint8_t uno_en_bit(volatile uint8_t *LUGAR, uint8_t BIT);
uint8_t BCD(uint8_t in);
//*************************************************************************/

#define tec_ddr DDRA
#define tec_port PORTA
#define tec_pin PINA

void boton(volatile uint8_t *LUGAR, uint8_t BIT){
	_delay_ms(50);
	while(cero_en_bit(LUGAR,BIT)){}
	_delay_ms(50);	
}
int se=0;
char Teclado(){
	tec_ddr=0b00001111;
	char x='.';
	while(x=='.'){
		se++;
		tec_port= 0b11111110;
		if(cero_en_bit(&tec_pin,4))boton(&tec_pin,4),x='+';
		if(cero_en_bit(&tec_pin,5))boton(&tec_pin,5),x='-';
		if(cero_en_bit(&tec_pin,6))boton(&tec_pin,6),x='x';
		if(cero_en_bit(&tec_pin,7))boton(&tec_pin,7),x='/';
		if(x!='.')break;
		tec_port= 0b11111101;
		if(cero_en_bit(&tec_pin,4))boton(&tec_pin,4),x='+';
		if(cero_en_bit(&tec_pin,5))boton(&tec_pin,5),x='3';
		if(cero_en_bit(&tec_pin,6))boton(&tec_pin,6),x='6';
		if(cero_en_bit(&tec_pin,7))boton(&tec_pin,7),x='9';
		if(x!='.')break;
		tec_port= 0b11111011;
		if(cero_en_bit(&tec_pin,4))boton(&tec_pin,4),x='0';
		if(cero_en_bit(&tec_pin,5))boton(&tec_pin,5),x='2';
		if(cero_en_bit(&tec_pin,6))boton(&tec_pin,6),x='5';
		if(cero_en_bit(&tec_pin,7))boton(&tec_pin,7),x='8';
		if(x!='.')break;
		tec_port= 0b11110111;
		if(cero_en_bit(&tec_pin,4))boton(&tec_pin,4),x='o';
		if(cero_en_bit(&tec_pin,5))boton(&tec_pin,5),x='1';
		if(cero_en_bit(&tec_pin,6))boton(&tec_pin,6),x='4';
		if(cero_en_bit(&tec_pin,7))boton(&tec_pin,7),x='7';
		if(x!='.')break;	
	}
	return x;
}


int main(void)
{	
	//sei();
	//clc();
	lcd_init(LCD_DISP_ON);
	lcd_clrscr();
	DDRB=255;
	ini:;
	PORTB=0;
	lcd_clrscr();
	lcd_puts("Cuantos cuadros?");
	char x='0';
	while(x<'1' || x>'9')x=Teclado();
	srand(se);
	int t=x-'0';
	int cords[t][2];
	for(int i=0;i<t;i++){
		int y=rand()%2+1;
		int z=rand()%10;
		for(int j=0;j<t;j++){
			if(y==cords[j][0] && z==cords[j][1]){
				y=rand()%2+1;
				z=rand()%10;
				j=-1;
			}
		}
		cords[i][0]=y;
		cords[i][1]=z;
	}
	lcd_clrscr();
	lcd_puts("Escondere ");
	lcd_putc(x);
	lcd_gotoxy(0,1);
	lcd_puts("Cuadritos.");
	_delay_ms(3000);
	lcd_clrscr();
	lcd_puts("Tu debes buscar ");
	lcd_gotoxy(0,1);
	lcd_putc(x);
	lcd_puts(" Cuadritos.");
	_delay_ms(3000);
	lcd_clrscr();
	lcd_puts("2 filas (1,2) ");
	lcd_gotoxy(0,1);
	lcd_puts("10 cols (0-9)");
	_delay_ms(3000);
	lcd_clrscr();
	lcd_puts("Presiona +");
	lcd_gotoxy(0,1);
	lcd_puts("para continuar..");
	while(Teclado()!='+'){}
	lcd_clrscr();
	lcd_puts("Trata de");
	lcd_gotoxy(0,1);
	lcd_puts("memorizar...");
	_delay_ms(3000);
	for(int i=0;i<t;i++){
		lcd_clrscr();
		lcd_puts("Cuadrito ");
		lcd_putc(i+'1');
		lcd_gotoxy(0,1);
		lcd_putc(cords[i][0]+'0');
		lcd_putc(',');
		lcd_putc(cords[i][1]+'0');
		_delay_ms(1000);
	}
	lcd_clrscr();
	lcd_puts("Tienes ");
	lcd_putc((t*2)/10+'0');
	lcd_putc((t*2)%10+'0');
	lcd_gotoxy(0,1);
	lcd_puts("intentos");
	_delay_ms(3000);
	int a=0;
	int pas[t];
	for(int i=0;i<t;i++)pas[i]=0;
	for(int i=0;i<2*t;i++){
		lcd_clrscr();
		lcd_puts("Intento ");
		lcd_putc(i+'1');
		lcd_puts(" (");
		int x=Teclado()-'0';
		lcd_putc(x+'0');
		lcd_putc(',');
		int y=Teclado()-'0';
		lcd_putc(y+'0');
		lcd_putc(')');
		int pasa=0;
		int repe=0;
		for(int j=0;j<t;j++){
			if(x==cords[j][0] && y==cords[j][1] && !pas[j]){
				pasa=1;
				pas[j]=1;
			}
			else if(x==cords[j][0] && y==cords[j][1]){
				repe=1;
			}
		}
		if(repe){
			lcd_gotoxy(0,1);
			lcd_puts("Lugar repetido");
			_delay_ms(2000);
			i--;
			continue;
		}
			if(x>2 || x<1){
				lcd_gotoxy(0,1);
				lcd_puts("No existe lugar");
				_delay_ms(2000);
			}
			else if(pasa){
				a++;
				lcd_gotoxy(0,1);
				lcd_puts("Acierto");
				PORTB=a;
				_delay_ms(2000);
				if(a==t){
					lcd_clrscr();
					lcd_puts("Tienes excelente");
					lcd_gotoxy(0,1);
					lcd_puts("memoria !!!");
					_delay_ms(3000);
					lcd_clrscr();
					lcd_puts("Ganaste!!!");
					lcd_gotoxy(0,1);
					lcd_puts("Felicidades!");
					_delay_ms(3000);
					goto ini;
				}
			}
			else{
				lcd_gotoxy(0,1);
				lcd_puts("Error");
				_delay_ms(2000);
			}
	}
    lcd_clrscr();
    lcd_puts("Tu memoria no es");
    lcd_gotoxy(0,1);
    lcd_puts("tan buena =(");
    _delay_ms(3000);
	goto ini;
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