/*
 * Tarning.inc
 *
 *  Created: 2015-11-25 10:06:45
 *   Author: Hadi  Deknache
 */ 

 ;------------------------------------------------------
 ;Definitions
 ;------------------------------------------------------

 Str_1:	
	.DB		"Welcome!", 0,0			;Lagrar welcome i programminnet f�r att anv�ndas och skriva ut

Rolling:
	.DB		"Rolling...",0,0			;Lagrar rolling i programminnet f�r att anv�ndas och skriva ut

Press_key:
	.DB		"Press 1 to roll",0	;Lagrar press 1 to roll i programminnet f�r att anv�ndas och skriva ut

Play:
	.DB		"Wanna Play?",0			;Lagrar wanna play i programminnet f�r att anv�ndas och skriva ut

Value:
	.DB		"Value:",0,0				;Lagrar value i programminnet f�r att anv�ndas och skriva ut



Pressed:
	RCALL Clear
	RCALL Rolling_txt			; Texten skrivs ut p� sk�rm
	RCALL delay_1_micros
	RET								; hoppar in i down_pressed rutinen f�r att v�nta tills anv�ndaren sl�pper kanppen
		

Give_number:
	
	RCALL Clear					; T�mmer sk�rmen
	RCALL Value_txt				; Skriver ut texten value p� lcdn
	RCALL delay_1_micros		; skapar delay f�r att visa talet
	RCALL Write_key				; Skriver ut talet bredvid value				
	RET

Clear:	
	LDI RVAL, 0x01			; Skapar en rutin f�r att t�mma sk�rmen
	RCALL lcd_write_instr	; Instruktionen g�rs
	RCALL delay_ms
	RET


Write_welcome:				; Anv�nds f�r att skriva ut text p� sk�rm
	LDI ZH, high(Str_1<<1)	; laddar z h�g med l�ga bitarna samt skiftar �t v�nster 
	LDI ZL, low(Str_1<<1)	; laddar z l�g med l�ga bitarna samt skiftar �t v�nster
	CLR R16					; t�mmer r16 f�r att lagra tecken till text
	RJMP Nxt1				; hoppar in i nxt1 f�r att skriva ut texten p� sk�rmen

Play_game:
	LDI ZH, high(play<<1)	; laddar z h�g med l�ga bitarna samt skiftar �t v�nster 
	LDI ZL, low(play<<1)	; laddar z l�g med l�ga bitarna samt skiftar �t v�nster
	CLR R16					; t�mmer r16 f�r att lagra tecken till text
	RJMP Nxt1				; hoppar in i nxt1 f�r att skriva ut texten p� sk�rmen

Rolling_txt:
	LDI ZH, high(Rolling<<1)	; laddar z h�g med l�ga bitarna samt skiftar �t v�nster 
	LDI ZL, low(Rolling<<1)		; laddar z l�g med l�ga bitarna samt skiftar �t v�nster
	CLR R16						; t�mmer r16 f�r att lagra tecken till text
	RJMP Nxt1					; hoppar in i nxt1 f�r att skriva ut texten p� sk�rmen

Press_txt:
	LDI ZH, high(Press_key<<1)	; laddar z h�g med l�ga bitarna samt skiftar �t v�nster
	LDI ZL, low(Press_key<<1)	; laddar z l�g med l�ga bitarna samt skiftar �t v�nster
	CLR R16						; t�mmer r16 f�r att lagra tecken till text
	RJMP Nxt1					; hoppar in i nxt1 f�r att skriva ut texten p� sk�rmen

Value_txt:
	LDI ZH, high(Value<<1)		; laddar z h�g med l�ga bitarna samt skiftar �t v�nster
	LDI ZL, low(Value<<1)		; laddar z l�g med l�ga bitarna samt skiftar �t v�nster
	CLR R16						; t�mmer r16 f�r att lagra tecken till text
	RJMP Nxt1					; hoppar in i nxt1 f�r att skriva ut texten p� sk�rmen


Nxt1: 
	LPM R24, Z+					; anv�nder programminnet och lagrar d�r z pekar i r24
	CPI R24, 0					; kollar ifall vi hamnat p� noll s� slutar vi skriva ut tecken
	BREQ END					; ifall vi �r f�rdiga avslutas hela processen
	RCALL lcd_write_chr			; skriver ut teckenet
	RJMP Nxt1					; b�rjar om och kollar n�sta tecken i registret
	
END:
	RET