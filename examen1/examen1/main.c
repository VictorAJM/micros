#define F_CPU 8000000UL
#include <stdlib.h>
#include <avr/io.h>				//Librería general del Microcontrolador
#include <stdint.h>				//Para poder declarar varialbes especiales
#include <util/delay.h>			//Para poder hacer delays
#include "lcd.h"
#include <stdlib.h> // Necesario para la función rand()
#include <avr/interrupt.h>
volatile uint8_t listo = 1;
volatile uint8_t segundos_listo = 0,randSeed = 1,presionado = 1;
volatile int copyOfTime = 0,timeinms = 0;
volatile uint8_t esperandoPrimero = 0,killmepls=0;
void _main() {
	
	lcd_puts("Iniciar...");
	while (listo) {
		randSeed++;
		if (randSeed>50) randSeed = 1;
	}
	esperandoPrimero = 1;
	lcd_clrscr();
	lcd_gotoxy(0,1);
	lcd_puts("Listo?");
	for (int i=0;i<4*segundos_listo&&!killmepls;i++)  {
		for (int j=0;j<=25&&!killmepls;j++) _delay_ms(10);
	}
	if (killmepls) {
		lcd_clrscr();
		lcd_puts("Todavia no!!!");
		PORTD=0;
		for (int j=0;j<6;j++) {
		PORTD ^= 1;
		for (int i=0;i<4;i++) _delay_ms(250);
		}
		lcd_clrscr();
	} else {
	PORTD = 1;
		TCNT0= 0;
		TIMSK= 2;
		OCR0= 124;
		TCCR0= 0b00001011;
		esperandoPrimero = 0;
	timeinms = 0;
	presionado = 1;
	copyOfTime=0;
	lcd_clrscr();
	while (presionado);
	if (timeinms <= 4000) {
		
		lcd_gotoxy(6,1);
		lcd_puts("Tpo: ");
		lcd_gotoxy(11,1);
		copyOfTime = timeinms;
		lcd_putc(copyOfTime/1000 +'0');
		copyOfTime %= 1000;
		lcd_gotoxy(12,1);
		lcd_putc('.');
		lcd_gotoxy(13,1);
		lcd_putc(copyOfTime/100 +'0');
			copyOfTime %= 100;
		lcd_gotoxy(14,1);
		lcd_putc(copyOfTime/10 +'0');
		copyOfTime %= 10;
		lcd_gotoxy(15,1);
		lcd_putc(copyOfTime +'0');
	} else {
		lcd_gotoxy(3,1);
		lcd_puts("Excediste Tpo");
	}
	for (int i=0;i<8;i++) _delay_ms(250);
	PORTD = 0;
	
	lcd_clrscr();
	}
}
void _init() {
	listo=1;
	segundos_listo = 0;
	randSeed = 1;
	timeinms = 0;
	presionado = 1;
	copyOfTime=0;
	esperandoPrimero=0;
	killmepls=0;
}
int main(void)
{
    /* Replace with your application code */
	DDRD = 0x01;
	PORTD = 0x00;
	MCUCR = 2;
	GIFR = 0b11100000;
	GICR = 0b01000000;
	// cambiar estas cosas :P

	sei();
	lcd_init(LCD_DISP_ON);
    while (1) 
    {
		_init();
		_main();
    }
}

ISR(INT0_vect) {
	if (esperandoPrimero) {
		presionado = 0;
		killmepls = 1;
		
	} else {
	if (listo) {
		_delay_ms(50);
		listo = 0;
		srand(randSeed);
		segundos_listo = rand()%9 + 2;
		
		while (!(PIND&(1<<2)));
		_delay_ms(50);
	}  else if (presionado) {
		// aqui mostramos el tiempo que tardo
		presionado = 0;
			_delay_ms(50);
			while (!(PIND&(1<<2)));
			_delay_ms(50);
	}
	}
}
ISR(TIMER0_COMP_vect) {
	if (timeinms>=4000) presionado=0;
	timeinms++;
}