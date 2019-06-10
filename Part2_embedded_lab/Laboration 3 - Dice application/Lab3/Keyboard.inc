/*
 * Keyboard.inc
 *
 *	Detta programm kollar efter knapptrykning på telefontangentbor
 *	Ifall tryckt så omvandlas det till det talet genom convert och visas på skärm	
 *
 *  Created: 2015-11-24 13:51:44
 *   Author: Hadi Deknache
 */ 
 
;==============================================================================
; Definitions of registers, etc. ("constants")
;==============================================================================
map_table: 
	.DB "147*2580369#"			; knapparna representerar telefontangentbordet

;==============================================================================
; Kyeboard main
;==============================================================================
 keyboard:
	CALL scan_keyboard		; kallar på scan keyboard för att avläsa tryck
	CALL read_keyboard
	RJMP keyboard			; Börjar om hela processen igen...


 ;----------------------------------------------------------------------------
 ; Scan_keybaord
 ; Parameter IN :	CHOICE: R18 är valet som lagrats
 ;					RESET : NOLLSTÄLLS					
 ;----------------------------------------------------------------------------
scan_keyboard:
	LDI CHOICE, RESET		; nollställer R18 ingen knapp tryckt)
	RET



 ;----------------------------------------------------------------------------
 ; read keyboard
 ; Parameter IN :	R19 räknare på tärningen
 ;	
 ;					
 ;	Begränsningar: Om talet är under 0 och över 6				
 ;----------------------------------------------------------------------------	


read_keyboard:
	RCALL delay_1_micros	; skapar en delay för att få alla funktioner att funger
	SBIC PINE, 6			; känner av ifall knapp 1 trycks
	RET						; Knapp nedtryckt, så hoppar vi in i pressed och väntar tills knapp släpps
	RJMP read_keyboard		; börjar om att kontrollera ifall knapp är tryckt


load:	
	LDI R19, 6				; laddat talet 6 för att räkna ner och vissa talet på skärmen
Down_pressed:
	RCALL delay_micros			
	SBIS PINE, 6			; Kollar om kanppen fortfarande är nedtryckt 
	RET						; Ifall den är så går vi till give number och skriver ut den 
	DEC R19					; minskar R19 är talet som ska visas på skärm efteråt
	BREQ load				; kollar ifall load blir dess angivna värde
	RJMP Down_pressed

 ;----------------------------------------------------------------------------
 ; Write_key
 ; Parameter IN :	R19 räknare på tärningen
 ;	
 ;					
 ;----------------------------------------------------------------------------	

Write_key:
	CHECK R19				; använder macro CHOICE för att skriva ut siffran på skärmen
	RCALL Delay_s			; Delay för att skriva ut långsammare
	RET

/*Convert:
	LDI ZH, high(map_table<<1)	; Laddar zh med höga delen i maptable 
	LDI ZL, low(map_table<<1)	; laddar zl med låga delen i maptable för 
	ADD ZL, R21					;Lägger till r21 med ZL för att få det tänkta tecknet
	LDI R21, 0x00				; nollställer r21 för att användas i nästa steg
	ADC ZH, R21					; lägger till carry med r21 i zh
	LPM R24, Z					; lägger där z pekar i r24 vilket represetera talet
	RET
	*/

	
	

