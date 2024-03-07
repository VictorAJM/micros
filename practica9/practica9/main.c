/*
 * practica9.c
 *
 * Created: 28/02/2024 09:15:04 a. m.
 * Author : victor
 */ 
#define F_CPU 8000000UL
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h" // Debes tener una librería para controlar el LCD
int ADC_Read(char channel)
{


    
    // se inicia la conversión.
    ADCSRA |= (1 << ADSC);
    
    // espera a que termina la conversión.
    while(ADCSRA & (1 << ADSC));
    
    return ADC;
}
int main(void)
{
	char String[5];
		DDRA=0x0;			/* Make ADC port as input */
		ADCSRA = (1 << ADEN) | (1 << ADPS1) | (1 << ADPS2);
		ADMUX = 0x47;			/* Vref: Avcc, ADC channel: 0 */

	// Inicialización del LCD
	lcd_init(LCD_DISP_ON);
	int value;
	while (1)
	{
		

		// Convertir a voltaje (0.0 a 5.0 V)
		//value = ADC_Read(0);

		// Mostrar en el LCD
		lcd_clrscr();
		
		lcd_puts("Voltaje");
		value=ADC_Read(0);	/* Read ADC channel 0 */
		float xd = (float)value * 5.0 /1023.0;
		itoa(value,String,10);	
		lcd_gotoxy(0,1);
		lcd_putc((int)xd +'0');
		xd *=10;
		lcd_gotoxy(1,1);
		lcd_putc(',');
		lcd_gotoxy(2,1);
		lcd_putc((int)xd %10 +'0');
		xd *=10;
		lcd_gotoxy(3,1);
		lcd_putc((int)xd %10 +'0');
		xd *=10;
		_delay_ms(500);
	}

	return 0;
}
