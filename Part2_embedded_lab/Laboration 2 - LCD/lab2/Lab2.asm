/*
 * lab2.asm
 * Laboration 2 av 3
 * Denna programmkod anv�nds f�r att kontrollera tangentbordet och visa nedtryckt siffra p� lcd:n
 * Talet p� leddisplayen representerar talen 0-11
 * D�r 1=0 och sista knappen # �r talet 11
 * 
 * Author:	HADI DEKNACHE
 *
 * Date:	2015-11-11
 */ 
 
;==============================================================================
; Definitions of registers, etc. ("constants")
;==============================================================================
	.DEF TEMP		= R16		; definierar R16 till TEMP
	.DEF RVAL		= R24		; Definierar R24 till RVAL
	.DEF CHOICE		= R18		; Definierar R18 till CHOICE
	.EQU NO_KEY		= 0x0f		; Ger NO_KEY v�rdet 0x0f
	.EQU RESET		= 0x0000	; Reset ges v�rdet 0000
	.EQU PM_START	= 0x0056	; PM_START ges v�rdet 0056

;==============================================================================
; Start of program
;==============================================================================
	.CSEG 					; Start av kod
	.ORG RESET				; R�knare �terst�lls till 0 i Reset(B�rjar p� allra b�rjan av minnet
	 RJMP init				; hoppar till init subrutinen
	.ORG PM_START 			; R�knare f�r v�rdet fr�n PM_START
	.INCLUDE "delay.inc"	; inkluderar delay.inc f�r att kunna anv�ndas
	.INCLUDE "lcd.inc"		; inkluderar lcd.inc f�r att kunna anv�ndas
;==============================================================================
; Basic initializations of stack pointer, I/O pins, etc.
;==============================================================================
init:
	; Set stack pointer to point at the end of RAM.
	LDI TEMP, LOW(RAMEND)
	OUT SPL, TEMP
	LDI TEMP, HIGH(RAMEND)
	OUT SPH, TEMP
	
	; Initialize pins
	CALL init_pins
	; Jump to main part of program
	CALL lcd_init
	RJMP main

;==============================================================================
; Initialize I/O pins
;==============================================================================
init_pins:	
	LDI TEMP, 0x80	 		
	OUT DDRC, TEMP	 		
		
	LDI TEMP, 0xf0	 		; Laddar TEMP med 0xf0(11110000)
	OUT DDRF, TEMP	 		; skriver ut det p� DDRF v�rdet i Temp f�r dem ska f� signaler

	OUT PORTF, TEMP 		; Skriver ut till PORTF v�rdet Temp f�r att f� signaler(lcd display)

	OUT PORTB, TEMP	 		; Temp v�rdet skickas ut till portB(f�r att f� signaler fr�n 4051 o 4555)

	OUT DDRB, TEMP	 		; Skriver ut temp i DDRB(4051 o 4555 fr�n knapptryckningen)

	OUT DDRD, TEMP

	SBI PORTD, 6			; Utg�ngar f�r portd6 f�r att reglera RS signaler
	SBI PORTD, 7			; Utg�ngar f�r portd7 f�r att reglera E(enable) signaler
	
	RET		 				; �terv�nder till init subrutinen

;==============================================================================
; Main part of program
;==============================================================================
main:
	LCD_WRITE_CHAR 'K'		; Bokstav K skrivs ut genom macro funktionen LCD_WRITE_CHAR samma operation f�r 3 n�stkommande 
	LCD_WRITE_CHAR 'E'		
	LCD_WRITE_CHAR 'Y'		
	LCD_WRITE_CHAR ':'		
	LDI RVAL, 0xC0			; S�tter cursorn p� andra raden b�rjan
	RCALL lcd_write_instr	; Kalla p� lcd write instr f�r att utf�ra instruktion ovanf�r
	RJMP keyboard_main		; Hoppar till keyboard main f�r att b�rja avl�sningen av keyboard

keyboard_main:
	CALL scan_keyboard		; kallar p� scan keyboard f�r att avl�sa tryck
	RJMP keyboard_main		; B�rjar om hela processen igen...
	
scan_keyboard:
	LDI CHOICE, RESET		; nollst�ller R188 ingen knapp tryckt)

	
check_keyboard:
	OUT PORTB, CHOICE		; R18 skickas till PORTB f�r ta emot v�rde p� knapptryckninge
	RCALL delay_micros		; pausar n�gra micros
	SBIC PINE, 6			; Kollar ifall n�gon knapp �r nedtryckt...
	RJMP Write_key			; Is�fall hoppar vi till write key f�r att skriva den
	INC CHOICE				; om inte nedtryckt �kar vi R18
	CPI RVAL, 12			; j�mf�r ifall RVAL �r 12
	BRNE check_keyboard		; ifall RVAL �r 12 s� branchar vi annars s� g�r vi tillbaka 
	LDI CHOICE, RESET		; om int s� laddar vi R18 med 0 nollst�ller knapp (ingen knapp nedtryckt)
	RET

Write_key:
	LSR CHOICE				; skiftar det bin�ra talet 4x f�r att f� siffrorna annars konstiga bokst�ver/tecken
	LSR CHOICE
	LSR CHOICE
	LSR CHOICE
	
	CHECK CHOICE			; anv�nder macro CHOICE f�r att skriva ut siffran p� sk�rmen
	RCALL delay_ms			; Delay f�r att skriva ut l�ngsammare
	
	RET


