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
	.DB		"Welcome!", 0,0			;Lagrar welcome i programminnet för att användas och skriva ut

Rolling:
	.DB		"Rolling...",0,0			;Lagrar rolling i programminnet för att användas och skriva ut

Press_key:
	.DB		"Press 1 to roll",0	;Lagrar press 1 to roll i programminnet för att användas och skriva ut

Play:
	.DB		"Wanna Play?",0			;Lagrar wanna play i programminnet för att användas och skriva ut

Value:
	.DB		"Value:",0,0				;Lagrar value i programminnet för att användas och skriva ut



Pressed:
	RCALL Clear
	RCALL Rolling_txt			; Texten skrivs ut på skärm
	RCALL delay_1_micros
	RET								; hoppar in i down_pressed rutinen för att vänta tills användaren släpper kanppen
		

Give_number:
	
	RCALL Clear					; Tömmer skärmen
	RCALL Value_txt				; Skriver ut texten value på lcdn
	RCALL delay_1_micros		; skapar delay för att visa talet
	RCALL Write_key				; Skriver ut talet bredvid value				
	RET

Clear:	
	LDI RVAL, 0x01			; Skapar en rutin för att tömma skärmen
	RCALL lcd_write_instr	; Instruktionen görs
	RCALL delay_ms
	RET


Write_welcome:				; Används för att skriva ut text på skärm
	LDI ZH, high(Str_1<<1)	; laddar z hög med låga bitarna samt skiftar åt vänster 
	LDI ZL, low(Str_1<<1)	; laddar z låg med låga bitarna samt skiftar åt vänster
	CLR R16					; tömmer r16 för att lagra tecken till text
	RJMP Nxt1				; hoppar in i nxt1 för att skriva ut texten på skärmen

Play_game:
	LDI ZH, high(play<<1)	; laddar z hög med låga bitarna samt skiftar åt vänster 
	LDI ZL, low(play<<1)	; laddar z låg med låga bitarna samt skiftar åt vänster
	CLR R16					; tömmer r16 för att lagra tecken till text
	RJMP Nxt1				; hoppar in i nxt1 för att skriva ut texten på skärmen

Rolling_txt:
	LDI ZH, high(Rolling<<1)	; laddar z hög med låga bitarna samt skiftar åt vänster 
	LDI ZL, low(Rolling<<1)		; laddar z låg med låga bitarna samt skiftar åt vänster
	CLR R16						; tömmer r16 för att lagra tecken till text
	RJMP Nxt1					; hoppar in i nxt1 för att skriva ut texten på skärmen

Press_txt:
	LDI ZH, high(Press_key<<1)	; laddar z hög med låga bitarna samt skiftar åt vänster
	LDI ZL, low(Press_key<<1)	; laddar z låg med låga bitarna samt skiftar åt vänster
	CLR R16						; tömmer r16 för att lagra tecken till text
	RJMP Nxt1					; hoppar in i nxt1 för att skriva ut texten på skärmen

Value_txt:
	LDI ZH, high(Value<<1)		; laddar z hög med låga bitarna samt skiftar åt vänster
	LDI ZL, low(Value<<1)		; laddar z låg med låga bitarna samt skiftar åt vänster
	CLR R16						; tömmer r16 för att lagra tecken till text
	RJMP Nxt1					; hoppar in i nxt1 för att skriva ut texten på skärmen


Nxt1: 
	LPM R24, Z+					; använder programminnet och lagrar där z pekar i r24
	CPI R24, 0					; kollar ifall vi hamnat på noll så slutar vi skriva ut tecken
	BREQ END					; ifall vi är färdiga avslutas hela processen
	RCALL lcd_write_chr			; skriver ut teckenet
	RJMP Nxt1					; börjar om och kollar nästa tecken i registret
	
END:
	RET