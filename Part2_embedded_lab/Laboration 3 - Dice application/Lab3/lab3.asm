/*
 * lab3.asm
 * Laboration 3 av 3
 * Denna programmkod anv�nds f�r att kontrollera tangentbordet n�r 1 trycks ner
 * lcddisplayen representerar talen 0-6
 * N�r knappen sl�pps visas ett random v�rde p� sk�rmen bredvid value
 * 
 * Author:	HADI DEKNACHE
 *
 * Date:	2015-11-24
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
	.INCLUDE "Keyboard.inc"
	.INCLUDE "Tarning.inc"
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
	RJMP START

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

	LDI R16, 0X0f			; Laddar 00001111 p� portb f�r att f� 1 knappen att fungera
	OUT PORTB, R16			; Aktiverar knappen genom portb
	
	RET		 				; �terv�nder till init subrutinen

;==============================================================================
; Main part of program
;==============================================================================
START:
	RCALL Clear				;T�mmer sk�rmen vid start
	RCALL Delay_s
	RCALL Write_welcome		;Skriver ut texten vid start
	RCALL Delay_s
	
	LDI RVAL, 0xC0			; S�tter cursorn p� andra raden b�rjan
	RCALL lcd_write_instr	; Kalla p� lcd write instr f�r att utf�ra instruktion ovanf�r

	RCALL Play_game			; Skriver ut texten vid start
	RCALL Delay_s			; S�tter en lagom l�ng delay f�r texten	

	
main: 
	RCALL Clear				; T�mmer sk�rmen f�r att visa upp n�sta text

	RCALL Delay_s			; S�tter en lagom l�ng delay f�r texten

	RCALL Press_txt			; Skriver ut texten f�r att anv�ndaren ska trycka p� knapp 1
	RCALL delay_micros		; Skapar en delay f�r att texten ska synas		

	RCALL read_keyboard		; B�rjar spelet genom att hoppa in i load

	RCALL pressed

	RCALL load

	RCALL Give_number

	RJMP main