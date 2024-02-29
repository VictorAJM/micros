;******************************************************
; Practica 10 - Notas Musicales
;
; Fecha: 14/11/2022
; Autor: Ariel Montserrat de la Cruz Sandoval
;******************************************************

.include "m16adef.inc"     
   
;******************************************************
;Registros (aquí pueden definirse)
;.def temporal=r19

;Palabras claves (aquí pueden definirse)
;.equ LCD_DAT=DDRC
;******************************************************

.org 0x0000
;Comienza el vector de interrupciones.
jmp RESET ; Reset Handler
jmp EXT_INT0 ; IRQ0 Handler
jmp EXT_INT1 ; IRQ1 Handler
jmp TIM2_COMP ; Timer2 Compare Handler
jmp TIM2_OVF ; Timer2 Overflow Handler
jmp TIM1_CAPT ; Timer1 Capture Handler
jmp TIM1_COMPA ; Timer1 CompareA Handler
jmp TIM1_COMPB ; Timer1 CompareB Handler
jmp TIM1_OVF ; Timer1 Overflow Handler
jmp TIM0_OVF ; Timer0 Overflow Handler
jmp SPI_STC ; SPI Transfer Complete Handler
jmp USART_RXC ; USART RX Complete Handler
jmp USART_UDRE ; UDR Empty Handler
jmp USART_TXC ; USART TX Complete Handler
jmp ADC_COMP ; ADC Conversion Complete Handler
jmp EE_RDY ; EEPROM Ready Handler
jmp ANA_COMP ; Analog Comparator Handler
jmp TWSI ; Two-wire Serial Interface Handler
jmp EXT_INT2 ; IRQ2 Handler
jmp TIM0_COMP ; Timer0 Compare Handler
jmp SPM_RDY ; Store Program Memory Ready Handler
; Termina el vector de interrupciones.

;******************************************************
;Aquí comenzará el programa
;******************************************************
Reset:
;Primero inicializamos el stack pointer...
ldi r16, high(RAMEND)
out SPH, r16
ldi r16, low(RAMEND)
out SPL, r16 
//sei

;******************************************************
;No olvides configurar al inicio los puertos que utilizarás
;También debes configurar si habrá o no pull ups en las entradas
;Para las salidas deberás indicar cuál es la salida inicial
;Los registros que vayas a utilizar inicializalos si es necesario
;******************************************************

ldi R16, 0b0001_1010
out TCCR0, R16


//PUERTOS
ser R16
out ddrB, R16 ; salida C
ldi R16, 0
out portB, R16

Musica:
rcall do
rcall corchea
rcall mi
rcall corchea
rcall la
rcall corchea
rcall si
rcall corchea
rcall mi
rcall corchea
rcall do
rcall corchea
rcall si
rcall corchea

rcall silencio
rcall corchea
rcall corchea

rjmp musica

DO:
	ldi R16, 59
	out OCR0, R16
	ldi R16, 0b0001_1011
	out TCCR0, R16
ret

RE:
	ldi R16, 52
	out OCR0, R16
	ldi R16, 0b0001_1011
	out TCCR0, R16
ret

MI:
	ldi R16, 2
	out OCR0, R16
	ldi R16, 0b0001_1101
	out TCCR0, R16
ret

FA:
	ldi R16, 44
	out OCR0, R16
	ldi R16, 0b0001_1011
	out TCCR0, R16
ret

SOL:
	ldi R16, 39
	out OCR0, R16
	ldi R16, 0b0001_1011
	out TCCR0, R16
ret

LA:
	ldi R16, 34
	out OCR0, R16
	ldi R16, 0b0001_1011
	out TCCR0, R16
ret

SI:
	ldi R16, 252
	out OCR0, R16
	ldi R16, 0b0001_1010
	out TCCR0, R16
ret

redonda:
	rcall blanca
	rcall blanca
ret

blanca:
	rcall negra
	rcall negra
ret

negra:
	rcall corchea
	rcall corchea
ret

silencio:
	ldi R16, 0
	out TCCR0, R16
ret

corchea:
; ============================= 
;    delay loop generator 
;     250000 cycles:
; ----------------------------- 
; delaying 249999 cycles:
          ldi  R17, $A7
WGLOOP0:  ldi  R18, $02
WGLOOP1:  ldi  R19, $F8
WGLOOP2:  dec  R19
          brne WGLOOP2
          dec  R18
          brne WGLOOP1
          dec  R17
          brne WGLOOP0
; ----------------------------- 
; delaying 1 cycle:
          nop
; ============================= 
ret

;******************************************************
;Aquí están las rutinas para el manejo de las interrupciones concretas
;******************************************************
TIM0_COMP:
	in R16, SREG
	push R16
	//code
	pop R16
	out SREG, R16
reti
EXT_INT0:  
	in R16, SREG
	push R16
	//CODIGO
	pop R16
	out SREG, R16
reti
; IRQ0 Handler
EXT_INT1:  
	in R16, SREG
	push R16
	//CODIGO
	pop R16
	out SREG, R16
reti 
; IRQ1 Handler
TIM2_COMP:  
	in R16, SREG
	push R16
	//CODIGO
	pop R16
	out SREG, R16
reti 
; Timer2 Compare Handler
TIM2_OVF:  
	in R16, SREG
	push R16
	//CODIGO
	pop R16
	out SREG, R16
reti 
; Timer2 Overflow Handler
TIM1_CAPT:  
	in R16, SREG
	push R16
	//CODIGO
	pop R16
	out SREG, R16
reti 
; Timer1 Capture Handler
TIM1_COMPA:  
	in R16, SREG
	push R16
	//CODIGO
	pop R16
	out SREG, R16
reti 
; Timer1 CompareA Handler
TIM1_COMPB:  
	in R16, SREG
	push R16
	//CODIGO
	pop R16
	out SREG, R16
reti 
; Timer1 CompareB Handler
TIM1_OVF:  
	in R16, SREG
	push R16
	//CODIGO
	pop R16
	out SREG, R16
reti 
; Timer1 Overflow Handler
TIM0_OVF:  
	in R16, SREG
	push R16
	//CODIGO
	pop R16
	out SREG, R16
reti ; Timer0 Overflow Handler
SPI_STC:  
	in R16, SREG
	push R16
	//CODIGO
	pop R16
	out SREG, R16
reti 
; SPI Transfer Complete Handler
USART_RXC:  
	in R16, SREG
	push R16
	//CODIGO
	pop R16
	out SREG, R16
reti 
; USART RX Complete Handler
USART_UDRE:  
	in R16, SREG
	push R16
	//CODIGO
	pop R16
	out SREG, R16
reti 
; UDR Empty Handler
USART_TXC:  
	in R16, SREG
	push R16
	//CODIGO
	pop R16
	out SREG, R16
reti 
; USART TX Complete Handler
ADC_COMP:  
	in R16, SREG
	push R16
	//CODIGO
	pop R16
	out SREG, R16
reti 
; ADC Conversion Complete Handler
EE_RDY:  
	in R16, SREG
	push R16
	//CODIGO
	pop R16
	out SREG, R16
reti 
; EEPROM Ready Handler
ANA_COMP:  
	in R16, SREG
	push R16
	//CODIGO
	pop R16
	out SREG, R16
reti 
; Analog Comparator Handler
TWSI:  
	in R16, SREG
	push R16
	//CODIGO
	pop R16
	out SREG, R16
reti ; Two-wire Serial Interface Handler
EXT_INT2: 
	in R16, SREG
	push R16
	//CODIGO
	pop R16
	out SREG, R16
reti 
; IRQ2 Handler
SPM_RDY:  
	in R16, SREG
	push R16
	//CODIGO
	pop R16
	out SREG, R16
reti 
; Store Program Memory Ready Handler