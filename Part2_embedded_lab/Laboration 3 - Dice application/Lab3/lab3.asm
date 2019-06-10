/*
 * lab3.asm
 * Laboration 3 av 3
 * Denna programmkod används för att kontrollera tangentbordet när 1 trycks ner
 * lcddisplayen representerar talen 0-6
 * När knappen släpps visas ett random värde på skärmen bredvid value
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
	.EQU NO_KEY		= 0x0f		; Ger NO_KEY vÄrdet 0x0f
	.EQU RESET		= 0x0000	; Reset ges värdet 0000
	.EQU PM_START	= 0x0056	; PM_START ges värdet 0056


;==============================================================================
; Start of program
;==============================================================================
	.CSEG 					; Start av kod
	.ORG RESET				; Räknare återställs till 0 i Reset(Börjar på allra början av minnet
	 RJMP init				; hoppar till init subrutinen
	.ORG PM_START 			; Räknare för värdet från PM_START
	.INCLUDE "delay.inc"	; inkluderar delay.inc för att kunna användas
	.INCLUDE "lcd.inc"		; inkluderar lcd.inc för att kunna användas
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
	OUT DDRF, TEMP	 		; skriver ut det på DDRF värdet i Temp för dem ska få signaler

	OUT PORTF, TEMP 		; Skriver ut till PORTF värdet Temp för att få signaler(lcd display)

	OUT PORTB, TEMP	 		; Temp värdet skickas ut till portB(för att få signaler från 4051 o 4555)

	OUT DDRB, TEMP	 		; Skriver ut temp i DDRB(4051 o 4555 från knapptryckningen)

	OUT DDRD, TEMP

	SBI PORTD, 6			; Utgångar för portd6 för att reglera RS signaler
	SBI PORTD, 7			; Utgångar för portd7 för att reglera E(enable) signaler

	LDI R16, 0X0f			; Laddar 00001111 på portb för att få 1 knappen att fungera
	OUT PORTB, R16			; Aktiverar knappen genom portb
	
	RET		 				; återvänder till init subrutinen

;==============================================================================
; Main part of program
;==============================================================================
START:
	RCALL Clear				;Tömmer skärmen vid start
	RCALL Delay_s
	RCALL Write_welcome		;Skriver ut texten vid start
	RCALL Delay_s
	
	LDI RVAL, 0xC0			; Sätter cursorn på andra raden början
	RCALL lcd_write_instr	; Kalla på lcd write instr för att utföra instruktion ovanför

	RCALL Play_game			; Skriver ut texten vid start
	RCALL Delay_s			; Sätter en lagom lång delay för texten	

	
main: 
	RCALL Clear				; Tömmer skärmen för att visa upp nästa text

	RCALL Delay_s			; Sätter en lagom lång delay för texten

	RCALL Press_txt			; Skriver ut texten för att användaren ska trycka på knapp 1
	RCALL delay_micros		; Skapar en delay för att texten ska synas		

	RCALL read_keyboard		; Börjar spelet genom att hoppa in i load

	RCALL pressed

	RCALL load

	RCALL Give_number

	RJMP main