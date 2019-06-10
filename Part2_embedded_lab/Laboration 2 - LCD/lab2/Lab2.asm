/*
 * lab2.asm
 * Laboration 2 av 3
 * Denna programmkod används för att kontrollera tangentbordet och visa nedtryckt siffra på lcd:n
 * Talet på leddisplayen representerar talen 0-11
 * Där 1=0 och sista knappen # är talet 11
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
	OUT DDRF, TEMP	 		; skriver ut det på DDRF värdet i Temp för dem ska få signaler

	OUT PORTF, TEMP 		; Skriver ut till PORTF värdet Temp för att få signaler(lcd display)

	OUT PORTB, TEMP	 		; Temp värdet skickas ut till portB(för att få signaler från 4051 o 4555)

	OUT DDRB, TEMP	 		; Skriver ut temp i DDRB(4051 o 4555 från knapptryckningen)

	OUT DDRD, TEMP

	SBI PORTD, 6			; Utgångar för portd6 för att reglera RS signaler
	SBI PORTD, 7			; Utgångar för portd7 för att reglera E(enable) signaler
	
	RET		 				; återvänder till init subrutinen

;==============================================================================
; Main part of program
;==============================================================================
main:
	LCD_WRITE_CHAR 'K'		; Bokstav K skrivs ut genom macro funktionen LCD_WRITE_CHAR samma operation för 3 nästkommande 
	LCD_WRITE_CHAR 'E'		
	LCD_WRITE_CHAR 'Y'		
	LCD_WRITE_CHAR ':'		
	LDI RVAL, 0xC0			; Sätter cursorn på andra raden början
	RCALL lcd_write_instr	; Kalla på lcd write instr för att utföra instruktion ovanför
	RJMP keyboard_main		; Hoppar till keyboard main för att börja avläsningen av keyboard

keyboard_main:
	CALL scan_keyboard		; kallar på scan keyboard för att avläsa tryck
	RJMP keyboard_main		; Börjar om hela processen igen...
	
scan_keyboard:
	LDI CHOICE, RESET		; nollställer R188 ingen knapp tryckt)

	
check_keyboard:
	OUT PORTB, CHOICE		; R18 skickas till PORTB för ta emot värde på knapptryckninge
	RCALL delay_micros		; pausar några micros
	SBIC PINE, 6			; Kollar ifall någon knapp är nedtryckt...
	RJMP Write_key			; Isåfall hoppar vi till write key för att skriva den
	INC CHOICE				; om inte nedtryckt ökar vi R18
	CPI RVAL, 12			; jämför ifall RVAL är 12
	BRNE check_keyboard		; ifall RVAL är 12 så branchar vi annars så går vi tillbaka 
	LDI CHOICE, RESET		; om int så laddar vi R18 med 0 nollställer knapp (ingen knapp nedtryckt)
	RET

Write_key:
	LSR CHOICE				; skiftar det binära talet 4x för att få siffrorna annars konstiga bokstäver/tecken
	LSR CHOICE
	LSR CHOICE
	LSR CHOICE
	
	CHECK CHOICE			; använder macro CHOICE för att skriva ut siffran på skärmen
	RCALL delay_ms			; Delay för att skriva ut långsammare
	
	RET


